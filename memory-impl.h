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

#include "status.h"

#include <faerieplay/common/utils-types.h>

#include <string>

#ifndef _MEMORY_IMPL_H
#define _MEMORY_IMPL_H


MIPS_OPEN_NS

typedef unsigned phys_addr_t;



struct mem_impl_t
{
    void * priv_impl;

    size_t size;
};

// this is required to disable C++ name mangling, as we need the simple names to
// load via dlsym(), in memory.cc

extern "C" {
    
/// Begin the initialization of the physical memory.
status_t mem_impl_init (mem_impl_t * mem,
			size_t size);

/// Called when the initialization (eg. loading of text and static data) is
/// done.
status_t mem_impl_init_complete (mem_impl_t * mem);

/// Read some bytes from the memory.
status_t mem_impl_read (mem_impl_t * mem,
			phys_addr_t addr,
			byte * o_buf, size_t len);

/// Write bytes to the memory.
status_t mem_impl_write (mem_impl_t * mem,
			 phys_addr_t addr,
			 const byte * buf, size_t len);

/// Dump the memory contents to the given file.
void mem_impl_dump (const mem_impl_t * mem,
		    const std::string& filename);

}

CLOSE_NS


#endif // _MEMORY_IMPL_H
