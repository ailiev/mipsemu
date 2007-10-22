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

#include "instructions.h"

#include "status.h"
#include "common.h"


#ifndef _ALU_H
#define _ALU_H

MIPS_OPEN_NS

status_t exec_arith (instruction_t * instr);


// this is private, but exposed for testing
void long_multiply (int32_t x, int32_t y,
		    uint32_t * o_lo, uint32_t * o_hi);

CLOSE_NS

#endif /* _ALU_H */
