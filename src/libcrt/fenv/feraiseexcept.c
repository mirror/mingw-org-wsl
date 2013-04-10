/**
 * @file feraiseexcept.c
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
#include <fenv.h> 

/* 7.6.2.3
   The feraiseexcept function raises the supported exceptions
   represented by its argument The order in which these exceptions
   are raised is unspecified, except as stated in F.7.6.
   Whether the feraiseexcept function additionally raises
   the inexact exception whenever it raises the overflow
   or underflow exception is implementation-defined. */

int feraiseexcept (int excepts)
{
  fenv_t _env;
  __asm__ volatile ("fnstenv %0;" : "=m" (_env));
  _env.__status_word |= excepts & FE_ALL_EXCEPT;
  __asm__ volatile ("fldenv %0;"
		    "fwait;" : : "m" (_env));
  return 0;
}
