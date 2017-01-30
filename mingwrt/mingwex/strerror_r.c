/*
 * strerror_r.c
 *
 * Implementation of POSIX standard IEEE 1003.1-2001 strerror_r() function.
 *
 * $Id$
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2016, 2017, MinGW.org Project
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int strerror_r( int errnum, char *buf, size_t len )
{
  /* Copy the error message, as retrieved by strerror(), to the user
   * supplied buffer, so protecting it from subsequent overwrite by a
   * future call to strerror(); returns zero on success, otherwise sets
   * errno to, and returns, EINVAL if the user specified errnum doesn't
   * refer to a valid message, or ERANGE if the associated message, and
   * its terminating NUL, will not fit within the specified buffer.
   *
   * Note that Microsoft's strerror() DOES appear to be thread-safe,
   * but it uses a single static buffer per thread; thus, within any
   * one thread, successive calls will overwrite the previous contents
   * of this buffer; use of strerror_r() allows the user to save a copy
   * of strerror()'s buffer contents, following each call, where they
   * are not subject to overwriting by a subsequent strerror() call.
   */
  if( buf == NULL )
    /* POSIX does not recommend any handling for the case of a NULL
     * return buffer argument; rather than segfault, we will treat it
     * as a zero-length buffer, into which we can fit no message text
     * at all, and so we simply return, setting errno to ERANGE.
     */
    return errno = ERANGE;

  /* The buffer pointer isn't NULL; assume it is valid, (we will fail
   * on segfault if it isn't), and proceed to validate errnum.
   */
  if( ((unsigned)(errnum)) >= sys_nerr )
  { /* Note that we check errnum as unsigned; this will also catch a
     * negative value, since it will appear to be within the positive
     * range INT_MAX < errnum <= UINT_MAX, while sys_nerr is expected
     * to be less than INT_MAX.
     */
    snprintf( buf, len, "Unknown error: %d", errnum );
    return errno = EINVAL;
  }
  /* errnum appears to be valid; copy the associated message, while
   * checking that its entire text is copied...
   */
  if( snprintf( buf, len, "%s", strerror( errnum )) >= len )
    /*
     * ...otherwise, set errno on truncation.
     */
    return errno = ERANGE;

  /* If we get to here, return zero, indicating success; (DO NOT
   * modify errno, in this case).
   */
  return 0;
}

/* $RCSfile$: end of file */
