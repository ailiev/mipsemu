/*
 * Simple emulator for a MIPS machine, with a pluggable emulated RAM. Can run
 * executables compiled with gcc against dietlibc and using a few syscalls.
 *
 * Copyright (C) 2003-2007, Alexander Iliev <sasho@cs.dartmouth.edu> and
 * Sean W. Smith <sws@cs.dartmouth.edu>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
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
