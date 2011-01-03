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
