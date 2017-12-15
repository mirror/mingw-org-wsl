/*
 * clockapi.c
 *
 * Implementation of the common elements of the POSIX clock API.
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

static struct __clockid__ clock_api[] =
{ { /* CLOCK_REALTIME pre-initialization implementation reference data.
     */
    CLOCK_TYPE_REALTIME,	/* Fixed category index */
    CLOCK_REALTIME_FREQUENCY,	/* Always updated at this frequency */
    0LL,			/* Resolution in ns; needs initialization */
    UNIX_EPOCH_AS_FILETIME	/* Fixed timebase reference */
  },
  { /* CLOCK_MONOTONIC pre-initialization implementation reference data.
     */
    CLOCK_TYPE_MONOTONIC,	/* Fixed category index */
    NANOSECONDS_PER_SECOND,	/* Update frequency; needs initialization */
    0LL,			/* Resolution in ns; needs initialization */
    0LL 			/* Fixed timebase reference */
  }
};

/* Publicly visible references to the preceding (opaque) clock definitions.
 */
clockid_t CLOCK_REALTIME = &clock_api[CLOCK_TYPE_REALTIME];
clockid_t CLOCK_MONOTONIC = &clock_api[CLOCK_TYPE_MONOTONIC];

CLOCK_INLINE
int64_t clock_api_getres_interval( clockid_t clock_api )
{
  /* Initialization helper for POSIX clock implementation; called ONLY
   * by __clock_api_is_valid(), and triggered by an uninitialized value
   * of zero (0LL) for the "resolution" field within the implementation
   * reference data structure; returns the initialized value thereof.
   */
  if( clock_api->resolution > 0LL )
    /* Already initialized: immediately return initialized value.
     */
    return clock_api->resolution;

  else if( clock_api->resolution == 0LL )
    /* Not yet initialized: perform type specific initialization.
     */
    switch( clock_api->type )
    {
      /* We must be prepared to retrieve clock frequencies from Windows
       * APIs, which report either LARGE_INTEGER or FILETIME values, but
       * we prefer to interpret them as scalar int64_t values.
       */
      union { int64_t value; LARGE_INTEGER qpc_value; FILETIME rtc_value; }
	freq;

      case CLOCK_TYPE_REALTIME:
	/* Clocks in this category use the GetSystemTimeAsFileTime() API
	 * to read the system clock; although this is nominally updated at
	 * 100ns intervals, it is unrealistic to expect resolution at such
	 * a high frequency.  Thus, we read it once, then again in a busy
	 * wait loop, until we detect a change, and compute the actual
	 * update interval between the two reported values.
	 */
	GetSystemTimeAsFileTime( &freq.rtc_value );
	clock_api->resolution = freq.value;
	do { GetSystemTimeAsFileTime( &freq.rtc_value );
	   } while( freq.value == clock_api->resolution );
	freq.value -= clock_api->resolution;

	/* Ultimately, we initialize the effective resolution, converting
	 * from this indicated count of 100ns intervals, to nanoseconds.
	 */
	return clock_api->resolution = freq.value * 100LL;

      case CLOCK_TYPE_MONOTONIC:
	/* Clocks in this category use the QueryPerformanceCounter() API
	 * to count arbitrarily scaled time slices, relative to an equally
	 * arbitrary timebase; we must use the QueryPerformanceFrequency()
	 * call to verify availability of this API, and to establish its
	 * update frequency and resolution in nanoseconds.
	 */
	if( QueryPerformanceFrequency( &freq.qpc_value ) && (freq.value > 0LL) )
	  return clock_api->resolution = NANOSECONDS_PER_SECOND
	    / (clock_api->frequency = freq.value);
    }

  /* If we get to here, initialization of the specified clock failed; set
   * its "resolution" to -1LL, thus marking it as unavailable.
   */
  return clock_api->resolution = ((uint64_t)(clock_api_invalid_error()));
}

int __clock_api_is_valid( clockid_t clock_id )
{
  /* Helper function, called by any of clock_getres(), clock_gettime(),
   * or clock_settime(), to check availability of the specified clock,
   * initializing it if necessary, returning...
   */
  if(  (clock_id != NULL)
  &&  ((unsigned)(clock_id->type) < CLOCK_TYPE_UNIMPLEMENTED)
  &&   (clock_api_getres_interval( clock_id ) > 0LL)  )
    /*
     * ...a nominally TRUE value of 1, in the case of a valid clock...
     */
    return 1;

  /* ...or FALSE (zero), and setting "errno", otherwise.
   */
  errno = EINVAL;
  return 0;
}

/* $RCSfile$: end of file */
