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


#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>


int mydiv (int x, int y) {
    x = x / y;

    return x;
}

int main (int argc, char* argv[]) {

    char *int_strs[2] = { argv[1], argv[2] };
    int is[2] = { atoi(int_strs[0]), atoi(int_strs[1]) };
    
    int res = mydiv (is[0], is[1]);

    return res;
//    return is[0] % is[1];
}
