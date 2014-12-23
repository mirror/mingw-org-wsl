/*
 * nsleep.c
 *
 * Core implementation of the __mingw_sleep() API, which facilitates the
 * provision of (mostly) POSIX compliant sleep(), usleep(), and nanosleep()
 * functions, (per inline implementations in unistd.h).
 *
 * $Id$
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2014, MinGW.org Project.
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OF OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */
#include <errno.h>
#include <limits.h>
#include <unistd.h>

/* Including windows.h, just to declare Sleep(), seems like overkill; we
 * prefer to declare it directly, to ensure we get the kernel DLL import,
 * without the overhead of redirection through a libkernel.a trampoline.
 */
__declspec(dllimport) _stdcall void Sleep( unsigned long );

int __mingw_sleep( unsigned long secs, unsigned long nsecs )
{
  /* Entry point for general purpose sleep() function API, supporting
   * the __CRT_INLINE implementations of the three functions identified
   * in the file description above.
   */
  if( (secs | nsecs) > 0UL )
  {
    /* At least one of the seconds or nanoseconds components must
     * be non-zero, to require us to perform any action.
     */
    if( nsecs < 1000000000UL )
    {
      /* POSIX requires the nanoseconds component of the specified
       * interval to be less than one full second (1,000,000,000 ns);
       * we've satisfied that requirement, so we proceed to combine
       * the seconds and nanoseconds components into a millisecond
       * representation, as required by the kernel's Sleep() API,
       * (using a 64-bit representation, to avoid overflow).
       */
      unsigned long long interval = (secs > 0UL)
	? secs * 1000ULL + ((nsecs > 0UL) ? nsecs / 1000000ULL : 0ULL)
	: (nsecs + 999999ULL) / 1000000ULL;

      /* It is unlikely that we should ever need this, (but it is
       * possible, so we proceed defensively)...
       */
      while( interval > (unsigned long long)(LONG_MAX) )
      {
	/* ...breaking excessively long intervals into cycles of
	 * LONG_MAX milliseconds, (~25 days, and we may be asked
	 * to sleep through up to 2000 cycles, or ~136 years), so
	 * that we avoid any interval value with the high bit set
	 * (lest that be interpreted as "sleep forever").
	 */
	Sleep( (unsigned long)(LONG_MAX) );
	interval -= (unsigned long long)(LONG_MAX);
      }
      /* Since suspension requests of 25 days are unlikely, in
       * the majority of cases we should simply skip over the
       * preceding loop; we must still call Sleep(), either to
       * satisfy the original request in its entirety, or the
       * residual from the loop.
       */
      Sleep( (unsigned long)(interval) );
    }
    else
    { /* We were given a nanoseconds component value, within the
       * interval specification, which exceeds one full second; in
       * this event, POSIX specifies the following failure:
       */
      errno = EINVAL;
      return -1;
    }
  }
  /* On success, or maybe having done nothing at all, we simply
   * return zero; (note that Windows Sleep() isn't interruptible
   * in the way that that POSIX sleep() is, so we do not provide
   * any indication of an uncompleted interval).
   */
  return 0;
}

/* $RCSfile$: end of file */
