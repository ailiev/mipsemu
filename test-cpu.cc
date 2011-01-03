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


#include "cpu.h"
#include "instructions.h"

#include <iostream>

#include <string.h>

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
