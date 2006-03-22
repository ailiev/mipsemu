// -*- c++ -*-

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
