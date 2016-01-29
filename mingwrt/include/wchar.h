/*
 * wchar.h
 *
 * Declarations relating to support for wide characters; many are simply
 * inherited by (sub-optimal) inclusion of other header files.
 *
 * $Id$
 *
 * Written by Rob Savoye <rob@cygnus.com>
 * Copyright (C) 1997, 1999-2009, 2011, 2015, 2016, MinGW.org Project.
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
#ifndef _WCHAR_H
#define _WCHAR_H
#pragma GCC system_header

/* All the headers include this file.
 */
#include <_mingw.h>

#ifndef __STRICT_ANSI__
 /* MSDN says that isw* char classifications are in wchar.h and wctype.h.
  * Although the wctype names are ANSI, their exposure in this header is
  * not; nevertheless, we replicate them here, for MSDN conformity.
  */
# include <wctype.h>

 /* This is also necessary, to support the non-ANSI wchar.h declarations
  * which MSDN identifies as being provided here.
  */
# include <sys/types.h>
#endif	/* !__STRICT_ANSI__ */

#define WCHAR_MIN	0
#define WCHAR_MAX	0xffff

# define WEOF		(wchar_t)(0xffff)

#ifndef RC_INVOKED
#define __WCHAR_H_SOURCED__
/* ISO-C, POSIX, and Microsoft specify an overlap of content between
 * <wchar.h> and other system header files; by inclusion of such other
 * headers within this "__WCHAR_H_SOURCED__" scope, we may selectively
 * retrieve the overlapping content, without requiring duplication of
 * that content here; thus, from...
 */
#include <stdio.h>
/* ...we obtain (possibly indirect) definitions and declarations for:
 *
 *  macros  NULL, FILENAME_MAX
 *  types   size_t, wchar_t, wint_t, va_list (a.k.a. __VALIST), FILE
 *  types   ssize_t, off_t, __off64_t, (conditionally, as needed)
 *
 *  int     fwprintf (FILE *, const wchar_t *, ...);
 *  int     wprintf (const wchar_t *, ...);
 *  int     vfwprintf (FILE *, const wchar_t *, __VALIST);
 *  int     vwprintf (const wchar_t *, __VALIST);
 *  int     snwprintf (wchar_t *, size_t, const wchar_t *, ...);
 *  int    _snwprintf (wchar_t *, size_t, const wchar_t *, ...);
 *  int    _vscwprintf (const wchar_t *, __VALIST);
 *  int    _vsnwprintf (wchar_t *, size_t, const wchar_t *, __VALIST);
 *  int     vsnwprintf (wchar_t *, size_t, const wchar_t *, __VALIST);
 *  int     fwscanf (FILE *, const wchar_t *, ...);
 *  int     wscanf (const wchar_t *, ...);
 *  int     swscanf (const wchar_t *, const wchar_t *, ...);
 *  int     vwscanf (const wchar_t *, __VALIST);
 *  int     vfwscanf (FILE *, const wchar_t *, __VALIST);
 *  int     vswscanf (const wchar_t *, const wchar_t *, __VALIST);
 *  wint_t  fgetwc (FILE *);
 *  wint_t  fputwc (wchar_t, FILE *);
 *  wint_t  ungetwc (wchar_t, FILE *);
 *
 *  The following pair of Microsoft functions conflict with their
 *  corresponding ISO-C prototypes; consequently they will not be
 *  declared when "__STRICT_ANSI__" checking is in effect:
 *
 *  int  swprintf (wchar_t *, const wchar_t *, ...);
 *  int  vswprintf (wchar_t *, const wchar_t *, __VALIST);
 *
 *  The following group of functions is specified by ISO-C, but
 *  their Microsoft implementations are available only if use of
 *  "__MSVCRT__" is specified:
 *
 *  wchar_t * fgetws (wchar_t *, int, FILE *);
 *  int       fputws (const wchar_t *, FILE *);
 *  wint_t    getwc (FILE *);
 *  wint_t    getwchar (void);
 *  wint_t    putwc (wint_t, FILE *);
 *  wint_t    putwchar (wint_t);
 *
 *  The following group of functions is also dependent on use of
 *  "__MSVCRT__"; however, these are Microsoft specific, so their
 *  are not declared if "__STRICT_ANSI__" checking is specified:
 *
 *  wchar_t * _getws (wchar_t *);
 *  int       _putws (const wchar_t *);
 *  FILE    * _wfdopen(int, const wchar_t *);
 *  FILE    * _wfopen (const wchar_t *, const wchar_t *);
 *  FILE    * _wfreopen (const wchar_t *, const wchar_t *, FILE *);
 *  FILE    * _wfsopen (const wchar_t *, const wchar_t *, int);
 *  wchar_t * _wtmpnam (wchar_t *);
 *  wchar_t * _wtempnam (const wchar_t *, const wchar_t *);
 *  int       _wrename (const wchar_t *, const wchar_t *);
 *  int       _wremove (const wchar_t *);
 *  void      _wperror (const wchar_t *);
 *  FILE    * _wpopen (const wchar_t *, const wchar_t *);
 *
 */
