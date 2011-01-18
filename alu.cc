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


#include "alu.h"

#include "cpu.h"

#include "status.h"
#include "common.h"

#include <faerieplay/common/utils-macros.h>


MIPS_OPEN_NS

status_t exec_arith (instruction_t * instr)
{
    uint32_t result;
    uint64_t result_64;		// for multiplication
    
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

    case mult:
	result_64 =
	    SIGNEXTEND_WORD(instr->operands[0], 32, 64) *
	    SIGNEXTEND_WORD(instr->operands[1], 32, 64);
	goto write_mult_result;
    case multu:
	result_64 =
	    static_cast<uint64_t>(instr->operands[0]) *
	    static_cast<uint64_t>(instr->operands[1]);
	goto write_mult_result;
	
    write_mult_result:
	write_register (static_cast<register_id>(lo), GETBITS(result_64, 0, 31),
                        instr->pc);
	write_register (static_cast<register_id>(hi), GETBITS(result_64, 32, 63),
                        instr->pc);

	goto egress;		// we're not writing a destination register,
				// just skip out
    
    case div:
	write_register (static_cast<register_id>(lo), signed_act(/),
                        instr->pc);
	write_register (static_cast<register_id>(hi), signed_act(%),
                        instr->pc);
	goto egress;
    case divu:
	write_register (static_cast<register_id>(lo), act(/),
                        instr->pc);
	write_register (static_cast<register_id>(hi), act(%),
                        instr->pc);
	goto egress;

    default:
	break;
    }

    write_register (instr->destreg, result, instr->pc);

    goto egress;

 egress:
    return rc;
}



#if 0
// from http://www.cs.uaf.edu/2004/fall/cs301/notes/notes/node47.html
void long_multiply (int32_t v1, int32_t v2,
		    uint32_t * o_lo, uint32_t * o_hi)
{
}
// 2-digit multiplication in base 2^32:
//          A B
//        x C D
//        ------
//        AD || BD
//+ AC || CB || 0
//
    int32_t a, b, c, d;
    int32_t c1, c2, c3;

//    int32_t HI, LO;

    a = GETBITS (v1, 16, 31);
    b = GETBITS (v1, 0, 15);
    c = GETBITS (v2, 16, 31);
    d = GETBITS (v2, 0, 15);

    
    
    LO = b * d;                   /* BD */
    x = a * d + c * b;            /* AD + CB */
    y = GETBITS (LO,16,31) + x;

    LO = CONCAT_16BIT (y & 0xffff, LO & 0xffff);   // (LO & 0xffff) | ((y & 0xffff) << 16);
    HI = GETBITS (y,16,31) + (a*c);

//  HI += a * c;                  /* AC */

    *o_lo = LO;
    *o_hi = HI;
}
#endif

CLOSE_NS
