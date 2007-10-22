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

//int g_dummy = 100;


int add5 (int x) {
    return x+5;
}


int main (int argc, char* argv[]) {

    char *int_strs[2] = { argv[1], argv[2] };
    unsigned is[2] = { atoi(int_strs[0]), atoi(int_strs[1]) };

//    char * arg = argv[1];
//    char s1[] = "012345678901234567";
//    char s2[32] = " papa bye bye";

    return is[0] / is[1];

//    strcat (s2, s1);

/*     len = strlen(arg); */

/*     write (1, arg, len); */
    
/*     return len; */
//    return g_dummy + is[0] * is[1];

//    int x = g_dummy;
    
//    int z = add5(x);
    
//    write (1, int_str, strlen(int_str));
//    write (3, &i, sizeof(i));
//    char * text = (char*) malloc (20);

//    return i + strlen(int_str) + z;
}
