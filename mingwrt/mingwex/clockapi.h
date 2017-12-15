/*
 * clockapi.h
 *
 * Private header, declaring the common elements of the POSIX clock API.
 *
 * $Id$
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2017, MinGW.org Project
 *
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
 *
 */
#include <time.h>
#include <stdint.h>
#include <winbase.h>
#include <errno.h>

typedef enum
{ /* The categories of clock, for which we provide support.
   */
  CLOCK_TYPE_REALTIME,		/* CLOCK_REALTIME and derivatives */
  CLOCK_TYPE_MONOTONIC, 	/* CLOCK_MONOTONIC and derivatives */

  /* Only the above represent valid clock categories; we end the
   * enumeration with this comparator reference value, to which,
   * when compared as unsigned, all unsupported category values
   * will be equal or greater.
   */
  CLOCK_TYPE_UNIMPLEMENTED
} CLOCK_TYPE;

/* POSIX specifies that CLOCK_REALTIME shall report time elapsed, in
 * seconds and nanoseconds, since the start of the Unix epoch, (i.e.
 * since 1970-01-01 00:00:00), but we count it, in 100ns increments,
 * since the start of the Windows FILETIME epoch, (1601-01-01 00:00).
 * The following manifest constants facilitate the conversion from
 * Windows FILETIME to Unix epoch; (11644473600LL seconds of the
 * Windows FILETIME epoch have elapsed, when the Unix epoch begins).
 */
#define NANOSECONDS_PER_SECOND     1000000000LL
#define CLOCK_REALTIME_FREQUENCY  (NANOSECONDS_PER_SECOND / 100LL)
#define UNIX_EPOCH_AS_FILETIME    (11644473600LL * CLOCK_REALTIME_FREQUENCY)

typedef struct __clockid__
{ /* Formal definition of the clockid_t structure; (opaque to
   * user application code).
   */
  CLOCK_TYPE	type;
  int64_t	frequency;
  int64_t	resolution;
  int64_t	timebase;
} *clockid_t;

/* Prototype for clockid_t validation function; considered private
 * within the scope of the implementation, (so not declared publicly),
 * this also provides initialization support.
 */
extern int __clock_api_is_valid( clockid_t );

#define CLOCK_INLINE  static __inline__ __attribute__((__always_inline__))

CLOCK_INLINE
int clock_api_invalid_error( void )
{ /* Inline helper function, to facilitate return from any of the
   * standard clock API functions, while setting both "errno", and
   * the return status, to report an invalid operation.
   */
  errno = EINVAL; return -1;
}

/* $RCSfile$: end of file */
