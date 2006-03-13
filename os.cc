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

    default:
	ERREXIT (ILLSYSCALL);
	break;
    }

 error_egress:
// egress:
    return rc;
}


CLOSE_NS
