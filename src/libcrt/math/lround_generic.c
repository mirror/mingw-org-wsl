/**
 * @file lround_generic.c
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

/*
 * Provides a generic implementation for the `lround()', `lroundf()',
 * `lroundl()', `llround()', `llroundf()' and `llroundl()' functions;
 * compile with `-D FUNCTION=name', with `name' set to each of these
 * six in turn, to create separate object files for each of the six
 * functions.
 */
#ifndef FUNCTION
/*
 * Normally specified with `-D FUNCTION=name', on the command line.
 * Valid FUNCTION names are `lround', `lroundf', `lroundl', `llround'
 * `llroundf' and `llroundl'; specifying anything else will most likely
 * cause a compilation error.  If user did not specify an appropriate
 * FUNCTION name, default to `lround'.
 */
#define FUNCTION lround
#endif

#include "round_internal.h"

#include <limits.h>
#include <errno.h>

/* Generic implementation.
 * The user is required to specify the FUNCTION name;
 * the RETURN_TYPE and INPUT_TYPE macros resolve to appropriate
 * type declarations, to match the selected FUNCTION prototype,
 * while RETURN_MAX and RETURN_MIN map to the correspondingly
 * appropriate limits.h manifest values, to establish the
 * valid range for the RETURN_TYPE.
 */
RETURN_TYPE FUNCTION( INPUT_TYPE x )
{
  if( !isfinite( x ) || !isfinite( x = round_internal( x ) )
  ||  (x > MAX_RETURN_VALUE) || (x < MIN_RETURN_VALUE)        )
    /*
     * Undefined behaviour...
     * POSIX requires us to report a domain error; ANSI C99 says we
     * _may_ report a range error, and previous MinGW implementation
     * set `errno = ERANGE' here; we change that, conforming to the
     * stricter requiremment of the POSIX standard.
     */
    errno = EDOM;

  return (RETURN_TYPE)(x);
}

/* $RCSfile: lround_generic.c,v $$Revision: 1.1 $: end of file */
