/**
 * @file init.c
 * Copyright (C) 2012 MinGW.org project
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
 */

/* ---------------------------------------------------------------------------
 * Implements the runtime initialisation code to populate the argument
 * vector, which will subsequently be passed to the main() function.
 *
 * Written by Rob Savoye <rob@cygnus.com>
 * Updated by Mumit Khan <khan@xraylith.wisc.edu>,
 *   Earnie Boyd <earnie@users.sourceforge.net>, and
 *   Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 1997, 1998, 1999, 2004, 2012, MinGW Project
 *
 * This file was formerly #included by both crt1.c and dllcrt1.c;
 * it is now used only by crt1.c
 *
 * ---------------------------------------------------------------------------
 */
#include <glob.h>

/* Access to a standard 'main'-like argument count and list. Also included
 * is a table of environment variables.
 */
int     _argc = 0;
char ** _argv = 0;

/* NOTE: Thanks to Pedro A. Aranda Gutiirrez <paag@tid.es> for pointing
 * this out to me. GetMainArgs (used below) takes a fourth argument
 * which is an int that controls the globbing of the command line. If
 * _CRT_glob is non-zero the command line will be globbed (e.g. *.*
 * expanded to be all files in the startup directory). In the mingw32
 * library a _CRT_glob variable is defined as being -1, enabling
 * this command line globbing by default. To turn it off and do all
 * command line processing yourself (and possibly escape bogons in
 * MS's globbing code) include a line in one of your source modules
 * defining _CRT_glob and setting it to zero, like this:
 *  int _CRT_glob = 0;
 */
extern int _CRT_glob;
#define _CRT_GLOB_OPT	_CRT_glob & __CRT_GLOB_USE_MSVCRT__

#define ARGV_INLINE  static __inline__ __attribute__((__always_inline__))

typedef struct { int newmode; } _startupinfo;
extern void __getmainargs( int *, char ***, char ***, int, _startupinfo * );

#define ARGV_ESCAPE     __CRT_GLOB_ESCAPE_CHAR__
#define ARGV_SQUOTE     __CRT_GLOB_USE_SINGLE_QUOTE__
#define ARGV_NOGROUP    __CRT_GLOB_BRACKET_GROUPS__

ARGV_INLINE
int do_glob( const char *pattern, int flags, int (*errfn)(), glob_t *gl_buf )
{
  /* Helper used by the MinGW replacement command line globbing handler,
   * to invoke the glob() function, while ensuring that the GLOB_APPEND
   * option is enabled at the appropriate time.
   */
  if( gl_buf->gl_pathc > 0 )
    flags |= GLOB_APPEND;
  return __mingw_glob( pattern, flags, errfn, gl_buf );
}

ARGV_INLINE
char *backslash( int count, char *buf )
{
  /* Helper used by the MinGW replacement command line globbing handler,
   * to provide appropriate handling of backslashes while preparing the
   * command line arguments for globbing.
   */
  while( count-- )
    *buf++ = '\\';
  return buf;
}

ARGV_INLINE
char *unquote( int quote, int altquote, int escape, int *state, char *buf )
{
  /* Helper used by the MinGW replacement command line globbing handler,
   * to provide a single level of reduction for balanced quotation marks,
   * while preparing the command line arguments for globbing.
   */
  buf = backslash( escape >> 1, buf );
  if( (escape & 1) || (*state == altquote) )
    /*
     * In this case, the quotation mark is to be interpreted as a literal,
     * and is NOT a candidate for reduction...
     */
    *buf++ = quote;
  else
    /* ...while this is the more usual case, of a quotation mark used to
     * delimit a single argument; it must be reduced.
     */
    *state ^= quote;
  return buf;
}

