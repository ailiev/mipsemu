/*
 * Simple emulator for a MIPS machine, with a pluggable emulated RAM. Can run
 * executables compiled with gcc against dietlibc and using a few syscalls.
 *
 * Copyright (C) 2011, Alexander Iliev <alex.iliev@gmail.com>
 *
 * All rights reserved.
 *
 * This code is released under a BSD license.
 * Please see LICENSE.txt for the full license and disclaimers.
 *
*/


/* test program to exercise strlen(3) */

#include <unistd.h>
#include <stdlib.h>
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
    ssize_t rc;

    for (i=0; i < ARRLEN(msgs); ++i) {
        size_t s = strlen(msgs[i]);
        rc = write (1, msgs[i], s);
        if (rc != s) {
            exit(2);
        }

        rc = write (1, "\n", 1);
        if (rc != 1) {
            exit(2);
        }
    }

    return 0;
}
