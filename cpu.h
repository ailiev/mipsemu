// -*- c++ -*-

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

