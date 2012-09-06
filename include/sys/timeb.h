/**
 * @file timeb.h
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
#ifndef	_TIMEB_H_
#define	_TIMEB_H_

/*
 * Support for the UNIX System V ftime system call.
 */

/* All the headers include this file. */
#include <_mingw.h>
#include <sys/types.h>

#ifndef	RC_INVOKED

/*
 * TODO: Structure not tested.
 */
struct _timeb
{
	time_t	time;
	short	millitm;
	short	timezone;
	short	dstflag;
};

#if __MSVCRT_VERSION__ >= 0x0800
/*
 * TODO: Structure not tested.
 */
struct __timeb32
{
	__time32_t	time;
	short	millitm;
	short	timezone;
	short	dstflag;
};
#endif /* __MSVCRT_VERSION__ >= 0x0800 */

#ifndef	_NO_OLDNAMES
/*
 * TODO: Structure not tested.
 */
struct timeb
{
	time_t	time;
	short	millitm;
	short	timezone;
	short	dstflag;
};
#endif

#ifdef	__cplusplus
extern "C" {
#endif

/* TODO: Not tested. */
_CRTIMP void __cdecl __MINGW_NOTHROW	_ftime (struct _timeb*);

#ifndef	_NO_OLDNAMES
/* FIXME for __MSVCRT_VERSION__ >= 0x0800 */
_CRTIMP void __cdecl __MINGW_NOTHROW	ftime (struct timeb*);
#endif	/* Not _NO_OLDNAMES */

/* This requires newer versions of msvcrt.dll (6.10 or higher).  */ 
#if __MSVCRT_VERSION__ >= 0x0601
struct __timeb64
{
  __time64_t time;
  short millitm;
  short timezone;
  short dstflag;
};

_CRTIMP void __cdecl __MINGW_NOTHROW	_ftime64 (struct __timeb64*);
#endif /* __MSVCRT_VERSION__ >= 0x0601 */

#if __MSVCRT_VERSION__ >= 0x0800
_CRTIMP void __cdecl __MINGW_NOTHROW	_ftime32 (struct __timeb32*);
#ifndef _USE_32BIT_TIME_T
_CRTALIAS void __cdecl __MINGW_NOTHROW	_ftime (struct _timeb* _v) { return(_ftime64 ((struct __timeb64*)_v)); }
#else
_CRTALIAS void __cdecl __MINGW_NOTHROW	_ftime (struct _timeb* _v) { return(_ftime32 ((struct __timeb32*)_v)); }
#endif
#endif /* __MSVCRT_VERSION__ >= 0x0800 */

#ifdef	__cplusplus
}
#endif

#endif	/* Not RC_INVOKED */

#endif	/* Not _TIMEB_H_ */
