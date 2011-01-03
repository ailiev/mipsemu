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

#include <faerieplay/common/utils.h>	// writefile()

#include <string.h>


MIPS_OPEN_NS


//
// just use a local array for the RAM
//

struct priv_impl_t {

    byte * ram;

};


status_t mem_impl_init (mem_impl_t * mem,
			size_t size)
{
    status_t rc = STATUS_OK;
    
    priv_impl_t * impl;

    CHECK_ALLOC ( impl, (priv_impl_t*) malloc (sizeof(priv_impl_t)) );

    impl->ram = new byte[size];
    memset (impl->ram, 0, size);

    mem->size = size;
    mem->priv_impl = impl;


 error_egress:
    
    return rc;
}



status_t mem_impl_read (mem_impl_t * mem,
			phys_addr_t addr,
			byte * o_buf, size_t len)
{
    priv_impl_t * impl = static_cast<priv_impl_t*> (mem->priv_impl);

    // NOTE: the caller should have checked for out-of-bounds access, and
    // signalled to his caller.
    assert (addr + len <= mem->size);
    
    memcpy (o_buf, impl->ram + addr, len);

    return STATUS_OK;
}

status_t mem_impl_write (mem_impl_t * mem,
			 phys_addr_t addr,
			 const byte * buf, size_t len)
{
    priv_impl_t * impl = static_cast<priv_impl_t*> (mem->priv_impl);

    // NOTE: the caller should have checked for out-of-bounds access.
    assert (addr + len <= mem->size);
    
    memcpy (impl->ram + addr, buf, len);

    return STATUS_OK;
}


/// Called when the initialization (eg. loading of text and static data) is done
status_t mem_impl_init_complete (mem_impl_t * mem)
{
    return STATUS_OK;
}

void mem_impl_dump (const mem_impl_t * mem,
		    const std::string& filename)
{
    priv_impl_t * impl = static_cast<priv_impl_t*> (mem->priv_impl);

    const ByteBuffer membytes (impl->ram, mem->size, ByteBuffer::SHALLOW);
    writefile (filename, membytes);
}


CLOSE_NS
