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


#include <assert.h>

#include "instructions.h"

#include <faerieplay/common/utils-macros.h>

MIPS_OPEN_NS

struct mips_instr_str_name
{
    mips_instr_name op;
    const char * opname;
};

static const mips_instr_str_name g_op_names[] =  
{
    { illegal_instruction, "illegal_instruction" }, 
    { add, "add" },
    { addi, "addi" },
    { addiu, "addiu" },
    { addu, "addu" },
    { i_and, "i_and" },
    { andi, "andi" },
//    { bczt, "bczt" },
    { beq, "beq" },
    { bgez, "bgez" },
    { bgezal, "bgezal" },
    { bgtz, "bgtz" },
    { blez, "blez" },
    { bltz, "bltz" },
    { bltzal, "bltzal" },
    { bne, "bne" },
    { i_break, "i_break" },
//    { bzcf, "bzcf" },
    { div, "div" },
    { divu, "divu" },
    { j, "j" },
    { jal, "jal" },
    { jalr, "jalr" },
    { jr, "jr" },
    { lb, "lb" },
    { lbu, "lbu" },
    { lh, "lh" },
    { lhu, "lhu" },
    { lui, "lui" },
    { lw, "lw" },
//    { lwcz, "lwcz" },
//     { lwl, "lwl" },
//     { lwr, "lwr" },
    { mfc0, "mfc0" },			// move from the exception coprocessor
//    { mfcz, "mfcz" },
    { mfhi, "mfhi" },
    { mflo, "mflo" },
//    { mtcz, "mtcz" },
    { movn, "movn" },
    { movz, "movz" },
    { mthi, "mthi" },
    { mtlo, "mtlo" },
    { mult, "mult" },
    { multu, "multu" },
    { nop, "nop" },
    { nor, "nor" },
    { i_or, "i_or" },
    { ori, "ori" },
//    { rfe, "rfe" },
    { sb, "sb" },
    { sh, "sh" },
    { sll, "sll" },
    { sllv, "sllv" },
    { slt, "slt" },
    { slti, "slti" },
    { sltiu, "sltiu" },
    { sltu, "sltu" },
    { sra, "sra" },
    { srav, "srav" },
    { srl, "srl" },
    { srlv, "srlv" },
    { sub, "sub" },
    { subu, "subu" },
    { sw, "sw" },
//    { swcz, "swcz" },
//     { swl, "swl" },
//     { swr, "swr" },
    { syscall, "syscall" },
    { i_xor, "i_xor" },
    { xori, "xori" }
};


std::ostream& operator<< (std::ostream& os, mips_instr_name name)
{
    assert (g_op_names[name].op == name);
    return os << g_op_names[name].opname;
}




mips_instr_info g_instr_info [NUM_INSTRS];


void init_instr_info ()
{
#define MKINFO(name, v1,v2,v3) {		\
    name,					\
	mips_instr_info::v1,			\
	mips_instr_info::v2,			\
	v3,					\
	false,					\
	false,					\
	false					\
	}

#define SETINFO_SMALL(instr, info) instr_info[instr] = info
    
// set up the link flags separately afterwards
#define SETINFO(instr, v1, v2, v3)				\
    {								\
        mips_instr_info __kuku = MKINFO (instr, v1,v2,v3);	\
        g_instr_info[instr] = __kuku;				\
    }

	
    SETINFO (add,	arith,	    none,   2);
    SETINFO (addi,	arith,	    end16,  1);
    SETINFO (addiu,	arith,	    end16,  1);
    SETINFO (addu,	arith,	    none,   2);
    SETINFO (i_and,	arith,	    none,   2);
    SETINFO (andi,	arith,	    end16,  1);
    SETINFO (beq,	branch,	    end16,  2);
    SETINFO (bgez,	branch,	    end16,  1);
    SETINFO (bgezal,	branch,	    end16,  1);
    SETINFO (bgtz,	branch,	    end16,  1);
    SETINFO (blez,	branch,	    end16,  1);
    SETINFO (bltz,	branch,	    end16,  1);
    SETINFO (bltzal,	branch,	    end16,  1);
    SETINFO (bne,	branch,	    end16,  2);
    SETINFO (i_break,	trap,	    breakcode, 0);
    SETINFO (div,	arith,	    none,   2);
    SETINFO (divu,	arith,	    none,   2);
    SETINFO (j,		jump,	    end26,  0);
    SETINFO (jal,	jump,	    end26,  0);
    SETINFO (jalr,	jump,	    none,   1);
    SETINFO (jr,	jump,	    none,   1);
    SETINFO (lb,	load,	    end16,  1);
    SETINFO (lbu,	load,	    end16,  1);
    SETINFO (lh,	load,	    end16,  1);
    SETINFO (lhu,	load,	    end16,  1);
    SETINFO (lui,	immediate,  end16,  0);
    SETINFO (lw,	load,	    end16,  1);
//     SETINFO (lwl,	load,	    end16,  1);
//     SETINFO (lwr,	load,	    end16,  1);

    SETINFO (mfc0,	move,	    none,   1);

    SETINFO (movn,	move,	    none,   2);
    SETINFO (movz,	move,	    none,   2);

    SETINFO (mflo,	move,	    none,   0);
    SETINFO (mfhi,	move,	    none,   0);
    SETINFO (mthi,	move,	    none,   1);
    SETINFO (mtlo,	move,	    none,   1);
    
    SETINFO (mult,	arith,	    none,   2);
    SETINFO (multu,	arith,	    none,   0);

    SETINFO (nop,	misc,	    none,   0);

    SETINFO (nor,	arith,	    none,   2);
    SETINFO (i_or,	arith,	    none,   2);
    SETINFO (ori,	arith,	    end16,  1);