ARGV_INLINE
void __mingw_setargv( const char *cmdline )
{
  /* Implementation of the MinGW replacement command line interpreter.
   */
  char cmdbuf[1 + strlen( cmdline ) << 1];
  int c, gotarg = 0, quoted = 0, bracket = 0, bslash = 0;
  char *argptr = cmdbuf; const char *cmdptr = cmdline;
  glob_t gl_argv;

  /* Capture any non-default globbing options, which the user may have
   * specified via a custom setting for _CRT_glob.
   */
  int gl_opts = GLOB_NOCHECK;
  if( _CRT_glob & __CRT_GLOB_CASE_SENSITIVE__ )
    gl_opts |= GLOB_CASEMATCH;

  /* We explicitly DO NOT use the GLOB_DOOFFS capability; ensure that
   * the associated field, in the glob_t structure, is initialised to
   * correctly reflect this.
   */
  gl_argv.gl_offs = 0;

  /* Scan the command line, and prepare it for globbing.
   */
  while( c = *cmdptr++ )
  {
    /* Got a character to process...
     */
    switch( c )
    {
      /* Specific characters, which serve as globbing tokens,
       * need special handling.
       */
      case '\\':
	/* We don't (yet) know if this is a literal backslash,
	 * (directory separator), or an escape for a following
	 * quote character; just note its presence, until we
	 * have looked far enough ahead to decide.
	 */
	++bslash;
	break;

      case '[':
	/* POSIX defines this as a globbing token, (introducing
	 * a character group); we don't support this by default,
	 * so defeat it, unless the extended behaviour has been
	 * requested by the user.
	 */
	bracket = (_CRT_glob & ARGV_NOGROUP) ? 0 : ARGV_NOGROUP;

      case '*':
      case '?':
	/* These standard globbing tokens...
	 */
      case ARGV_ESCAPE:
	/* ...and the escape character itself, need to be escaped
	 * when they appear in any context in which they should be
	 * interpreted literally, rather than globbed.
	 */
	argptr = backslash( bslash, argptr );
	if( quoted || (bracket == ARGV_NOGROUP) || (c == ARGV_ESCAPE) )
	  *argptr++ = ARGV_ESCAPE;
	bracket = bslash = 0;
	*argptr++ = c;
	break;

      case '"':
	/* The double quote always acts as an argument quoting
	 * character, (unless escaped); handle it accordingly.
	 */
	argptr = unquote( c, '\'', bslash, &quoted, argptr );
	gotarg = 1; bslash = 0;
	break;

      case '\'':
	/* POSIX also defines the single quote as a quoting
	 * character, but MS-Windows does not; we offer this
	 * extended handling...
	 */
	if( _CRT_glob & ARGV_SQUOTE )
	{
	  /* ...only when the user has explicitly enabled the
	   * POSIX compatible extended quoting option.
	   */
	  argptr = unquote( c, '"', bslash, &quoted, argptr );
	  gotarg = 1; bslash = 0;
	  break;
	}

      default:
	/* With one exception, any other character is handled
	 * literally, after flushing out any pending backslashes.
	 */
	argptr = backslash( bslash, argptr );
	if( (quoted == 0) && isspace( c ) )
	{
	  /* The one exception is any white space character,
	   * when it is not contained within quotes; this acts
	   * as an argument separator, (or is simply discarded
	   * if there is no argument already collected)...
	   */
	  if( gotarg || (argptr > cmdbuf) )
	  {
	    /* ...so, when there is a argument pending, we may
	     * now add it to the globbed argument vector.
	     */
	    *argptr = '\0';
	    do_glob( argptr = cmdbuf, gl_opts, NULL, &gl_argv );
	    gotarg = 0;
	  }
	}
	else
	  /* In every other case, we simply collect the current
	   * literal character into the next pending argument.
	   */
	  *argptr++ = c;

	/* Irrespective of how we handled the current character,
	 * we can be certain that there are no pending backslashes
	 * by the time we get to here.
	 */
	bslash = 0;
    }
  }
  /* Finally, when we've run out of command line characters to process,
   * flush out any final pending backslashes, ...
   */
  argptr = backslash( bslash, argptr );
  if( gotarg || (argptr > cmdbuf) )
  {
    /* ...and add any final pending argument to the globbed vector.
     */
    *argptr = '\0';
    do_glob( argptr = cmdbuf, gl_opts, NULL, &gl_argv );
  }
  /* ...and store the resultant globbed vector into the "argc" and "argv"
   * variables to be passed to main(); note that this allows us to safely
   * discard our working glob_t structure, but we MUST NOT globfree() it,
   * as that would destroy the content of "argv".
   */
  _argc = gl_argv.gl_pathc;
  _argv = gl_argv.gl_pathv;
}

static void _mingw32_init_mainargs()
{
  /* Initialise the _argc, _argv and environ variables.
   *
   * FIXME: consider renaming to _mingw_init_mainargs?
   * (Both here, and in crt1.c)?
   */
  if( (_CRT_glob & __CRT_GLOB_USE_MINGW__) == 0 )
  {
    /* This is the old start-up mechanism, in which we use a start-up
     * hook provided by Microsoft's runtime library to initialise the
     * argument and environment vectors.
     *
     * Note that the preferred method for accessing the environment
     * vector is via a direct pointer retrieved from the runtime DLL,
     * using a system call declared in stdlib.h; thus, we don't need
     * to preserve the pointer returned by the start-up hook, so we
     * may simply capture it locally, and subsequently discard it.
     */
    char **dummy_envp; _startupinfo start_info = { 0 };
    __getmainargs( &_argc, &_argv, &dummy_envp, _CRT_GLOB_OPT, &start_info );
  }
  else
    /* Here, we implement a new, more POSIX compatible mechanism,
     * for initialising the argument vector; note that we delegate
     * to the previously defined inline function, which avoids the
     * broken globbing behaviour of some more recent versions of
     * MSVCRT.DLL
     */
    __mingw_setargv( GetCommandLine() );
}
