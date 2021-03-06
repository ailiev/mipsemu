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


/* test with a string constant in rodata section */

#include <unistd.h>
#include <string.h>

int main ()
{
    const char msg[] = "the string constant goes into the rodata section. extra char:";

    write (1, msg, sizeof(msg));
    write (1, msg+15, 1);      /* should be 't',from the middle of 'constant' */
    write (1, "\n", 1);
    return 0;
}
