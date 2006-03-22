#include "os.h"
#include "mman.h"

#include "cpu.h"

#include "common.h"
#include "status.h"

#include <pir/common/logging.h>

// this is a MIPS OS!
#include <dietlibc/mips/syscalls.h>

//#include <sys/mman.h>		// for MAP_FAILED

#include <errno.h>

#include <iostream>

MIPS_OPEN_NS


namespace {
    Log::logger_t s_logger = Log::makeLogger ("mips-syscall",
					      boost::none, boost::none);
}


namespace {
    status_t do_mmap ();
}



status_t exec_syscall ()
{
//    const uint32_t syscall_num_exit = __NR_exit;

    status_t rc = STATUS_OK;
    
    uint32_t callnum = read_register (v0);

    void * buf = NULL;

    switch (callnum) {
    case __NR_exit:
    {
	// read out the exit code, treat as a signed int
	int32_t exitcode = read_register (a0);
	std::cout << "MIPS Process exited with code " << exitcode << std::endl;
	// and we exit ourselves...
	exit (EXIT_SUCCESS);
	break;
    }
    case __NR_write:
    {
	int fd = read_register (a0);
	addr_t buf_vaddr = read_register (a1);
	size_t count = read_register (a2);

	LOG (Log::DEBUG, s_logger,
	     "write fd " << fd << " @0x" << std::hex << buf_vaddr
	     << ", " << std::dec << count << " bytes");

	ssize_t rc;
	
	CHECK_ALLOC ( buf, malloc (count) );
	
	CHECKCALL ( mem_read_bytes (&g_mainmem,
				    buf_vaddr,
				    buf, count) );

	{
	    char begin[] = "MIPS: syscall write-->";
	    write (fd, begin, sizeof(begin)-1);
	}

	rc = ::write (fd, buf , count);
	write_register (v0, rc);

	{
	    char end[] = "<-- end write\n";
	    write (fd, end, sizeof(end)-1);
	}

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
// egress:
    if (buf) free (buf);
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

