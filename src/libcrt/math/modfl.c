/**
 * @file modfl.c
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
#include <math.h>
#include <errno.h>
#define FE_ROUNDING_MASK \
  (FE_TONEAREST | FE_DOWNWARD | FE_UPWARD | FE_TOWARDZERO)

long double
modfl (long double value, long double* iptr)
{
  long double int_part;
  unsigned short saved_cw;
  unsigned short tmp_cw;
  /* truncate */ 
  asm ("fnstcw %0;" : "=m" (saved_cw)); /* save control word */
  tmp_cw = (saved_cw & ~FE_ROUNDING_MASK) | FE_TOWARDZERO;
  asm ("fldcw %0;" : : "m" (tmp_cw));
  asm ("frndint;" : "=t" (int_part) : "0" (value)); /* round */
  asm ("fldcw %0;" : : "m" (saved_cw)); /* restore saved cw */
  if (iptr)
    *iptr = int_part;
  return (isinf (value) ?  0.0L : value - int_part);
}
