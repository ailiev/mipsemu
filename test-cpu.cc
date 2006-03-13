#include "cpu.h"
#include "instructions.h"

#include <iostream>


// how to get a list of all the binary instructions in an executable:
// mipsel-linux-objdump -d simple | pcregrep '^\s+(\d|[a-f])+:' | awk '{print $2}'

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

	cout << inst << endl;
    }
}
