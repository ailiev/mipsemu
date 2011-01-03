// -*- c++ -*-
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
#include "memory.h"
#include "registers.h"

#include "status.h"

#include <stdint.h>

#ifndef _MIPS_CPU_H
#define _MIPS_CPU_H


MIPS_OPEN_NS

status_t prepare_cpu (mem_t * mem,
		      int argc, char * argv[]);

void write_register (register_id regnum, uint32_t val);
uint32_t read_register (register_id regnum);

status_t run_process (mem_t * mem,
		      addr_t start_addr);

status_t decode_instruction (uint32_t instr, instruction_t * o_instr);



CLOSE_NS


#endif // _MIPS_CPU_H

