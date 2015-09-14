/*
 * string.h
 *
 * ISO-C standard header, with MSVC compatible extensions.
 *
 * $Id$
 *
 * Written by Rob Savoye <rob@cygnus.com>
 * Copyright (C) 1997-2000, 2002-2004, 2007, 2009, 2015, MinGW.org Project.
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
#ifndef _STRING_H
#define _STRING_H

/* All MinGW system headers must include this...
 */
#include <_mingw.h>

#ifndef RC_INVOKED
/* ISO-C requires this header to expose definitions for NULL and size_t,
 * retaining compatiblity with their fundamental <stddef.h> definitions.
 */
#define __need_NULL
#define __need_size_t
#ifndef __STRICT_ANSI__
 /* MSVC extends this requirement to include a definition of wchar_t,
  * (which contravenes strict ISO-C standards conformity).
  */
# define __need_wchar_t
#endif
#include <stddef.h>

_BEGIN_C_DECLS

/* Prototypes for the ISO-C Standard library string functions.
 */
_CRTIMP void * __cdecl __MINGW_NOTHROW	memchr (const void*, int, size_t) __MINGW_ATTRIB_PURE;
_CRTIMP int    __cdecl __MINGW_NOTHROW 	memcmp (const void*, const void*, size_t) __MINGW_ATTRIB_PURE;
_CRTIMP void * __cdecl __MINGW_NOTHROW 	memcpy (void*, const void*, size_t);
_CRTIMP void * __cdecl __MINGW_NOTHROW	memmove (void*, const void*, size_t);
_CRTIMP void * __cdecl __MINGW_NOTHROW	memset (void*, int, size_t);
_CRTIMP char * __cdecl __MINGW_NOTHROW	strcat (char*, const char*);
_CRTIMP char * __cdecl __MINGW_NOTHROW	strchr (const char*, int)  __MINGW_ATTRIB_PURE;
_CRTIMP int    __cdecl __MINGW_NOTHROW	strcmp (const char*, const char*)  __MINGW_ATTRIB_PURE;
_CRTIMP int    __cdecl __MINGW_NOTHROW	strcoll (const char*, const char*);	/* Compare using locale */
_CRTIMP char * __cdecl __MINGW_NOTHROW	strcpy (char*, const char*);
_CRTIMP size_t __cdecl __MINGW_NOTHROW	strcspn (const char*, const char*)  __MINGW_ATTRIB_PURE;
_CRTIMP char * __cdecl __MINGW_NOTHROW	strerror (int); /* NOTE: NOT an old name wrapper. */

_CRTIMP size_t __cdecl __MINGW_NOTHROW	strlen (const char*)  __MINGW_ATTRIB_PURE;
_CRTIMP char * __cdecl __MINGW_NOTHROW	strncat (char*, const char*, size_t);
_CRTIMP int    __cdecl __MINGW_NOTHROW	strncmp (const char*, const char*, size_t)  __MINGW_ATTRIB_PURE;
_CRTIMP char * __cdecl __MINGW_NOTHROW	strncpy (char*, const char*, size_t);
_CRTIMP char * __cdecl __MINGW_NOTHROW	strpbrk (const char*, const char*)  __MINGW_ATTRIB_PURE;
_CRTIMP char * __cdecl __MINGW_NOTHROW	strrchr (const char*, int)  __MINGW_ATTRIB_PURE;
_CRTIMP size_t __cdecl __MINGW_NOTHROW	strspn (const char*, const char*)  __MINGW_ATTRIB_PURE;
_CRTIMP char * __cdecl __MINGW_NOTHROW	strstr (const char*, const char*)  __MINGW_ATTRIB_PURE;
_CRTIMP char * __cdecl __MINGW_NOTHROW	strtok (char*, const char*);
_CRTIMP size_t __cdecl __MINGW_NOTHROW	strxfrm (char*, const char*, size_t);

#ifndef __STRICT_ANSI__
/*
 * Extra non-ANSI functions provided by the CRTDLL library
 */
