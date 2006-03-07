#include "instructions.h"

MIPS_OPEN_NS


struct mips_instr_info {

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

    unsigned char num_ops;

    bool should_link;

};



mips_instr_info instr_info [NUM_INSTRS];


void init_mips_instr_info ()
{
#define MKINFO(v1, v2, v3, v4) { mips_instr_info::v1,	\
			         mips_instr_info::v2,	\
			         mips_instr_info::v3,	\
                                 mips_instr_info::v4 }

    mips_instr_info default_info = MKINFO (arith, none, two, false);

#define SETINFO_SMALL(instr, info) instr_info[instr] = info
    
// set up the link flag separately
#define SETINFO(instr, v1, v2, v3, false)		\
    {							\
        mips_instr_info __kuku = MKINFO (v1,v2,v3);	\
        instr_info[instr] = __kuku;			\
    }

	
    SETINFO (add,	arith,	    none,   2);
    SETINFO (addi,	arith,	    end16,  2);
    SETINFO (addiu,	arith,	    end16,  2);
    SETINFO (addu,	arith,	    none,   2);
    SETINFO (i_and,	arith,	    none,   2);
    SETINFO (andi,	arith,	    end16,  2);
    SETINFO (beq,	branch,	    end16,  2);
    SETINFO (bgez,	branch,	    end16,  1);
    SETINFO (bgezal,	branch,	    end16,  1);
    SETINFO (bgtz,	branch,	    end16,  1);
    SETINFO (blez,	branch,	    end16,  1);
    SETINFO (bltz,	branch,	    end16,  1);
    SETINFO (bltzal,	branch,	    end16,  1);
    SETINFO (bne,	branch,	    end16,  2);
    SETINFO (i_break,	trap,	    breakcode, 0);
    SETINFO (div,	arithm,	    none,   2);
    SETINFO (divu,	arith,	    none,   2);
    SETINFO (j,		jump,	    end26,  0);
    SETINFO (jal,	jump,	    end26,  0);
    SETINFO (jalr,	jump,	    none,   1);
    SETINFO (jr,	jump,	    none,   1);
    SETINFO (lb,	mem,	    end16,  1);
    SETINFO (lbu,	load,	    end16,  1);
    SETINFO (lh,	load,	    end16,  1);
    SETINFO (lhu,	load,	    end16,  1);
    SETINFO (lui,	immediate,  end16,  0);
    SETINFO (lw,	load,	    end16,  1);
    SETINFO (lwl,	load,	    end16,  1);
    SETINFO (lwr,	load,	    end16,  1);
    SETINFO (mfc0,	move,	    none,   0);
    SETINFO (mflo,	move,	    none,   0);
    SETINFO (mthi,	move,	    none,   0);
    SETINFO (mtlo,	move,	    none,   0);
    SETINFO (mult,	arith,	    none,   2);
    SETINFO (multu,	arith,	    none,   0);
    SETINFO (nop,	misc,	    none,   0);
    SETINFO (nor,	arith,	    none,   2);
    SETINFO (i_or,	arith,	    none,   2);
    SETINFO (ori,	arith,	    end16,  2);
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
    SETINFO (swl, 	store,	    end16,  2);
    SETINFO (swr, 	store,	    end16,  2);
    SETINFO (syscall,	misc,	    none,   1);
    SETINFO (i_xor,	arith,	    none,   2);
    SETINFO (xori,	arith,	    end16,  1);

    // set up which instructions link a return address in $ra
    mips_instr linking_instrs[] = { bgezal, jal, jalr };
    for (unsigned i=0; i < ARRLEN(linking_instrs); i++)
    {
	linking_instrs[i].should_link = true;
    }

};


CLOSE_NS