_BEGIN_C_DECLS

#ifndef _WSTDLIB_DEFINED
/* Also declared in stdlib.h; FIXME: should be factored out.
 */
_CRTIMP long __cdecl __MINGW_NOTHROW 	wcstol (const wchar_t*, wchar_t**, int);
_CRTIMP unsigned long __cdecl __MINGW_NOTHROW wcstoul (const wchar_t*, wchar_t**, int);
_CRTIMP double __cdecl __MINGW_NOTHROW	wcstod (const wchar_t*, wchar_t**);
#if !defined __NO_ISOCEXT /* in libmingwex.a */
float __cdecl __MINGW_NOTHROW wcstof (const wchar_t * __restrict__, wchar_t ** __restrict__);
long double __cdecl __MINGW_NOTHROW wcstold (const wchar_t * __restrict__, wchar_t ** __restrict__);
#endif /* __NO_ISOCEXT */
#ifdef __MSVCRT__
_CRTIMP wchar_t* __cdecl __MINGW_NOTHROW _wgetenv(const wchar_t*);
_CRTIMP int __cdecl __MINGW_NOTHROW	_wputenv(const wchar_t*);
_CRTIMP void __cdecl __MINGW_NOTHROW	_wsearchenv(const wchar_t*, const wchar_t*, wchar_t*);
_CRTIMP int __cdecl __MINGW_NOTHROW	_wsystem(const wchar_t*);
_CRTIMP void __cdecl __MINGW_NOTHROW	_wmakepath(wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*);
_CRTIMP void __cdecl __MINGW_NOTHROW	_wsplitpath (const wchar_t*, wchar_t*, wchar_t*, wchar_t*, wchar_t*);
_CRTIMP wchar_t* __cdecl __MINGW_NOTHROW _wfullpath (wchar_t*, const wchar_t*, size_t);
#endif
#define  _WSTDLIB_DEFINED
#endif /* _WSTDLIB_DEFINED */

#ifndef _WTIME_DEFINED
#if defined __MSVCRT__ && ! defined __STRICT_ANSI__
/* Wide function prototypes, also declared in time.h; FIXME: factor out.
 */
_CRTIMP wchar_t* __cdecl __MINGW_NOTHROW	_wasctime (const struct tm*);
#if __MSVCRT_VERSION__ < 0x0800
_CRTIMP wchar_t* __cdecl __MINGW_NOTHROW	_wctime (const time_t*);
#endif
_CRTIMP wchar_t* __cdecl __MINGW_NOTHROW	_wstrdate (wchar_t*);
_CRTIMP wchar_t* __cdecl __MINGW_NOTHROW	_wstrtime (wchar_t*);
#if __MSVCRT_VERSION__ >= 0x601
_CRTIMP wchar_t* __cdecl __MINGW_NOTHROW	_wctime64 (const __time64_t*);
#endif
#if __MSVCRT_VERSION__ >= 0x0800
_CRTIMP wchar_t* __cdecl __MINGW_NOTHROW	_wctime32 (const __time32_t*);
#ifndef _USE_32BIT_TIME_T
_CRTALIAS wchar_t* __cdecl __MINGW_NOTHROW	_wctime (const time_t* _v)	{ return(_wctime64 (_v)); }
#else
_CRTALIAS wchar_t* __cdecl __MINGW_NOTHROW	_wctime (const time_t* _v)	{ return(_wctime32 (_v)); }
#endif
#endif

