/*
 * ofmtctl.c
 *
 * Implementation of a MinGW.org specific helper routine, to manipulate
 * supplementary output format control flags other than those specified
 * for the Microsoft output format control API.
 *
 * $Id$
 *
 * Written by Keith Marshall  <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2015, MinGW.org Project.
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OF OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */
#include <stdio.h>

/* MinGW uses this public symbol to represent both Microsoft's exponent
 * digit format flag, and supplementary MinGW.org specific flags.
 */
extern unsigned int __mingw_output_format_flags;

/* The MinGW.org specific output format flag management API function.
 * This provides both get and set capabilities for the MinGW specified
 * flags; it has no effect on the Microsoft specified flags; use their
 * _get_output_format() and _set_output_format() API functions when it
 * is desired to manipulate them.
 */
unsigned int _mingw_output_format_control
( unsigned int flags_to_keep, unsigned int flags_to_set )
{
  /* Return value is always based on current flag state.
   */
  unsigned int retval = __mingw_output_format_flags;

  /* Adjust flags as specified by the mask of flags to keep,
   * and add in any extra flags to set; always keep the state
   * of the Microsoft specified flag bits, and decline to set
   * them to any new state.
   */
  __mingw_output_format_flags &= flags_to_keep | _EXPONENT_DIGIT_MASK;
  __mingw_output_format_flags |= flags_to_set & ~_EXPONENT_DIGIT_MASK;

  /* Finally, exclude the Microsoft specified bits from the
   * state to be returned, and return the original state of
   * the MinGW specified bits.
   */
  return retval & ~_EXPONENT_DIGIT_MASK;
}

/* $RCSfile$: end of file */
