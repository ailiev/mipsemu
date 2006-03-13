#include "instructions.h"

#include "status.h"
#include "common.h"


#ifndef _ALU_H
#define _ALU_H

MIPS_OPEN_NS

status_t exec_arith (instruction_t * instr);

CLOSE_NS

#endif /* _ALU_H */
