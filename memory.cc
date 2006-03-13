#include "memory.h"

#include "status.h"
#include "common.h"

#include <pir/common/utils-macros.h>

#include <string.h>



MIPS_OPEN_NS


mem_t g_mainmem;		// declared extern in memory.h

status_t mem_init (mem_t * mem,
		   size_t size,
		   size_t textstart,
		   size_t textsize)
{
    status_t rc = STATUS_OK;
    
    memset (mem, 0, sizeof(*mem));
    
    mem->size = size;
    
    mem->mem = new byte[size];
    if (mem->mem == NULL) ERREXIT (NOMEM);

    mem->text_start = textstart;
    mem->textsize = textsize;
    
 error_egress:

    return rc;
}

status_t mem_get_special_locations (mem_t * mem,
				    byte ** o_text_addr,
				    byte ** o_data_addr)
{
    *o_text_addr = mem->mem;
    *o_data_addr = mem->mem + mem->textsize;

    return STATUS_OK;
}


status_t mem_write (mem_t * mem,
		    addr_t vaddr, word_t val)
{
    const size_t read_size = sizeof(word_t);

    status_t rc = STATUS_OK;
    
    addr_t addr;
    CHECKCALL ( virt2phys_addr (mem, vaddr, &addr) );

    if (addr + read_size > mem->size) ERREXIT(ILLADDR);

    memcpy (mem->mem + addr, &val, read_size);

 error_egress:

    return rc;
}

status_t mem_read (mem_t * mem,
		   addr_t vaddr,
		   word_t * o_val)
{
    const size_t read_size = sizeof(word_t);

    status_t rc = STATUS_OK;
    
    addr_t addr;
    CHECKCALL ( virt2phys_addr (mem, vaddr, &addr) );

    if (addr + read_size > mem->size) ERREXIT(ILLADDR);

    memcpy (o_val, mem->mem + addr, read_size);

 error_egress:

    return rc;
}


   
/// convert a full 32-bit address, in MIPS conventions, to an address into one
/// of our compact memory arrays.
status_t virt2phys_addr (const mem_t * mem,
			 addr_t full_addr,
			 addr_t * o_addr)
{
    status_t rc = STATUS_OK;

    if (full_addr < mem->text_start ||
	GETBIT(full_addr, mem_t::KERNEL_DETECT_BIT) == 1)
    {
	// too high or too low!
	ERREXIT (ILLADDR);
    }

    
    if (GETBIT(full_addr, mem_t::STACK_DETECT_BIT) == 0)
    {
	if (GETBIT(full_addr, mem_t::DATA_DETECT_BIT) == 0)
	{
	    // text section
	    *o_addr = full_addr - mem->text_start;
	}
	else
	{
	    // data section
	    *o_addr = mem->textsize +
		(full_addr - mem_t::DATA_START); // offset into the data section
	}
    }
    else
    {
	// stack bit is 1
	*o_addr = (mem->size - 1) -
	    (mem_t::STACK_TOP - full_addr); // the offset from top of stack
    }

 error_egress:

    return rc;
}


CLOSE_NS
