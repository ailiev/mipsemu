// -*- c++ -*-
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

#ifndef _MIPS_COMMON_H
#define _MIPS_COMMON_H

// To achieve the sign-extension from 16 bit to 32 bit, first cast to
// 16 signed bits, and only then sign-extend via a cast to 32bit signed.
// this generalizes to any of 8, 16, 32, 64 bits:
#define SIGNEXTEND_WORD(x,from,to) \
    static_cast<int ## to ## _t> (static_cast<int ## from ## _t> (x))

#define GEN_OPEN_NS(name) namespace name {
    
#define MIPS_OPEN_NS namespace mips {

#define OPEN_ANON_NS namespace {
    
#define CLOSE_NS }



#endif // _MIPS_COMMON_H
