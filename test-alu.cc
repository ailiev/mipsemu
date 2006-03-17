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
