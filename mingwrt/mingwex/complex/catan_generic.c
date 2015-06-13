/*
 * catan_generic.c
 *
 * $Id$
 *
 * Compute the complex arctan corresponding to a complex tangent value;
 * a generic implementation for catan(), catanf(), and catanl().
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * This is an adaptation of an original contribution by Danny Smith
 * Copyright (C) 2003-2005, 2015, MinGW.org Project
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
 * This is a generic implementation for all of the catan(), catanl(),
 * and catanh() functions; each is to be compiled separately, i.e.
 *
 *   gcc -D FUNCTION=catan  -o catan.o  catan_generic.c
 *   gcc -D FUNCTION=catanl -o catanl.o catan_generic.c
 *   gcc -D FUNCTION=catanf -o catanf.o catan_generic.c
 *
 */
#include <math.h>
#include <complex.h>

#ifndef FUNCTION
/* If user neglected to specify it, the default compilation is for
 * the catan() function.
 */
# define FUNCTION catan
#endif

#define argtype_catan  double
#define argtype_catanl long double
#define argtype_catanf float

#define PASTE(PREFIX,SUFFIX)   PREFIX##SUFFIX
#define mapname(PREFIX,SUFFIX) PASTE(PREFIX,SUFFIX)

#define ARGTYPE(FUNCTION) PASTE(argtype_,FUNCTION)
#define ARGCAST(VALUE)    mapname(argcast_,FUNCTION)(VALUE)

#define argcast_catan(VALUE)  VALUE
#define argcast_catanl(VALUE) PASTE(VALUE,L)
#define argcast_catanf(VALUE) PASTE(VALUE,F)

#define mapfunc(NAME) mapname(mapfunc_,FUNCTION)(NAME)

#define mapfunc_catan(NAME)  NAME
#define mapfunc_catanl(NAME) PASTE(NAME,l)
#define mapfunc_catanf(NAME) PASTE(NAME,f)

/* Define the generic function implementation.
 */
ARGTYPE(FUNCTION) complex FUNCTION( ARGTYPE(FUNCTION) complex Z )
{
  ARGTYPE(FUNCTION) x = __real__ Z;	/* real part of Z saved as x */
  ARGTYPE(FUNCTION) y = __imag__ Z;	/* imaginary part of Z saved as iy */

  /* Having thus saved the original value of Z as separate real and
   * imaginary parts, we may reuse Z to accumulate the arctan value,
   * noting that...
   */
  if( isfinite( mapfunc(hypot)( x, y )) )
  {
    /* ...for any complex number with finite modulus, its argtan may
     * be computed as:
     *
     *   catan(Z) = (clog(1.0 + iZ) - clog(1.0 - iZ)) / 2.0i
     *
     * For computational convenience, we may introduce an additional
     * intermediate accumulator variable...
     */
    ARGTYPE(FUNCTION) complex tmp;

    /* ...in which we initially compute the (1.0 - iZ) term...
     */
    __real__ tmp = ARGCAST(1.0) + y;
    __imag__ tmp = -x;

    /* ...while computing (1.0 + iZ) directly in Z itself.
     */
    __real__ Z = ARGCAST(1.0) - y;
    __imag__ Z = x;

    /* We may then compute and combine the complex logarithms
     * of this pair of sub-expressions, while we simultaneously
     * perform the REAL division by 2.0...
     */
    tmp = ARGCAST(0.5) * (mapfunc(clog)( Z ) - mapfunc(clog)( tmp ));

    /* ...and finally, the division by i has the effect of
     * exchanging the real and imaginary parts of the result,
     * with a change of sign in the resultant imaginary part.
     */
    __real__ Z = __imag__ tmp;
    __imag__ Z = -(__real__ tmp);
  }

  else
  { /* Conversely, if the modulus of Z is in any way undefined,
     * we return a real value, with modulus of PI / 2.0, and with
     * the same sign as the original real part of Z.
     */
    __real__ Z = mapfunc(copysign)( ARGCAST(M_PI_2), x );
    __imag__ Z = ARGCAST(0.0);
  }

  /* In either case, Z now represents the arctan of its original
   * value, which we are required to return.
   */
  return Z;
}

/* $RCSfile$: end of file */
