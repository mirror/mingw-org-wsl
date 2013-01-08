/**
 * @file asinh.c
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

 /* asinh(x) = copysign(log(fabs(x) + sqrt(x * x + 1.0)), x) */
double asinh(double x)
{
  double z;
  if (!isfinite (x))
    return x;
  z = fabs (x);

  /* Avoid setting FPU underflow exception flag in x * x. */
#if 0
  if ( z < 0x1p-32)
    return x;
#endif

  /* Use log1p to avoid cancellation with small x. Put
     x * x in denom, so overflow is harmless. 
     asinh(x) = log1p (x + sqrt (x * x + 1.0) - 1.0)
              = log1p (x + x * x / (sqrt (x * x + 1.0) + 1.0))  */

  z = __fast_log1p (z + z * z / (__fast_sqrt (z * z + 1.0) + 1.0));

  return ( x > 0.0 ? z : -z);
}

