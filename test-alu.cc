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


#include "alu.h"

#include <pir/common/utils-macros.h>

#include <iostream>

using namespace std;

int main (int argc, char * argv[]) {

    int64_t x = atoi(argv[1]),
	y = atoi(argv[2]);

    int64_t z = x * y;

    int32_t lo, hi;

    lo = GETBITS(z, 0ULL, 31ULL);
    hi = GETBITS(z, 32ULL, 63ULL);
    
//    mips::long_multiply (x, y, &lo, &hi);

    cout << "z=" << z << endl;
    cout << "lo=" << lo << ", hi=" << hi << endl;
    
    return 0;
}
