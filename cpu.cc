#include "instructions.h"

#include <pir/common/utils-types.h>
#include <pir/common/utils-macros.h>
#include <pir/common/logging.h>

#include <stdint.h>

MIPS_OPEN_NS

static mips_instr_name decode_instr_name (uint32_t instr);
static void get_register_nums (uint32_t instr, instruction_t * o_instr);

static mips_instr_name decode_0_opcode (uint32_t instr);
static mips_instr_name decode_1_opcode (uint32_t instr);


namespace {
    Log::logger_t s_logger = Log::makeLogger ("mips-cpu",
					    boost::none, boost::none);
}

void decode_instruction (uint32_t instr, instruction_t * o_instr)
{
    o_instr->name = decode_instr_name (instr);
    get_register_nums (instr, o_instr);
}


// fill in the three register fields of the instruction_t
void get_register_nums (uint32_t instr, instruction_t * o_instr)
{
    mips_instr_info * info = g_instr_info + o_instr->name;
    instr_fields fields;

    assert (info->name == o_instr->name);

    // set up a instr_fields to access the bit-fields inside 'instr' easily.
    assert (sizeof(fields) == sizeof(instr));
    memcpy (&fields, &instr, sizeof(instr));

    // the input registers, however many there are
    switch (info->num_ops) {
    case 2:
	o_instr->in2 = fields.rt;
	// fall-through needed here
    case 1:
	o_instr->in1 = fields.rs;
    }

    // the shift instructions cause trouble here: they ignore rs and get their
    // single input from rt
    switch (info->name) {
    case sll:
    case srl:
    case sra:
	o_instr->in1 = fields.rt;
    default:
	break;
    }

    // the output register
    if (info->has_out)
    {
	switch (info->immed_type) {
	case mips_instr_info::end16:
	    // if there is a 16-bit immediate, destination is where $rt usually
	    // is
	    o_instr->dest = fields.rt;
	    break;
	default:
	    o_instr->dest = fields.rd;
	}
    }
	    
}


mips_instr_name decode_instr_name (uint32_t instr)
{
    // if 0 is not handled specially, it will be decoded (seemingly correctly)
    // as a 'sll'. Since nop is quite common, use a special test up front.
    if (instr == 0U) return nop;
    
    byte opcode = GETBITS (instr, 26, 31);

    LOG (Log::DEBUG, s_logger,
	 "opcode = " << (unsigned)opcode);
    
    switch (opcode) {
#define f(val,ret) case val: return ret

	f (0, decode_0_opcode (instr));
	f (1, decode_1_opcode  (instr));

	f (2, j);
	f (3, jal);
	f (4, beq);
	f (5, bne);
	f (6, blez);
	f (7, bgtz);

	f (8, addi);
	f (9, addiu);
	f (10, slti);
	f (11, sltiu);
	f (12, andi);
	f (13, ori);
	f (14, xori);
	f (15, lui);

	f (32, lb);
	f (33, lh);
	f (34, lwl);
	f (35, lw);
	f (36, lbu);
	f (37, lhu);
	f (38, lwr);

	f (40, sb);
	f (41, sh);
	f (42, swl);
	f (43, sw);
	f (46, swr);
#undef f
    }

    return illegal_instruction;

}

mips_instr_name decode_0_opcode (uint32_t instr)
{
    byte funct = GETBITS (instr, 0, 5);

    LOG (Log::DEBUG, s_logger,
	 "funct = " << (unsigned)funct);
    
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
	f (36, i_and);
	f (37, i_or);
	f (38, i_xor);
	f (39, nor);

	f (42, slt);
	f (43, sltu);
#undef f
    }

    return illegal_instruction;

}

mips_instr_name decode_1_opcode (uint32_t instr)
{
    byte rt = GETBITS (instr, 16, 20);
    LOG (Log::DEBUG, s_logger,
	 "rt = " << (unsigned)rt);

    switch (rt) {
#define f(val,ret) case val: return ret
	f (0, bltz);
	f (1, bgez);
// "likely" variants
// 	f (2, bltzl);
// 	f (3, bgezl);

	f (16, bltzal);
	f (17, bgezal);
#undef f
    }

    return illegal_instruction;
}


const char* register_name (unsigned reg_num)
{
    static const char* regnames[] = {
	"zero",
	"at",
	"v0",
	"v1",
	"a0",
	"a1",
	"a2",
	"a3",
	"t0",
	"t1",
	"t2",
	"t3",
	"t4",
	"t5",
	"t6",
	"t7",
	"s0",
	"s1",
	"s2",
	"s3",
	"s4",
	"s5",
	"s6",
	"s7",
	"t8",
	"t9",
	"k0",
	"k1",
	"gp",
	"sp",
	"fp",
	"ra"
    };


    assert (reg_num < ARRLEN(regnames));

    return regnames[reg_num];
}

CLOSE_NS
