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


#define SYSCALL_MALLOC 4513

void * malloc (unsigned size)
{
    void * answer;
    
    /* load up the paramater, call the syscall, and get the response out */
    asm (
	"   li      $2, %2 \n"		/* $2 = $v0 */
	"\t move    $4, %1 \n"	/* $4 = $a0 */
	"\t syscall        \n"
	"\t move    %0, $2"
	: "=r" (answer)
	: "r"  (size),
	   "i" (SYSCALL_MALLOC)	/* an immediate */
	: "2", "4"		/* trashed registers */
	);

    return answer;
}
