#include "cpu.h"
#include "instructions.h"

#include <iostream>

using namespace std;


int main (int argc, char *argv[])
{
    mips::instruction_t inst;

    uint32_t inst_code;

    mips::init_instr_info ();    

    while (cin >> hex >> inst_code)
    {
	memset (&inst, 0, sizeof(inst));
	
	clog << "Binary instruction: " << hex << inst_code << endl;

	mips::decode_instruction (inst_code, &inst);

	// print the registers
	mips::mips_instr_info * info = mips::g_instr_info + inst.name;
	cout << inst.name;
	if (info->has_out) {
	    cout << " " << mips::register_name (inst.destreg);
	}
	if (info->num_ops > 0) {
	    cout << ", " << mips::register_name (inst.inregs[0]);
	}
	if (info->num_ops > 1) {
	    cout << ", " << mips::register_name (inst.inregs[1]);
	}
	cout << endl;
    }
}
