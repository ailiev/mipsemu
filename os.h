// -*- c++ -*-
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

#include "common.h"
#include "status.h"


#ifndef _SYSCALL_H
#define _SYSCALL_H

MIPS_OPEN_NS

status_t exec_syscall ();

CLOSE_NS

#endif /* _SYSCALL_H_H */