#endif	/* __MSVCRT__ && ! __STRICT_ANSI__ */
_CRTIMP size_t __cdecl __MINGW_NOTHROW	wcsftime (wchar_t*, size_t, const wchar_t*, const struct tm*);
#define _WTIME_DEFINED
#endif /* _WTIME_DEFINED */


/* Wide character string functions must be specified here, as required
 * by the ISO-C Standard; however, MSVC contravenes this standard by also
 * requiring them to appear in <string.h>, so we specify them in a shared
 * <parts/wchar.h> header, which we may include both here and in <string.h>
 */
#include <parts/wchar.h>


/* These are resolved by -lmingwex. Alternatively, they can be resolved by
   adding -lmsvcp60 to your command line, which will give you the VC++
   versions of these functions. If you want the latter and don't have
   msvcp60.dll in your windows system directory, you can easily obtain
   it with a search from your favorite search engine.  */
#ifndef __STRICT_ANSI__
typedef wchar_t _Wint_t;
#endif

typedef int mbstate_t;

wint_t __cdecl __MINGW_NOTHROW btowc(int);
size_t __cdecl __MINGW_NOTHROW mbrlen(const char * __restrict__, size_t,
		      mbstate_t * __restrict__);
size_t __cdecl __MINGW_NOTHROW mbrtowc(wchar_t * __restrict__, const char * __restrict__,
		       size_t, mbstate_t * __restrict__);
size_t __cdecl __MINGW_NOTHROW mbsrtowcs(wchar_t * __restrict__, const char ** __restrict__,
			 size_t, mbstate_t * __restrict__);
size_t __cdecl __MINGW_NOTHROW wcrtomb(char * __restrict__, wchar_t,
		       mbstate_t * __restrict__);
size_t __cdecl __MINGW_NOTHROW wcsrtombs(char * __restrict__, const wchar_t ** __restrict__,
			 size_t, mbstate_t * __restrict__);
int __cdecl __MINGW_NOTHROW wctob(wint_t);

#ifndef __NO_ISOCEXT /* these need static lib libmingwex.a */
int __cdecl __MINGW_NOTHROW fwide(FILE*, int);
int __cdecl __MINGW_NOTHROW mbsinit(const mbstate_t*);
#ifndef __NO_INLINE__
__CRT_INLINE int __cdecl __MINGW_NOTHROW fwide(FILE* __UNUSED_PARAM(stream),
					       int mode)
  {return mode;} /* Nothing to do  */
__CRT_INLINE int __cdecl __MINGW_NOTHROW mbsinit(const mbstate_t* __UNUSED_PARAM(ps))
  {return 1;}
#endif
wchar_t* __cdecl __MINGW_NOTHROW wmemset(wchar_t *, wchar_t, size_t);
wchar_t* __cdecl __MINGW_NOTHROW wmemchr(const wchar_t*, wchar_t, size_t);
int wmemcmp(const wchar_t*, const wchar_t *, size_t);
wchar_t* __cdecl __MINGW_NOTHROW wmemcpy(wchar_t* __restrict__,
		         const wchar_t* __restrict__,
			 size_t);
wchar_t* __cdecl __MINGW_NOTHROW wmemmove(wchar_t* s1, const wchar_t *, size_t);
long long __cdecl __MINGW_NOTHROW wcstoll(const wchar_t * __restrict__,
			  wchar_t** __restrict__, int);
unsigned long long __cdecl __MINGW_NOTHROW wcstoull(const wchar_t * __restrict__,
			    wchar_t ** __restrict__, int);
#endif /* __NO_ISOCEXT */

#ifndef	__STRICT_ANSI__
/* non-ANSI wide char functions from io.h, direct.h, sys/stat.h and locale.h.  */

#ifndef	_FSIZE_T_DEFINED
typedef	unsigned long	_fsize_t;
#define _FSIZE_T_DEFINED
#endif

