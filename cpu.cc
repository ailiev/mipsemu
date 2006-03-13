#include "cpu.h"

#include "instructions.h"
#include "memory.h"
#include "alu.h"
#include "os.h"

#include "status.h"
#include "common.h"

#include <pir/common/utils-types.h>
#include <pir/common/utils-macros.h>
#include <pir/common/logging.h>

#include <stdint.h>


MIPS_OPEN_NS


namespace {
    status_t execute_instruction (instruction_t * instr);
    
    mips_instr_name decode_instr_name (uint32_t instr);
    
    status_t exec_branch (instruction_t * instr);
    status_t exec_jump (instruction_t * instr);
    status_t exec_load (instruction_t * instr);
    status_t exec_store (instruction_t * instr);
    status_t exec_move (instruction_t * instr);
    status_t exec_break (const instruction_t * instr);
    
    void prepare_inputs (uint32_t instr, instruction_t * o_instr);
    
    void 	    get_register_nums (uint32_t instr, instruction_t * o_instr);
    
    mips_instr_name decode_0_opcode (uint32_t instr);
    mips_instr_name decode_1_opcode (uint32_t instr);
    
}



namespace {
    register_file_t s_regs;
}


namespace {
    Log::logger_t s_logger = Log::makeLogger ("mips-cpu",
					      boost::none, boost::none);
}


void prepare_cpu ()
{
    memset (s_regs, 0, sizeof(s_regs));
    
    s_regs[zero]    = 0;		// make this explicit

    // stack pointer, pointing the topmost *word* on the stack
    s_regs[sp]	    = mem_t::STACK_TOP - (sizeof(word_t)-1);

    // TODO: could set up an argv pointer on the stack too.
    // not sure yet how argc is done
}



status_t run_process (mem_t * mem,
		      addr_t start_addr)
{
    status_t rc = STATUS_OK;
    
    write_register (pc, start_addr);
    
    // presumably an exit syscall will exit this process too.
    while (true)
    {
	uint32_t instr_code;
	instruction_t instr;
	
	CHECKCALL (mem_read (mem,
			     read_register (pc),
			     &instr_code));

	CHECKCALL (decode_instruction (instr_code,
				       &instr));
	LOG (Log::DEBUG, s_logger,
	     "instruction name = " << instr.name);

	CHECKCALL (execute_instruction (&instr));
    }

 error_egress:

    return rc;
}
				       

status_t decode_instruction (uint32_t instr, instruction_t * o_instr)
{
    o_instr->name = decode_instr_name (instr);
    get_register_nums (instr, o_instr);
    prepare_inputs (instr, o_instr);

    return STATUS_OK;
}



OPEN_ANON_NS


status_t execute_instruction (instruction_t * instr)
{
    status_t rc = STATUS_OK;
    
    mips_instr_info * info = g_instr_info + instr->name;

    switch (info->instr_type) {
    case mips_instr_info::arith:
	rc = exec_arith (instr);
	break;
    case mips_instr_info::load:
	rc = exec_load (instr);
	break;
    case mips_instr_info::store:
	rc = exec_store (instr);
	break;
    case mips_instr_info::branch:
	rc = exec_branch (instr);
	break;
    case mips_instr_info::jump:
	rc = exec_jump (instr);
	break;
    case mips_instr_info::move:
	rc = exec_move (instr);
	break;
    default:
	break;
    }

    if (rc != STATUS_OK) {
	return rc;
    }

    
    // leftovers
    switch (instr->name) {
    case nop:
	break;
    case syscall:
	rc = exec_syscall ();
	break;
    case lui:
    {
	uint32_t val = (instr->operands[0] << 16) & 0xFFFF0000;
	write_register (instr->destreg, val);
	break;
    }
    case i_break:
	rc = exec_break (instr);
	break;
    default:
	break;
    }

    if (rc != STATUS_OK) {
	return rc;
    }

    

    // jumps and branches always update the pc, even for a not-taken branch.
    // Also, need to check if a delayed branch should now be taken.
    
    if (info->instr_type != mips_instr_info::branch &&
	info->instr_type != mips_instr_info::jump)
    {
	uint32_t branch_target = read_register (br_target);
	if (branch_target > 0) {
	    // we just executed a delay slot instruction, and now we branch to
	    // the target.
	    write_register (pc, branch_target);

	    // reset that register
	    write_register (br_target, 0);
	}
	else {
	    // next please...
	    write_register (pc, read_register(pc) + 4);
	}
    }

    return rc;
}


