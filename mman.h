// -*- c++ -*-
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
