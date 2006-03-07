// -*- c++ -*-

#include <pir/common/utils-types.h>

#include "common.h"

MIPS_OPEN_NS

enum mips_instr_name
{
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
    lwl,
    lwr,
    mfc0,			// move from the exception coprocessor
//    mfcz,
    mflo,
//    mtcz,
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
    swl,
    swr,
    syscall,
    i_xor,
    xori,
    NUM_INSTRS
};


struct instruction_t {
    mips_instr_name name;
    byte rs, rt, rd;		// up to three register numbers
    
    uint32_t immed;
};

    
CLOSE_NS
