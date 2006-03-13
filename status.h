// -*- c++ -*-

#include "common.h"

#ifndef _MIPS_STATUS_H
#define _MIPS_STATUS_H

MIPS_OPEN_NS

#define ERREXIT(status) { rc = STATUS_ ## status; goto error_egress; }

#define CHECKCALL(f) { rc = f; if (rc != STATUS_OK) goto error_egress; }


enum status_t {
    STATUS_OK = 0,
    STATUS_NOMEM,
    STATUS_ALIGN,
    STATUS_ILLADDR,		/* segmentation fault?? */
    STATUS_ILLSYSCALL,
    STATUS_UNIMPLEMENTED,

    NUM_STATUS
};

CLOSE_NS

#endif // _MIPS_STATUS_H