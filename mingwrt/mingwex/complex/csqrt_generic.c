/*
 * csqrt_generic.c
 *
 * $Id$
 *
 * Compute the principal square root of a complex number; this provides
 * a generic implementation for csqrt(), csqrtf(), and csqrtl().
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * This is an adaptation of an original contribution by Danny Smith
 * Copyright (C) 2003, 2014, 2015, MinGW.org Project
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, this permission notice, and the following
 * disclaimer shall be included in all copies or substantial portions of
 * the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OF OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 *
 * This is a generic implementation for all of the csqrt(), csqrtl(),
 * and csqrth() functions; each is to be compiled separately, i.e.
 *
 *   gcc -D FUNCTION=csqrt  -o csqrt.o  csqrt_generic.c
 *   gcc -D FUNCTION=csqrtl -o csqrtl.o csqrt_generic.c
 *   gcc -D FUNCTION=csqrtf -o csqrtf.o csqrt_generic.c
 *
 */
#include <math.h>
#include <complex.h>

#ifndef FUNCTION
/* If user neglected to specify it, the default compilation is for
 * the csqrt() function.
 */
# define FUNCTION csqrt
#endif

#define argtype_csqrt  double
#define argtype_csqrtl long double
#define argtype_csqrtf float

#define PASTE(PREFIX,SUFFIX)   PREFIX##SUFFIX
#define mapname(PREFIX,SUFFIX) PASTE(PREFIX,SUFFIX)

#define ARGTYPE(FUNCTION) PASTE(argtype_,FUNCTION)
#define ARGCAST(VALUE)    mapname(argcast_,FUNCTION)(VALUE)

#define argcast_csqrt(VALUE)  VALUE
#define argcast_csqrtl(VALUE) PASTE(VALUE,L)
#define argcast_csqrtf(VALUE) PASTE(VALUE,F)

#define mapfunc(NAME) mapname(mapfunc_,FUNCTION)(NAME)

#define mapfunc_csqrt(NAME)  NAME
#define mapfunc_csqrtl(NAME) PASTE(NAME,l)
#define mapfunc_csqrtf(NAME) PASTE(NAME,f)

/* Prefer fast versions of mathematical functions.
 */
#include "../math/fastmath.h"

#define log    __fast_log
#define log1p  __fast_log1p
#define sqrt   __fast_sqrt

/* Define the generic function implementation.
 */
ARGTYPE(FUNCTION) complex FUNCTION( ARGTYPE(FUNCTION) complex Z )
{
  /* Compute the principal square root of complex number Z, which we
   * consider to be represented in the cartesian form, Z = x + iy
   */
  ARGTYPE(FUNCTION) x = __real__ Z;
  ARGTYPE(FUNCTION) y = __imag__ Z;

  /* Now, we may recompute the value of Z, such that it will become
   * the principal square root of x + iy; let's call it a + ib.  Thus,
   * in the general case, we may state that:
   *
   *   (a + ib) * (a + ib) = x + iy			(1)
   *
   * which may be expanded to:
   *
   *   a^2 + i^2 * b^2 + 2 * a * b * i = x + iy 	(2)
   *
   * or, since i^2 == -1, (by definition):
   *
   *   a^2 - b^2 + 2abi = x + iy			(3)
   *
   * Comparing real and imaginary parts of LHS and RHS, we may
   * deduce the following pair of simultaneous equations:
   *
   *   a^2 - b^2 = x					(4)
   *   2ab = y						(5)
   *
   * Rearranging (5), and substituting to eliminate b from (4),
   * we deduce that:
   *
   *   a^2 - (y / 2a)^2 = x				(6)
   *
   * or, expanding and rearranging:
   *
   *   4a^2 * a^2 - 4a^2 * x = y^2			(7)
   *
   * which, since x and y are known, is quadratic in a^2:
   *
   *   (a^2)^2 - x * a^2 = y^2 / 4			(8)
   *
   * Completing the square on the LHS, and adjusting the RHS to
   * preserve equality:
   *
   *   (a^2)^2 - x * a^2 + x^2 / 4 = y^2 / 4 + x^2 / 4	(9)
   *
   * Factorizing, and solving for a^2:
   *
   *   (a^2 - x / 2)^2 = (y^2 + x^2) / 4	       (10)
   *
   * hence:
   *
   *   a^2 = sqrt(y^2 + x^2) / 2 + x / 2	       (11)
   *
   * and further, taking the principal (positive) square root yields the
   * general expression for the real part of the complex square root:
   *
   *   a = sqrt((sqrt(y^2 + x^2) + x) / 2)	       (12)
   *
   * Having calculated this real part, we may back-substitute into (5),
   * rearranged to yield the imaginary part:
   *
   *   b = y / (2 * a)				       (13)
   *
   *
   * The preceding analysis applies in the general case; however...
   */
  if( y == ARGCAST(0.0) )
  {
    /* ...in the special case where Z has no imaginary part, (i.e.
     * y == 0, and Z is entirely real)...
     */
    if( x < ARGCAST(0.0) )
    {
      /* ...and when Z represents a negative real number, then it
       * follows from (12) that the real part of its square root is
       * zero, (since we always take positive square root terms)...
       */
      __real__ Z = ARGCAST(0.0);

      /* ...but the solution of (13) then becomes indeterminate, so
       * we must deduce the imaginary result by rearrangement of (4),
       * adopting the convention whereby the sign of the signed zero
       * defining the imaginary part of Z is preserved...
       */
      __imag__ Z = mapfunc(copysign)(mapfunc(sqrt)(-x), y);
    }
    else
    { /* ...whilst in the case where Z represents a positive real
       * number, we simply set the real part of the result as the
       * positive square root of x, leaving the imaginary part as
       * the unchanged signed zero value of y; (result following
       * directly from (12) and (13)).
       */
      __real__ Z = mapfunc(sqrt)(x);
    }
  }
  else if( x == ARGCAST(0.0) )
  {
    /* This is a further special case, in which Z represents an
     * entirely imaginary number, (with no real part).  Here, we
     * could apply (12) and (13); however, the knowledge that x is
     * zero allows us to employ a simplified derivation from (12)
     * to compute the real part of the principal square root...
     */
    __real__ Z = x = mapfunc(sqrt)(ARGCAST(0.5) * mapfunc(fabs)(y));

    /* ...while we may deduce from (4) that the imaginary part is
     * numerically equal to the real part, and once again we adopt
     * the convention of preserving the sign of y, in the result,
     * (as is required to satisfy (13)).
     */
    __imag__ Z = mapfunc(copysign)(x, y);
  }
  else
  { /* Finally, this represents the general complex number case; we
     * may apply (12) and (13) directly, (noting that hypot(x, y) is
     * functionally equivalent to sqrt(y^2 + x^2), with the benefit
     * of protection against overflow when x or y is large).
     */
    __real__ Z = x = mapfunc(sqrt)(ARGCAST(0.5) * (mapfunc(hypot)(x, y) + x));
    __imag__ Z = ARGCAST(0.5) * y / x;
  }
  return Z;
}

/* $RCSfile$: end of file */
