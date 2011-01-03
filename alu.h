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
