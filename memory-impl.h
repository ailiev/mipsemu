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

#include "status.h"

#include <pir/common/utils-types.h>

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
