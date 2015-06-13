/*
 * cpow_generic.c
 *
 * $Id$
 *
 * Compute the result of raising a complex number, Z, to a complex
 * power, N; this provides a generic implementation for each of the
 * cpow(), cpowf(), and cpowl() functions.
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
 * This is a generic implementation for all of the cpow(), cpowl(),
 * and cpowh() functions; each is to be compiled separately, i.e.
 *
 *   gcc -D FUNCTION=cpow  -o cpow.o  cpow_generic.c
 *   gcc -D FUNCTION=cpowl -o cpowl.o cpow_generic.c
 *   gcc -D FUNCTION=cpowf -o cpowf.o cpow_generic.c
 *
 */
#include <math.h>
#include <complex.h>

#ifndef FUNCTION
/* If user neglected to specify it, the default compilation is for
 * the cpow() function.
 */
# define FUNCTION cpow
#endif

#define argtype_cpow  double
#define argtype_cpowl long double
#define argtype_cpowf float

#define PASTE(PREFIX,SUFFIX)   PREFIX##SUFFIX
#define mapname(PREFIX,SUFFIX) PASTE(PREFIX,SUFFIX)

#define ARGTYPE(FUNCTION) PASTE(argtype_,FUNCTION)
#define ARGCAST(VALUE)    mapname(argcast_,FUNCTION)(VALUE)

#define argcast_cpow(VALUE)  VALUE
#define argcast_cpowl(VALUE) PASTE(VALUE,L)
#define argcast_cpowf(VALUE) PASTE(VALUE,F)

#define mapfunc(NAME) mapname(mapfunc_,FUNCTION)(NAME)

#define mapfunc_cpow(NAME)  NAME
#define mapfunc_cpowl(NAME) PASTE(NAME,l)
#define mapfunc_cpowf(NAME) PASTE(NAME,f)

/* Danny Smith's original implementation explicitly referenced the
 * DLL entry point for the pow() function, in the case of the cpow()
 * function only; the following variation on mapfunc() reproduces
 * this implementation model.
 */
extern double (*_imp__pow)( double, double );
#define powfunc mapname(powfunc_,FUNCTION)
#define powfunc_cpow  (*_imp__pow)
#define powfunc_cpowf  powf
#define powfunc_cpowl  powl

/* Define the generic function implementation.
 */
ARGTYPE(FUNCTION) complex FUNCTION
( ARGTYPE(FUNCTION) complex Z, ARGTYPE(FUNCTION) complex N )
{
  ARGTYPE(FUNCTION) radius;
  if( (radius = mapfunc(hypot)( __real__ Z, __imag__ Z )) == ARGCAST(0.0) )
    /*
     * Modulus of Z is zero, hence result is also zero; force it.
     */
    __real__ Z = __imag__ Z = ARGCAST(0.0);

  else
  { /* Compute the complex power function result, in terms of its
     * polar (r, theta) representation in the complex plane.
     */
    ARGTYPE(FUNCTION) r = mapfunc(carg)( Z );
    ARGTYPE(FUNCTION) theta = r * __real__ N;

    if( __imag__ N == ARGCAST(0.0) )
      /*
       * For entirely real N, the power function tends to yield
       * more accuracy than exponential expansion.
       */
      r = powfunc( radius, __real__ N );

    else
    {
      theta += (radius = mapfunc(log)( radius )) * __imag__ N;
      r = mapfunc(exp)( radius * __real__ N - r * __imag__ N );
    }

    /* Convert polar to cartesian representation for return.
     */
    __real__ Z = r * mapfunc(cos)( theta );
    __imag__ Z = r * mapfunc(sin)( theta );
  }

  /* Regardless of how we got here, the original base value has
   * now been raised to the specified power; return it.
   */
  return Z;
}

/* $RCSfile$: end of file */
