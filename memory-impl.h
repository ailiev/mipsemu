// -*- c++ -*-

#include "status.h"

#include <pir/common/utils-types.h>

#include <string>

#ifndef _MEMORY_IMPL_H
#define _MEMORY_IMPL_H


MIPS_OPEN_NS

typedef unsigned phys_addr_t;



struct mem_impl_t {
    void * priv_impl;

    size_t size;
};


status_t mem_impl_init (mem_impl_t * mem,
			size_t size);

/// Called when the initialization (eg. loading of text and static data) is done
status_t mem_impl_init_complete (mem_impl_t * mem);


status_t mem_impl_read (mem_impl_t * mem,
			phys_addr_t addr,
			byte * o_buf, size_t len);

status_t mem_impl_write (mem_impl_t * mem,
			 phys_addr_t addr,
			 const byte * buf, size_t len);


void mem_impl_dump (const mem_impl_t * mem,
		    const std::string& filename);


CLOSE_NS


#endif // _MEMORY_IMPL_H