//    SETINFO (rfe,	jump,	    none,   0);

    SETINFO (sb,	store,	    end16,  2);
    SETINFO (sh,	store,	    end16,  2);
    SETINFO (sll,	arith,	    shift,  1);
    SETINFO (sllv,	arith,	    none,   2);
    SETINFO (slt,	arith,	    none,   2);
    SETINFO (slti,	arith,	    end16,  1);
    SETINFO (sltiu,	arith,	    end16,  1);
    SETINFO (sltu,	arith,	    none,   2);
    SETINFO (sra,	arith,	    shift,  1);
    SETINFO (srav,	arith,	    none,   2);
    SETINFO (srl,	arith,	    shift,  1);
    SETINFO (srlv,	arith,	    none,   2);
    SETINFO (sub,	arith,	    none,   2);
    SETINFO (subu,	arith,	    none,   2);
    SETINFO (sw, 	store,	    end16,  2);
//     SETINFO (swl, 	store,	    end16,  2);
//     SETINFO (swr, 	store,	    end16,  2);
    SETINFO (syscall,	misc,	    none,   0);
    SETINFO (i_xor,	arith,	    none,   2);
    SETINFO (xori,	arith,	    end16,  1);

    // set up which instructions link a return address in $ra
    mips_instr_name linking_instrs[] = { bgezal, jal, jalr };
    for (unsigned i=0; i < ARRLEN(linking_instrs); i++)
    {
	g_instr_info[ linking_instrs[i] ].should_link = true;
    }


    
    //
    // which instructions have a destination register?
    //
    for (unsigned i=0; i < ARRLEN(g_instr_info); i++)
    {
	mips_instr_info * info = &g_instr_info[i];
	
	assert (info->name == i);
	
	switch (info->instr_type) {
	case mips_instr_info::arith:
	case mips_instr_info::load:
	case mips_instr_info::immediate:
	case mips_instr_info::move:
	    info->has_out = true;
	default:
	    break;
	};

	// negative exceptions
	switch (info->name)
	{
#define d(v) case v: info->has_out = false
	    // these write results only to hi-lo regs
	    d(mult);
	    d(div);
	    d(divu);
	    d(multu);

	    // these have implicit destination regs
	    d(mthi);
	    d(mtlo);
#undef d
	default:
	    break;
	}

	// positive exceptions

    } // end for
    


    // mark signed arithmetic operations
    // NOTE: these operations require the use of 2s-complement arithmetic,
    // eg. addiu can have a negative immediate.
    // The question of whether or not to trap on overflow is separate
    // (though largely overlapping), and
    // ignored here
    mips_instr_name signed_instrs[] =
	{
	    // add and sub just need to trap on overflow, which we're not doing
	    // right now
//	    add,		// tr
// 	    sub,
	    addi, addiu,	// the immediate needs to be sign-extended
	    div, mult,
	    slt,		// compare as signed
	    slti,		// sign-extend immediate, and compare as signed
	    sra, srav,		// shift as signed, to shift in a sign bit from
                                // the left
	    lb, lh		// sign-extend after loading
	};
    for (unsigned i=0; i < ARRLEN(signed_instrs); i++)
    {
	g_instr_info[ signed_instrs[i] ].is_signed = true;
    }
	
	

};


type_R_syntax decode_R_instr (uint32_t instr)
{
    type_R_syntax answer;

    // WARNING: this only works on little-endian for now.
    
#define _set_instr_field(field,type,i,j) answer.field = static_cast<type> (GETBITS (instr, i, j))

    _set_instr_field (opcode, byte, 26, 31);
    
    _set_instr_field (rs, register_id, 21, 25);
    _set_instr_field (rt, register_id, 16, 20);
    _set_instr_field (rd, register_id, 11, 15);

    _set_instr_field (shamt, byte, 6, 10);
    _set_instr_field (funct, byte, 0, 5);

#undef _set_instr_field

    return answer;
}


#if 0
type_I_syntax decode_I_instr (uint32_t instr)
{
    type_I_syntax answer;

#define _set_instr_field(field,type,i,j) answer.field = static_cast<type> (GETBITS (instr, i, j))

    _set_instr_field (opcode, byte, 0, 5);
    
    _set_instr_field (rs, register_id, 6, 10);
    _set_instr_field (rt, register_id, 11, 15);

    _set_instr_field (imm, uint16_t, 16, 31);

#undef _set_instr_field

    return answer;
}


type_J_syntax decode_J_instr (uint32_t instr)
{
    type_J_syntax answer;

#define _set_instr_field(field,i,j) answer.field = GETBITS (instr, i, j)

    _set_instr_field (opcode, 0, 5);
    
    _set_instr_field (addr, 6, 31);

#undef _set_instr_field

    return answer;
}
#endif


std::ostream& operator<< (std::ostream& os, const instruction_t & instr)
{
    mips_instr_info * info = g_instr_info + instr.name;

    std::ios::fmtflags saved_flags = os.flags();
	
    os << instr.name;
    if (info->has_out) {
	os << " " << register_name (instr.destreg);
    }
    if (info->num_ops > 0) {
	os << ", " << register_name (instr.inregs[0]);
    }
    if (info->num_ops > 1) {
	os << ", " << register_name (instr.inregs[1]);
    }

    if (info->immed_type != mips_instr_info::none)
    {
	// print the immediate.
	uint32_t immed = instr.operands[info->num_ops];
	os << ", ";
	if (instr.name == jal) {
	    os << std::hex;
	}

	// HACK: to decide if it should be signed - if it's bigger than 2^31
	if (immed >= (1U << 31)) {
	    os << static_cast<int32_t>(immed);
	}
	else {
	    os << immed;
	}
    }

    os.setf(saved_flags);

    return os;
}

CLOSE_NS
