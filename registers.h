// -*-c++-*-

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
	ra,

	pc,			// program counter

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