#ifndef _WFINDDATA_T_DEFINED
struct _wfinddata_t {
	unsigned	attrib;
	time_t		time_create;	/* -1 for FAT file systems */
	time_t		time_access;	/* -1 for FAT file systems */
	time_t		time_write;
	_fsize_t	size;
	wchar_t		name[260];	/* may include spaces. */
};
struct _wfinddatai64_t {
	unsigned    attrib;
	time_t      time_create;
	time_t      time_access;
	time_t      time_write;
	__int64     size;
	wchar_t     name[260];
};
#if __MSVCRT_VERSION__ >= 0x0601
struct __wfinddata64_t {
        unsigned    attrib;
        __time64_t  time_create;
        __time64_t  time_access;
        __time64_t  time_write;
/* 8 bytes are returned so it can't be _fsize_t */
        __int64    size;
        wchar_t     name[260];
};
#endif
#if __MSVCRT_VERSION__ >= 0x0800
struct __wfinddata32_t {
	unsigned	attrib;
	__time32_t	time_create;
	__time32_t	time_access;
	__time32_t	time_write;
	__int32		size;
	wchar_t		name[FILENAME_MAX];
};

struct _wfinddata32i64_t {
	unsigned	attrib;
	__time32_t	time_create;
	__time32_t	time_access;
	__time32_t	time_write;
	__int64		size;
	wchar_t		name[FILENAME_MAX];
};

struct _wfinddata64i32_t {
	unsigned	attrib;
	__time64_t	time_create;
	__time64_t	time_access;
	__time64_t	time_write;
	__int32		size;
	wchar_t		name[FILENAME_MAX];
};
#endif /* __MSVCRT_VERSION__ >= 0x0800 */
#define _WFINDDATA_T_DEFINED
#endif

/* Wide character versions. Also defined in io.h. */
/* CHECK: I believe these only exist in MSVCRT, and not in CRTDLL. Also
   applies to other wide character versions? */
#if !defined (_WIO_DEFINED)
#if defined (__MSVCRT__)
#include <stdint.h>  /* For intptr_t.  */
_CRTIMP int __cdecl __MINGW_NOTHROW	_waccess (const wchar_t*, int);
_CRTIMP int __cdecl __MINGW_NOTHROW	_wchmod (const wchar_t*, int);
_CRTIMP int __cdecl __MINGW_NOTHROW	_wcreat (const wchar_t*, int);
#if __MSVCRT_VERSION__ < 0x0800
_CRTIMP long __cdecl __MINGW_NOTHROW	_wfindfirst (const wchar_t*, struct _wfinddata_t *);
_CRTIMP int __cdecl __MINGW_NOTHROW	_wfindnext (long, struct _wfinddata_t *);
#endif
_CRTIMP int __cdecl __MINGW_NOTHROW	_wunlink (const wchar_t*);
_CRTIMP int __cdecl __MINGW_NOTHROW	_wopen (const wchar_t*, int, ...);
_CRTIMP int __cdecl __MINGW_NOTHROW	_wsopen (const wchar_t*, int, int, ...);
_CRTIMP wchar_t* __cdecl __MINGW_NOTHROW _wmktemp (wchar_t*);
#if __MSVCRT_VERSION__ < 0x0800
_CRTIMP long __cdecl __MINGW_NOTHROW	_wfindfirsti64 (const wchar_t*, struct _wfinddatai64_t*);
_CRTIMP int __cdecl __MINGW_NOTHROW 	_wfindnexti64 (long, struct _wfinddatai64_t*);
#else
_CRTIMP long __cdecl __MINGW_NOTHROW	_wfindfirst32i64 (const wchar_t*, struct _wfinddata32i64_t*);
_CRTIMP long __cdecl __MINGW_NOTHROW	_wfindfirst64i32 (const wchar_t*, struct _wfinddata64i32_t*);
_CRTIMP int  __cdecl __MINGW_NOTHROW	_wfindnext32i64 (long, struct _wfinddata32i64_t*);
_CRTIMP int  __cdecl __MINGW_NOTHROW	_wfindnext64i32 (long, struct _wfinddata64i32_t*);
#endif /* __MSVCRT_VERSION__ < 0x0800 */
#if __MSVCRT_VERSION__ >= 0x0601
_CRTIMP intptr_t __cdecl __MINGW_NOTHROW _wfindfirst64(const wchar_t*, struct __wfinddata64_t*);
_CRTIMP intptr_t __cdecl __MINGW_NOTHROW _wfindnext64(intptr_t, struct __wfinddata64_t*);
#endif /* __MSVCRT_VERSION__ >= 0x0601 */
#if __MSVCRT_VERSION__ >= 0x0800
_CRTIMP long __cdecl __MINGW_NOTHROW	_wfindfirst32 (const wchar_t*, struct __wfinddata32_t*);
_CRTIMP int  __cdecl __MINGW_NOTHROW	_wfindnext32 (long, struct __wfinddata32_t*);
#ifndef _USE_32BIT_TIME_T
_CRTALIAS long __cdecl __MINGW_NOTHROW	_wfindfirst (const wchar_t* _v1, struct _wfinddata_t* _v2)	 { return(_wfindfirst64i32 (_v1,(struct _wfinddata64i32_t*)_v2)); }
_CRTALIAS int  __cdecl __MINGW_NOTHROW	_wfindnext (long _v1, struct _wfinddata_t* _v2)			 { return(_wfindnext64i32  (_v1,(struct _wfinddata64i32_t*)_v2)); }
_CRTALIAS long __cdecl __MINGW_NOTHROW	_wfindfirsti64 (const wchar_t* _v1, struct _wfinddatai64_t* _v2) { return(_wfindfirst64 (_v1,(struct __wfinddata64_t*)_v2)); }
_CRTALIAS int  __cdecl __MINGW_NOTHROW	_wfindnexti64 (long _v1, struct _wfinddatai64_t* _v2)		 { return(_wfindnext64  (_v1,(struct __wfinddata64_t*)_v2)); }
#else
_CRTALIAS long __cdecl __MINGW_NOTHROW	_wfindfirst (const wchar_t* _v1, struct _wfinddata_t* _v2)	 { return(_wfindfirst32 (_v1,(struct __wfinddata32_t*)_v2)); }
_CRTALIAS int  __cdecl __MINGW_NOTHROW	_wfindnext (long _v1, struct _wfinddata_t* _v2)			 { return(_wfindnext32  (_v1,(struct __wfinddata32_t*)_v2)); }
_CRTALIAS long __cdecl __MINGW_NOTHROW	_wfindfirsti64 (const wchar_t* _v1, struct _wfinddatai64_t* _v2) { return(_wfindfirst32i64 (_v1,(struct _wfinddata32i64_t*)_v2)); }
_CRTALIAS int  __cdecl __MINGW_NOTHROW	_wfindnexti64 (long _v1, struct _wfinddatai64_t* _v2)		 { return(_wfindnext32i64  (_v1,(struct _wfinddata32i64_t*)_v2)); }
#endif /* !_USE_32BIT_TIME_T*/
#endif /* __MSVCRT_VERSION__ >= 0x0800 */

