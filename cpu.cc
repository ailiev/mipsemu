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

    status_t write_argv (mem_t * mem,
			 int argc, char * argv[],
			 addr_t * o_argc_addr);    
    
}



namespace {
    register_file_t s_regs;
}


namespace {
    Log::logger_t s_logger = Log::makeLogger ("mips-cpu",
					      boost::none, boost::none);
}


// TODO: ignoring envp for now
status_t prepare_cpu (mem_t * mem,
		      int argc, char * argv[])
{
    status_t rc = STATUS_OK;
    
    addr_t argc_addr;
    
    memset (s_regs, 0, sizeof(s_regs));
    
    s_regs[zero]    = 0;		// make this explicit


    CHECKCALL ( write_argv (mem, argc, argv, &argc_addr) );
    
    // and set $sp to point to argc, one word below &argv[0]
    s_regs[sp] = argc_addr;

    // easier to load it up into a hex editor to have a look
    mem_dump (mem, "memory-at-start");

 error_egress:
    return rc;
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
	addr_t pc_val = read_register (pc);
	
	CHECKCALL (mem_read (mem,
			     pc_val,
			     &instr_code));

	memset (&instr, 0, sizeof(instr));
	CHECKCALL (decode_instruction (instr_code,
				       &instr));
#ifdef gcc_4x
	LOG (Log::DEBUG, s_logger,
	     "pc = 0x" << std::hex << pc_val
	     << "; instr code = 0x"
	     << std::hex << std::setw(8) << std::setfill('0') << instr_code
	     << "; decoded: " << instr);
#else
	LOG (Log::DEBUG, s_logger,
	     "pc = " << pc_val
	     << "; instr code = "
	     << instr_code
	     << "; decoded: " << instr);
#endif	

	CHECKCALL (execute_instruction (&instr));
    }

 error_egress:

    return rc;
}
				       

status_t decode_instruction (uint32_t instr, instruction_t * o_instr)
{
    o_instr->code = instr;
    o_instr->name = decode_instr_name (instr);
    get_register_nums (instr, o_instr);
    prepare_inputs (instr, o_instr);

    return STATUS_OK;
}



OPEN_ANON_NS



/// @param o_argc_addr where argc was written, as a MIPS VA (virtual address)
status_t write_argv (mem_t * mem,
		     int argc, char * argv[],
		     addr_t * o_argc_addr)
{
    status_t rc = STATUS_OK;
    
    addr_t vaddr = mem_t::STACK_TOP + 1;
    
    // the vaddress of each argv, as we write them on the stack
    addr_t * argv_vaddrs = new size_t[argc];

    // write the argv values into the top of the stack
    for (int i = argc-1; i >= 0; i--)
    {
	// vaddr now points one byte above where this argv should *end*
	
	size_t len = strlen (argv[i]) + 1; // include the terminating 0-byte

	vaddr -= len;

	argv_vaddrs[i] = vaddr;

	CHECKCALL (
	    mem_write_bytes (mem, vaddr, reinterpret_cast<byte*>(argv[i]), len)
	    );

	LOG (Log::DEBUG, s_logger,
	     "argv[" << i << "] at vaddr " << vaddr);
    }

    // vaddr now points to start of the value argv[0]


    // now write (VM) pointers to all the argv's onto the stack

    // move vaddr down, and word-align it (which may move it a bit more down)
    vaddr -= 4;
    vaddr &= 0xFFFFFFFC;
    
    // write in a NULL for envp
    CHECKCALL ( mem_write (mem, vaddr, 0) );
    vaddr -= 4;
    // write in a NULL address, at the end (top) of the argv values
    CHECKCALL ( mem_write (mem, vaddr, 0) );
    
    // write in the addresses of the argv's we wrote above
    for (int i = argc-1; i >= 0; i--)
    {
	vaddr -= 4;
	CHECKCALL ( mem_write (mem, vaddr, argv_vaddrs[i]) );
	LOG (Log::DEBUG, s_logger,
	     "&argv[" << i << "] at vaddr "
#ifdef gcc_4x
	     << "0x" << std::hex
#endif
	     << vaddr);
    }


    // vaddr now has &argv[0]
    // now write in argc
    vaddr -= 4;
    CHECKCALL ( mem_write (mem, vaddr, argc) );
    
    LOG (Log::DEBUG, s_logger,
	 "argc at vaddr "
#ifdef gcc_40
	 << "0x" << std::hex
#endif
	 << vaddr);

    

 error_egress:
 egress:
    delete [] argv_vaddrs;
    *o_argc_addr = vaddr;
    return rc;
}



