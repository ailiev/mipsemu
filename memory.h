// -*- c++ -*-
/*
Copyright (C) 2003-2007, Alexander Iliev <sasho@cs.dartmouth.edu>

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.
* Neither the name of the author nor the names of its contributors may
  be used to endorse or promote products derived from this software without
  specific prior written permission.

This product includes cryptographic software written by Eric Young
(eay@cryptsoft.com)

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "memory-impl.h"
#include "status.h"
#include "common.h"

#include <pir/common/utils-types.h>

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
const size_t DEFAULT_DYN_MEM_SIZE = 17 * (1<<10);
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
