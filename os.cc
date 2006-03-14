#include "os.h"

#include "cpu.h"

#include "common.h"
#include "status.h"

// this is a MIPS OS!
#include <dietlibc/mips/syscalls.h>

#include <iostream>

MIPS_OPEN_NS

status_t exec_syscall ()
{
//    const uint32_t syscall_num_exit = __NR_exit;

    status_t rc = STATUS_OK;
    
    uint32_t callnum = read_register (v0);

    void * buf = NULL;

    switch (callnum) {
    case __NR_exit:
    {
	// read out the exit code
	uint32_t exitcode = read_register (a0);
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

	ssize_t rc;
	
	CHECK_ALLOC ( buf, malloc (count) );
	
	CHECKCALL ( mem_read_bytes (&g_mainmem,
				    buf_vaddr,
				    buf, count) );

	{
	    char msg[] = "syscall write:";
	    write (fd, msg, sizeof(msg)-1);
	}

	rc = write (fd, buf , count);
	write_register (v0, rc);


	break;
    }

    default:
	ERREXIT (ILLSYSCALL);
	break;
    }

 error_egress:
// egress:
    if (buf) free (buf);
    return rc;
}


CLOSE_NS
