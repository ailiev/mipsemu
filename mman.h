// -*- c++ -*-

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
