// -*- c++ -*-
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

#include "common.h"
#include "status.h"
#include "memory.h"


#ifndef _MIPS_MMAN_H
#define _MIPS_MMAN_H

MIPS_OPEN_NS

GEN_OPEN_NS(heap)
    
    
    // the public interface:
    status_t alloc_mem (size_t size, addr_t * o_addr);

status_t init ();






CLOSE_NS			// heap
CLOSE_NS			// mips


#endif /* _MIPS_MMAN_H */
