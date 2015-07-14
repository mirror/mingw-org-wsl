/*
 * w32api.h
 *
 * Package version identification, operating system support level set up,
 * and "convenience" macros to be shared by all package header files.
 *
 * $Id$
 *
 * Written by Earnie Boyd  <earnie@users.sourceforge.net>
 * Copyright (C) 2001-2011, 2015, MinGW.org Project
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
#ifndef _W32API_H
#define _W32API_H
#pragma GCC system_header

/* Package version identification: formerly specified as a simple
 * dotted numeric pair representing major.minor, this doesn't adapt
 * well to the inclusion of the patch-level, since the dotted triplet
 * representation of major.minor.patch is not a valid representation
 * of a numeric entity.  Thus, from version 3.18 onwards we adopt a
 * representation which encodes the version as a long integer value,
 * expressing:
 *
 *   __W32API_VERSION = 1,000,000 * major + 1,000 * minor + patch
 */
#define __W32API_VERSION		3017000L
#define __W32API_MAJOR_VERSION		      3
#define __W32API_MINOR_VERSION		     17
#define __W32API_PATCH_LEVEL		      0

/* The underlying operating system platform version, and its
 * identifying macros for application support, are established by:
 */
#include <sdkddkver.h>

/* The following defines are for documentation purposes.  Although not used
 * within it, they were provided in earlier versions of the Win32 API, as a
 * convenience for users who wished to symbolically declare a minimum level
 * of required operating system and Internet Explorer version support, when
 * assigning WINVER, _WIN32_WINDOWS, _WIN32_WINNT, and _WIN32_IE values.
 *
 * Formerly defined as macros, these are now considered deprecated in favour
 * of manifest definitions from <sdkddkver.h>; hence, reimplement in terms of
 * static long integer constants, and flag as deprecated.
 */
#define __WIN32_DEPRECATED_ALIAS( __type__, __name__, __value__ )\
  static const __type__ __name__ __attribute__((__deprecated__)) = __value__;

/* _WIN32_WINDOWS and/or WINVER may be set to any of the following manifest
 * values, to specify a minimum Win9x support level requirement:
 *
 * 				 Old Name	Preferred Name
 * 				 -------------	-----------------
 */
__WIN32_DEPRECATED_ALIAS( long,  Windows95,	_WIN32_WINDOWS_95 )
__WIN32_DEPRECATED_ALIAS( long,  Windows98,	_WIN32_WINDOWS_98 )
__WIN32_DEPRECATED_ALIAS( long,  WindowsME,	_WIN32_WINDOWS_ME )

/* _WIN32_WINNT and/or WINVER may be set to any of the following manifest
 * values, to specify a minimum WinNT support level requirement:
 *
 * 				 Old Name	Preferred Name
 * 				 -------------	-----------------
 */
__WIN32_DEPRECATED_ALIAS( long,  WindowsNT4,	_WIN32_WINNT_NT4 )
__WIN32_DEPRECATED_ALIAS( long,  Windows2000,	_WIN32_WINNT_WIN2K )
__WIN32_DEPRECATED_ALIAS( long,  WindowsXP,	_WIN32_WINNT_WINXP )
__WIN32_DEPRECATED_ALIAS( long,  Windows2003,	_WIN32_WINNT_WS03 )
__WIN32_DEPRECATED_ALIAS( long,  WindowsVista,	_WIN32_WINNT_VISTA )

/* _WIN32_IE may be set to any of the following manifest values, to
 * specify a minimum Internet Explorer support level requirement:
 *
 * 				 Old Name	Preferred Name
 * 				 -------------	-----------------
 */
__WIN32_DEPRECATED_ALIAS( long,  IE3,		_WIN32_IE_IE30 )
__WIN32_DEPRECATED_ALIAS( long,  IE301, 	_WIN32_IE_IE301 )
__WIN32_DEPRECATED_ALIAS( long,  IE302, 	_WIN32_IE_IE302 )
__WIN32_DEPRECATED_ALIAS( long,  IE4,		_WIN32_IE_IE40 )
__WIN32_DEPRECATED_ALIAS( long,  IE401, 	_WIN32_IE_IE401 )
__WIN32_DEPRECATED_ALIAS( long,  IE5,		_WIN32_IE_IE50 )
__WIN32_DEPRECATED_ALIAS( long,  IE5a,		_WIN32_IE_IE50 )
__WIN32_DEPRECATED_ALIAS( long,  IE5b,		_WIN32_IE_IE50 )
__WIN32_DEPRECATED_ALIAS( long,  IE501, 	_WIN32_IE_IE501 )
__WIN32_DEPRECATED_ALIAS( long,  IE55,		_WIN32_IE_IE55 )
__WIN32_DEPRECATED_ALIAS( long,  IE56,		_WIN32_IE_IE56 )
__WIN32_DEPRECATED_ALIAS( long,  IE6,		_WIN32_IE_IE60 )
__WIN32_DEPRECATED_ALIAS( long,  IE601, 	_WIN32_IE_IE60SP1 )
__WIN32_DEPRECATED_ALIAS( long,  IE602, 	_WIN32_IE_IE60SP2 )
__WIN32_DEPRECATED_ALIAS( long,  IE7,		_WIN32_IE_IE70 )


/* Only Microsoft could attempt to justify this insanity: when building
 * a UTF-16LE application -- apparently their understanding of Unicode is
 * limited to this -- the C/C++ runtime requires that the user must define
 * the _UNICODE macro, while to use the Windows API's UTF-16LE capabilities,
 * it is the UNICODE macro, (without the leading underscore), which must be
 * defined.  The (bogus) explanation appears to be that it is the C standard
 * which dictates the requirement for the leading underscore, to avoid any
 * possible conflict with a user defined symbol; (bogus because the macro
 * must be user defined anyway -- it is not a private symbol -- and in
 * any case, the Windows API already reserves the UNICODE symbol as
 * a user defined macro, with equivalent intent.
 *
 * The real explanation, of course, is that this is just another example
 * of Microsoft irrationality; in any event, there seems to be no sane
 * scenario in which defining one without the other would be required,
 * or indeed would not raise potential for internal inconsistency, so we
 * ensure that either both are, or neither is defined.
 */
#if defined UNICODE && ! defined _UNICODE
# define _UNICODE  UNICODE
#elif defined _UNICODE && ! defined UNICODE
# define UNICODE  _UNICODE
#endif

#ifdef __cplusplus
/* When compiling C++ code, these macros provide a convenient notation,
 * for designating those sections of system header files which declare
 * prototypes for API functions with "C" binding...
 */
# define _EXTERN_C       extern "C"
# define _BEGIN_C_DECLS  extern "C" {
# define _END_C_DECLS    }

#else
/* ...while remaining transparent, when compiling C code.
 */
# define _EXTERN_C       extern
# define _BEGIN_C_DECLS
# define _END_C_DECLS
#endif

#endif /* ! _W32API_H: $RCSfile$: end of file */
