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
 *
 */


#include "memory.h"

#include "memory-impl.h"

#include "status.h"
#include "common.h"

#include <faerieplay/common/utils-macros.h>
#include <faerieplay/common/utils.h>	// writefile()
#include <faerieplay/common/countarray.hpp>

#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>


#ifdef DYNAMIC_LINK
#include <dlfcn.h>		// dlopen() etc. these conform to POSIX.1-2001,
				// which probably limits portability.
				// TODO: easily fall back to compile-time
				// linking of mem impl if dlopen() etc not
				// supported.
#endif

#include <unistd.h>

#include <string.h>

#include <iomanip>


MIPS_OPEN_NS


mem_t g_mainmem;		// declared extern in memory.h


namespace {
    Log::logger_t s_logger = Log::makeLogger ("mips.mem");
}


namespace
{
    // function pointers for all the mem impl methods defined in memory-impl.h
    // to enable dynamic loading of the implementations.
    
    typedef status_t (*mem_impl_init_type) (mem_impl_t * mem,
					    size_t size);

    typedef status_t (*mem_impl_init_complete_type) (mem_impl_t * mem);

    typedef status_t (*mem_impl_read_type) (mem_impl_t * mem,
					    phys_addr_t addr,
					    byte * o_buf, size_t len);

    typedef status_t (*mem_impl_write_type) (mem_impl_t * mem,
					     phys_addr_t addr,
					     const byte * buf, size_t len);

    typedef void (*mem_impl_dump_type) (const mem_impl_t * mem,
					const std::string& filename);

#define INSTANTIATE_IMPL_PTR(name) name ## _type name ## _ptr
    
    INSTANTIATE_IMPL_PTR(mem_impl_init);
    INSTANTIATE_IMPL_PTR(mem_impl_init_complete);
    INSTANTIATE_IMPL_PTR(mem_impl_read);
    INSTANTIATE_IMPL_PTR(mem_impl_write);
    INSTANTIATE_IMPL_PTR(mem_impl_dump);

#undef INSTANTIATE_IMPL_PTR
}


