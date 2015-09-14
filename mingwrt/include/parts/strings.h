/*
 * parts/strings.h
 *
 * Internal header file, declaring function prototypes which we require
 * to be declared in our POSIX.1 conforming <strings.h> header, but for
 * which MSVC expects to find declarations in <string.h>.
 *
 * $Id$
 *
 * Written by Keith Marshall  <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2015, MinGW.org Project.
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
#if _FAKE_STRINGS_H_SOURCED
/*
 * Since we expect this part-header to be sourced exclusively by other
 * system headers, (nominally <strings.h>), we don't apply any conventional
 * multiple inclusion guard; rather, we rely on the guard within <strings.h>
 * itself, but allow other headers to fake it for one-shot inclusion...
 */
# undef _FAKE_STRINGS_H_SOURCED

#elif ! defined _STRINGS_H
/*
 * ...otherwise, we fail if the <strings.h> guard is not in place.
 */
# error "Never include <parts/strings.h> directly; use <strings.h> instead"
#endif

/* These are the MSVCRT.DLL equivalents for POSIX.1's strcasecmp() and
 * strncasecmp() functions, for which we provide in-line implementations
 * in <strings.h> respectively; MSVC expects to find these prototypes in
 * <string.h>, but we also need them in <strings.h>.
 */
_CRTIMP int __cdecl __MINGW_NOTHROW  _stricmp( const char *, const char * );
_CRTIMP int __cdecl __MINGW_NOTHROW _strnicmp( const char *, const char *, size_t );

/* $RCSfile$: end of file */
