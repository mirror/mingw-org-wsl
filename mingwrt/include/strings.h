/*
 * strings.h
 *
 * API declarations for POSIX.1-2008 string functions supported by MinGW.
 *
 * $Id$
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
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
#ifndef _STRINGS_H
#define _STRINGS_H
#pragma GCC system_header

/* All MinGW system headers must include this...
 */
#include <_mingw.h>

#ifndef RC_INVOKED
/* POSIX.1-2008 requires this header to expose the typedef for size_t; to
 * ensure consistency, we import this from GCC's own <stddef.h> header.
 */
#define __need_size_t
#include <stddef.h>

_BEGIN_C_DECLS

int __cdecl __MINGW_NOTHROW strcasecmp( const char *, const char * );
int __cdecl __MINGW_NOTHROW strncasecmp( const char *, const char *, size_t );

#ifndef __NO_INLINE__
/* Provide in-line implementations for each of the preceding two functions,
 * effectively aliasing them to their MSVCRT.DLL (non-standard) equivalents,
 * (for which we maintain prototypes in <parts/strings.h>).
 */
#include <parts/strings.h>

__CRT_ALIAS __JMPSTUB__(( FUNCTION = strcasecmp, REMAPPED = _stricmp ))
  int strcasecmp( const char *__s1, const char *__s2 )
  { return _stricmp( __s1, __s2 ); }

__CRT_ALIAS __JMPSTUB__(( FUNCTION = strncasecmp, REMAPPED = _strnicmp ))
  int strncasecmp( const char *__s1, const char *__s2, size_t __n )
  { return _strnicmp( __s1, __s2, __n ); }

#endif /* ! __NO_INLINE__ */

_END_C_DECLS

#endif /* ! RC_INVOKED */
#endif /* ! _STRINGS_H: $RCSfile$: end of file */
