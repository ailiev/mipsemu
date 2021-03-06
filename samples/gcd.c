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


#include <stdlib.h>

int gcd (int a, int b)
{
    int temp, i;

    while (b != 0) {
	temp	= b;
	b	= a % b;
	a	= temp;
    }

    return a;
}


int main (int argc, char* argv[])
{
    char *int_strs[2] = { argv[1], argv[2] };
    int a = atoi(int_strs[0]), b = atoi(int_strs[1]); 
    
    return gcd (a, b);
}