status_t exec_branch (instruction_t * instr)
{
    // for branch instructions, the target offset is in the last operand
    // (operands[num_ops]

    bool should_branch;

    addr_t pc_val = read_register (pc);

    switch (instr->name) {
#define c(name,op)							\
    case name:								\
	should_branch = instr->operands[0] op instr->operands[1]; break

	c (beq,		==);
	c (bgez,	>=);
	c (bgezal,	>=);
	c (bgtz,	>);
	c (blez,	<=);
	c (bltz,	<);
	c (bltzal,	<);
	c (bne,		!=);
#undef c
    default:
	break;
    }
	
    if (should_branch) {

	byte num_ops = g_instr_info[instr->name].num_ops;
	
	uint32_t target =
	    read_register (pc)
	    + static_cast<int32_t> (instr->operands[num_ops] << 2);
	// the offset is always signed (so we get sign-extension through the
	// cast), and is in words, not bytes

	write_register (br_target, target);
    }
    else {
	write_register (pc, pc_val + 4);
    }


    
    if (g_instr_info[instr->name].should_link) {
	write_register (ra, pc_val+8);
    }

    return STATUS_OK;
}


status_t exec_jump (instruction_t * instr)
{
    // the target address is in words, so multiply by 4 to get byte address
    // the high 4 bits come from the PC
    addr_t pc_val = read_register(pc);
    
    // should be 26 bits
    assert (instr->operands[0] <= 0x03FFFFFFU);
    
    uint32_t target =
	(pc_val & 0xF0000000U) | 
	(instr->operands[0] << 2);

    write_register (br_target, target);

    if (g_instr_info[instr->name].should_link) {
	write_register (ra, pc_val+8);
    }

    return STATUS_OK;
}


status_t exec_load (instruction_t * instr)
{
    status_t rc = STATUS_OK;
    
    word_t address =
	instr->operands[0] +
	static_cast<int32_t> (instr->operands[1]);

    uint32_t val;

    CHECKCALL ( mem_read (&g_mainmem, address, &val) );

    write_register (instr->destreg, val);

 error_egress:
    return rc;
}

status_t exec_store (instruction_t * instr)
{
    status_t rc = STATUS_OK;
    
    word_t address =
	instr->operands[0] +	// the rs register
	static_cast<int32_t> (instr->operands[2]); // the 16-bit immediate,
						   // signed

    // operands[1] has the rt register value
    CHECKCALL ( mem_write (&g_mainmem, address,
			   instr->operands[1]) );

 error_egress:
    return rc;
}


status_t exec_move (instruction_t * instr)
{
    status_t rc = STATUS_OK;
    
    byte src, dest;		// register numbers
    bool should_move = true;
    
    switch (instr->name) {
    case mfc0:
	ERREXIT(UNIMPLEMENTED);
	break;

    case mflo:
	src = lo;
	dest = instr->destreg;
	break;
    case mfhi:
	src = hi;
	dest = instr->destreg;
	break;
    case mtlo:
	src = instr->inregs[0];
	dest = lo;
	break;
    case mthi:
	src = instr->inregs[0];
	dest = hi;
	break;

    case movn:
	should_move = instr->operands[1] != 0;
	src = instr->inregs[0];
	dest = instr->destreg;
	break;
    case movz:
	should_move = instr->operands[1] == 0;
	src = instr->inregs[0];
	dest = instr->destreg;
	break;
	
    default:
	break;
    }

    if (should_move)
    {
	write_register (dest, read_register (src));
    }

 error_egress:
    return rc;
}


status_t exec_break (const instruction_t * instr)
{
    LOG (Log::DEBUG, s_logger,
	 "exec_break " << instr->operands[0]);
    return STATUS_OK;
}

