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

#include "registers.h"

#include "common.h"

#include <faerieplay/common/utils-types.h>

#include <stdint.h>

#include <iostream>


#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H


MIPS_OPEN_NS

// FIXME: check if we need a mul instruction

enum mips_instr_name
{
    illegal_instruction = 0,
    add,
    addi,
    addiu,
    addu,
    i_and,
    andi,
//    bczt,
    beq,
    bgez,
    bgezal,
    bgtz,
    blez,
    bltz,
    bltzal,
    bne,
    i_break,
//    bzcf,
    div,
    divu,
    j,
    jal,
    jalr,
    jr,
    lb,
    lbu,
    lh,
    lhu,
    lui,
    lw,
//    lwcz,

//     lwl,
//     lwr,

    mfc0,			// move from the exception coprocessor
//    mfcz,
    mfhi,
    mflo,
//    mtcz,
    movn,
    movz,
    mthi,
    mtlo,
    mult,
    multu,
    nop,
    nor,
    i_or,
    ori,
//    rfe,
    sb,
    sh,
    sll,
    sllv,
    slt,
    slti,
    sltiu,
    sltu,
    sra,
    srav,
    srl,
    srlv,
    sub,
    subu,
    sw,
//    swcz,

//     swl,
//     swr,

    syscall,
    i_xor,
    xori,
    NUM_INSTRS
};


struct mips_instr_info {

    mips_instr_name name;	// as a double-check
    
    enum
    {
	arith,
	load,
	store,
	immediate,
	branch,
	jump,
	trap,
	move,
	misc
    } instr_type;

    enum
    {
	none,
	end16,
	end26,
	shift,
	breakcode
    } immed_type;

    byte num_ops;		// the number of input *registers* 0-2

    bool has_out;		// does the instruction write a result to $rd?

    bool should_link;

    bool is_signed;		// should we do signed arithmetic?
};



extern mips_instr_info g_instr_info[];

/// initialize the global instruction info map. Must be called before using the
/// CPU.
void init_instr_info ();


// the most common breakdown of instruction binary format
//
// WARNING: this is only for where the uint32_t (or such) representation of the
// instruction is in *little-endian* byte order, and it's directly copied into
// an instr_fields instance with memcpy. Hence the fields appear to be in
// reverse.
struct type_R_syntax
{
    byte funct;	// 
    byte shamt;	// this field is only used as part of a 16-bit
				// immediate, or in shift instructions
    register_id rd;
    register_id rt;
    register_id rs;

    byte opcode;
};

// and where a 16-bit immediate is involved:
struct type_I_syntax
{
    uint16_t imm;

    register_id rt;
    register_id rs;

    byte opcode;
};

struct type_J_syntax
{
    uint32_t addr;
    byte opcode;
};




struct instruction_t {
    uint32_t code;
    
    uint32_t pc;
    
    mips_instr_name name;

    register_id inregs[2];	// up to two operand register numbers, 0-2
				//
				// the value of instruction fields rs and rt get
				// loaded in here, except for the shift
				// instructions which get their single input
				// from rt (not rs)
    
    register_id destreg;	// destination register number, from instruction
				// field rd, or rt if an I-type instruction.


    uint32_t operands[3];	// up to three operand *values*. beq and bne
				// have three operands: two vals to compare, and
				// a target addresses.
				//
				// The operands come either from the
				// corresponding inregs index, or from an
				// immediate (which goes at the end), or a
				// constant like 0 (eg for comparisons against
				// 0)
};


type_R_syntax decode_R_instr (uint32_t instr);

std::ostream& operator<< (std::ostream& os, mips_instr_name name);

std::ostream& operator<< (std::ostream& os, const instruction_t & instr);

CLOSE_NS


#endif // _INSTRUCTIONS_H
