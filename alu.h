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
