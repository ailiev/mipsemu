#include <libelf.h>

#include <gelf.h>


#include <stdio.h>

/*
  returns the *internal* offset of __start. (that's what
  the symbol table contains in any case)
  The absolute address is different, offset by the .vma field of the .text
  section (where __start resides)
  returns -1 on error
*/
long get_start_addr (Elf * elf)
{
    const char STARTSYM[] = "__start";

    Elf_Scn
	*temp_scn = NULL;
    
    Elf32_Shdr * shdr;

    size_t shstrndx;		/* not too sure what this means */

    if (elf_getshstrndx(elf, &shstrndx) == 0) {
	fprintf (stderr, "getshstrndx() failed: %s\n",
		 elf_errmsg(-1));
	goto error_egress;
    }

    /* iterate over the headers. */
    while ( (temp_scn = elf_nextscn(elf, temp_scn)) != NULL) {

	shdr = elf_getshdr (temp_scn);

	if (shdr == NULL) {
	    fprintf (stderr, "elf_getshdr() failed: %s\n",
		     elf_errmsg(-1));
	    goto error_egress;
	}

	if ( (name = elf_strptr(elf, shstrndx, shdr.sh_name) ) == NULL) {
	    fprintf (stderr, "elf_strptr() failed: %s\n",
		     elf_errmsg(-1));
	    goto error_egress;
	}

	if (strncmp (STARTSYM, name, sizeof(STARTSYM)) != 0) {
	    /* wrong name */
	    continue;
	}

	/* We got it! */
	
	
    }

 error_egress:
    
}