status_t execute_instruction (instruction_t * instr)
{
    // if nothing handles the instruction, we'll get an illegal instruction
    // error.
    status_t rc = STATUS_ILLINSTR;

    // for the debugger mostly
    addr_t pc_val;

    pc_val = read_register(pc);
    
    mips_instr_info * info = g_instr_info + instr->name;

    {
	// update the PC, either with the next instruction in line, or with the
	// target of a branch/jump executed last
	addr_t br_target_val = read_register(br_target);
	write_register (pc,
			br_target_val == 0 ?
			read_register(pc) + 4 :
			br_target_val);
	// reset br_target
	write_register (br_target, 0);
    }

    switch (info->instr_type) {
    case mips_instr_info::arith:
	rc = exec_arith (instr);
	break;
    case mips_instr_info::load:
	LOG (Log::DEBUG, s_logger, "memory access: load");
	rc = exec_load (instr);
	break;
    case mips_instr_info::store:
	LOG (Log::DEBUG, s_logger, "memory access: store");
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

	// these cases handled down below
    case mips_instr_info::immediate:
    case mips_instr_info::trap:
    case mips_instr_info::misc:
	break;
    }


    
    // leftovers - none of these match if the above switch matched
    switch (instr->name) {
    case nop:
	rc = STATUS_OK;
	break;
    case syscall:
	rc = exec_syscall ();
	break;
    case lui:
    {
	uint32_t val = (instr->operands[0] << 16) & 0xFFFF0000;
	write_register (instr->destreg, val);
	rc = STATUS_OK;
	break;
    }
    case i_break:
	rc = exec_break (instr);
	break;

    case illegal_instruction:
	ERREXIT(ILLADDR);

    default:
	break;
    }

 error_egress:
    return rc;
}


status_t exec_branch (instruction_t * instr)
{
    // for branch instructions, the target offset is in the last operand
    // (operands[num_ops]

    bool should_branch;

    mips_instr_info * info = g_instr_info + instr->name;
    

    addr_t pc_val = read_register (pc);

    switch (instr->name) {
	// these comparisons are fine unsigned
#define c(name,op)							\
    case name:								\
	should_branch = instr->operands[0] op instr->operands[1]; break

	c (beq,		==);
	c (bne,		!=);

#undef c

	// do a signed comparison (unsigned doesn't work with lt and gt zero
	// comparisons)
#define c(name,op)					\
    case name:						\
	should_branch =					\
	    static_cast<int32_t>(instr->operands[0]) op	\
	    static_cast<int32_t>(instr->operands[1]);	\
	break

	c (bgez,	>=);
	c (bgezal,	>=);
	c (bgtz,	>);
	c (blez,	<=);
	c (bltz,	<);
	c (bltzal,	<);
#undef c
    default:
	break;
    }
	
    if (should_branch) {

	// the offset is always signed, and is in words, not bytes
	// it is the third operand - the first two are the values to compare.
	// NOTE: the offset should be from the delay slot address apparently.
	uint32_t target =
	    pc_val
	    + SIGNEXTEND (instr->operands[2] << 2, 18, 32);

	write_register (br_target, target);
    }

    
    if (info->should_link) {
	// keep in mind that pc now points to the *next* instruction to execute
	// (the delay slot), so after the branch should return to instr. after
	// the PC (delay slot)
	write_register (ra, pc_val+4);
    }

    return STATUS_OK;
}


status_t exec_jump (instruction_t * instr)
{
    mips_instr_info * info = g_instr_info + instr->name;
    
    // the target address is in words, so multiply by 4 to get byte address
    // the high 4 bits come from the PC
    addr_t pc_val = read_register(pc);
    
    uint32_t target;

    if (info->immed_type == mips_instr_info::end26)
    {
	// an immediate value is more complicated: has to be multiplied by 4
	// (word to byte address) and combined with the PC

	// should be 26 bits
	assert (instr->operands[0] <= 0x03FFFFFFU);
    
	target =
	    (pc_val & 0xF0000000U) | 
	    (instr->operands[0] << 2);
    }
    else if (info->immed_type == mips_instr_info::none)
    {
	// just the value gotten from the input register
	target = instr->operands[0];
    }
    else {
	// ERROR!
    }
    
    write_register (br_target, target);

    if (g_instr_info[instr->name].should_link) {
	// keep in mind that pc now points to the *next* instruction to execute
	write_register (ra, pc_val+4);
    }

    return STATUS_OK;
}


status_t exec_load (instruction_t * instr)
{
    status_t rc = STATUS_OK;
//    mips_instr_info * info = g_instr_info + instr->name;
    
    word_t address =
	instr->operands[0] +
	SIGNEXTEND_WORD(instr->operands[1], 16, 32);

    LOG (Log::DEBUG, s_logger,
	 "loading from address "
#ifdef gcc_40
	 << "0x" << std::hex
#endif
	 << address);
    
    uint32_t val;

    // need to issue different kinds of reads for different word sizes.
    switch (instr->name) {
    case lb: case lbu:
	CHECKCALL ( mem_read_bytes (&g_mainmem, address,
				    reinterpret_cast<byte*>(&val), 1) );
	break;
    case lw:
	CHECKCALL ( mem_read (&g_mainmem, address, &val) );
	break;
    case lh: case lhu:
	CHECKCALL ( mem_read_bytes (&g_mainmem, address,
				    reinterpret_cast<byte*>(&val), 2) );
	break;
    default:
	break;
    }


    // more work for sub-word loads
    // WARNING: all the bit-extractions below are for little-endian words only
    switch (instr->name) {
    case lb:
	val = SIGNEXTEND_WORD (GETBITS(val,0,7), 8, 32);
	break;
    case lbu:
	val = GETBITS(val,0,7);
	break;
    case lh:
	val = SIGNEXTEND_WORD (GETBITS(val,0,15), 16, 32);
	break;
    case lhu:
	val = GETBITS(val,0,15);
	break;
    default:
	break;
    }

    write_register (instr->destreg, val);

 error_egress:
    return rc;
}

