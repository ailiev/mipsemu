#include <bfd.h>

#ifndef _MYBFD_H
#define _MYBFD_H

#ifdef __cplusplus
extern "C" {
#endif

    bfd * open_bfd (const char* filename);

    long get_start_addr (bfd * ibfd);

    void print_section (bfd * ibfd, const char* sectname);
    
    
#ifdef __cplusplus
}
#endif


#endif /* _MYBFD_H */