status_t mem_init (const char* mem_impl_file,
		   mem_t * mem,
		   size_t size,
		   size_t textstart,
		   size_t textsize,
		   size_t static_data_size)
{
    status_t rc = STATUS_OK;
    

#ifdef DYNAMIC_LINK

    char * dl_error;
    void * impl_handle;

    if (mem_impl_file == NULL) {
	LOG (Log::CRIT, s_logger,
	     "Name of RAM implementation library not given, "
	     "cannot create emulated RAM");
	return STATUS_MEMFAULT;
    }
	
	     
    impl_handle = dlopen (mem_impl_file, RTLD_NOW);
    
    if (impl_handle == NULL) {
	LOG (Log::CRIT, s_logger,
	     "Failed to load the memory implementation in " << mem_impl_file
	     << ": " << dlerror());

	return STATUS_MEMFAULT;
    }

#define MEM_IMPL_DLSYM(symname)					\
    dlerror();    /* Clear any existing error */		\
    symname ## _ptr = reinterpret_cast<symname ## _type>	\
	(dlsym (impl_handle, #symname));			\
    if ( (dl_error = dlerror()) != NULL )  {			\
	LOG (Log::CRIT, s_logger,				\
	     "Failed to load function " << #symname		\
	     << " from memory impl " << mem_impl_file		\
	     << ": " << dl_error);				\
	dlclose (impl_handle);					\
	return STATUS_MEMFAULT;					\
    }
    
    MEM_IMPL_DLSYM(mem_impl_init);
    MEM_IMPL_DLSYM(mem_impl_init_complete);
    MEM_IMPL_DLSYM(mem_impl_read);
    MEM_IMPL_DLSYM(mem_impl_write);
    MEM_IMPL_DLSYM(mem_impl_dump);

#undef MEM_IMPL_DLSYM
    
#else  // static linking, just set the pointers

    mem_impl_init_ptr 	       = &mem_impl_init;
    mem_impl_init_complete_ptr = &mem_impl_init_complete;
    mem_impl_read_ptr 	       = &mem_impl_read;
    mem_impl_write_ptr 	       = &mem_impl_write;
    mem_impl_dump_ptr 	       = &mem_impl_dump;

#endif // DYNAMIC_LINK

    
    memset (mem, 0, sizeof(*mem));
    
    mem->size = size;
    
    CHECKCALL ( mem_impl_init_ptr (&mem->impl, size) );

    mem->text_start = textstart;
    mem->textsize = textsize;
    mem->static_data_size = static_data_size;
    
    LOG(Log::INFO, s_logger,
        std::hex
        << "Memory layout: text start=0x" << textstart
        << ", text end / static data start=0x" << textstart+textsize
        << ", static data end=0x" << textstart+textsize+static_data_size);

error_egress:

    return rc;
}

/// Called when the initialization (eg. loading of text and static data) is done
status_t mem_init_complete (mem_t * mem)
{
    // just pass it on
    return mem_impl_init_complete_ptr (&mem->impl);
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
    
    LOG (Log::DEBUG, s_logger,
	 "mem_write virt addr 0x" << std::hex << vaddr << std::dec
	 << " len = " << read_size);
    CHECKCALL ( virt2phys_addr (mem, vaddr, &addr) );
    LOG (Log::DEBUG, s_logger,
	 "mem_write phys addr " << addr
	 << " len = " << read_size);

    if (addr + read_size > mem->size) ERREXIT(ILLADDR);

    CHECKCALL ( mem_impl_write_ptr (&mem->impl, addr, reinterpret_cast<byte*>(&val), read_size) );

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
	 "mem_write_bytes vaddr=0x" << std::hex << vaddr
         << ", phys addr=0x" << addr
	 << " len=" << std::dec << len);
    if (len <= 4) {
        LOG (Log::DEBUG, s_logger,
             "mem_write_bytes bytes=" << ByteBuffer(buf, len, ByteBuffer::deepcopy()));
    }
    
    // addr+len-1 is the largest index we're writing to
    if (addr+len-1 >= mem->size) ERREXIT(ILLADDR);
    
    CHECKCALL ( mem_impl_write_ptr (&mem->impl, addr, buf, len) );

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
	 "mem_read_bytes vaddr=0x" << std::hex << vaddr
         << ", phys addr=0x" << addr
	 << " len=" << std::dec << len);

    if (addr + len > mem->size) ERREXIT(ILLADDR);

    CHECKCALL ( mem_impl_read_ptr (&mem->impl, addr, o_buf, len) );

    if (len <= 4) {
        LOG (Log::DEBUG, s_logger,
             "mem_read_bytes bytes=" << ByteBuffer(o_buf, len, ByteBuffer::SHALLOW));
    }

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
	 "mem_read word vaddr=0x" << std::hex << vaddr
         << ", phys addr=0x" << addr);

    if (addr + read_size > mem->size) ERREXIT(ILLADDR);

    CHECKCALL ( mem_impl_read_ptr (&mem->impl, addr,
				   reinterpret_cast<byte*>(o_val), read_size) );

    LOG (Log::DEBUG, s_logger,
         "mem_read word=" << ByteBuffer(o_val, sizeof(word_t), ByteBuffer::SHALLOW));

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
	LOG (Log::ERROR, s_logger,
	     "Invalid virtual address (before mem start or into kernel space) "
             << "0x" << std::hex << full_addr);
	
        log4cpp::Appender::closeAll();
        s_logger->getStream(log4cpp::Priority::INFO).flush();
        s_logger->getStream(log4cpp::Priority::DEBUG).flush();
        s_logger->getStream(log4cpp::Priority::ERROR).flush();

        exit (21);
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
    mem_impl_dump_ptr (&mem->impl, filename);
}


CLOSE_NS
