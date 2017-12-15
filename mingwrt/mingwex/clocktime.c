/*
 * clocktime.c
 *
 * Implementation of the clock_gettime() element of the POSIX clock API.
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

int clock_gettime( clockid_t clock_id, struct timespec *current )
{
  /* Standard API function, first implemented in POSIX.1b-1993, to
   * read the current time indicated by a specified clock; it first
   * initializes the clock, if necessary, then reads its currently
   * indicated time, and encodes it for return, in the specified
   * "current" timespec structure, together with a "validity check"
   * status code.
   *
   * Note that, unlike the clock_getres() API, it is NOT permitted
   * to specify NULL for the timespec parameter here; doing so will
   * cause the call to fail, irrespective of the clock validity.
   */
  if( current == NULL )
    return clock_api_invalid_error();

  if( __clock_api_is_valid( clock_id ) )
  {
    /* We must be prepared to retrieve clock frequencies from Windows
     * APIs, which report either LARGE_INTEGER or FILETIME values, but
     * we prefer to interpret them as scalar int64_t values.
     */
    union { uint64_t value; LARGE_INTEGER qpc_value; FILETIME rtc_value; } ct;
    switch( clock_id->type )
    {
      case CLOCK_TYPE_REALTIME:
	/* The counter for CLOCK_REALTIME, and any derived clock, is
	 * represented by system time, expressed as a count of 100ns
	 * intervals since the start of the Windows FILETIME epoch.
	 */
	GetSystemTimeAsFileTime( &ct.rtc_value );
	break;

      case CLOCK_TYPE_MONOTONIC:
	/* Conversely, the counter for CLOCK_MONOTIME and derivatives
	 * is obtained from the Windows QPC API, if supported...
	 */
	if( QueryPerformanceCounter( &ct.qpc_value ) == 0 )
	  /*
	   * ...or forces an "invalid status" return, otherwise.
	   */
	  return clock_api_invalid_error();
    }
    /* In either case, once we have a valid count of clock ticks, we
     * must adjust it, relative to the timebase for the clock, (which
     * is recorded within the clock's implementation data structure),
     * then scale it, and break it down into seconds and nanoseconds
     * components, (again based on scaling factors which are similarly
     * recorded within the implementation data)...
     */
    ct.value -= clock_id->timebase;
    current->tv_nsec = (ct.value % clock_id->frequency)
      * NANOSECONDS_PER_SECOND / clock_id->frequency;
    current->tv_sec = ct.value / clock_id->frequency;

    /* ...before returning zero, as "successful completion" status...
     */
    return 0;
  }
  /* ...or -1, indicating failure.
   */
  return -1;
}

/* $RCSfile$: end of file */
