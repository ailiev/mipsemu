// -*- c++ -*-
/*
Copyright (C) 2003-2007, Alexander Iliev <sasho@cs.dartmouth.edu>

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.
* Neither the name of the author nor the names of its contributors may
  be used to endorse or promote products derived from this software without
  specific prior written permission.

This product includes cryptographic software written by Eric Young
(eay@cryptsoft.com)

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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

