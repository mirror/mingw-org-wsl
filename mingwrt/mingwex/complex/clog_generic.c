/*
 * clog_generic.c
 *
 * $Id$
 *
 * Compute the logarithm of a complex number; this provides a generic
 * implementation for the clog(), clogf(), and clogl() functions.
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * This is an adaptation of original contributions by Danny Smith
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
 * This is a generic implementation for all of the clog(), clogl(),
 * and clogf() functions; each is to be compiled separately, i.e.
 *
 *   gcc -D FUNCTION=clog  -o clog.o  clog_generic.c
 *   gcc -D FUNCTION=clogl -o clogl.o clog_generic.c
 *   gcc -D FUNCTION=clogf -o clogf.o clog_generic.c
 *
 */
#include <math.h>
#include <complex.h>

#ifndef FUNCTION
/* If user neglected to specify it, the default compilation is for
 * the clog() function.
 */
# define FUNCTION clog
#endif

#define argtype_clog  double
#define argtype_clogl long double
#define argtype_clogf float

#define PASTE(PREFIX,SUFFIX) PREFIX##SUFFIX
#define mapname(PREFIX,SUFFIX) PASTE(PREFIX,SUFFIX)

#define ARGTYPE(FUNCTION) PASTE(argtype_,FUNCTION)
#define ARGCAST(VALUE)    mapname(argcast_,FUNCTION)(VALUE)

#define argcast_clog(VALUE)  VALUE
#define argcast_clogl(VALUE) PASTE(VALUE,L)
#define argcast_clogf(VALUE) PASTE(VALUE,F)

#define mapfunc(NAME) mapname(mapfunc_,FUNCTION)(NAME)

#define mapfunc_clog(NAME)  NAME
#define mapfunc_clogl(NAME) PASTE(NAME,l)
#define mapfunc_clogf(NAME) PASTE(NAME,f)

/* Prefer the fast version of the log() function.
 */
#include "../math/fastmath.h"
#define log __fast_log

/* Define the generic function implementation.
 */
ARGTYPE(FUNCTION) complex FUNCTION( ARGTYPE(FUNCTION) complex Z )
{
  /* Compute the value to return; real part is the logarithm of the
   * modulus of Z, (equivalent to the length of the hypotenuse of the
   * triangle formed when representing Z by cartesian co-ordinates in
   * the complex number plane); imaginary part is its phase angle,
   * (a.k.a. its argument, in the polar representation).
   *
   * Note that the applicable POSIX and ISO-C standards do not require
   * any specific error return, and none is provided; (in particular,
   * whereas the modulus of Z is ALWAYS >= 0.0, and thus there is no
   * scope for a log() domain error to occur, modulus of Z == 0.0
   * causes a log() range error for which errno is NOT set).
   */
  ARGTYPE(FUNCTION) complex result;
  __real__ result = mapfunc(log)( mapfunc(hypot)( __real__ Z, __imag__ Z ) );
  __imag__ result = mapfunc(carg)( Z );
  return result;
}

/* $RCSfile$: end of file */
