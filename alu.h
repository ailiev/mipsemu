status_t exec_arith (instruction_t * instr)
{
    word_t result;
    
    switch (instr->name) {
#define act(op)							\
	result = instr->operands[0] op instr->operands[1];	\
	break

#define d2(n1,n2,op)	case n1: case n2: act(op)

	d2 (add, addi,	    +);
	d2 (addu, addiu,    +);

	d2 (sub, subu,	    -);

	d2 (i_and, andi,    &&);
	d2 (i_or, ori,	    ||);

	d2 (sll, sllv,	    <<);
	// FIXME: sra should shift in the sign bit from the left (msb).
	d2 (sra, srav,	    >>);
	d2 (srl, srlv,	    >>);

	d2 (slt, slti,	    <);
	// FIXME: how do these unsigned versions differ from signed ones?
	d2 (sltu, sltiu,    <);

	d2 (i_xor, xori,    ^);

#undef act
#undef d2

    case nor:
	// do as (not or)
	result = ! (instr->operands[0] || instr->operands[1]);
	break;
    }

    write_register (instr->destreg, result);
}




//	d1 (nor,	    
