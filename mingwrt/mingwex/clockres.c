/*
 * clockres.c
 *
 * Implementation of the clock_getres() element of the POSIX clock API.
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
#include "clockapi.h"

int clock_getres( clockid_t clock_id, struct timespec *counter )
{
  /* Standard API function, first implemented in POSIX.1b-1993, to
   * query the resolution of a specified clock; it first initializes
   * the clock, if necessary, then returns the resolution value, as
   * recorded within the associated implementation data structure,
   * together with a "validity check" status code.
   */
  if( __clock_api_is_valid( clock_id ) )
  {
    /* The clock is valid; its resolution must be broken down into
     * separate seconds and nanoseconds components, but only if the
     * caller provided a struct timespec to receive them.
     */
    if( counter != NULL )
    { counter->tv_nsec = clock_id->resolution % NANOSECONDS_PER_SECOND;
      counter->tv_sec = clock_id->resolution / NANOSECONDS_PER_SECOND;
    }
    /* In any case, we return zero to indicate a valid clock...
     */
    return 0;
  }
  /* ...or -1 otherwise.
   */
  return -1;
}

/* $RCSfile$: end of file */
