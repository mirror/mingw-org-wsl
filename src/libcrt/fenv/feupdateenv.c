/**
 * @file feupdateenv.c
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

/* 7.6.4.4
   The feupdateenv function saves the currently raised exceptions in
   its automatic storage, installs the floating-point environment
   represented by the object pointed to by envp, and then raises the
   saved exceptions. The argument envp shall point to an object
   set by a call to feholdexcept or fegetenv, or equal the macro
   FE_DFL_ENV or an implementation-defined environment macro. */


int feupdateenv (const fenv_t * envp)
{
  unsigned int _fexcept;
  __asm__ ("fnstsw %%ax" : "=a" (_fexcept)); /*save excepts */
  if (__HAS_SSE)
    {
      unsigned int  _csr;
      __asm__ ("stmxcsr %0" : "=m" (_csr));
      _fexcept |= _csr;
    }
  fesetenv (envp); /* install the env  */
  feraiseexcept (_fexcept & FE_ALL_EXCEPT); /* raise the execeptions */
  return 0;
}
