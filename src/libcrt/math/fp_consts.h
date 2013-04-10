/**
 * @file fp_consts.h
 * Copyright 2012, 2013 MinGW.org project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#ifndef _FP_CONSTS_H
#define _FP_CONSTS_H

/*
According to IEEE 754 a QNaN has exponent bits of all 1 values and
initial significand bit of 1.  A SNaN has has an exponent of all 1
values and initial significand bit of 0 (with one or more other
significand bits of 1). An Inf has significand of 0 and
exponent of all 1 values. A denormal value has all exponent bits of 0.

The following does _not_ follow those rules, but uses values
equal to those exported from MS C++ runtime lib, msvcprt.dll
for float and double. MSVC however, does not have long doubles.
*/


#define __DOUBLE_INF_REP { 0, 0, 0, 0x7ff0 }
#define __DOUBLE_QNAN_REP { 0, 0, 0, 0xfff8 }  /* { 0, 0, 0, 0x7ff8 }  */
#define __DOUBLE_SNAN_REP { 0, 0, 0, 0xfff0 }  /* { 1, 0, 0, 0x7ff0 }  */
#define __DOUBLE_DENORM_REP {1, 0, 0, 0}

#define D_NAN_MASK 0x7ff0000000000000LL /* this will mask NaN's and Inf's */

#define __FLOAT_INF_REP { 0, 0x7f80 }
#define __FLOAT_QNAN_REP { 0, 0xffc0 }  /* { 0, 0x7fc0 }  */
#define __FLOAT_SNAN_REP { 0, 0xff80 }  /* { 1, 0x7f80 }  */
#define __FLOAT_DENORM_REP {1,0}

#define F_NAN_MASK 0x7f800000

/*
   This assumes no implicit (hidden) bit in extended mode.
   Padded to 96 bits
 */
#define __LONG_DOUBLE_INF_REP { 0, 0, 0, 0x8000, 0x7fff, 0 }
#define __LONG_DOUBLE_QNAN_REP { 0, 0, 0, 0xc000, 0xffff, 0 } 
#define __LONG_DOUBLE_SNAN_REP { 0, 0, 0, 0x8000, 0xffff, 0 }
#define __LONG_DOUBLE_DENORM_REP {1, 0, 0, 0, 0, 0}

union _ieee_rep
{
  unsigned short rep[6];
  float float_val;
  double double_val;
  long double ldouble_val;
} ;

#endif