#endif /* defined (__MSVCRT__) */
#define _WIO_DEFINED
#endif /* _WIO_DEFINED */

#ifndef _WDIRECT_DEFINED
/* Also in direct.h */
#ifdef __MSVCRT__
_CRTIMP int __cdecl __MINGW_NOTHROW	  _wchdir (const wchar_t*);
_CRTIMP wchar_t* __cdecl __MINGW_NOTHROW  _wgetcwd (wchar_t*, int);
_CRTIMP wchar_t* __cdecl __MINGW_NOTHROW  _wgetdcwd (int, wchar_t*, int);
_CRTIMP int __cdecl __MINGW_NOTHROW	  _wmkdir (const wchar_t*);
_CRTIMP int __cdecl __MINGW_NOTHROW	  _wrmdir (const wchar_t*);
#endif	/* __MSVCRT__ */
#define _WDIRECT_DEFINED
#endif /* _WDIRECT_DEFINED */

#ifndef _STAT_DEFINED
/*
 * The structure manipulated and returned by stat and fstat.
 *
 * NOTE: If called on a directory the values in the time fields are not only
 * invalid, they will cause localtime et. al. to return NULL. And calling
 * asctime with a NULL pointer causes an Invalid Page Fault. So watch it!
 */
struct _stat
{
	_dev_t	st_dev;		/* Equivalent to drive number 0=A 1=B ... */
	_ino_t	st_ino;		/* Always zero ? */
	_mode_t	st_mode;	/* See above constants */
	short	st_nlink;	/* Number of links. */
	short	st_uid;		/* User: Maybe significant on NT ? */
	short	st_gid;		/* Group: Ditto */
	_dev_t	st_rdev;	/* Seems useless (not even filled in) */
	_off_t	st_size;	/* File size in bytes */
	time_t	st_atime;	/* Accessed date (always 00:00 hrs local
				 * on FAT) */
	time_t	st_mtime;	/* Modified time */
	time_t	st_ctime;	/* Creation time */
};

