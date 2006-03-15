#include "alu.h"

#include "cpu.h"

#include "status.h"
#include "common.h"

#include <pir/common/utils-macros.h>


MIPS_OPEN_NS

status_t exec_arith (instruction_t * instr)
{
    uint32_t result;
    status_t rc = STATUS_OK;
    
    switch (instr->name) {
	// FIXME: not handling overflow issues for now
#define act(op) instr->operands[0] op instr->operands[1]
#define signed_act(op)					\
	static_cast<int32_t> (instr->operands[0]) op	\
	static_cast<int32_t> (instr->operands[1])

#define d2(n1,n2,op)	case n1: case n2: result = act(op)
#define ds2(n1,n2,op)	case n1: case n2: result = signed_act(op)
#define d1(n1,op)	case n1: result = act(op)
#define ds1(n1,op)	case n1: result = signed_act(op)
	
	d2  (add, addi,	    +);	    break;
	d2  (addu, addiu,   +);	    break;

	d1  (sub,	    -);	    break;
	d1  (subu,	    -);	    break;

	d2 (i_and, andi,    &);    break;
	d2 (i_or, ori,	    |);    break;

	d2 (sll, sllv,	    <<);    break;

	ds2 (sra, srav,	    >>);    break;
	d2 (srl, srlv,	    >>);    break;

	ds2 (slt, slti,	    <);	    break;

	d2 (sltu, sltiu,    <);	    break;

	d2 (i_xor, xori,    ^);	    break;

#undef d2

    case nor:
	// do as (not or)
	result = ! (instr->operands[0] || instr->operands[1]);
	break;

    default:
	break;
			
    }

    write_register (instr->destreg, result);
    goto egress;


    // multiply
    // FIXME: just writing a zero into hi for now
    {
	uint32_t res;
	if	(instr->name == mult)  res = signed_act(*);
	else if (instr->name == multu) res = act(*);

	write_register (lo, res);
	write_register (hi, 0);
// 	write_register (lo, GETBITS(res, 0, 31));
// 	write_register (hi, GETBITS(res, 32,63));
    }
    goto egress;


    // divide
    if (instr->name == div) {
	write_register (lo, signed_act(/));
	write_register (hi, signed_act(%));
    }
    else if (instr->name == divu) {
	write_register (lo, act(/));
	write_register (hi, act(%));
    }
    goto egress;


 egress:
    return rc;
}


CLOSE_NS
