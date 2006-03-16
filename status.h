// -*- c++ -*-

#include "common.h"

#include <signal.h>

#ifndef _MIPS_STATUS_H
#define _MIPS_STATUS_H

MIPS_OPEN_NS

#define ERREXIT(status) { rc = STATUS_ ## status; raise(SIGTRAP); goto error_egress; }

#define CHECKRC(rc) if (rc != STATUS_OK) { raise(SIGTRAP); goto error_egress; }

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

    NUM_STATUS
};

const char* status_name (status_t);

CLOSE_NS

#endif // _MIPS_STATUS_H
