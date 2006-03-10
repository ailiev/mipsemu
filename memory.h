// -*- c++ -*-

#include "status.h"
#include "common.h"

#include <pir/common/utils-types.h>


MIPS_OPEN_NS


typedef uint32_t addr_t;

typedef uint32_t word_t;
typedef uint16_t hw_t;		// half-word
typedef uint64_t dword_t;	// double word



struct mem_t {

    static const addr_t TEXT_START = 0x00400000;
    static const addr_t DATA_START = 0x10000000;
    static const addr_t STACK_TOP  = 0x7FFFFFFF;

    // this bit is not set in text section, and is set in the data section
    // (unconditionally, unless text is bigger than about 264M, in which case
    // data section needs to be moved from its traditional start location)
    static const byte DATA_DETECT_BIT = 28;

    // this bit is not set in the data section (unless heap goes above
    // 0x3FFFFFFF), and is set in the stack (unless stack goes below
    // 0x3FFFFFFF). This leaves 1G for stack and about 800M for data (static +
    // heap). should be enough!
    static const byte STACK_DETECT_BIT = 30;

    // not set for all valid addresses, set for kernel addresses
    static const byte KERNEL_DETECT_BIT = 31;

    byte * mem;
    size_t size;

    size_t textsize;
};


status_t mem_init (mem_t * mem,
		   size_t size,
		   size_t textsize);

status_t mem_write (mem_t * mem,
		    addr_t full_addr, word_t val);


status_t convert_addr (const mem_t * mem,
		       addr_t full_addr,
		       addr_t * o_addr);
