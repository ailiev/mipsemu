#include <dietlibc/syscalls.h>

status_t exec_syscall (instruction_t * instr)
{
    status_t rc = STATUS_OK;
    
    uint32_t callnum = read_register (v0);

    switch (callnum) {
    case __NR_exit:
	// read out the exit code
	uint32_t exitcode = read_register (a0);
	cout << "Process exited with code " << exitcode << endl;
	break;

    default:
	ERREXIT (ILLSYSCALL);
	break;
    }

    return rc;
}


