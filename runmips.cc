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

#include "cpu.h"
#include "memory.h"

#include "status.h"
#include "mman.h"

#include <faerieplay/common/logging.h>
#include <faerieplay/common/utils.h>

#include <bfd.h>


using std::cerr;
using std::endl;

#define BFD_FATAL(msg) { bfd_perror(msg); goto error_egress; }

namespace
{
    Log::logger_t s_logger = Log::makeLogger ("mips.runmips");

    void usage (char * argv[])
    {
	cerr << "Usage: " << argv[0]
	     << " [-m <mem impl shared object>] [-h] <mips exe> [MIPS program args ...]"
	     << endl
	     << "\tUse -- to ensure that the rest of the options" << endl
	     << "\tgo to the MIPS program." << endl;
    }
	
}


int main (int argc, char * argv[])
{
    mips::status_t rc = mips::STATUS_OK;

    int main_rc = EXIT_SUCCESS;

    
    const char * mem_impl = NULL;

    int opt;
//    opterr = 0;			// no messages from getopt() please
    while ((opt = getopt(argc, argv, "+m:h")) != -1) {
	switch (opt) {

	case 'm':
	    // only pick up the first -m option!
	    if (mem_impl == NULL) mem_impl = optarg;
	    break;

	case 'h':
	    usage(argv);
	    exit (EXIT_SUCCESS);
	    break;
	    
	default:
// 	    LOG (Log::WARN, s_logger,
// 		 "configs: unknown opt=" << char(optopt)
// 		 << ", optarg=" << (optarg ? optarg : "null"));
	    // probably a mips program option.
	    break;
	}
    }
    
    if (optind >= argc) {
	// no program specified.
	usage(argv);
	exit(0);
    }

    const char * execfile = argv[optind];

    
    mips::addr_t start_addr = 0;

    bfd *ibfd = NULL;

    byte * buf = NULL;

    size_t data_size, rodata_size;

    size_t memsize;
    
    asection
	*text = NULL,
	*rodata = NULL,
	*data = NULL,
	*bss = NULL;
    


    bfd_init();

    mips::init_instr_info();
    
    
    //
    // open the bfd
    //
    ibfd = open_bfd (execfile);
    if (ibfd == NULL) goto error_egress;

//     print_section (ibfd, ".text");
//     printf ("\n\n");
//     print_section (ibfd, ".data");
//     printf ("\n\n");
//     print_section (ibfd, ".bss");
//     printf ("\n\n");
//     print_section (ibfd, ".rodata");
    
    

#define get_section(name)					\
    name = bfd_get_section_by_name (ibfd, "." #name);		\
    if (name == NULL) BFD_FATAL ("Getting ." #name " section");

    // it seems that these three sections are always present, even if zero-sized
    // (mostly the data section can be zero size, if there are no globals)
    get_section (text);
//    get_section (data);
    get_section (bss);

#undef get_section

    LOG (Log::INFO, s_logger,
	 "Text section size = " << bfd_section_size (ibfd, text) << " bytes");

    // .data section may not be present
    data = bfd_get_section_by_name (ibfd, ".data");
    if (data != NULL) {
	data_size = bfd_section_size (ibfd, data);
    }
    else {
	data_size = 0;
    }

    // .rodata section may not be present
    rodata = bfd_get_section_by_name (ibfd, ".rodata");
    if (rodata != NULL) {
	rodata_size = bfd_section_size (ibfd, rodata);
    }
    else {
	rodata_size = 0;
    }
    
//     if (rodata == NULL) {
// 	CHECK_ALLOC ( rodata, malloc (sizeof(*rodata)) );
// 	memset (rodata, 0, sizeof(*rodata));
//     }

    // initialize memory with elf section sizes, and dynamic memory size
    {
	memsize =
	    bfd_section_size (ibfd,text)
	    + rodata_size
	    + data_size
	    + bfd_section_size (ibfd,bss)
	    + mips::DEFAULT_DYN_MEM_SIZE;

	LOG (Log::DEBUG, s_logger,
	     "RAM actually needed (bytes) = " << memsize);
	
	LOG (Log::INFO, s_logger,
	     "RAM to be allocated (bytes) = " << memsize);
    }
    
    mips::mem_init (
	mem_impl,
	&mips::g_mainmem,
	memsize,
	text->vma,
	bfd_section_size (ibfd,text) + rodata_size, // text size (incl. rodata)
	data_size + bfd_section_size (ibfd,bss)	// static data size
	);
    
    // copy text and data sections into new memory
    {
	int rc;			// NOTE: shadows the outer rc
	const size_t BUFSIZE = 64 * (1<<10);

	assert (bfd_section_size (ibfd,text)  <= BUFSIZE 	&&
		rodata_size <= BUFSIZE 	&&
		data_size  <= BUFSIZE);
	
	CHECK_ALLOC ( buf, (byte*) malloc (BUFSIZE) );


	// text section
	
	rc = bfd_get_section_contents (ibfd,
				       text,
				       buf,
				       0, bfd_section_size (ibfd,text));
	if (!rc) BFD_FATAL ("Reading in text section");

	CHECKCALL ( mips::mem_write_bytes (&mips::g_mainmem,
				     text->vma,
				     buf, bfd_section_size (ibfd,text)) );
				     

	// rodata section if present
	
	if (rodata != NULL)
	{
	    rc = bfd_get_section_contents (ibfd,
					   rodata,
					   buf,
					   0, bfd_section_size (ibfd,rodata));
	    if (!rc) BFD_FATAL ("Reading in rodata section");

	    // FIXME: is rodata->vma == text->vma + text->size ??
	    // (ie. rodata vaddr is straight after text)
	    CHECKCALL ( mips::mem_write_bytes (&mips::g_mainmem,
					 rodata->vma,
					 buf, bfd_section_size (ibfd,rodata)) );
	    
	}

	// data section if present
	if (data != NULL) {
            rc = bfd_get_section_contents (ibfd,
                                           data,
                                           buf,
                                           0, bfd_section_size (ibfd,data));
            if (!rc) BFD_FATAL ("Reading in data section");

            CHECKCALL ( mips::mem_write_bytes (&mips::g_mainmem,
                                               data->vma,
                                               buf, bfd_section_size (ibfd,data)) );
        }

    }

    // prepare the heap
    CHECKCALL ( mips::heap::init () );

    CHECKCALL ( mips::mem_init_complete (&mips::g_mainmem) );
    
    // get the start address
    {
	long start_offset = get_start_addr (ibfd);
	if (start_offset < 0)
	{
	    ERREXIT (FORMAT);
	}
	start_addr = text->vma + start_offset;
    }

    // start the process
    // first get our own options out of the way, leaving the MIPS exe name, and
    // its options in argv.
    
    // NOTE: optind should now be the index of the last argument (MIPS exe file)
    // which this program uses. The rest are args for the target program.
    for (int i=optind; i < argc; i++) {
	argv[i-(optind)] = argv[i];
    }
    argc -= (optind);

    LOG (Log::INFO, s_logger,
	 "argv going to target program: " << print_seq(argv, argv+argc));
    
    CHECKCALL ( mips::prepare_cpu (&mips::g_mainmem,
				   argc, argv) );

    LOG (Log::INFO, s_logger,
	 "CPU ready, argv and argc on stack, starting main function");

    CHECKCALL ( mips::run_process (&mips::g_mainmem, start_addr) );

    goto egress;
    
    // TODO: not bothering to clean up the asection's since this code runs only
    // once

 error_egress:
    cerr << "Error exit, with mips status " << mips::status_name(rc) << endl;
    main_rc = EXIT_FAILURE;

 egress:

    if (buf != NULL)
    {
	free (buf);
    }
    
    return main_rc;
    
}
