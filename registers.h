// -*-c++-*-
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

#include "common.h"

#include <stdint.h>

#include <iostream>

#ifndef _REGISTERS_H
#define _REGISTERS_H


MIPS_OPEN_NS


    enum register_id {
	zero = 0,
	at,
	v0,
	v1,
	a0,
	a1,
	a2,
	a3,
	t0,
	t1,
	t2,
	t3,
	t4,
	t5,
	t6,
	t7,
	s0,
	s1,
	s2,
	s3,
	s4,
	s5,
	s6,
	s7,
	t8,
	t9,
	k0,
	k1,
	gp,
	sp,
	fp,
	ra
    };

enum special_regs {
	pc = ra + 1,		// program counter

	br_target,		// branch target, set by a successful branch
				// instruction, to be branched to after the next
				// instruction.

	lo,			// mult/divide result registers
	hi,

	NUMREGS
    };

typedef uint32_t register_file_t [NUMREGS];


const char* register_name (register_id reg_num);

std::ostream& dump_registers (std::ostream& os);

CLOSE_NS

#endif /* _REGISTERS_H */
