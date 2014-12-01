/*
 * mkstemp.c
 *
 * Implementation of an (approximately) POSIX conforming mkstemp(3)
 * function; invocation is via an inline wrapper, defined in stdlib.h,
 * which delegates to the library routine defined herein.
 *
 * $Id$
 *
 * Written by Keith Marshall  <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2013, 2014, MinGW.org Project.
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
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

/* Candidate names for the temporary file are generated, based on a
 * cryptographically secure random character sequence; this externally
 * implemented character sequence generator is shared by mkstemp(3)
 * and mkdtemp(3).
 */
extern char *__mingw_crypto_tmpname( char * );

int __mingw_mkstemp( int setmode, char *template )
{
  /* Implementation of the low-level functional support for mkstemp(3);
   * this provides the formal function implementation, including support
   * for adjustment of its behaviour w.r.t. temporary file persistence.
   *
   * By default, temporary files will persist until explicitly deleted;
   * POSIX prescribes that temporary files are to be created with the
   * following attributes, (with O_BINARY added, to ensure there is
   * no undue influence from "helpful" text mode transformations):
   */
  static int omode = _O_CREAT | _O_EXCL | _O_RDWR | _O_BINARY;

  if( setmode )
    /* On POSIX platforms, programmers may adopt an idiom such as:
     *
     *   if( mkstemp( template ) >= 0 )
     *   { unlink( template );
     *     . . .
     *   }
     *
     * to ensure that a temporary file does NOT persist after it is
     * closed; MS-Windows does not allow such use of unlink(2), while
     * the file remains open.  Thus, MS-Windows programmers must take
     * extra care, to close and unlink temporary files AFTER use, if
     * similar behaviour is desired.
     *
     * To mitigate this MS-Windows limitation, we provide support for
     * an alternative, MinGW specific idiom:
     *
     *   #include <fcntl.h>
     *
     *   _MKSTEMP_SETMODE( _O_TEMPORARY );
     *   if( mkstemp( template ) >= 0 )
     *   {
     *     . . . 
     *   }
     *
     * to achieve a similar effect to that of the above POSIX idiom.
     */
    return omode = (omode & ~_O_TEMPORARY) | (setmode & _O_TEMPORARY);

  else
  { /* Formal MinGW implementation of the mkstemp(3) function; to begin,
     * we assume that it may fail, and record an invalid file descriptor
     * for return in such eventuality.
     */
    int fd = -1;

    /* Check that the caller gave us a viable template...
     */
    if( template == NULL )
    {
      /* ...bailing out, if nothing at all...
       */
      errno = EINVAL;
    }
    else
    { /* ...but assume that anything at all is potentially viable;
       * set up a retry limit, and estimate the storage requirement
       * for a working scratch buffer.
       */
      int retry = TMP_MAX;
      size_t bufsiz = 1 + strlen( template );

      /* Until we either get a valid file descriptor, or we exhaust
       * the retry limit while attempting to get one...
       */
      while( (fd < 0) && (retry-- > 0) )
      {
	/* ...set up the scratch buffer, copy the template into it,
	 * then transform to get a cryptographically secure candidate
	 * file name for the temporary file; (each retry cycle will
	 * generate a randomly differing candidate file name)...
	 */
	char filename[bufsiz];
	if( __mingw_crypto_tmpname( strcpy( filename, template ) ) == NULL )
	{
	  /* ...bailing out, on any unsuccessful attempt to generate
	   * the candidate name; (this is most likely to occur during
	   * the first cycle, due to a malformed template; if we can
	   * successfully generate the first candidate, successive
	   * attempts are unlikely to fail).
	   */
	  errno = EINVAL;
	  retry = 0;
	}
	else
	{ /* We got a usable candidate file name; attempt to open it
	   * as a new file...
	   */
	  if( (fd = open( filename, omode, _S_IREAD | _S_IWRITE )) >= 0 )
	    /*
	     * ...and, on success, update the template to reflect the
	     * name of the file we've opened, and we are done...
	     */
	    strcpy( template, filename );

	  /* ...but, if we failed for any reason other than that a file
	   * with the candidate name already exists...
	   */
	  else if( errno != EEXIST )
	    /*
	     * ...then, any retry will most likely also fail, so we may
	     * as well just give up now.
	     */
	    retry = 0;
	}
      }
    }
    /* Finally, whether we succeeded in opening any temporary file, or we
     * ultimately gave up in disgust, we return the prevailing state of the
     * file descriptor we attempted to assign.
     */
    return fd;
  }
}

/* $RCSfile$: end of file */
