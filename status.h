// -*- c++ -*-

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
