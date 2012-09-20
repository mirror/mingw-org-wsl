/**
 * @file utime.h
 * @copy 2012 MinGW.org project
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
#ifndef	_UTIME_H_
#define	_UTIME_H_
#pragma GCC system_header
#include <_mingw.h>

#define __need_wchar_t
#define __need_size_t

#include <sys/types.h>

#ifndef RC_INVOKED
#include <stddef.h>
/*
 * Structure used by _utime function.
 */
struct _utimbuf
{
	time_t	actime;		/* Access time */
	time_t	modtime;	/* Modification time */
};
struct __utimbuf32
{
	__time32_t actime;
	__time32_t modtime;
};


#ifndef	_NO_OLDNAMES
/* NOTE: Must be the same as _utimbuf above. */
struct utimbuf
{
	time_t	actime;
	time_t	modtime;
};
#endif	/* Not _NO_OLDNAMES */

#ifdef	__cplusplus
extern "C" {
#endif

_CRTIMP int __cdecl __MINGW_NOTHROW	_utime (const char*, struct _utimbuf*);

#ifndef	_NO_OLDNAMES
_CRTIMP int __cdecl __MINGW_NOTHROW	utime (const char*, struct utimbuf*);
#endif	/* Not _NO_OLDNAMES */

_CRTIMP int __cdecl __MINGW_NOTHROW	_futime (int, struct _utimbuf*);

/* The wide character version, only available for MSVCRT versions of the
 * C runtime library. */
_CRTIMP int __cdecl __MINGW_NOTHROW	_wutime (const wchar_t*, struct _utimbuf*);

/* These require newer versions of msvcrt.dll (6.10 or higher).  */ 
struct __utimbuf64
{
	__time64_t actime;
	__time64_t modtime;
};

_CRTIMP int __cdecl __MINGW_NOTHROW	_utime64 (const char*, struct __utimbuf64*);
_CRTIMP int __cdecl __MINGW_NOTHROW	_wutime64 (const wchar_t*, struct __utimbuf64*);
_CRTIMP int __cdecl __MINGW_NOTHROW	_futime64 (int, struct __utimbuf64*);

_CRTIMP int __cdecl __MINGW_NOTHROW	_utime32 (const char*, struct __utimbuf32*);
_CRTIMP int __cdecl __MINGW_NOTHROW	_wutime32 (const wchar_t*, struct __utimbuf32*);
_CRTIMP int __cdecl __MINGW_NOTHROW	_futime32 (int, struct __utimbuf32*);

#ifndef _USE_32BIT_TIME_T
_CRTALIAS int __cdecl __MINGW_NOTHROW	_utime (const char* _v1, struct _utimbuf* _v2)	   { return(_utime64  (_v1,(struct __utimbuf64*)_v2)); }
_CRTALIAS int __cdecl __MINGW_NOTHROW	_wutime (const wchar_t* _v1, struct _utimbuf* _v2) { return(_wutime64 (_v1,(struct __utimbuf64*)_v2)); }
_CRTALIAS int __cdecl __MINGW_NOTHROW	_futime (int _v1, struct _utimbuf* _v2)		   { return(_futime64 (_v1,(struct __utimbuf64*)_v2)); }
#else

_CRTALIAS int __cdecl __MINGW_NOTHROW	_utime (const char* _v1, struct _utimbuf* _v2)	   { return(_utime32  (_v1,(struct __utimbuf32*)_v2)); }
_CRTALIAS int __cdecl __MINGW_NOTHROW	_wutime (const wchar_t* _v1, struct _utimbuf* _v2) { return(_wutime32 (_v1,(struct __utimbuf32*)_v2)); }
_CRTALIAS int __cdecl __MINGW_NOTHROW	_futime (int _v1, struct _utimbuf* _v2)		   { return(_futime32 (_v1,(struct __utimbuf32*)_v2)); }
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* Not RC_INVOKED */

#endif	/* Not _UTIME_H_ */
