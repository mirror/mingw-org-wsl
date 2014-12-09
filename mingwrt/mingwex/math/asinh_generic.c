/*
 * asinh_generic.c
 *
 * Compute inverse hyberbolic sine; this is a generic implementation for
 * all of the asinh(), asinhl(), and asinhf() functions.
 *
 * $Id$
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright 2013, 2014, MinGW.org Project
 *
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
 *
 *
 * This module should be compiled separately for each supported function:
 *
 *   gcc -D FUNCTION=asinh  -o asinh.o  asinh_generic.c
 *   gcc -D FUNCTION=asinhl -o asinhl.o asinh_generic.c
 *   gcc -D FUNCTION=asinhf -o asinhf.o asinh_generic.c
 *
 */
#include <math.h>

#ifndef FUNCTION
/* If user neglected to specify it, the default compilation is for
 * the asinh() function.
 */
# define FUNCTION asinh
#endif

#define argtype_asinh  double
#define argtype_asinhl long double
#define argtype_asinhf float

#define PASTE(PREFIX,SUFFIX)   PREFIX##SUFFIX
#define mapname(PREFIX,SUFFIX) PASTE(PREFIX,SUFFIX)

#define ARGTYPE(FUNCTION) PASTE(argtype_,FUNCTION)
#define ARGCAST(VALUE)    mapname(argcast_,FUNCTION)(VALUE)

#define argcast_asinh(VALUE)  VALUE
#define argcast_asinhl(VALUE) PASTE(VALUE,L)
#define argcast_asinhf(VALUE) PASTE(VALUE,F)

#define mapfunc(NAME) mapname(mapfunc_,FUNCTION)(NAME)

#define mapfunc_asinh(NAME)  NAME
#define mapfunc_asinhl(NAME) PASTE(NAME,l)
#define mapfunc_asinhf(NAME) PASTE(NAME,f)

/* Prefer fast versions of mathematical functions.
 */
#include "fastmath.h"

#define log    __fast_log
#define log1p  __fast_log1p
#define sqrt   __fast_sqrt

/* Define the generic function implementation.
 */
ARGTYPE(FUNCTION) FUNCTION( ARGTYPE(FUNCTION) x )
{
  if( isfinite(x) )
  {
    /* For all finite values of x, we may compute asinh(x) in terms of
     * the magnitude of x...
     */
    ARGTYPE(FUNCTION) h, z;
    if( (z = mapfunc(fabs)( x )) > ARGCAST(1.0) )
    {
      /* When z is greater than 1.0, there is a possibility of overflow
       * in the computation of z * z; this would propagate to the result
       * of computing sqrt( 1.0 + z * z ), even when the ultimate result
       * should be representable.  Thus, we adopt a transformation based
       * on hypot(), which cannot overflow, viz.:
       *
       *    sqrt( 1.0 + z * z )
       *
       * is equivalent to
       *
       *    z * sqrt( 1.0 + (1.0 / z) * (1.0 / z) )
       */
      h = ARGCAST(1.0) / z;
      h = z * mapfunc(sqrt)( ARGCAST(1.0) + h * h );
    }
    else
    { /* z is less that 1.0: we may safely compute z * z without fear of
       * overflow; it may underflow to zero, in which case we may simply
       * ignore the effect, as it is insignificant.
       */
      h = mapfunc(sqrt)( ARGCAST(1.0) + z * z );
    }

    /* Now, we may compute the absolute value of the inverse hyperbolic
     * sine function, according to its analytical definition:
     *
     *   arsinh( z ) = log( z + sqrt( 1.0 + z * z ) )
     *
     * or, since we've already computed h = sqrt( 1.0 + z * z ):
     *
     *   arsinh( z ) = log( z + h )
     *
     * We may note that, in spite of our efforts to avoid overflow in the
     * computation of h, this expression for arsinh(z) remains vulnerable to
     * overflow as z approaches the representable limit of finite floating
     * point values, even when the ultimate result is both representable and
     * computable.  We may further note that h >= z is always true, with h
     * approaching an asymptotic minimum of 1.0, as z becomes vanishingly
     * small, while h becomes approximately equal to z as z becomes very
     * large; thus we may transform the expression to:
     *
     *   arsinh( z ) = log( z / h + 1.0 ) + log( h )
     *
     * or its equivalent representation:
     *
     *   arsinh( z ) = log1p( z / h ) + log( h )
     *
     * which is computable, without overflow, for all finite values of z
     * with corresponding finite values of h for which the logarithm is
     * computable.
     *
     * Finally, we note that the ultimate result has the same sign as the
     * original value of x, with magnitude as computed by the preceding
     * expression; thus...
     */
    return mapfunc(copysign)( mapfunc(log1p)( z / h ) + mapfunc(log)( h ), x );
  }
  /* If we get to here, x was infinite; we can do no more than return an
   * equivalent infinite result.
   */
  return x;
}

/* $RCSfile$: end of file */
