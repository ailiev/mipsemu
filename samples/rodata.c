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


/* A simple program which creates an rodata section */

#include <unistd.h>
#include <string.h>

int main ()
{
    /* the string constant goes into rodata */
    const char msg[] = "kuku makes the world go round";

    write (1, msg, strlen(msg));
    return 0;
}

