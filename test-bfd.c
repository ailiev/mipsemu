/*
 * Simple emulator for a MIPS machine, with a pluggable emulated RAM. Can run
 * executables compiled with gcc against dietlibc and using a few syscalls.
 *
 * Copyright (C) 2003-2007, Alexander Iliev <sasho@cs.dartmouth.edu> and
 * Sean W. Smith <sws@cs.dartmouth.edu>
 *
 * All rights reserved.
 *
 * This code is released under a BSD license.
 * Please see LICENSE.txt for the full license and disclaimers.
 *
*/


#include "mybfd.h"

#include <stdlib.h>
#include <stdio.h>

#include <string.h>

// Acknowledgement:
// BFD example code from Phrack Volume 0xA Issue 56, article 0x09,
// "BACKDOORING BINARY OBJECTS" by klog <klog@promisc.org>



int main (int argc, char *argv[])
{
    // load the code of an executable into a newly allocated word array and
    // return the start address (within that array)

    long start_addr;
    int rc = EXIT_SUCCESS;

    bfd *ibfd = NULL;

    if (argc < 2 || strcmp(argv[1], "-h") == 0) {
	printf ("Usage: %s <ELF dietlibc-linked executable>\n", argv[0]);
	exit (EXIT_SUCCESS);
    }
    
    bfd_init();
    
//    print_bfd_targets();

    ibfd = open_bfd (argv[1]);
    if (ibfd == NULL)
    {
	bfd_perror ("open_bfd");
	goto error_egress;
    }

    start_addr = get_start_addr (ibfd);
    if (start_addr < 0) goto error_egress;
    printf ("Start address is 0x%lx\n", start_addr);

    print_section (ibfd, ".text");
    printf ("\n\n");
    print_section (ibfd, ".data");
    printf ("\n\n");
    print_section (ibfd, ".bss");
    
    goto egress;
    
 error_egress:
    rc = EXIT_FAILURE;

 egress:

    if (ibfd != NULL) bfd_close (ibfd);
    
    return rc;

}

