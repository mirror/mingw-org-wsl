/*
 * mkdtemp.c
 *
 * Implementation of an (approximately) POSIX conforming mkdtemp(3).
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
#include <direct.h>
#include <errno.h>

/* Candidate names for the temporary directory are generated, based on
 * a cryptographically secure random character sequence; this externally
 * implemented character sequence generator is shared by mkstemp(3) and
 * mkdtemp(3).
 */
extern char *__mingw_crypto_tmpname( char * );

char *__mingw_mkdtemp( char *template )
{
  /* Formal MinGW implementation of the mkdtemp(3) function; to begin,
   * check that the caller gave us a viable template...
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

    /* Until we either successfully create a directory, or we have
     * exhausted the retry limit while attempting to do so...
     */
    while( retry-- > 0 )
    {
      /* ...set up the scratch buffer, copy the template into it,
       * then transform to get a cryptographically secure candidate
       * name for the temporary directory; (each retry cycle will
       * generate a randomly differing candidate name)...
       */
      char dirname[bufsiz];
      if( __mingw_crypto_tmpname( strcpy( dirname, template ) ) == NULL )
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
      { /* We got a usable candidate directory name; try to create
	 * the named directory...
	 */
	if( mkdir( dirname ) == 0 )
	  /*
	   * ...and, on success, update the template to reflect the
	   * name of the directory we've created, and we are done...
	   */
	  return strcpy( template, dirname );

	/* ...but, if we failed for any reason other than that a file
	 * or a directory with the candidate name already exists...
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
  /* If we get to here, then all of our attempts to create a directory
   * were unsuccessful; return NULL, to indicate failure.
   */
  return NULL;
}

/* $RCSfile$: end of file */
