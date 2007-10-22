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


#include <sys/mman.h>

int main (int argc, char * argv[]) {

    char buf[16];

    buf[16] = argv[1][24];
    
    char * mem = mmap (12345678, 8765,
		       PROT_READ | PROT_WRITE,
		       MAP_ANONYMOUS | MAP_PRIVATE,
		       5, 1001);

    mem[0] = 'f';
    return mem[1];
}

