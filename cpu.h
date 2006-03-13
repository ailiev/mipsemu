// -*- c++ -*-

#include "instructions.h"
#include "memory.h"

#include "status.h"

#include <stdint.h>


#ifndef _MIPS_CPU_H
#define _MIPS_CPU_H


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



void prepare_cpu ();

void write_register (byte regnum, uint32_t val);
uint32_t read_register (byte regnum);

status_t run_process (mem_t * mem,
		      addr_t start_addr);

status_t decode_instruction (uint32_t instr, instruction_t * o_instr);

const char* register_name (unsigned reg_num);

CLOSE_NS


#endif // _MIPS_CPU_H

