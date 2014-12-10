/*
 * casin_generic.c
 *
 * $Id$
 *
 * Compute the complex arcsin corresponding to a complex sine value;
 * a generic implementation for casin(), casinf(), and casinl().
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * This is an adaptation of an original contribution by Danny Smith
 * Copyright (C) 2003, 2014, MinGW.org Project
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
 * This is a generic implementation for all of the casin(), casinl(),
 * and casinh() functions; each is to be compiled separately, i.e.
 *
 *   gcc -D FUNCTION=casin  -o casin.o  casin_generic.c
 *   gcc -D FUNCTION=casinl -o casinl.o casin_generic.c
 *   gcc -D FUNCTION=casinf -o casinf.o casin_generic.c
 *
 */
#include <math.h>
#include <complex.h>

#ifndef FUNCTION
/* If user neglected to specify it, the default compilation is for
 * the casin() function.
 */
# define FUNCTION casin
#endif

#define argtype_casin  double
#define argtype_casinl long double
#define argtype_casinf float

#define PASTE(PREFIX,SUFFIX)   PREFIX##SUFFIX
#define mapname(PREFIX,SUFFIX) PASTE(PREFIX,SUFFIX)

#define ARGTYPE(FUNCTION) PASTE(argtype_,FUNCTION)
#define ARGCAST(VALUE)    mapname(argcast_,FUNCTION)(VALUE)

#define argcast_casin(VALUE)  VALUE
#define argcast_casinl(VALUE) PASTE(VALUE,L)
#define argcast_casinf(VALUE) PASTE(VALUE,F)

#define mapfunc(NAME) mapname(mapfunc_,FUNCTION)(NAME)

#define mapfunc_casin(NAME)  NAME
#define mapfunc_casinl(NAME) PASTE(NAME,l)
#define mapfunc_casinf(NAME) PASTE(NAME,f)

/* Define the generic function implementation.
 */
ARGTYPE(FUNCTION) complex FUNCTION( ARGTYPE(FUNCTION) complex Z )
{
  ARGTYPE(FUNCTION) x = __real__ Z;	/* real part of Z saved as x */
  ARGTYPE(FUNCTION) y = __imag__ Z;	/* imaginary part of Z saved as iy */

  /* Having thus saved the original value of Z as separate real and
   * imaginary parts, we may reuse Z to compute the arcsin value...
   */
  if( (y == ARGCAST(0.0)) && (ARGCAST(1.0) >= mapfunc(fabs)(x)) )
  {
    /* ...but when Z is entirely real, and lies within the valid
     * domain, (-1.0 .. +1.0), for real sine values, we may simply
     * optimize this call, using the real arcsin function...
     */
    __real__ Z = mapfunc(asin)(x);
  }
  else
  { /* Z is complex, (i.e. it has a non-zero imaginary part), or it
     * is entirely real but lies outside the valid domain for a real
     * sine value; we must evaluate the complex arcsin expression:
     *
     *   casin(Z) = -i * clog(i * Z + csqrt(1.0 - Z * Z))
     *
     * Here, we use a local accumulator for the evaluation:
     */
    ARGTYPE(FUNCTION) complex ZZ;

    /* First, note that we may express 1.0 - Z * Z as equivalent to
     * 1.0 - (x + iy) * (x + iy), which expands to:
     *
     *   1.0 - (x * x + i * y * i * y + 2.0 * i * x * y)
     *
     * and, noting that i * i is equivalent to -1, this simplifies
     * to become:
     *
     *   1.0 - (x * x - y * y + 2.0 * i * x * y)
     *
     * Separating real and imaginary parts yields:
     *
     *   (1.0 - x * x - y * y) - (i * 2.0 * x * y)
     *
     * and factorization of the real part then yields:
     *
     *   (1.0 - (x - y) * (x + y)) - (i * 2.0 * x * y)
     *
     * hence...
     */
    __real__ ZZ = ARGCAST(1.0) - (x - y) * (x + y);
    __imag__ ZZ = ARGCAST(-2.0) * x * y;

    /* ...and the complex square root term may be computed as...
     */
    ZZ = mapfunc(csqrt)(ZZ);

    /* ...to which we then add i * (x + iy), (i.e. i times the
     * original value of Z); here, we note that i * iy is equal to
     * -1 * y, and hence adding it is equivalent to subtracting y
     *  from the real part of our recomputed Z, while adding i * x
     *  is equivalent to adding x to the imaginary part...
     */
    __real__ ZZ -= y;
    __imag__ ZZ += x;

    /* ...thus obtaining the intermediate expression value from
     * which we must compute the complex logarithm...
     */
    ZZ = mapfunc(clog)(ZZ);

    /* ...and ultimately, the arcsin value to be returned is the
     * value of this complex logarithm multiplied by -1 * i; (the
     * imaginary part of the intermediate result, multiplied by i
     * becomes the real part of the result, with inverted sign,
     * which is then inverted again on multiplication by -1...
     */
    __real__ Z = __imag__ ZZ;

    /* ...while the real part of the intermediate simply becomes
     * the imaginary part of the result, with sign preserved, but
     * then inverted by multiplication by -1).
     */
    __imag__ Z = ARGCAST(-1.0) * __real__ ZZ;
  }
  return Z;
}

/* $RCSfile$: end of file */
