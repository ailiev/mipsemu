/*
 * Simple emulator for a MIPS machine, with a pluggable emulated RAM. Can run
 * executables compiled with gcc against dietlibc and using a few syscalls.
 *
 * Copyright (C) 2003-2007, Alexander Iliev <sasho@cs.dartmouth.edu> and
 * Sean W. Smith <sws@cs.dartmouth.edu>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 * 
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <bfd.h>


// Acknowledgement:
// BFD example code from Phrack Volume 0xA Issue 56, article 0x09,
// "BACKDOORING BINARY OBJECTS" by klog <klog@promisc.org>

const char* BFD_TARGET = "elf32-little";

static void print_bfd_targets ();



bfd * open_bfd (const char* execfile)
{
    bfd *ibfd = NULL;

//    print_bfd_targets();

    ibfd = bfd_openr (execfile, BFD_TARGET);
    if (ibfd == NULL)
    {
	char buf[1024];
	snprintf (buf, sizeof(buf),
		  "Error opening executable %s", execfile);
	// in case snprintf did not do this.
	buf[sizeof(buf)-1] = '\0';
	bfd_perror (buf);
	goto error_egress;
    }

    // make sure it's an object (or executable) file
    if (! bfd_check_format (ibfd, bfd_object))
    {
	bfd_perror ("binary file not an executable");
	goto error_egress;
    }

    goto egress;
    
 error_egress:
    if (ibfd != NULL) bfd_close (ibfd);
    return NULL;

 egress:

    return ibfd;
}


// returns the *internal* offset of __start. (that's what
// the symbol table contains in any case)
// The absolute address is different, offset by the .vma field of the .text
// section (where __start resides)
// returns -1 on error
long get_start_addr (bfd * ibfd)
{
    const char* STARTSYM = "__start";
    long retval = -1;
    
    long symtab_space, num_symbols;
    asymbol **symbol_table = NULL;

    long i;
    
    symtab_space = bfd_get_symtab_upper_bound (ibfd);
    if (symtab_space <= 0) goto error_egress;
    
    symbol_table = (asymbol **) malloc (symtab_space);
    if (symbol_table == NULL) goto error_egress;

    num_symbols = bfd_canonicalize_symtab (ibfd, symbol_table);
    if (num_symbols < 0) goto error_egress;
    
    for (i = 0; i < num_symbols; i++)
    {
	if (strcmp (symbol_table[i]->name, STARTSYM) == 0)
	{
	    retval = symbol_table[i]->value;
	}
    }
    
    if (retval == -1)
    {
	fprintf (stderr,
		 "get_start_addr() failed to find __start "
		 "in the symbol table, with %ld symbols\n",
		 num_symbols);
	goto error_egress;
    }
    
    goto egress;
    
 error_egress:
    retval = -1;

 egress:
    free (symbol_table);	/* no problem with NULL symbol_table */

    return retval;
}



void print_section (bfd * ibfd, const char* name)
{
    asection * sect = NULL;    
    unsigned long * sectcont = NULL;
    int rc;
    
    printf ("Printing section %s\n", name);

    sect = bfd_get_section_by_name (ibfd, name);

    if (sect == NULL) goto error_egress;

    printf ("vma = 0x%x\n"
	    "lma = 0x%x\n",
	    sect->vma, sect->lma);

    printf ("size = %d\n",
	    bfd_section_size (ibfd,sect));
    
    sectcont = malloc (bfd_section_size (ibfd,sect));
    if (sectcont == NULL) goto error_egress;
    
    rc = bfd_get_section_contents (ibfd, sect,
				   sectcont,
				   0, bfd_section_size (ibfd,sect));
    if (!rc) goto error_egress;

    {
	unsigned long addr;
	for (addr = 0;
	     addr < bfd_section_size (ibfd,sect) / sizeof(sectcont[0]);
	     addr++)
	{
	    printf ("%.4lx: %.8lx\n", addr, sectcont[addr]);
	}
    }

    goto egress;
    
 error_egress:
    bfd_perror ("print_section");

 egress:
    fflush (stdin);
    free (sectcont);

}


void print_bfd_targets ()
{
    const char ** targets = bfd_target_list ();
    const char ** t = targets;
    
    printf ("%s\n", "Printing all BFD known targets");
    
    
    for ( ; *t != NULL; t++)
    {
	printf ("%s\n", *t);
    }

    free (targets);
}
