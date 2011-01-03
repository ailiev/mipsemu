/*
 * Simple emulator for a MIPS machine, with a pluggable emulated RAM. Can run
 * executables compiled with gcc against dietlibc and using a few syscalls.
 *
 * Copyright (C) 2003-2007, Alexander Iliev <sasho@cs.dartmouth.edu> and
 * Sean W. Smith <sws@cs.dartmouth.edu>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
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
