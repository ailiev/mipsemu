// -*- c++ -*-

#ifndef _MIPS_COMMON_H
#define _MIPS_COMMON_H

// To achieve the sign-extension from 16 bit to 32 bit, first cast to
// 16 signed bits, and only then sign-extend via a cast to 32bit signed.
#define SIGNEXTEND_16TO32(x) static_cast<int32_t>(static_cast<int16_t>(x))

#define MIPS_OPEN_NS namespace mips {

#define OPEN_ANON_NS namespace {
    
#define CLOSE_NS }



#endif // _MIPS_COMMON_H
