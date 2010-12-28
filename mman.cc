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


#include "mman.h"
#include "common.h"
#include "memory.h"

#include <faerieplay/common/utils-macros.h>

#include <string.h>


MIPS_OPEN_NS

GEN_OPEN_NS(heap)
    
OPEN_ANON_NS


enum heap_allocstatus_t
{
    ALLOC_FREE = 0xDE,
    ALLOC_USED = 0xAB
};

enum heap_markerkind_t
{
    MARKER_BEGIN = 0xDE,
    MARKER_END = 0xAB
};

    
// flags for heap regions
enum heap_flags_t {
    // the final (highest) region on the heap - it won't have an end marker.
    LAST_REG = (1<<0)
};



struct heap_tag_t
{
    heap_markerkind_t	kind	: 8;
    heap_allocstatus_t	alloc	: 8;
    heap_flags_t	flags	: 8;
    byte		fill	: 8;
} __attribute__((__packed__));


    
// the structure marking allocated memory regions.
// may use more fields, eg. protection bits etc.
struct reg_begin_marker_t
{
    // a combination of a heap_markerkind_t in byte 0, a heap_allocstatus_t in
    // byte 1
    heap_tag_t tag;
    uint32_t size;
};

// this structure just serves to point to the corresponding
// heap_mem_begin_marker_t at the start of the region, so it should not have any
// more fields.
struct reg_end_marker_t
{
    heap_tag_t tag;
    uint32_t size;
};


/// put in markers for a free region as specified.
/// @param start_addr where the begin marker should go.
/// @param orig the original free mamory marker
/// @param new_alloc the newly allocated region marker, at the beginning of
/// #orig.
status_t mark_free_region (mem_t * mem,
			   addr_t start_addr,
			   const reg_begin_marker_t * orig,
			   const reg_begin_marker_t * new_alloc);



const size_t REG_MARKER_OVERHEAD =
sizeof(reg_begin_marker_t) +
sizeof(reg_end_marker_t);


/// get the offset to the next region, from the beginning of the region reg
/// (including the two markers, that's the whole point here).
inline size_t next_reg_offset (const reg_begin_marker_t& reg)
{
    return reg.size + REG_MARKER_OVERHEAD;
}



CLOSE_NS			// anon





status_t init ()
{
    status_t rc = STATUS_OK;
    
    //
    // need to place the first region marker
    //
    
    reg_begin_marker_t marker;
    marker.tag.kind  = MARKER_BEGIN;
    marker.tag.alloc = ALLOC_FREE;
    marker.tag.flags = LAST_REG;
    
    // the size is set to be all the dynamic memory, though the stack also takes
    // up space
    marker.size = g_mainmem.size - g_mainmem.textsize - g_mainmem.static_data_size;

    CHECKCALL ( mem_write_bytes (&g_mainmem,
				 mem_heap_start (&g_mainmem),
				 reinterpret_cast<byte*>(&marker), sizeof(marker)) );

 error_egress:
    return rc;
}

    
status_t alloc_mem (size_t size, addr_t * o_addr)
{
    status_t rc = STATUS_OK;

    bool done = false;
    
    // get the first marker, and follow the links until we find a free one large
    // enough.
    reg_begin_marker_t reg_marker;

    addr_t reg_addr = mem_heap_start(&g_mainmem);

    do {
	CHECKCALL ( mem_read_bytes (&g_mainmem,
				    reg_addr,
				    reinterpret_cast<byte*> (&reg_marker),
				    sizeof(reg_marker)) );

	if (reg_marker.tag.alloc == ALLOC_FREE &&
	    reg_marker.size >= size + REG_MARKER_OVERHEAD)
	{
	    // this is it!
	    //
	    // re-write the begin marker, generate a new end marker,
	    // generate a new free region after the one we're allocating,

	    reg_begin_marker_t new_begin;
	    reg_end_marker_t   new_end;

	    addr_t mem_start = reg_addr + sizeof(new_begin);
	    // one past the end of the allocated memory, write the end marker in
	    // there
	    addr_t mem_end = mem_start + size;
	    
	    memset (&new_begin, 0, sizeof(new_begin));
	    memset (&new_end, 0, sizeof(new_end));
	    
	    new_begin.tag.kind	    = MARKER_BEGIN;
	    new_begin.tag.alloc	    = ALLOC_USED;
	    new_begin.size = size;

	    new_end.tag.kind  = MARKER_END;
	    new_end.tag.alloc = ALLOC_USED;
	    new_end.size     = size;

	    CHECKCALL ( mem_write_bytes (&g_mainmem,
					 reg_addr,
					 reinterpret_cast<byte*>(&new_begin),
					 sizeof(new_begin)) );
	    CHECKCALL ( mem_write_bytes (&g_mainmem,
					 mem_end,
					 reinterpret_cast<byte*>(&new_end),
					 sizeof(new_end)) );

	    if (reg_marker.size > size + REG_MARKER_OVERHEAD)
	    {
		// need to create a new free region after this allocated one
		
		CHECKCALL ( mark_free_region (
				&g_mainmem,
				reg_addr,
				&reg_marker, &new_begin) );
	    }
	    
	    done = true;
	    *o_addr = mem_start;
	}
	else
	{
	    // not free, or not big enough, go to next
	    reg_addr += next_reg_offset (reg_marker);
	}

    } while (!done);

    
 error_egress:
    return rc;
}



OPEN_ANON_NS

status_t mark_free_region (mem_t * mem,
			   addr_t start_addr,
			   const reg_begin_marker_t * orig,
			   const reg_begin_marker_t * new_alloc)
{
    status_t rc = STATUS_OK;
    
    reg_begin_marker_t begin_marker = *orig;

    // this takes into account that the orig->size did not include the orig
    // markers.
    begin_marker.size = orig->size - (new_alloc->size + REG_MARKER_OVERHEAD);

    CHECKCALL ( mem_write_bytes (mem,
				 start_addr + next_reg_offset(*new_alloc),
				 reinterpret_cast<byte*>(&begin_marker),
				 sizeof(begin_marker)) );

    // and now perhaps an end marker, but only if orig was not the last region
    // in the heap.
    if (! (orig->tag.flags & LAST_REG))
    {
	reg_end_marker_t end_marker;
	BZERO (end_marker);

	end_marker.tag.kind = MARKER_END;
	end_marker.tag.alloc = ALLOC_FREE;
	end_marker.size = begin_marker.size;
	
	CHECKCALL ( mem_write_bytes (mem,
				     start_addr +
				     next_reg_offset(*orig) + begin_marker.size,
				     reinterpret_cast<byte*>(&end_marker),
				     sizeof(end_marker)) );
    }

 error_egress:
    return rc;
}

	
CLOSE_NS			// anon



CLOSE_NS			// heap

CLOSE_NS			// mips
