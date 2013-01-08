/**
 * @file vsnprintf.c
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
 * Provides an implementation of the "vsnprintf" function, conforming
 * generally to C99 and SUSv3/POSIX specifications, with extensions
 * to support Microsoft's non-standard format specifications.  This
 * is included in libmingwex.a, replacing the redirection through
 * libmoldnames.a, to the MSVCRT standard "_vsnprintf" function; (the
 * standard MSVCRT function remains available, and may  be invoked
 * directly, using this fully qualified form of its name).
 */

#include <stdio.h>
#include <stdarg.h>

#include "pformat.h"

int __cdecl __vsnprintf (char *, size_t, const char *fmt, va_list) __MINGW_NOTHROW;
int __cdecl __mingw_alias(vsnprintf) (char *, size_t, const char *, va_list) __MINGW_NOTHROW;

int __cdecl __vsnprintf( char *buf, size_t length, const char *fmt, va_list argv )
{
  register int retval;

  if( length == (size_t)(0) )
    /*
     * No buffer; simply compute and return the size required,
     * without actually emitting any data.
     */
    return __pformat( 0, buf, 0, fmt, argv );

  /* If we get to here, then we have a buffer...
   * Emit data up to the limit of buffer length less one,
   * then add the requisite NUL terminator.
   */
  retval = __pformat( 0, buf, --length, fmt, argv );
  buf[retval < length ? retval : length] = '\0';

  return retval;
}

/* $RCSfile: vsnprintf.c,v $Revision: 1.3 $: end of file */