status_t exec_store (instruction_t * instr)
{
    status_t rc = STATUS_OK;
    
    word_t address =
	instr->operands[0] +	// the rs register
	SIGNEXTEND_WORD (instr->operands[2], 16, 32); // the 16-bit immediate,
						   // signed

    // operands[1] has the rt register value
    switch (instr->name) {
    case sw:
	CHECKCALL ( mem_write (&g_mainmem, address,
			       instr->operands[1]) );
	break;
    case sb:
    {
	byte b = static_cast<byte> (instr->operands[1]);
	CHECKCALL ( mem_write_bytes (&g_mainmem, address, &b, 1) );
	break;
    }
    case sh:
    {
	uint16_t h = static_cast<uint16_t> (instr->operands[1]);
	CHECKCALL ( mem_write_bytes (&g_mainmem, address,
				     reinterpret_cast<byte*>(&h), 2) );
	break;
    }
    default:
	break;
    }

 error_egress:
    return rc;
}


status_t exec_move (instruction_t * instr)
{
    status_t rc = STATUS_OK;
    
    register_id src, dest;		// register numbers
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
	if (info->instr_type == mips_instr_info::branch &&
	    info->num_ops == 1)
	{
	    // these branch instructions have *two* immediate params - the zero
	    // and the offset. the zero offset should go at the end, so:
	    opidx ++;
	}
	
	// the idea with the casting is to do sign-extending if signed and
	// zero-extending if unsigned.
	o_instr->operands[opidx] =
	    info->instr_type == mips_instr_info::arith &&
	    info->is_signed ?
	    SIGNEXTEND_WORD (GETBITS(instr,0,15), 16, 32) :
	    (GETBITS(instr,0,15));

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

    LOG (Log::DEBUG, s_logger,
	 "operand vals: "
#ifdef gcc_40
	 << "(hex) " << std::hex
#endif
	 << o_instr->operands[0] << ", "
	 << o_instr->operands[1] << ", "
	 << o_instr->operands[2]);
	
}


// fill in the three register fields of the instruction_t
void get_register_nums (uint32_t instr, instruction_t * o_instr)
{
    mips_instr_info * info = g_instr_info + o_instr->name;
    type_R_syntax fields;

    assert (info->name == o_instr->name);

    // set up a type_R_syntax to access the bit-fields inside 'instr' easily.
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

    // the shift variable instructions have their registers in the 'wrong' order
    // - first arg is in rt and second is in rs, and order matters a lot
    switch (info->name) {
    case sllv:
    case srlv:
    case srav:
	std::swap (o_instr->inregs[0], o_instr->inregs[1]);
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

//     LOG (Log::DUMP, s_logger,
// 	 "opcode = 0x" << std::hex << unsigned(opcode));
    
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
//	f (34, lwl);
	f (35, lw);
	f (36, lbu);
	f (37, lhu);
//	f (38, lwr);

	f (40, sb);
	f (41, sh);
//	f (42, swl);
	f (43, sw);
//	f (46, swr);
#undef f
    }

    return illegal_instruction;

}

mips_instr_name decode_0_opcode (uint32_t instr)
{
    byte funct = GETBITS (instr, 0, 5);

//     LOG (Log::DUMP, s_logger,
// 	 "funct = " << (unsigned)funct);
    
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


const char* register_name (register_id reg_num)
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

	{ pc, "pc" },
	{ br_target, "br_target" },
	{ lo, "lo" },			
	{ hi, "hi" }
    };


    // static checks, should incorporate into build process somehow, not into
    // every call
    assert (ARRLEN(reg_infos) == NUMREGS);
    assert (reg_infos[reg_num].id == reg_num);
    
    return reg_infos[reg_num].name;
}


uint32_t read_register (register_id regid)
{
//    assert (regid < ARRLEN(s_regs));
    return s_regs[regid];
}

void write_register (register_id regid, uint32_t val)
{
//    assert (regnum < ARRLEN(s_regs));
    s_regs[regid] = val;
}

// std::ostream& dump_registers (std::ostream& os)
// {
//     for (int i=0; i < 8; i++) {
// 	for (int j=0; j < 4; j++) {
// 	    register_id id = i + (8*j);
// 	    os << register_name(id) << " = "
// 	       << std::hex << std:: read_register(id) << " ";
	    
// 		}
CLOSE_NS
