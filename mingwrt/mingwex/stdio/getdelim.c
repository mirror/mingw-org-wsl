/*
 * getdelim.c
 *
 * Implementation of POSIX standard IEEE 1003.1-2008 getdelim() function;
 * also provides the core functionality to support an inline implementation
 * of the getline() function, within <stdio.h>
 *
 * $Id$
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2012, 2015, MinGW.org Project
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
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

#ifndef EOVERFLOW
/* This is one of the errno failure states specified by POSIX, for both
 * getdelim(), and for getline().  It is not normally available for use
 * in Windows applications, so, although not identical, substitute the
 * semantically similar ERANGE.
 */
#define EOVERFLOW  ERANGE
#endif

#undef  CRT_INLINE
#define CRT_INLINE  static __inline__ __attribute__((__always_inline__))

CRT_INLINE ssize_t getline_abort( int error_code )
{
  /* A local helper, to set errno and return getline()'s end-of-input state.
   */
  errno = error_code;
  return (ssize_t)(-1);
}

#define RESTRICT  __restrict__

ssize_t getdelim
( char **RESTRICT linebuf, size_t *RESTRICT len, int brk, FILE *RESTRICT stream )
{
  /* Capture a string of characters from the input stream,
   * up to and including the specified "brk" delimiter, or to EOF,
   * storing the resultant string in the designated buffer.
   *
   * Also serves as getline(), via this inline wrapper in <stdio.h>:
   *
   *  static __inline__ __attribute__((__always_inline__)) ssize_t getline
   *  ( char **RESTRICT linebuf, size_t *RESTRICT len, FILE *RESTRICT stream )
   *  { return getdelim( linebuf, len, '\n', stream ); }
   *
   */
  int nextchar = EOF;
  ssize_t count = (ssize_t)(0);

  /* Caller MUST pass us valid references to locations where the
   * buffer address, and its allocated length will be returned...
   */
  if( (linebuf == NULL) || (len == NULL) )
    /*
     * ...otherwise the call is invalid.
     */
    return getline_abort( EINVAL );

  /* Passing a NULL pointer as the stream reference may result
   * in a segmentation fault...
   */
  if( stream == NULL )
    /* ...so also provide a graceful exit, in this case.
     */
    return getline_abort( EBADF );

  if( feof( stream ) || ferror( stream ) )
    /*
     * When already at end-of-file, or following any persistent
     * prior stream I/O error, we have nothing to return.
     */
    return (ssize_t)(-1);

  /* Typically, the caller will initialize the line buffer to
   * zero length, with a NULL reference pointer; (POSIX allows
   * this, and even allows for a NULL pointer with a non-zero
   * initial length specification, but is not explicit about
   * how this case should be handled...
   */
  if( (*linebuf == NULL) && (*len > 0)
  /*
   * ...so we assume that we should allocate a new buffer
   * of the specified length...
   */
  && ((*linebuf = malloc( *len )) == NULL) )
    /*
     * ...but if that isn't feasible, revert to the typical
     * default initial zero length NULL buffer state).
     */
    *len = 0;

  /* Okay to accept input...
   * read character by character, until "brk" or EOF...
   */
  while( (nextchar != brk) && ((nextchar = fgetc( stream )) != EOF) )
  {
    if( ferror( stream ) )
      /* We caught an I/O error; bail out, assuming that fgetc() has
       * already set errno appropriately, and returning nothing.
       */
      return (ssize_t)(-1);

    if( count == SSIZE_MAX )
      /* We've read another character, but we've already accumulated
       * as many as we can account for in the return value; POSIX says
       * that we MAY fail, in this case.
       */
      return getline_abort( EOVERFLOW );

    /* We will store the resultant string into the buffer located
     * at the address pointed to by *linebuf; this MUST be a dynamically
     * allocated buffer of size as specified by *len, so we may increase
     * its size if necessary, (allowing space to accommodate the current
     * input character, and a terminating NUL).
     */
    if( (count + 2) > *len )
    { char *newbuf = realloc( *linebuf, *len + 64 );
      if( newbuf == NULL )
	/* Failed to expand the buffer; report insufficient memory.
	 */
	return getline_abort( ENOMEM );

      /* Buffer expansion was successful; update reference data.
       */
      *linebuf = newbuf;
      *len += 64;
    }

    /* We successfully read a character; append it to the buffer.
     */
    (*linebuf)[count++] = nextchar;
  }

  /* Finished the current string capture; ensure that the buffer
   * is properly terminated, by appending a NUL.
   */
  (*linebuf)[count] = '\0';

  /* If we've successfully read at least one character, then we
   * return the count of characters read, else we return nothing.
   */
  return (count > (ssize_t)(0)) ? count : (ssize_t)(-1);
}

/* $RCSfile$: end of file */
