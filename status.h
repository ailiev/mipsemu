// -*- c++ -*-
/*
Copyright (C) 2003-2007, Alexander Iliev <sasho@cs.dartmouth.edu>

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.
* Neither the name of the author nor the names of its contributors may
  be used to endorse or promote products derived from this software without
  specific prior written permission.

This product includes cryptographic software written by Eric Young
(eay@cryptsoft.com)

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "common.h"

#include <signal.h>

#ifndef _MIPS_STATUS_H
#define _MIPS_STATUS_H

MIPS_OPEN_NS

#define ERREXIT(status) { rc = mips::STATUS_ ## status; raise(SIGTRAP); goto error_egress; }

#define CHECKRC(rc) if (rc != mips::STATUS_OK) { raise(SIGTRAP); goto error_egress; }

#define CHECKCALL(f) { rc = f; CHECKRC(rc); }


#define CHECK_ALLOC(ptr, alloc_func) {		\
    ptr = alloc_func;				\
    if (ptr == NULL) ERREXIT(NOMEM);		\
}


enum status_t {
    STATUS_OK = 0,
    STATUS_NOMEM,
    STATUS_ALIGN,
    STATUS_ILLINSTR,
    STATUS_ILLADDR,		/* segmentation fault?? */
    STATUS_ILLSYSCALL,
    STATUS_UNIMPLEMENTED,

    STATUS_MEMFAULT,		// a "physical" memory failure (ie. the RAM
				// (virtual) device failed)

    STATUS_FORMAT,		// binary format problem

    NUM_STATUS
};

const char* status_name (status_t);

CLOSE_NS

#endif // _MIPS_STATUS_H
