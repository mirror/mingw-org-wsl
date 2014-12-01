/*
 * cryptnam.c
 *
 * Implementation of a cryptographically secure random character sequence
 * generator; this is specifically tailored to satisfy the requirement for
 * replacement of the sequence of six 'XXXXXX's, within the templates for
 * the file name, or the directory name, in MinGW.org implementations of
 * the mkstemp(3) and mkdtemp(3) functions, respectively.
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
#define WIN32_LEAN_AND_MEAN

#include <limits.h>
#include <windows.h>
#include <wincrypt.h>
#include <string.h>

#define CRYPTO_INLINE  static __inline__ __attribute__((__always_inline__))

CRYPTO_INLINE HCRYPTPROV crypto_provider( void )
#define RSA_MODE( OPT, FLAG )  PROV_RSA_##OPT, CRYPT_##FLAG
{
  /* Helper to establish a cryptographic provider context for the
   * cryptographically secure random number generator.
   *
   * At the outset, this provider requires initialization.
   */
  static HCRYPTPROV id = (HCRYPTPROV)(0);

  /* On second, and subsequent calls, it should already have been
   * initialized...
   */
  if( id != (HCRYPTPROV)(0) )
    /*
     * ...so, simply return the saved context handle...
     */
    return id;

  /* If we're still here, this must be the first call, (or any
   * preceding call failed to initialize the context); initialize
   * it now, and if successful...
   */
  if( CryptAcquireContext( &id, NULL, NULL, RSA_MODE( FULL, VERIFYCONTEXT ) ) )
    /*
     * ...return the now-initialized context handle.
     */
    return id;

  /* And finally, if we ever get to here, the context remains
   * uninitialized; ensure that it remains marked as such, and
   * return the uninitialized context handle.
   */
  return id = (HCRYPTPROV)(0);
}

CRYPTO_INLINE void *crypto_randomize( void *buf, size_t buflen )
{
  /* Helper to fill a specified buffer, of specified length,
   * with cryptographically secure random bytes...
   */
  if( CryptGenRandom( crypto_provider(), buflen, buf ) )
    /*
     * ...returning a pointer to the buffer, when successful...
     */
    return buf;

  /* ...or nothing, otherwise.
   */
  return NULL;
}

CRYPTO_INLINE unsigned char *crypto_random_filename_char( unsigned char *caret )
{
  /* Helper to generate a random sequence of characters, suitable for
   * use in file names; although there are other valid possibilities, we
   * restrict this to the set of lower case ASCII alpha-numerics, giving
   * us 36 degrees of freedom for each character; (note that we cannot
   * gain additional degrees of freedom by using mixed case, because
   * the MS-Windows file system is case-insensitive).
   */
  const unsigned char span = 'z' - 'a' + 1 + '9' - '0' + 1;

  /* We also wish to ensure that each of the possible 36 characters has
   * an equal probability of selection; thus, of the UCHAR_MAX possible
   * raw byte selections, we want to consider at most the largest even
   * multiple of the 36 character span, which lies below the UCHAR_MAX
   * limit, (which, since zero is a valid choice, is one less than the
   * result of discounting the remainder from modulo division).
   */
  const unsigned char max = UCHAR_MAX - (UCHAR_MAX % span) - 1;

  /* Deposit randomly selected characters at the "caret" location...
   */
  do { if( crypto_randomize( caret, sizeof( unsigned char ) ) == NULL )
	 /*
	  * ...bailing out, on any failure of the sequence generator...
	  */
         return NULL;

       /* ...until we get one which is within the largest possible
	* subset which yields equal probabilty to each outcome, when
	* reduced modulo the 36 available degrees of freedom.
	*/
     } while( *caret > max );

  /* Perform the modulo 36 reduction, and offset the result into the
   * alpha-numeric character range...
   */
  *caret = '0' + (*caret % span);
  /*
   * ...while discounting those unsuitable characters which lie within
   * the range, between '9' and 'a' exclusively.
   */
  if( *caret > '9' ) *caret += 'a' - '9' - 1;

  /* Finally, return the "caret" location, indicating the successful
   * transformation of the character in that position.
   */
  return caret;
}

char *__mingw_crypto_tmpname( char *template )
{
  /* Helper function, based on Microsoft's wincrypt API, to construct
   * the candidate names for temporary files, both in a less predictable
   * manner than Microsoft's _mktemp() function, and without suffering
   * its inherent limitation of allowing no more than 26 file names
   * per template per process thread.
   *
   * We begin by locating the position, within the given template,
   * where the string of six replaceable 'XXXXXX's should begin.
   */
  char *tail = template + strlen( template ) - 6;

  /* Provided this appears sane -- i.e. it at least doesn't place the
   * six character "tail" before the start of the template itself...
   */
  if( tail >= template )
  {
    /* ...then, walk over each of the six bytes of the "tail", until
     * we reach the NUL terminator...
     */
    while( *tail )
    {
      /* ...checking that each byte is initially ASCII 'X', as POSIX
       * requires them to be; (note that we don't consider that these
       * may be MBCS trail bytes, since the required 'X' is a single
       * byte in an MBCS representation anyway)...
       */
      if( (*tail != 'X') || (crypto_random_filename_char( tail++ ) == NULL) )
	/*
	 * ...bailing out, and returning nothing, if not.
	 */
	return NULL;
    }
  }
  /* Finally, when we have successfully replaced all six 'XXXXXX's,
   * we return the modified template, in place.
   */
  return template;
}

/* $RCSfile$: end of file */
