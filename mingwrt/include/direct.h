/*
 * direct.h
 *
 * Functions for manipulating paths and directories, (included from io.h),
 * and functions for manipulating the current drive assignment.
 *
 * $Id$
 *
 * Written by Rob Savoye <rob@cygnus.com>
 * Copyright (C) 1997, 1999-2001, 2003, 2004, 2007, 2016, MinGW.org Project.
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
#ifndef _DIRECT_H
#pragma GCC system_header
#define _DIRECT_H

#define __DIRECT_H_SOURCED__
/* All MinGW headers are required to include <_mingw.h>; additionally,
 * much of the content which we need here is defined in <io.h>, but we
 * also need the declaration of the _getdiskfree() function prototype,
 * and the definition for its associated _diskfree_t data structure,
 * from <dos.h>; thus, we may simply include <dos.h> here, and let
 * it take care of including both <mingw.h> and <io.h> for us.
 */
#include <dos.h>

#undef __DIRECT_H_SOURCED__
#ifndef RC_INVOKED

_BEGIN_C_DECLS

/* Functions for manipulating disk drive selection.
 */
_CRTIMP __cdecl __MINGW_NOTHROW  int _getdrive (void);
_CRTIMP __cdecl __MINGW_NOTHROW  unsigned long _getdrives(void);
_CRTIMP __cdecl __MINGW_NOTHROW  int _chdrive (int);
_CRTIMP __cdecl __MINGW_NOTHROW  char *_getdcwd (int, char*, int);

/* The following group of functions  are available only within
 * MSVCRT.DLL, (i.e. they are NOT provided by CRTDLL.DLL); they
 * are also declared in <wchar.h>, hence avoid declaring them a
 * second time.
 */
#if defined __MSVCRT__ && ! defined _WDIRECT_DEFINED

_CRTIMP __cdecl __MINGW_NOTHROW  int _wchdir (const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *_wgetcwd (wchar_t *, int);
_CRTIMP __cdecl __MINGW_NOTHROW  wchar_t *_wgetdcwd (int, wchar_t *, int);
_CRTIMP __cdecl __MINGW_NOTHROW  int _wmkdir (const wchar_t *);
_CRTIMP __cdecl __MINGW_NOTHROW  int _wrmdir (const wchar_t *);

#define _WDIRECT_DEFINED
#endif	/* __MSVCRT__ && !_WDIRECT_DEFINED */

_END_C_DECLS

#endif	/* ! RC_INVOKED */
#endif  /* !_DIRECT_H: $RCSfile$: end of file */
