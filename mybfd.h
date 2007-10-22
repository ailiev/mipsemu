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

#include <bfd.h>

#ifndef _MYBFD_H
#define _MYBFD_H

#ifdef __cplusplus
extern "C" {
#endif

    bfd * open_bfd (const char* filename);

    long get_start_addr (bfd * ibfd);

    void print_section (bfd * ibfd, const char* sectname);
    
    
#ifdef __cplusplus
}
#endif


#endif /* _MYBFD_H */
