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

struct test_obj_t {
    const char a[64], b[64];
    int equal;
};

int main ()
{
    const struct test_obj_t tests [] = {
        { "12", "12", 1 },
        { "12", "2", 0 },
        { "123", "123", 1 },
        { "123456", "123456", 1 },
        { "123456", "12345", 0 },
        { "1234567890123456789012345678901", "1234567890123456789012345678901", 1},
        { "1234567890123456789012345678901", "123456789012345678901234567890", 0},
        { "123456789012345678901234567890", "1234567890123456789012345678901", 0},
        { "12345678901234567890123456789012", "12345678901234567890123456789012", 1},
    };

    int i;

    for (i=0; i < ARRLEN(tests); ++i) {
        int expected = tests[i].equal;
        int actual = strcmp(tests[i].a, tests[i].b) == 0;

        if (actual != expected) {
            {
                char msg[] = "failed:";
                write(1, msg, sizeof(msg));
            }
            write (1, tests[i].a, strlen(tests[i].a));
            {
                char msg[] = " == ";
                write(1, msg, sizeof(msg));
            }
            write (1, tests[i].b, strlen(tests[i].b));

            write (1, "\n", 1);
            return 2;
        }
    }

    return 0;
}
