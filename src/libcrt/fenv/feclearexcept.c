/**
 * @file feclearexcept.c
 * @copy 2012 MinGW.org project
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

/* 7.6.2.1
   The feclearexcept function clears the supported exceptions
   represented by its argument.  */

int feclearexcept (int excepts)
{
  fenv_t _env;
  excepts &= FE_ALL_EXCEPT;
  __asm__ volatile ("fnstenv %0;" : "=m" (_env)); /* get the env */
  _env.__status_word &= ~excepts; /* clear the except */
  __asm__ volatile ("fldenv %0;" :: "m" (_env)); /*set the env */

  if (__HAS_SSE)
    {
       unsigned _csr;
       __asm__ volatile("stmxcsr %0" : "=m" (_csr)); /* get the register */
       _csr &= ~excepts; /* clear the except */
       __asm__ volatile("ldmxcsr %0" : : "m" (_csr)); /* set the register */
    }
  return 0;
}
