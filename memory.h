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

#include "memory-impl.h"
#include "status.h"
#include "common.h"

#include <faerieplay/common/utils-types.h>

#include <stdint.h>
#include <stddef.h>

#include <string>


#ifndef _MEMORY_H
#define _MEMORY_H


MIPS_OPEN_NS


typedef uint32_t addr_t;

typedef uint32_t word_t;
typedef uint16_t hw_t;		// half-word
typedef uint64_t dword_t;	// double word


// the total dynamic memory, ie. heap + stack, in bytes
const size_t DEFAULT_DYN_MEM_SIZE = 128 * (1<<10);
// current graph V=7 D=5: needs 13K
//		V=15, D=5: need 12648
//		V=31, D=5, need 12648
//		V=63, D=5, need 16760
//		V=127, D=10, 34K



struct mem_t {

//    static const addr_t TEXT_START = 0x00400000;
    // getting eg. 0x4000b0 in practice
    static const addr_t DATA_START = 0x10000000;
    // topmost valid stack byte-address
    static const addr_t STACK_TOP  = 0x7FFFFFFF;

    // this bit is not set in text section, and is set in the data section
    // (unconditionally, unless text is bigger than about 264M, in which case
    // data section needs to be moved from its traditional start location)
    static const byte DATA_DETECT_BIT = 28;

    // this bit is not set in the data section (unless heap goes above
    // 0x3FFFFFFF), and is set in the stack (unless stack goes below
    // 0x3FFFFFFF). This leaves 1G for stack and about 800M for data (static +
    // heap). should be enough!
    static const byte STACK_DETECT_BIT = 30;

    // not set for all valid addresses, set for kernel addresses
    static const byte KERNEL_DETECT_BIT = 31;


    addr_t text_start;
    
    mem_impl_t impl;
    
    size_t size;

    size_t textsize;
    size_t static_data_size;
};


/// Initialize the memory represented by o_mem.
/// Use the memory implementation indicated by mem_impl_file.
status_t mem_init (const char* mem_impl_file,
		   mem_t * o_mem,
		   size_t size,
		   addr_t textstart,
		   size_t textsize,
		   size_t static_data_size);

status_t mem_write (mem_t * mem,
		    addr_t vaddr, word_t val);

status_t mem_write_bytes (mem_t * mem,
			  addr_t dest_vaddr,
			  const byte * buf, size_t len);

/// Called when the initialization (eg. loading of text and static data) is done
status_t mem_init_complete (mem_t * mem);

status_t mem_read_bytes (mem_t * mem,
			 addr_t vaddr,
			 byte * o_buf, size_t len);

status_t mem_read (mem_t * mem,
		   addr_t vaddr,
		   word_t * o_val);


status_t virt2phys_addr (const mem_t * mem,
			 addr_t full_addr,
			 addr_t * o_addr);

void mem_dump (const mem_t * mem,
	       const std::string& filename);



/// where is the start of the heap? (virtual address)
inline addr_t mem_heap_start(const mem_t * mem)
{
    return mem_t::DATA_START + mem->static_data_size;
}



extern mem_t g_mainmem;

CLOSE_NS

#endif // _MEMORY_H
