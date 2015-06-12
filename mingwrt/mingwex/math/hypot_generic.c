/*
 * hypot_generic.c
 *
 * Compute the length of the hypotenuse of a right triangle, given the
 * lengths of the two perpendicular sides.
 *
 * $Id$
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright 2015, MinGW.org Project
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
 *   gcc -D FUNCTION=hypot  -o hypot.o  hypot_generic.c
 *   gcc -D FUNCTION=hypotl -o hypotl.o hypot_generic.c
 *   gcc -D FUNCTION=hypotf -o hypotf.o hypot_generic.c
 *
 */
#include <math.h>
#include <float.h>
#include <errno.h>

#ifndef FUNCTION
/* If user neglected to specify it, the default compilation is for
 * the hypot() function.
 */
# define FUNCTION hypot
#endif

#define argtype_hypot  double
#define argtype_hypotl long double
#define argtype_hypotf float

#define PASTE(PREFIX,SUFFIX)   PREFIX##SUFFIX
#define mapname(PREFIX,SUFFIX) PASTE(PREFIX,SUFFIX)

#define ARGTYPE(FUNCTION) PASTE(argtype_,FUNCTION)
#define ARGCAST(VALUE)    mapname(argcast_,FUNCTION)(VALUE)

#define argcast_hypot(VALUE)  VALUE
#define argcast_hypotl(VALUE) PASTE(VALUE,L)
#define argcast_hypotf(VALUE) PASTE(VALUE,F)

#define mapfunc(NAME) mapname(mapfunc_,FUNCTION)(NAME)

#define mapfunc_hypot(NAME)  NAME
#define mapfunc_hypotl(NAME) PASTE(NAME,l)
#define mapfunc_hypotf(NAME) PASTE(NAME,f)

#define hypot_argval_max  DBL_MAX
#define hypotf_argval_max FLT_MAX
#define hypotl_argval_max LDBL_MAX

#define hypot_result_overflow  HUGE_VAL
#define hypotf_result_overflow HUGE_VALF
#define hypotl_result_overflow HUGE_VALL

/* Prefer fast version of the sqrt() function.
 */
#include "fastmath.h"
#define sqrt __fast_sqrt

/* Define the generic function implementation.
 */
#define METHODL 1
ARGTYPE(FUNCTION) FUNCTION( ARGTYPE(FUNCTION) x, ARGTYPE(FUNCTION) y )
{
# if ARGCAST(METHOD)
  /*
   * By default, we implement the actual computation for the
   * hypotl() function only, (since only METHODL is explicitly
   * defined as non-zero); to do likewise for the hypot() and
   * hypotf() functions, compile with -D METHOD and -D METHODF
   * set respectively.
   *
   */
  if( isfinite(x) && isfinite(y) )
  {
    /* For all finite values of x and y, we may compute hypot(x,y)
     * in terms of their respective magnitudes; we apply Pythagoras'
     * theorum, but to avoid a possible overflow when computing the
     * sum of the squares of x and y, we use a transformed variant
     * of the conventional formula, based on the assumption that
     * the arguments are ordered such that |x| >= |y|...
     */
    ARGTYPE(FUNCTION) h;
    if( (h = x = mapfunc(fabs)( x )) < (y = mapfunc(fabs)( y )) )
    {
      /* ...otherwise, we transpose them.
       */
      x = y; y = h;
    }
    /* After ensuring that |x| >= |y|, we must perform one more
     * sanity check to ensure that we don't have |x| == 0.0, (in
     * which case |y| must also be 0.0, and the quotient |y|/|x|
     * becomes indeterminate).
     */
    if( x == ARGCAST(0.0) )
      /*
       * For this specific case, we may avoid the need to compute
       * the indeterminate quotient, by simple evaluation of the
       * normal expression of Pythagoras' theorum:
       *
       *   hypot = sqrt( x * x + y * y )
       *
       * directly, to obtain the expected result of zero.
       */
      return ARGCAST(0.0);

    /* We can now be confident that the ratio...
     */
    h = y / x;
    /*
     * ...is determinate, and must lie in the range 0.0 .. 1.0, so
     * we may safely compute the overflow protected transformation
     * of the expression of Pythagoras' theorum:
     *
     *   hypot = x * sqrt( 1.0 + (y / x) * (y / x))
     *
     * without any possibility of overflow, when squaring the y / x
     * ratio term; however, there is still a slight possibility that
     * x itself is so large that multiplication by the square root
     * term, (which must lie in the range 1.0 .. sqrt(2.0)), may
     * cause overflow in the final result...
     */
    h = mapfunc(sqrt)( ARGCAST(1.0) + h * h );
    if( x > (mapname(FUNCTION,_argval_max) / h) )
    {
      /* ...in which case, we set errno, and return the appropriate
       * representation of HUGE_VAL...
       */
      errno = ERANGE;
      return mapname(FUNCTION,_result_overflow);
    }
    /* ...otherwise, we may compute and return the requisite result;
     * we may be certain that this is unaffected by OVERFLOW.  On the
     * other hand, UNDERFLOW may have occurred in the intermediate
     * computation of y/x; however, the effect is insignificant.
     */
    return x * h;
  }
  /* If we get to here, one or both of x and y was indefinite; POSIX
   * requires us to return +inf, if either x or y is infinite, (even
   * if the other is nan)...
   */
  if( isinf( x ) ) return mapfunc(copysign)( x, ARGCAST(+1.0) );
  if( isinf( y ) ) return mapfunc(copysign)( y, ARGCAST(+1.0) );
  /*
   * ...otherwise, combine them to force an indefinite result.
   */
  return x + y;

#else
  /* For the hypot() and hypotf() implementations, we prefer to
   * compute an intermediate result in the long double domain...
   */
  long double intermediate = hypotl( (long double)(x), (long double)(y) );

  /* ...then check that this may be represented within the
   * effective domain of the return data type...
   */
  if(  isfinite( intermediate )
  &&  (intermediate > (long double)(mapname(FUNCTION,_argval_max))) )
  {
    /* ...otherwise flag a RANGE error, and return the
     * appropriate representation of HUGE_VAL...
     */
    errno = ERANGE;
    return mapname(FUNCTION,_result_overflow);
  }
  /* ...or the valid imtermediate result, cast to the
   * appropriate data type for the function.
   */
  return (ARGTYPE(FUNCTION))(intermediate);

#endif
}

/* $RCSfile$: end of file */
