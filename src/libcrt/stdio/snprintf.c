/**
 * @file snprintf.c
 * @copy 2012 MinGW.org project
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
 * Provides an implementation of the "snprintf" function, conforming
 * generally to C99 and SUSv3/POSIX specifications, with extensions
 * to support Microsoft's non-standard format specifications.  This
 * is included in libmingwex.a, replacing the redirection through
 * libmoldnames.a, to the MSVCRT standard "_snprintf" function; (the
 * standard MSVCRT function remains available, and may  be invoked
 * directly, using this fully qualified form of its name).
 */

#include <stdio.h>
#include <stdarg.h>

#include "pformat.h"

int __cdecl __snprintf (char *, size_t, const char *fmt, ...) __MINGW_NOTHROW;
int __cdecl __mingw_alias(snprintf) (char *, size_t, const char *, ...) __MINGW_NOTHROW;

int __cdecl __vsnprintf (char *, size_t, const char *fmt, va_list) __MINGW_NOTHROW;

int __cdecl __snprintf( char *buf, size_t length, const char *fmt, ... )
{
  va_list argv; va_start( argv, fmt );
  register int retval = __vsnprintf( buf, length, fmt, argv );
  va_end( argv );
  return retval;
}

/* $RCSfile: snprintf.c,v $Revision: 1.3 $: end of file */