#ifndef	_NO_OLDNAMES
/* NOTE: Must be the same as _stat above. */
struct stat
{
	dev_t	st_dev;		/* Equivalent to drive number 0=A 1=B ... */
	ino_t	st_ino;		/* Always zero ? */
	mode_t	st_mode;	/* See above constants */
	short	st_nlink;	/* Number of links. */
	short	st_uid;		/* User: Maybe significant on NT ? */
	short	st_gid;		/* Group: Ditto */
	dev_t	st_rdev;	/* Seems useless (not even filled in) */
	off_t	st_size;	/* File size in bytes */
	time_t	st_atime;	/* Accessed date (always 00:00 hrs local
				 * on FAT) */
	time_t	st_mtime;	/* Modified time */
	time_t	st_ctime;	/* Creation time */
};
#endif /* _NO_OLDNAMES */

#if defined (__MSVCRT__)
struct _stati64 {
    _dev_t st_dev;
    _ino_t st_ino;
    unsigned short st_mode;
    short st_nlink;
    short st_uid;
    short st_gid;
    _dev_t st_rdev;
    __int64 st_size;
    time_t st_atime;
    time_t st_mtime;
    time_t st_ctime;
};

#if __MSVCRT_VERSION__ >= 0x0601
struct __stat64
{
    _dev_t st_dev;
    _ino_t st_ino;
    _mode_t st_mode;
    short st_nlink;
    short st_uid;
    short st_gid;
    _dev_t st_rdev;
    __int64 st_size;
    __time64_t st_atime;
    __time64_t st_mtime;
    __time64_t st_ctime;
};
#endif  /* __MSVCRT_VERSION__ >= 0x0601*/

#if __MSVCRT_VERSION__ >= 0x0800
struct __stat32
{
	_dev_t		st_dev;
	_ino_t		st_ino;
	_mode_t		st_mode;
	short		st_nlink;
	short		st_uid;
	short		st_gid;
	_dev_t		st_rdev;
	__int32		st_size;
	__time32_t	st_atime;
	__time32_t	st_mtime;
	__time32_t	st_ctime;
};
struct _stat32i64 {
	_dev_t		st_dev;
	_ino_t		st_ino;
	_mode_t		st_mode;
	short		st_nlink;
	short		st_uid;
	short		st_gid;
	_dev_t		st_rdev;
	__int64		st_size;
	__time32_t	st_atime;
	__time32_t	st_mtime;
	__time32_t	st_ctime;
};
struct _stat64i32 {
	_dev_t		st_dev;
	_ino_t		st_ino;
	_mode_t		st_mode;
	short		st_nlink;
	short		st_uid;
	short		st_gid;
	_dev_t		st_rdev;
	__int32		st_size;
	__time64_t	st_atime;
	__time64_t	st_mtime;
	__time64_t	st_ctime;
};
#endif /* __MSVCRT_VERSION__ >= 0x0800 */

#endif  /* __MSVCRT__ */
#define _STAT_DEFINED
#endif /* _STAT_DEFINED */

#if !defined ( _WSTAT_DEFINED)
/* also declared in sys/stat.h */
#if defined __MSVCRT__
#if __MSVCRT_VERSION__ < 0x0800
_CRTIMP int __cdecl __MINGW_NOTHROW	_wstat (const wchar_t*, struct _stat*);
_CRTIMP int __cdecl __MINGW_NOTHROW	_wstati64 (const wchar_t*, struct _stati64*);
#endif /* __MSVCRT_VERSION__ < 0x0800 */
#if __MSVCRT_VERSION__ >= 0x0601
_CRTIMP int __cdecl __MINGW_NOTHROW _wstat64 (const wchar_t*, struct __stat64*);
#endif /* __MSVCRT_VERSION__ >= 0x0601 */
#if __MSVCRT_VERSION__ >= 0x0800
_CRTIMP int __cdecl __MINGW_NOTHROW	_wstat32 (const wchar_t*, struct __stat32*);
_CRTIMP int __cdecl __MINGW_NOTHROW	_wstat32i64 (const wchar_t*, struct _stat32i64*);
_CRTIMP int __cdecl __MINGW_NOTHROW	_wstat64i32 (const wchar_t*, struct _stat64i32*);
#ifndef _USE_32BIT_TIME_T
_CRTALIAS int __cdecl __MINGW_NOTHROW	_wstat (const wchar_t* _v1, struct _stat* _v2)	     { return(_wstat64i32 (_v1,(struct _stat64i32*)_v2)); }
_CRTALIAS int __cdecl __MINGW_NOTHROW	_wstati64 (const wchar_t* _v1, struct _stati64* _v2) { return(_wstat64 (_v1,(struct __stat64*)_v2)); }
#else
_CRTALIAS int __cdecl __MINGW_NOTHROW	_wstat (const wchar_t* _v1, struct _stat* _v2)	     { return(_wstat32 (_v1,(struct __stat32*)_v2)); }
_CRTALIAS int __cdecl __MINGW_NOTHROW	_wstati64 (const wchar_t* _v1, struct _stati64* _v2) { return(_wstat32i64 (_v1,(struct _stat32i64*)_v2)); }
#endif /* !_USE_32BIT_TIME_T */
#endif /* __MSVCRT_VERSION__ >= 0x0800 */
#endif  /* __MSVCRT__ */
#define _WSTAT_DEFINED
#endif /* ! _WSTAT_DEFIND  */

