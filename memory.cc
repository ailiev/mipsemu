#include "memory.h"

#include "memory-impl.h"

#include "status.h"
#include "common.h"

#include <pir/common/utils-macros.h>
#include <pir/common/utils.h>	// writefile()

#include <string.h>



MIPS_OPEN_NS


mem_t g_mainmem;		// declared extern in memory.h


namespace {
    Log::logger_t s_logger = Log::makeLogger ("mips-mem",
					      boost::none, boost::none);
}



status_t mem_init (mem_t * mem,
		   size_t size,
		   size_t textstart,
		   size_t textsize,
		   size_t static_data_size)
{
    status_t rc = STATUS_OK;
    
    memset (mem, 0, sizeof(*mem));
    
    mem->size = size;
    
    CHECKCALL ( mem_impl_init (&mem->impl, size) );

    mem->text_start = textstart;
    mem->textsize = textsize;
    mem->static_data_size = static_data_size;
    
 error_egress:

    return rc;
}

/// Called when the initialization (eg. loading of text and static data) is done
status_t mem_init_complete (mem_t * mem)
{
    // just pass it on
    return mem_impl_init_complete (&mem->impl);
}


status_t mem_write (mem_t * mem,
		    addr_t vaddr, word_t val)
{
    const size_t read_size = sizeof(word_t);

    status_t rc = STATUS_OK;
    
    addr_t addr;

    // make sure it's word-aligned
    if (vaddr & 0x3 != 0)
    {
	ERREXIT (ALIGN);
    }
    
    CHECKCALL ( virt2phys_addr (mem, vaddr, &addr) );
    LOG (Log::DEBUG, s_logger,
	 "mem_write phys addr 0x" << std::hex << addr
	 << " len = " << std::dec << read_size);

    if (addr + read_size > mem->size) ERREXIT(ILLADDR);

    CHECKCALL ( mem_impl_write (&mem->impl, addr, reinterpret_cast<byte*>(&val), read_size) );

 error_egress:

    return rc;
}

status_t mem_write_bytes (mem_t * mem,
			  addr_t vaddr,
			  const byte * buf, size_t len)
{
    status_t rc = STATUS_OK;
    
    phys_addr_t addr;
    CHECKCALL ( virt2phys_addr (mem, vaddr, &addr) );
    LOG (Log::DEBUG, s_logger,
	 "mem_write_bytes phys addr 0x" << std::hex << addr
	 << " len = " << std::dec << len);

    if (addr + len > mem->size) ERREXIT(ILLADDR);
    
    CHECKCALL ( mem_impl_write (&mem->impl, addr, buf, len) );

 error_egress:
    return rc;
}

status_t mem_read_bytes (mem_t * mem,
			 addr_t vaddr,
			 byte * o_buf, size_t len)
{
    status_t rc = STATUS_OK;
    
    phys_addr_t addr;
    CHECKCALL ( virt2phys_addr (mem, vaddr, &addr) );

    LOG (Log::DEBUG, s_logger,
	 "mem_read_bytes phys addr 0x" << std::hex << addr
	 << " len = " << std::dec << len);

    if (addr + len > mem->size) ERREXIT(ILLADDR);
    
    CHECKCALL ( mem_impl_read (&mem->impl, addr, o_buf, len) );

 error_egress:
    return rc;
}


status_t mem_read (mem_t * mem,
		   addr_t vaddr,
		   word_t * o_val)
{
    const size_t read_size = sizeof(word_t);

    status_t rc = STATUS_OK;
    
    phys_addr_t addr;

    // make sure it's word-aligned
    if (vaddr & 0x3 != 0)
    {
	ERREXIT (ALIGN);
    }

    CHECKCALL ( virt2phys_addr (mem, vaddr, &addr) );

    LOG (Log::DEBUG, s_logger,
	 "mem_read phys addr 0x" << std::hex << addr);

    if (addr + read_size > mem->size) ERREXIT(ILLADDR);

    CHECKCALL ( mem_impl_read (&mem->impl, addr,
			       reinterpret_cast<byte*>(o_val), read_size) );

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


void mem_dump (const mem_t * mem,
	       const std::string& filename)
{
    mem_impl_dump (&mem->impl, filename);
}


CLOSE_NS
