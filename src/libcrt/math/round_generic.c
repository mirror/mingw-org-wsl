/**
 * @file round_generic.c
 * Copyright 2008, 2012-2014 MinGW.org Project
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
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 *
 *
 * Provides a generic implementation for the `round()', `roundf()'
 * and `roundl()' functions; compile with `-D FUNCTION=name', with
 * `name' set to each of these three in turn, to create separate
 * object files for each of the three functions.
 *
 */
#ifndef FUNCTION
/*
 * Normally specified with `-D FUNCTION=name', on the command line.
 * Valid FUNCTION names are `round', `roundf' and `roundl'; specifying
 * anything else will most likely cause a compilation error.  If user
 * did not specify any FUNCTION name, default to `round'.
 */
#define FUNCTION round
#endif

#include "round_internal.h"

/* Generic implementation.
 * The user is required to specify the FUNCTION name;
 * the RETURN_TYPE and INPUT_TYPE macros resolve to appropriate
 * type declarations, to match the selected FUNCTION prototype.
 */
RETURN_TYPE FUNCTION( INPUT_TYPE x )
{
  /* Round to nearest integer, away from zero for half-way.
   *
   * We split it with the `round_internal()' function in
   * a private header file, so that it may be shared by this,
   * `lround()' and `llround()' implementations.
   */
  return isfinite( x ) ? round_internal( x ) : x;
}

/* $RCSfile: round_generic.c,v $$Revision: 1.1 $: end of file */