_CRTIMP char * __cdecl __MINGW_NOTHROW	_strerror (const char *);
_CRTIMP void * __cdecl __MINGW_NOTHROW	_memccpy (void*, const void*, int, size_t);
_CRTIMP int    __cdecl __MINGW_NOTHROW 	_memicmp (const void*, const void*, size_t);
_CRTIMP char * __cdecl __MINGW_NOTHROW 	_strdup (const char*) __MINGW_ATTRIB_MALLOC;
_CRTIMP int    __cdecl __MINGW_NOTHROW	_strcmpi (const char*, const char*);
_CRTIMP int    __cdecl __MINGW_NOTHROW	_stricoll (const char*, const char*);
_CRTIMP char * __cdecl __MINGW_NOTHROW	_strlwr (char*);
_CRTIMP char * __cdecl __MINGW_NOTHROW	_strnset (char*, int, size_t);
_CRTIMP char * __cdecl __MINGW_NOTHROW	_strrev (char*);
_CRTIMP char * __cdecl __MINGW_NOTHROW	_strset (char*, int);
_CRTIMP char * __cdecl __MINGW_NOTHROW	_strupr (char*);
_CRTIMP void   __cdecl __MINGW_NOTHROW	_swab (const char*, char*, size_t);

/* MSVC's non-ANSI _stricmp() and _strnicmp() functions must also be
 * prototyped here, but we need to share them with <strings.h>, where
 * we declare their POSIX strcasecmp() and strncasecmp() equivalents.
 */
#define _FAKE_STRINGS_H_SOURCED 1
#include <parts/strings.h>

# ifdef __MSVCRT__
 /* These were not present in the CRTDLL prior to the first release of
  * MSVCRT.DLL, but are available in all versions of that library.
  */
_CRTIMP int    __cdecl __MINGW_NOTHROW  _strncoll(const char*, const char*, size_t);
_CRTIMP int    __cdecl __MINGW_NOTHROW  _strnicoll(const char*, const char*, size_t);
# endif

# ifndef _NO_OLDNAMES
 /* Non-underscore decorated versions of non-ANSI functions. They live in the
  * OLDNAMES libraries, whence they provide a little extra portability.
  */
_CRTIMP void * __cdecl __MINGW_NOTHROW	memccpy (void*, const void*, int, size_t);
_CRTIMP int    __cdecl __MINGW_NOTHROW	memicmp (const void*, const void*, size_t);
_CRTIMP char * __cdecl __MINGW_NOTHROW	strdup (const char*) __MINGW_ATTRIB_MALLOC;
_CRTIMP int    __cdecl __MINGW_NOTHROW	strcmpi (const char*, const char*);
_CRTIMP int    __cdecl __MINGW_NOTHROW	stricmp (const char*, const char*);
_CRTIMP int    __cdecl __MINGW_NOTHROW	stricoll (const char*, const char*);
_CRTIMP char * __cdecl __MINGW_NOTHROW	strlwr (char*);
_CRTIMP int    __cdecl __MINGW_NOTHROW	strnicmp (const char*, const char*, size_t);
_CRTIMP char * __cdecl __MINGW_NOTHROW	strnset (char*, int, size_t);
_CRTIMP char * __cdecl __MINGW_NOTHROW	strrev (char*);
_CRTIMP char * __cdecl __MINGW_NOTHROW	strset (char*, int);
_CRTIMP char * __cdecl __MINGW_NOTHROW	strupr (char*);

#  ifndef _UWIN
  /* FIXME: Do we really care that UWin doesn't support this?  We are
   * under no obligation to support UWin.
   */
_CRTIMP void   __cdecl __MINGW_NOTHROW	swab (const char*, char*, size_t);

#  endif /* ! _UWIN */
# endif /* ! _NO_OLDNAMES */

# define _FAKE_WCHAR_H_SOURCED 1
# define __need_wstring_function_prototypes
 /* This inclusion of <wchar.h> string function prototypes is required for
  * MSVC <string.h> compatibility.  Strictly conforming ISO-C applications
  * should include <wchar.h>; they should not rely on this anomaly.
  */
# include <parts/wchar.h>

#endif /* ! __STRICT_ANSI__ */

_END_C_DECLS

#endif /* ! RC_INVOKED */
#endif /* ! _STRING_H: $RCSfile$: end of file */
