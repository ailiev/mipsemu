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


/* test program to exercise strcat(3) */

#include <unistd.h>
#include <string.h>

#include <faerieplay/common/utils-macros.h>

int main ()
{
    const char * msgs[] = {
        "",
        "123",
        "1234",
        "123456",
        "12345678",
        "123456789012345678901234567890123456789012" /* 42 chars */
    };

    int i;
    char dest[128];

    for (i=0; i < ARRLEN(msgs); ++i) {
        strcat(dest, msgs[i]);
        write (1, dest, strlen(dest));
        write (1, "\n", 1);
    }

    return 0;
}
