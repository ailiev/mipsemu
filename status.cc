/*
 * Simple emulator for a MIPS machine, with a pluggable emulated RAM. Can run
 * executables compiled with gcc against dietlibc and using a few syscalls.
 *
 * Copyright (C) 2003-2007, Alexander Iliev <sasho@cs.dartmouth.edu> and
 * Sean W. Smith <sws@cs.dartmouth.edu>
 *
 * All rights reserved.
 *
 * This code is released under a BSD license.
 * Please see LICENSE.txt for the full license and disclaimers.
 *
*/


#include "status.h"

#include <assert.h>

MIPS_OPEN_NS


struct status_name_t {
    status_t id;
    const char * name;
};

namespace {
    status_name_t s_names[NUM_STATUS] = {
	{ STATUS_OK, "STATUS_OK" },
	{ STATUS_NOMEM, "STATUS_NOMEM" },
	{ STATUS_ALIGN, "STATUS_ALIGN" },
	{ STATUS_ILLINSTR, "STATUS_ILLINSTR" },
	{ STATUS_ILLADDR, "STATUS_ILLADDR" },		/* segmentation fault?? */
	{ STATUS_ILLSYSCALL, "STATUS_ILLSYSCALL" },
	{ STATUS_UNIMPLEMENTED, "STATUS_UNIMPLEMENTED" }
	
    };
}

const char* status_name (status_t id)
{
    assert (id < NUM_STATUS);
    assert (s_names[id].id == id);
    
    return s_names[id].name;
}

CLOSE_NS
