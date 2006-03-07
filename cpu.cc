#include <pir/common/utils-types.h>

void decode_instruction (uint32_t instr, instruction_t * o_instr)
{
    mips_instr_name name = decode_instr_name (instr);
}


mips_instr_name decode_instr_name (uint32_t instr)
{
    byte opcode = GETBITS (instr, 26, 31);
    switch (opcode) {
#define f(val,ret) case val: return ret

	f (0, decode_0_opcode (instr));
	f (1, decode_1_opcode  (instr));

	f (2, j);
	f (3, jal);

    }

}

mips_instr_name decode_0_opcode (uint32_t instr)
{
    byte funct = GETBITS (instr, 0, 5);

    switch (funct) {
#define f(val,ret) case val: return ret
	f (0, sll);
	f (2, srl);
	f (3, sra);
	f (4, sllv);
	f (6, srlv);
	f (7, srav);
	f (8, jr);
	f (9, jalr);
	f (10, movz);
	f (11, movn);
	f (12, syscall);
	f (13, i_break);
//	f (15, sync);

	f (16, mfhi);
	f (17, mthi);
	f (18, mflo);
	f (19, mtlo);

	f (24, mult);
	f (25, multu);
	f (26, div);
	f (27, divu);

	f (32, add);
	f (33, addu);
	f (34, sub);
	f (35, subu);
	f (36, and);
	f (37, or);
	f (38, xor);
	f (39, nor);

	f (42, slt);
	f (43, sltu);
#undef f
    }

}

mips_instr_name decode_1_opcode (uint32_t instr)
{
    byte rt = GETBITS (instr, 16, 20);

    switch (rt) {
#define f(val,ret) case val: return ret
	f (0, bltz);
	f (1, bgez);
	f (2, bltzl);
	f (3, bgezl);

	f (16, bltzal);
	f (17, bgezal);
#undef f
    }
}

	