#ifndef _WLOCALE_DEFINED  /* also declared in locale.h */
_CRTIMP wchar_t* __cdecl __MINGW_NOTHROW _wsetlocale (int, const wchar_t*);
#define _WLOCALE_DEFINED
#endif

#ifndef _WPROCESS_DEFINED
/* Also declared in process.h; FIXME: to be factored out.
 */
#include <stdint.h>  /* For intptr_t.  */
_CRTIMP intptr_t __cdecl __MINGW_NOTHROW _wexecl	(const wchar_t*, const wchar_t*, ...);
_CRTIMP intptr_t __cdecl __MINGW_NOTHROW _wexecle	(const wchar_t*, const wchar_t*, ...);
_CRTIMP intptr_t __cdecl __MINGW_NOTHROW _wexeclp	(const wchar_t*, const wchar_t*, ...);
_CRTIMP intptr_t __cdecl __MINGW_NOTHROW _wexeclpe	(const wchar_t*, const wchar_t*, ...);
_CRTIMP intptr_t __cdecl __MINGW_NOTHROW _wexecv	(const wchar_t*, const wchar_t* const*);
_CRTIMP intptr_t __cdecl __MINGW_NOTHROW _wexecve	(const wchar_t*, const wchar_t* const*, const wchar_t* const*);
_CRTIMP intptr_t __cdecl __MINGW_NOTHROW _wexecvp	(const wchar_t*, const wchar_t* const*);
_CRTIMP intptr_t __cdecl __MINGW_NOTHROW _wexecvpe	(const wchar_t*, const wchar_t* const*, const wchar_t* const*);

_CRTIMP intptr_t __cdecl __MINGW_NOTHROW _wspawnl	(int, const wchar_t*, const wchar_t*, ...);
_CRTIMP intptr_t __cdecl __MINGW_NOTHROW _wspawnle	(int, const wchar_t*, const wchar_t*, ...);
_CRTIMP intptr_t __cdecl __MINGW_NOTHROW _wspawnlp	(int, const wchar_t*, const wchar_t*, ...);
_CRTIMP intptr_t __cdecl __MINGW_NOTHROW _wspawnlpe	(int, const wchar_t*, const wchar_t*, ...);
_CRTIMP intptr_t __cdecl __MINGW_NOTHROW _wspawnv	(int, const wchar_t*, const wchar_t* const*);
_CRTIMP intptr_t __cdecl __MINGW_NOTHROW _wspawnve	(int, const wchar_t*, const wchar_t* const*, const wchar_t* const*);
_CRTIMP intptr_t __cdecl __MINGW_NOTHROW _wspawnvp	(int, const wchar_t*, const wchar_t* const*);
_CRTIMP intptr_t __cdecl __MINGW_NOTHROW _wspawnvpe	(int, const wchar_t*, const wchar_t* const*, const wchar_t* const*);

#define _WPROCESS_DEFINED
#endif
#endif /* ! __STRICT_ANSI__ */

_END_C_DECLS

#undef __WCHAR_H_SOURCED__
#endif /* ! RC_INVOKED */
#endif /* ! _WCHAR_H */
