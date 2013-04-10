/**
 * @file acosh.c
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
#include <math.h>
#include <errno.h>
#include "fastmath.h"

/* acosh(x) = log (x + sqrt(x * x - 1)) */
double acosh (double x)
{
  if (isnan (x)) 
    return x;

  if (x < 1.0)
    {
      errno = EDOM;
      return nan("");
    }

  if (x > 0x1p32)
    /*  Avoid overflow (and unnecessary calculation when
        sqrt (x * x - 1) == x). GCC optimizes by replacing
        the long double M_LN2 const with a fldln2 insn.  */ 
    return __fast_log (x) + 6.9314718055994530941723E-1L;

  /* Since  x >= 1, the arg to log will always be greater than
     the fyl2xp1 limit (approx 0.29) so just use logl. */ 
  return __fast_log (x + __fast_sqrt((x + 1.0) * (x - 1.0)));
}
