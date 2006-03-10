#include "common.h"

MIPS_OPEN_NS

#define ERREXIT(status) { rc = STATUS_ ## status; goto error_egress; }

#define CHECKCALL(f) rc = f; if (rc != STATUS_OK) goto error_egress


enum status_t {
    STATUS_OK = 0,
    STATUS_NOMEM,
    STATUS_ALIGN,
    STATUS_ILLADDR,		/* segmentation fault?? */
    STATUS_ILLSYSCALL,

    NUM_STATUS
};

CLOSE_NS

    
