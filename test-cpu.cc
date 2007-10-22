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


#include "cpu.h"
#include "instructions.h"

#include <iostream>


// how to get a list of all the binary instructions in an executable:
// mipsel-linux-objdump -d simple | pcregrep '^\s+(\d|[a-f])+:' | awk '{print $2}'

using namespace std;


int main (int argc, char *argv[])
{
    mips::instruction_t inst;

    uint32_t inst_code;

    mips::init_instr_info ();    

    while (cin >> hex >> inst_code)
    {
	memset (&inst, 0, sizeof(inst));
	
	clog << "Binary instruction: " << hex << inst_code << endl;

	mips::decode_instruction (inst_code, &inst);

	cout << inst << endl;
    }
}
