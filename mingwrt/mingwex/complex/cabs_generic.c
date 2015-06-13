/*
 * cabs_generic.c
 *
 * $Id$
 *
 * Compute the modulus of a complex number; this provides a generic
 * implementation for the cabs(), cabsf(), and cabsl() functions.
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * This is an adaptation of original contributions by Danny Smith
 * Copyright (C) 2003, 2015, MinGW.org Project
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
 *   gcc -D FUNCTION=cabs  -o cabs.o  cabs_generic.c
 *   gcc -D FUNCTION=cabsl -o cabsl.o cabs_generic.c
 *   gcc -D FUNCTION=cabsf -o cabsf.o cabs_generic.c
 *
 */
#include <math.h>
#include <complex.h>

#ifndef FUNCTION
/* If user neglected to specify it, the default compilation is for
 * the cabs() function.
 */
# define FUNCTION cabs
#endif

#define argtype_cabs  double
#define argtype_cabsl long double
#define argtype_cabsf float

#define PASTE(PREFIX,SUFFIX) PREFIX##SUFFIX
#define mapfunc(NAME) mapname(mapfunc_,FUNCTION)(NAME)
#define mapname(PREFIX,SUFFIX) PASTE(PREFIX,SUFFIX)

#define ARGTYPE(FUNCTION) PASTE(argtype_,FUNCTION)

#define mapfunc_cabs(NAME)  NAME
#define mapfunc_cabsl(NAME) PASTE(NAME,l)
#define mapfunc_cabsf(NAME) PASTE(NAME,f)

/* Define the generic function implementation.
 */
ARGTYPE(FUNCTION) FUNCTION( ARGTYPE(FUNCTION) complex Z )
{
  return mapfunc(hypot)( __real__ Z, __imag__ Z );
}

/* $RCSfile$: end of file */
