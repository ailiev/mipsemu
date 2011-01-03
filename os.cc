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


#include "os.h"
#include "mman.h"

#include "cpu.h"

#include "common.h"
#include "status.h"

#include <faerieplay/common/logging.h>

// this is a MIPS OS!
#include <mips/syscalls.h>

//#include <sys/mman.h>		// for MAP_FAILED

#include <errno.h>

#include <string>


MIPS_OPEN_NS


namespace {
    Log::logger_t s_logger = Log::makeLogger ("mips.syscall");
}


namespace {
    status_t do_mmap ();
}



status_t exec_syscall ()
{
//    const uint32_t syscall_num_exit = __NR_exit;

    status_t rc = STATUS_OK;

    ssize_t sysrc;
    
    uint32_t callnum = read_register (v0);

    byte * buf = NULL;

    switch (callnum) {
    case __NR_exit:
    {
	// read out the exit code, treat as a signed int
	int32_t exitcode = read_register (a0);
	LOG (Log::INFO, s_logger,
	     "MIPS Process exited with code " << exitcode);
	// and we exit ourselves...
	exit (exitcode);
	break;
    }
    case __NR_write:
    {
	int fd = read_register (a0);
	addr_t buf_vaddr = read_register (a1);
	size_t count = read_register (a2);

	LOG (Log::DEBUG, s_logger,
	     "write fd " << fd << " @" << buf_vaddr
	     << ", " << count << " bytes");

	CHECK_ALLOC ( buf, (byte*) malloc (count) );
	
	rc = mem_read_bytes (&g_mainmem,
			     buf_vaddr,
			     buf, count);
	if (rc != STATUS_OK)
	{
	    switch (rc) {
	    case STATUS_ILLADDR:
		// report out-of-range access to caller and continue.
		write_register (a3, static_cast<uint32_t> (-1));
		write_register (v0, EFAULT);
		goto egress;
	    default:
		goto error_egress;
	    }
	}


	{
	    // cast from byte* to char*
	    std::string s (reinterpret_cast<char*>(buf), count);
	    LOG (Log::INFO, s_logger,
		 "syscall write-->" << s << "<--");
	}

	sysrc = ::write (fd, buf , count);

	if (sysrc < 0)
	{
	    // error
	    write_register (v0, errno);
	    write_register (a3, -1);
	}
	else
	{
	    write_register (v0, sysrc);
	    write_register (a3, 0);
	}
	
	break;
    }

    case __NR_read:
    {
	int fd = read_register (a0);
	addr_t buf_vaddr = read_register (a1);
	size_t count = read_register (a2);

	LOG (Log::DEBUG, s_logger,
	     "read fd " << fd << " @" << buf_vaddr
	     << ", " << count << " bytes");

	CHECK_ALLOC ( buf, (byte*) malloc (count) );

	sysrc = ::read (fd, buf, count);
	
	if (sysrc < 0)
	{
	    write_register (v0, errno);
	    write_register (a3, static_cast<uint32_t>(sysrc));
	    break;
	}

	rc = mem_write_bytes (&g_mainmem,
			      buf_vaddr,
			      buf, count);
	if (rc != STATUS_OK)
	{
	    switch (rc) {
	    case STATUS_ILLADDR:
		// report out-of-range access to caller and continue.
		write_register (v0, EFAULT);
		write_register (a3, -1);
		goto egress;
	    default:
		goto error_egress;
	    }
	}

	write_register (v0, sysrc);
	write_register (a3, 0);	// to make sure __unified_syscall does not flag
				// a failed syscall
	break;
    }	

    case __NR_mmap:
	CHECKCALL ( do_mmap () );
	break;

    case __NR_munmap:
	std::clog << "munmap not implemented yet" << std::endl;
	break;

    default:
	ERREXIT (ILLSYSCALL);
	break;
    }

 error_egress:

 egress:
    if (buf) free (buf);

    // TODO: do the register setting stuff in here rather than in all the
    // handlers.
    
    return rc;
}



OPEN_ANON_NS


status_t do_mmap ()
{
    status_t rc = STATUS_OK;
    
    addr_t start_vaddr = read_register(a0);
    word_t len = read_register(a1);
    word_t prot = read_register(a2);
    word_t flags = read_register(a3);

    // these two on the stack:
    word_t fd;
    word_t offset;

    // the answer
    addr_t alloc_addr;
    
    // from looking at some generated assembly:
    // arg 5: sp+16
    // arg 6: sp+20
    // also, in this case ra was saved to sp+24 before that call.
    // the stack size can vary and these args always seem to go into those
    // offsets relative to sp.
    //
    // ra goes at the top of the frame though, not always at sp+24
    addr_t sp_val = read_register(sp);
    CHECKCALL ( mem_read (&g_mainmem, sp_val+16, &fd) );
    CHECKCALL ( mem_read (&g_mainmem, sp_val+20, &offset) );


    // and do the allocation
    CHECKCALL ( heap::alloc_mem (len, &alloc_addr) );

    goto egress;
    
 error_egress:
    write_register (a3, static_cast<uint32_t>(-1));	// MAP_FAILED is -1
    write_register (v0, ENOMEM); 
    return rc;
    
 egress:
    write_register (v0, alloc_addr);
    write_register (a3, 0);	// __unified_syscall looks for an error
				// indication here!
    return rc;
}

CLOSE_NS			// anon


CLOSE_NS			// mips