void prepare_inputs (uint32_t instr, instruction_t * o_instr)
{
    mips_instr_info * info = g_instr_info + o_instr->name;

    // the input registers, however many there are
    switch (info->num_ops) {
    case 2:
	o_instr->operands[1] = read_register (o_instr->inregs[1]);
    case 1:
	o_instr->operands[0] = read_register (o_instr->inregs[0]);
    }

    //
    // immediates:
    //
    
    // which operand is this (zero-based of course)
    unsigned opidx = info->num_ops;
    
    switch (info->immed_type) {

    case mips_instr_info::end16:
	// the idea with the casting is to do sign-extending if signed and
	// zero-extending if unsigned.
	o_instr->operands[opidx] =
	    info->instr_type == mips_instr_info::arith &&
	    info->is_signed ?
	    static_cast<int32_t>  (GETBITS(instr,0,15)) :
	    static_cast<uint32_t> (GETBITS(instr,0,15));
	break;

    case mips_instr_info::end26:
	// a jump instruction
	o_instr->operands[opidx] = GETBITS(instr,0,25);
	break;
    case mips_instr_info::breakcode:
	// raise instruction with this code
	o_instr->operands[opidx] = GETBITS(instr,6,25);
	break;
    case mips_instr_info::shift:
	o_instr->operands[opidx] = GETBITS(instr,6,10);
	break;
    case mips_instr_info::none:
	break;

    }

    // put in a zero for conditional branches which compare a register to zero.
    if (info->instr_type == mips_instr_info::branch &&
	info->num_ops == 1)
    {
	o_instr->operands[1] = 0;
    }
	
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
	o_instr->inregs[1] = fields.rt;
	// fall-through needed here
    case 1:
	o_instr->inregs[0] = fields.rs;
    }

    // the shift instructions cause trouble here: they ignore rs and get their
    // single input from rt
    switch (info->name) {
    case sll:
    case srl:
    case sra:
	o_instr->inregs[0] = fields.rt;
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
	    o_instr->destreg = fields.rt;
	    break;
	default:
	    o_instr->destreg = fields.rd;
	}
    }
	    
}


mips_instr_name decode_instr_name (uint32_t instr)
{
    // if 0 is not handled specially, it will be decoded (seemingly correctly)
    // as a 'sll'. Since nop is quite common, use a special test up front.
    if (instr == 0U) return nop;
    
    byte opcode = GETBITS (instr, 26, 31);

    LOG (Log::DUMP, s_logger,
	 "opcode = 0x" << std::hex << unsigned(opcode));
    
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


CLOSE_NS			// anonymous namespace


const char* register_name (unsigned reg_num)
{
    struct reg_info_t {
	register_id id;
	const char * name;
    };
    
    static reg_info_t reg_infos[] = {
	{ zero, "zero" },
	{ at, "at" },
	{ v0, "v0" },
	{ v1, "v1" },
	{ a0, "a0" },
	{ a1, "a1" },
	{ a2, "a2" },
	{ a3, "a3" },
	{ t0, "t0" },
	{ t1, "t1" },
	{ t2, "t2" },
	{ t3, "t3" },
	{ t4, "t4" },
	{ t5, "t5" },
	{ t6, "t6" },
	{ t7, "t7" },
	{ s0, "s0" },
	{ s1, "s1" },
	{ s2, "s2" },
	{ s3, "s3" },
	{ s4, "s4" },
	{ s5, "s5" },
	{ s6, "s6" },
	{ s7, "s7" },
	{ t8, "t8" },
	{ t9, "t9" },
	{ k0, "k0" },
	{ k1, "k1" },
	{ gp, "gp" },
	{ sp, "sp" },
	{ fp, "fp" },
	{ ra, "ra" },

	{ pc, "pc" }
    };


    assert (reg_num < NUMREGS);
    assert (reg_infos[reg_num].id == reg_num);
    
    return reg_infos[reg_num].name;
}


uint32_t read_register (byte regnum)
{
    assert (regnum < ARRLEN(s_regs));
    return s_regs[regnum];
}

void write_register (byte regnum, uint32_t val)
{
    assert (regnum < ARRLEN(s_regs));
    s_regs[regnum] = val;
}


CLOSE_NS
