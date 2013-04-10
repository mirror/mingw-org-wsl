/**
 * @file fesetexceptflag.c
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
#include "cpu_features.h"

/* 7.6.2.4
   The fesetexceptflag function sets the complete status for those
   exception flags indicated by the argument excepts, according to the
   representation in the object pointed to by flagp. The value of
   *flagp shall have been set by a previous call to fegetexceptflag
   whose second argument represented at least those exceptions
   represented by the argument excepts. This function does not raise
   exceptions, but only sets the state of the flags. */ 

int fesetexceptflag (const fexcept_t * flagp, int excepts) 
{ 
  fenv_t _env;

  excepts &= FE_ALL_EXCEPT;
  __asm__ volatile ("fnstenv %0;" : "=m" (_env));
  _env.__status_word &= ~excepts;
  _env.__status_word |= (*flagp & excepts);
  __asm__ volatile ("fldenv %0;" : : "m" (_env));

  if (__HAS_SSE)
   {
      unsigned int _csr;
      __asm__ __volatile__("stmxcsr %0" : "=m" (_csr));
      _csr &= ~excepts;
      _csr |= *flagp & excepts;
      __asm__ volatile ("ldmxcsr %0" : : "m" (_csr));
   }

  return 0;
}
