// -*- c++ -*-

#include "instructions.h"

#include <stdint.h>

#ifndef _MIPS_CPU_H
#define _MIPS_CPU_H


MIPS_OPEN_NS

void decode_instruction (uint32_t instr, instruction_t * o_instr);

const char* register_name (unsigned reg_num);

CLOSE_NS


#endif // _MIPS_CPU_H

