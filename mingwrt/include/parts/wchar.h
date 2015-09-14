/*
 * parts/wchar.h
 *
 * Internal header file, declaring types and structures which nominally
 * originate from <wchar.h>, but which POSIX, or MSVC, require to be made
 * visible on inclusion of certain other headers, without inclusion of
 * <wchar.h> itself.
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
#if _FAKE_WCHAR_H_SOURCED
/*
 * Since we expect this part-header to be sourced exclusively by other
 * system headers, (nominally <wchar.h>), we don't apply any conventional
 * multiple inclusion guard; rather, we rely on the guard within <wchar.h>
 * itself, but allow other headers to fake it for one-shot inclusion...
 */
# undef _FAKE_WCHAR_H_SOURCED

#elif ! defined _WCHAR_H
/*
 * ...otherwise, we fail if the <wchar.h> guard is not in place.
 */
# error "Never include <parts/wchar.h> directly; use <wchar.h> instead"
#endif

#if defined _WCHAR_H || defined __need_wstring_function_prototypes
/*
 * Wide character versions of the ISO-C standard string functions.
 */
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  wcscat (wchar_t *, const wchar_t *);
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  wcschr (const wchar_t *, wchar_t);
_CRTIMP int       __cdecl __MINGW_NOTHROW  wcscmp (const wchar_t *, const wchar_t *);
_CRTIMP int       __cdecl __MINGW_NOTHROW  wcscoll (const wchar_t *, const wchar_t *);
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  wcscpy (wchar_t *, const wchar_t *);
_CRTIMP size_t    __cdecl __MINGW_NOTHROW  wcscspn (const wchar_t *, const wchar_t *);
_CRTIMP size_t    __cdecl __MINGW_NOTHROW  wcslen (const wchar_t *);
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  wcsncat (wchar_t *, const wchar_t *, size_t);
_CRTIMP int       __cdecl __MINGW_NOTHROW  wcsncmp (const wchar_t *, const wchar_t *, size_t);
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  wcsncpy (wchar_t *, const wchar_t *, size_t);
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  wcspbrk (const wchar_t *, const wchar_t *);
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  wcsrchr (const wchar_t *, wchar_t);
_CRTIMP size_t    __cdecl __MINGW_NOTHROW  wcsspn (const wchar_t *, const wchar_t *);
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  wcsstr (const wchar_t *, const wchar_t *);
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  wcstok (wchar_t *, const wchar_t *);
_CRTIMP size_t    __cdecl __MINGW_NOTHROW  wcsxfrm (wchar_t *, const wchar_t *, size_t);

#ifndef __STRICT_ANSI__
/* UTF-16LE versions of non-ANSI string functions provided by CRTDLL.
 */
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  _wcsdup (const wchar_t *);
_CRTIMP int       __cdecl __MINGW_NOTHROW  _wcsicmp (const wchar_t *, const wchar_t *);
_CRTIMP int       __cdecl __MINGW_NOTHROW  _wcsicoll (const wchar_t *, const wchar_t *);
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  _wcslwr (wchar_t*);
_CRTIMP int       __cdecl __MINGW_NOTHROW  _wcsnicmp (const wchar_t *, const wchar_t *, size_t);
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  _wcsnset (wchar_t *, wchar_t, size_t);
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  _wcsrev (wchar_t *);
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  _wcsset (wchar_t *, wchar_t);
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  _wcsupr (wchar_t *);

#ifdef __MSVCRT__
_CRTIMP int       __cdecl __MINGW_NOTHROW  _wcsncoll (const wchar_t *, const wchar_t *, size_t);
_CRTIMP int       __cdecl __MINGW_NOTHROW  _wcsnicoll (const wchar_t *, const wchar_t *, size_t);

/* A wide character counterpart to the strerror() API was introduced in
 * MSVCR70.DLL, and subsequently back-ported to MSVCRT.DLL in WinXP.
 */
#if __MSVCRT_VERSION__ >= __MSVCR70_DLL || NTDDI_VERSION >= NTDDI_WINXP
 /*
  * These are are the wide character counterparts to the strerror()
  * function itself, and the _strerror() function, respectively.
  */
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  _wcserror (int);
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW __wcserror (const wchar_t *);

#endif /* MSVCR70.DLL / WinXP */
#endif /* __MSVCRT__ */

/* MSVCRT.DLL provides neither _wcscmpi() nor wcscmpi(); the heritage
 * is uncertain, but for the convenience, (and portability), of legacy
 * applications which assume wcscmpi() should be available:
 */
#define _wcscmpi _wcsicmp
int __cdecl __MINGW_NOTHROW wcscmpi (const wchar_t *, const wchar_t *);

#if ! defined __NO_INLINE__ && ! defined __have_wcscmpi
__CRT_ALIAS __JMPSTUB__(( FUNCTION = wcscmpi, REMAPPED = _wcsicmp ))
  int wcscmpi (const wchar_t * __ws1, const wchar_t * __ws2)
  { return _wcsicmp (__ws1, __ws2); }

# define __have_wcscmpi
#endif

#ifndef _NO_OLDNAMES
 /* Older CRTDLL versions may have provided these alternatively named
  * functions; we continue to support them, via the OLDNAME libraries:
  */
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  wcsdup (const wchar_t*);
_CRTIMP int       __cdecl __MINGW_NOTHROW  wcsicmp (const wchar_t*, const wchar_t*);
_CRTIMP int       __cdecl __MINGW_NOTHROW  wcsicoll (const wchar_t*, const wchar_t*);
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  wcslwr (wchar_t*);
_CRTIMP int       __cdecl __MINGW_NOTHROW  wcsnicmp (const wchar_t*, const wchar_t*, size_t);
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  wcsnset (wchar_t*, wchar_t, size_t);
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  wcsrev (wchar_t*);
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  wcsset (wchar_t*, wchar_t);
_CRTIMP wchar_t * __cdecl __MINGW_NOTHROW  wcsupr (wchar_t*);

#endif /* ! _NO_OLDNAMES */

#endif /* ! __STRICT_ANSI__ */
#endif /* __need_wstring_function_prototypes */

/* $RCSfile$: end of file */
