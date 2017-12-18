/*
 * strtok_r.c
 *
 * Implementation of "re-entrant" version of ISO-C strtok() function.
 *
 * $Id$
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2017, MinGW.org Project.
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
#include <string.h>

char *strtok_r
(char *__restrict__ s, const char *__restrict__ sep, char **__restrict__ state)
{
  /* "Re-entrant" version of ISO-C strtok() function; maintains state
   * via caller provided pointer variable, to avoid interference between
   * concurrent invocations on distinct source strings.  Requires initial
   * call with non-NULL "s", to retrieve the first token and initialize
   * "state", followed by repeated calls with "s" == NULL, to retrieve
   * subsequent tokens.
   */
  if( s == NULL )
    /* Non-initialization call; retrieve previously saved state.
     */
    s = *state;

  /* Step over any leading separator characters, at the beginning of "s";
   * check that this didn't take us all the way to the terminating NUL...
   */
  if( *(s += strspn (s, sep)) == '\0' )
  {
    /* ...or if it did, initialize/reset "state", to indicate that there
     * are no (more) tokens to retrieve; return NULL token, to indicate
     * that there are none available.
     */
    *state = s;
    return NULL;
  }
  /* Locate the first separator charactor, if any, following the current
   * token; reset "state" to mark its position, then, ensuring that we
   * never advance beyond the terminal NUL of "s"...
   */
  if( *(*state = s + strcspn (s, sep)) != '\0' )
    /* ...when an actual separator has been identified, replace it with
     * NUL, to terminate the token, and advance "state" to the point at
     * which scanning for any potential "next" token should resume.
     */
    *(*state)++ = '\0';

  return s;
}

/* $RCSfile$: end of file */
