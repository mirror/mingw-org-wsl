/*
 * stdlib.h
 *
 * ANSI/POSIX + Microsoft compatible standard library function prototypes,
 * associated macros, and manifest constant definitions.
 *
 * $Id$
 *
 * Written by Rob Savoye <rob@cygnus.com>
 * Copyright (C) 1997-2009, 2011, 2014, 2015, MinGW.org Project.
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
#ifndef _STDLIB_H
#define _STDLIB_H

/* All the headers include this file. */
#include <_mingw.h>

#define __need_size_t
#define __need_wchar_t
#define __need_NULL

#ifndef RC_INVOKED
#include <stddef.h>
#endif /* RC_INVOKED */

/* RAND_MAX is the maximum value that may be returned by rand.
 * The minimum is zero.
 */
#define	RAND_MAX	0x7FFF

/* These values may be used as exit status codes.
 */
#define	EXIT_SUCCESS	0
#define	EXIT_FAILURE	1

/* Definitions for path name functions.
 * NOTE: All of these values have simply been chosen to be conservatively high.
 *       Remember that with long file names we can no longer depend on
 *       extensions being short.
 */
#ifndef __STRICT_ANSI__

#ifndef MAX_PATH
#define	MAX_PATH	(260)
#endif

#define	_MAX_PATH	MAX_PATH
#define	_MAX_DRIVE	(3)
#define	_MAX_DIR	256
#define	_MAX_FNAME	256
#define	_MAX_EXT	256

#endif	/* ! __STRICT_ANSI__ */

#ifndef RC_INVOKED

_BEGIN_C_DECLS

#if !defined (__STRICT_ANSI__)
/* This seems like a convenient place to declare these variables, which
 * give programs using WinMain (or main for that matter) access to main-ish
 * argc and argv. environ is a pointer to a table of environment variables.
 * NOTE: Strings in _argv and environ are ANSI strings.
 */
extern int	_argc;
extern char**	_argv;

/* Imports from the runtime DLL, for the above variables.
 */
#ifdef __MSVCRT__

extern int*  __cdecl __MINGW_NOTHROW   __p___argc(void);
extern char*** __cdecl __MINGW_NOTHROW  __p___argv(void);
extern wchar_t***  __cdecl __MINGW_NOTHROW __p___wargv(void);

#define __argc (*__p___argc())
#define __argv (*__p___argv())
#define __wargv (*__p___wargv())

#else  /* ! __MSVCRT__ */

#ifndef __DECLSPEC_SUPPORTED

extern int*    _imp____argc_dll;
extern char***  _imp____argv_dll;
#define __argc (*_imp____argc_dll)
#define __argv (*_imp____argv_dll)

#else  /* __DECLSPEC_SUPPORTED */

__MINGW_IMPORT int    __argc_dll;
__MINGW_IMPORT char**  __argv_dll;
#define __argc __argc_dll
#define __argv __argv_dll

#endif  /* __DECLSPEC_SUPPORTED */

#endif  /* __MSVCRT__ */
#endif  /* __STRICT_ANSI__ */

#ifndef MB_CUR_MAX
/* FIXME: also defined in <ctype.h>; should be factored out.
 */
#ifdef __DECLSPEC_SUPPORTED
# ifdef __MSVCRT__
#  define MB_CUR_MAX __mb_cur_max
   __MINGW_IMPORT int __mb_cur_max;
# else  /* ! __MSVCRT__ */
#  define MB_CUR_MAX __mb_cur_max_dll
   __MINGW_IMPORT int __mb_cur_max_dll;
# endif  /* ! __MSVCRT__ */

#else  /* ! __DECLSPEC_SUPPORTED */
# ifdef __MSVCRT__
   extern int* _imp____mb_cur_max;
#  define MB_CUR_MAX (*_imp____mb_cur_max)
# else  /* ! __MSVCRT__ */
   extern int*  _imp____mb_cur_max_dll;
#  define MB_CUR_MAX (*_imp____mb_cur_max_dll)
# endif  /* ! __MSVCRT__ */
#endif  /*  __DECLSPEC_SUPPORTED */
#endif  /* MB_CUR_MAX */

/* FIXME: Nominally in <errno.h>, Microsoft likes to declare errno
 * in <stdlib.h> as well; we should factor this out.
 */
#ifdef _UWIN
# undef errno
  extern int errno;
#else
 _CRTIMP int __cdecl __MINGW_NOTHROW *_errno(void);
# define errno  (*_errno())
#endif
_CRTIMP int __cdecl __MINGW_NOTHROW *__doserrno(void);
#define _doserrno  (*__doserrno())

#if !defined (__STRICT_ANSI__)
/* Use environ from the DLL, not as a global.
 */
#ifdef __MSVCRT__
  extern _CRTIMP char *** __cdecl __MINGW_NOTHROW __p__environ(void);
  extern _CRTIMP wchar_t *** __cdecl __MINGW_NOTHROW  __p__wenviron(void);
# define _environ (*__p__environ())
# define _wenviron (*__p__wenviron())
#else  /* ! __MSVCRT__ */
# ifndef __DECLSPEC_SUPPORTED
    extern char *** _imp___environ_dll;
#   define _environ (*_imp___environ_dll)
# else  /* __DECLSPEC_SUPPORTED */
    __MINGW_IMPORT char ** _environ_dll;
#   define _environ _environ_dll
# endif  /* __DECLSPEC_SUPPORTED */
#endif  /* ! __MSVCRT__ */

#define environ _environ

#ifdef	__MSVCRT__
/* One of the MSVCRTxx libraries */

#ifndef __DECLSPEC_SUPPORTED
  extern int*	_imp___sys_nerr;
# define	sys_nerr	(*_imp___sys_nerr)
#else /* __DECLSPEC_SUPPORTED */
  __MINGW_IMPORT int	_sys_nerr;
# ifndef _UWIN
#   define	sys_nerr	_sys_nerr
# endif  /* _UWIN */
#endif  /* __DECLSPEC_SUPPORTED */

#else  /* ! __MSVCRT__ */

/* CRTDLL run time library */

#ifndef __DECLSPEC_SUPPORTED
  extern int*	_imp___sys_nerr_dll;
# define sys_nerr	(*_imp___sys_nerr_dll)
#else  /* __DECLSPEC_SUPPORTED */
  __MINGW_IMPORT int	_sys_nerr_dll;
# define sys_nerr	_sys_nerr_dll
#endif  /* __DECLSPEC_SUPPORTED */

#endif  /* ! __MSVCRT__ */

#ifndef __DECLSPEC_SUPPORTED
extern char***	_imp__sys_errlist;
#define	sys_errlist	(*_imp___sys_errlist)
#else  /* __DECLSPEC_SUPPORTED */
__MINGW_IMPORT char*	_sys_errlist[];
#ifndef _UWIN
#define	sys_errlist	_sys_errlist
#endif  /* _UWIN */
#endif  /* __DECLSPEC_SUPPORTED */

/*
 * OS version and such constants.
 */

#ifdef	__MSVCRT__
/* msvcrtxx.dll */

extern _CRTIMP unsigned __cdecl __MINGW_NOTHROW int*	__p__osver(void);
extern _CRTIMP unsigned __cdecl __MINGW_NOTHROW int*	__p__winver(void);
extern _CRTIMP unsigned __cdecl __MINGW_NOTHROW int*	__p__winmajor(void);
extern _CRTIMP unsigned __cdecl __MINGW_NOTHROW int*	__p__winminor(void);

#ifndef __DECLSPEC_SUPPORTED
# define _osver		(*__p__osver())
# define _winver	(*__p__winver())
# define _winmajor	(*__p__winmajor())
# define _winminor	(*__p__winminor())
#else
__MINGW_IMPORT unsigned int _osver;
__MINGW_IMPORT unsigned int _winver;
__MINGW_IMPORT unsigned int _winmajor;
__MINGW_IMPORT unsigned int _winminor;
#endif  /* __DECLSPEC_SUPPORTED */

#else  /* ! __MSVCRT__; thus CRTDLL */

#ifndef __DECLSPEC_SUPPORTED

extern unsigned int*	_imp___osver_dll;
extern unsigned int*	_imp___winver_dll;
extern unsigned int*	_imp___winmajor_dll;
extern unsigned int*	_imp___winminor_dll;

#define _osver		(*_imp___osver_dll)
#define _winver		(*_imp___winver_dll)
#define _winmajor	(*_imp___winmajor_dll)
#define _winminor	(*_imp___winminor_dll)

#else  /* __DECLSPEC_SUPPORTED */

__MINGW_IMPORT unsigned int	_osver_dll;
__MINGW_IMPORT unsigned int	_winver_dll;
__MINGW_IMPORT unsigned int	_winmajor_dll;
__MINGW_IMPORT unsigned int	_winminor_dll;

#define _osver		_osver_dll
#define _winver		_winver_dll
#define _winmajor	_winmajor_dll
#define _winminor	_winminor_dll

#endif  /* __DECLSPEC_SUPPORTED */
#endif  /* CRTDLL */

#if defined  __MSVCRT__
/* Although _pgmptr is exported as DATA, be safe and use the access
 * function __p__pgmptr() to get it.
 */
_CRTIMP char** __cdecl __MINGW_NOTHROW __p__pgmptr(void);
#define _pgmptr     (*__p__pgmptr())
_CRTIMP wchar_t** __cdecl __MINGW_NOTHROW __p__wpgmptr(void);
#define _wpgmptr    (*__p__wpgmptr())

#else  /* ! __MSVCRT__; thus CRTDLL */

# ifndef __DECLSPEC_SUPPORTED
  extern char** __imp__pgmptr_dll;
# define _pgmptr (*_imp___pgmptr_dll)

# else  /* __DECLSPEC_SUPPORTED */
 __MINGW_IMPORT char* _pgmptr_dll;
# define _pgmptr _pgmptr_dll
# endif  /* __DECLSPEC_SUPPORTED */
/* no wide version in CRTDLL */
#endif  /* CRTDLL */

/* This variable determines the default file mode.
 * TODO: Which flags work?
 */
#if !defined (__DECLSPEC_SUPPORTED) || defined (__IN_MINGW_RUNTIME)

#ifdef __MSVCRT__
extern int* _imp___fmode;
#define	_fmode	(*_imp___fmode)
#else
/* CRTDLL */
extern int* _imp___fmode_dll;
#define	_fmode	(*_imp___fmode_dll)
#endif

#else  /* __DECLSPEC_SUPPORTED */

#ifdef __MSVCRT__
__MINGW_IMPORT  int _fmode;
#else  /* ! __MSVCRT__ */
__MINGW_IMPORT  int _fmode_dll;
#define	_fmode	_fmode_dll
#endif  /* ! __MSVCRT__ */

#endif  /* __DECLSPEC_SUPPORTED */

#endif  /* ! __STRICT_ANSI__ */

_CRTIMP int __cdecl __MINGW_NOTHROW atoi (const char *);
_CRTIMP long __cdecl __MINGW_NOTHROW  atol (const char *);

_CRTIMP double __cdecl __MINGW_NOTHROW strtod (const char *, char **);
_CRTIMP double __cdecl __MINGW_NOTHROW atof (const char *);

#if !defined (__STRICT_ANSI__)
_CRTIMP double __cdecl __MINGW_NOTHROW _wtof (const wchar_t *);
_CRTIMP int __cdecl __MINGW_NOTHROW _wtoi (const wchar_t *);
_CRTIMP long __cdecl __MINGW_NOTHROW _wtol (const wchar_t *);
#endif

#if __USE_MINGW_ANSI_STDIO
/* Microsoft's strtod() and atof() implementations, (in MSVCRT.DLL),
 * mishandle infinities and NaNs; on the basis that this conditional
 * exposes a more ISO-C conforming printf() I/O family implementaion,
 * we substitute a similarly more conforming implementation for each
 * of this pair of (somewhat related) functions.
 *
 * Note that we provide neither __JMPSTUB__ nor __LIBIMPL__ external
 * equivalents for either of these two inline functions, because they
 * would conflict with the runtime DLL implementations; users needing
 * an address reference for either must provide an equivalent of the
 * inline implementation, as non-inlined within their own code.
 */
extern double __cdecl __MINGW_NOTHROW
__strtod (const char *__restrict__, char **__restrict__);

__CRT_ALIAS double __cdecl __MINGW_NOTHROW
strtod (const char *__restrict__ __nptr, char **__restrict__ __endptr)
{ return __strtod( __nptr, __endptr ); }

__CRT_ALIAS double __cdecl __MINGW_NOTHROW
atof (const char *__nptr) { return __strtod( __nptr, NULL ); }

#endif  /* __USE_MINGW_ANSI_STDIO */

#ifdef _ISOC99_SOURCE
/* Irrespective of requested standards conformity, where MSVCRT.DLL
 * falls short, ISO-C99 offers this pair of alternative return type
 * specific variants of strtod(), which MSVCRT.DLL does not, but we
 * do, in libmingwex.a:
 */
float __cdecl __MINGW_NOTHROW strtof
(const char *__restrict__, char **__restrict__);

long double __cdecl __MINGW_NOTHROW
strtold (const char *__restrict__, char **__restrict__);

#endif  /* _ISOC99_SOURCE */

_CRTIMP long __cdecl __MINGW_NOTHROW strtol (const char *, char **, int);
_CRTIMP unsigned long __cdecl __MINGW_NOTHROW strtoul (const char *, char **, int);

#ifndef _WSTDLIB_DEFINED
/* FIXME: also declared in <wchar.h>; should be factored out.
 */
_CRTIMP long __cdecl __MINGW_NOTHROW wcstol (const wchar_t *, wchar_t **, int);
_CRTIMP unsigned long __cdecl __MINGW_NOTHROW wcstoul (const wchar_t *, wchar_t **, int);
_CRTIMP double __cdecl __MINGW_NOTHROW wcstod (const wchar_t *, wchar_t **);

#ifdef _ISOC99_SOURCE
/* Variants on wcstod(), specified by ISO-C99; once again, MSVCRT.DLL
 * doesn't have them, but we offer them in libmingwex.a
 */
float __cdecl __MINGW_NOTHROW wcstof( const wchar_t *__restrict__, wchar_t **__restrict__);
long double __cdecl __MINGW_NOTHROW wcstold (const wchar_t *__restrict__, wchar_t **__restrict__);
#endif  /* _ISOC99_SOURCE */

#ifdef __MSVCRT__
_CRTIMP wchar_t __cdecl __MINGW_NOTHROW *_wgetenv (const wchar_t *);
_CRTIMP int __cdecl __MINGW_NOTHROW _wputenv (const wchar_t *);
_CRTIMP void __cdecl __MINGW_NOTHROW _wsearchenv (const wchar_t *, const wchar_t *, wchar_t *);
_CRTIMP int __cdecl __MINGW_NOTHROW _wsystem (const wchar_t *);

_CRTIMP void __cdecl __MINGW_NOTHROW _wmakepath
(wchar_t *, const wchar_t *, const wchar_t *, const wchar_t *, const wchar_t *);

_CRTIMP void __cdecl __MINGW_NOTHROW _wsplitpath
(const wchar_t *, wchar_t *, wchar_t *, wchar_t *, wchar_t *);

_CRTIMP wchar_t* __cdecl __MINGW_NOTHROW _wfullpath (wchar_t *, const wchar_t *, size_t);

#endif  /* __MSVCRT__ */

#define _WSTDLIB_DEFINED
#endif  /* ! _WSTDLIB_DEFINED */

_CRTIMP size_t __cdecl __MINGW_NOTHROW wcstombs	(char*, const wchar_t*, size_t);
_CRTIMP int __cdecl __MINGW_NOTHROW wctomb (char*, wchar_t);

_CRTIMP int __cdecl __MINGW_NOTHROW mblen (const char*, size_t);
_CRTIMP size_t __cdecl __MINGW_NOTHROW mbstowcs (wchar_t*, const char*, size_t);
_CRTIMP int __cdecl __MINGW_NOTHROW mbtowc (wchar_t*, const char*, size_t);

_CRTIMP int __cdecl __MINGW_NOTHROW rand (void);
_CRTIMP void __cdecl __MINGW_NOTHROW srand (unsigned int);

_CRTIMP void* __cdecl __MINGW_NOTHROW calloc (size_t, size_t) __MINGW_ATTRIB_MALLOC;
_CRTIMP void* __cdecl __MINGW_NOTHROW malloc (size_t) __MINGW_ATTRIB_MALLOC;
_CRTIMP void* __cdecl __MINGW_NOTHROW realloc (void*, size_t);
_CRTIMP void __cdecl __MINGW_NOTHROW free (void*);
_CRTIMP void __cdecl __MINGW_NOTHROW abort (void) __MINGW_ATTRIB_NORETURN;
_CRTIMP void __cdecl __MINGW_NOTHROW exit (int) __MINGW_ATTRIB_NORETURN;

/* Note: this is in startup code, not imported directly from the runtime DLL
 */
int __cdecl __MINGW_NOTHROW atexit (void (*)(void));

_CRTIMP int __cdecl __MINGW_NOTHROW system (const char*);
_CRTIMP char* __cdecl __MINGW_NOTHROW getenv (const char*);

/* bsearch() and qsort() are also declared in non-ANSI header <search.h>
 */
_CRTIMP void* __cdecl
bsearch (const void*, const void*, size_t, size_t, int (*)(const void*, const void*));

_CRTIMP void __cdecl qsort(void*, size_t, size_t, int (*)(const void*, const void*));

_CRTIMP int __cdecl __MINGW_NOTHROW abs (int) __MINGW_ATTRIB_CONST;
_CRTIMP long __cdecl __MINGW_NOTHROW labs (long) __MINGW_ATTRIB_CONST;

/*
 * div_t and ldiv_t are structures used to return the results of div and
 * ldiv.
 *
 * NOTE: div and ldiv appear not to work correctly unless
 *       -fno-pcc-struct-return is specified. This is included in the
 *       mingw32 specs file.
 */
typedef struct { int quot, rem; } div_t;
typedef struct { long quot, rem; } ldiv_t;

_CRTIMP div_t __cdecl __MINGW_NOTHROW div (int, int) __MINGW_ATTRIB_CONST;
_CRTIMP ldiv_t __cdecl __MINGW_NOTHROW ldiv (long, long) __MINGW_ATTRIB_CONST;

#if !defined (__STRICT_ANSI__)
/* NOTE: Officially the three following functions are obsolete. The Win32 API
 *       functions SetErrorMode, Beep and Sleep are their replacements.
 */
_CRTIMP void __cdecl __MINGW_NOTHROW _beep (unsigned int, unsigned int) __MINGW_ATTRIB_DEPRECATED;
/* Not to be confused with  _set_error_mode (int).  */
_CRTIMP void __cdecl __MINGW_NOTHROW _seterrormode (int) __MINGW_ATTRIB_DEPRECATED;
_CRTIMP void __cdecl __MINGW_NOTHROW _sleep (unsigned long) __MINGW_ATTRIB_DEPRECATED;

_CRTIMP void __cdecl __MINGW_NOTHROW _exit (int) __MINGW_ATTRIB_NORETURN;

/* _onexit is MS extension. Use atexit for portability.  */
/* Note: This is in startup code, not imported directly from dll */
typedef  int (* _onexit_t)(void);
_onexit_t __cdecl __MINGW_NOTHROW _onexit( _onexit_t );

_CRTIMP int __cdecl __MINGW_NOTHROW _putenv (const char*);
_CRTIMP void __cdecl __MINGW_NOTHROW _searchenv (const char*, const char*, char*);

_CRTIMP char* __cdecl __MINGW_NOTHROW _ecvt (double, int, int*, int*);
_CRTIMP char* __cdecl __MINGW_NOTHROW _fcvt (double, int, int*, int*);
_CRTIMP char* __cdecl __MINGW_NOTHROW _gcvt (double, int, char*);

_CRTIMP void __cdecl __MINGW_NOTHROW _makepath (char*, const char*, const char*, const char*, const char*);
_CRTIMP void __cdecl __MINGW_NOTHROW _splitpath (const char*, char*, char*, char*, char*);
_CRTIMP char* __cdecl __MINGW_NOTHROW _fullpath (char*, const char*, size_t);

_CRTIMP char* __cdecl __MINGW_NOTHROW _itoa (int, char*, int);
_CRTIMP char* __cdecl __MINGW_NOTHROW _ltoa (long, char*, int);
_CRTIMP char* __cdecl __MINGW_NOTHROW _ultoa(unsigned long, char*, int);
_CRTIMP wchar_t* __cdecl __MINGW_NOTHROW _itow (int, wchar_t*, int);
_CRTIMP wchar_t* __cdecl __MINGW_NOTHROW _ltow (long, wchar_t*, int);
_CRTIMP wchar_t* __cdecl __MINGW_NOTHROW _ultow (unsigned long, wchar_t*, int);

#ifdef __MSVCRT__
_CRTIMP __int64 __cdecl __MINGW_NOTHROW	_atoi64 (const char *);
_CRTIMP char* __cdecl __MINGW_NOTHROW _i64toa (__int64, char *, int);
_CRTIMP char* __cdecl __MINGW_NOTHROW _ui64toa (unsigned __int64, char *, int);
_CRTIMP __int64 __cdecl __MINGW_NOTHROW _wtoi64 (const wchar_t *);
_CRTIMP wchar_t* __cdecl __MINGW_NOTHROW _i64tow (__int64, wchar_t *, int);
_CRTIMP wchar_t* __cdecl __MINGW_NOTHROW _ui64tow (unsigned __int64, wchar_t *, int);

_CRTIMP unsigned int __cdecl __MINGW_NOTHROW (_rotl)(unsigned int, int) __MINGW_ATTRIB_CONST;
_CRTIMP unsigned int __cdecl __MINGW_NOTHROW (_rotr)(unsigned int, int) __MINGW_ATTRIB_CONST;
_CRTIMP unsigned long __cdecl __MINGW_NOTHROW (_lrotl)(unsigned long, int) __MINGW_ATTRIB_CONST;
_CRTIMP unsigned long __cdecl __MINGW_NOTHROW (_lrotr)(unsigned long, int) __MINGW_ATTRIB_CONST;

_CRTIMP int __cdecl __MINGW_NOTHROW _set_error_mode (int);

# define _OUT_TO_DEFAULT	0
# define _OUT_TO_STDERR 	1
# define _OUT_TO_MSGBOX 	2
# define _REPORT_ERRMODE	3

# if __MSVCRT_VERSION__ >= __MSVCR80_DLL
#  ifndef _UINTPTR_T_DEFINED
#   define _UINTPTR_T_DEFINED
#   ifdef _WIN64
      typedef unsigned __int64 uintptr_t;
#   else
      typedef unsigned int uintptr_t;
#   endif
#  endif

_CRTIMP unsigned int __cdecl __MINGW_NOTHROW _set_abort_behavior (unsigned int, unsigned int);

/* These masks work with msvcr80.dll version 8.0.50215.44 (a beta release).
 */
#  define _WRITE_ABORT_MSG	1
#  define _CALL_REPORTFAULT	2

typedef void
(* _invalid_parameter_handler) (
    const wchar_t *,
    const wchar_t *,
    const wchar_t *,
    unsigned int,
    uintptr_t);
_invalid_parameter_handler _set_invalid_parameter_handler (_invalid_parameter_handler);

# endif  /* __MSVCRT_VERSION__ >= __MSVCR80_DLL */
#endif  /* __MSVCRT__ */

#ifndef	_NO_OLDNAMES

_CRTIMP int __cdecl __MINGW_NOTHROW	putenv (const char*);
_CRTIMP void __cdecl __MINGW_NOTHROW	searchenv (const char*, const char*, char*);

_CRTIMP char* __cdecl __MINGW_NOTHROW	itoa (int, char*, int);
_CRTIMP char* __cdecl __MINGW_NOTHROW	ltoa (long, char*, int);

#ifndef _UWIN
_CRTIMP char* __cdecl __MINGW_NOTHROW	ecvt (double, int, int*, int*);
_CRTIMP char* __cdecl __MINGW_NOTHROW	fcvt (double, int, int*, int*);
_CRTIMP char* __cdecl __MINGW_NOTHROW	gcvt (double, int, char*);

#endif  /* ! _UWIN */
#endif	/* ! _NO_OLDNAMES */
#endif	/* ! __STRICT_ANSI__ */

#ifdef _ISOC99_SOURCE
/* Further APIs required to support ISO-C99, but missing from MSVCRT.DLL;
 * we provide them in libmingwex.a
 *
 *
 * ISO-C99 name for _exit()
 */
void __cdecl __MINGW_NOTHROW _Exit(int) __MINGW_ATTRIB_NORETURN;

#ifndef __NO_INLINE__
__CRT_INLINE __JMPSTUB__(( FUNCTION = _Exit, REMAPPED = _exit ))
void __cdecl __MINGW_NOTHROW _Exit( int __status ){ _exit (__status); }
#endif

typedef struct { long long quot, rem; } lldiv_t;
lldiv_t __cdecl __MINGW_NOTHROW lldiv (long long, long long) __MINGW_ATTRIB_CONST;

long long __cdecl __MINGW_NOTHROW llabs (long long);

#ifndef __NO_INLINE__
__CRT_INLINE
/* No JMPSTUB or LIBIMPL reference here -- we provide a free-standing
 * implementation, along with imaxabs(), in mingwex/imaxabs.c
 */
long long __cdecl __MINGW_NOTHROW llabs( long long __j )
{ return __j >= 0 ? __j : -__j; }
#endif

long long  __cdecl __MINGW_NOTHROW
strtoll (const char *__restrict__, char **__restrict, int);

unsigned long long  __cdecl __MINGW_NOTHROW
strtoull (const char *__restrict__, char **__restrict__, int);

#ifdef __MSVCRT__
/* MSVCRT.DLL does not provide ISO-C99's atoll() function, but it does
 * provide an analogue, in _atoi64(); map it accordingly.
 */
long long  __cdecl __MINGW_NOTHROW atoll (const char *);

#ifndef __NO_INLINE__
__CRT_INLINE __JMPSTUB__(( FUNCTION = atoll, REMAPPED = _atoi64 ))
long long __cdecl __MINGW_NOTHROW atoll (const char * _c){ return _atoi64 (_c); }
#endif

#endif  /* __MSVCRT__ */
#endif  /* _ISOC99_SOURCE */

#if defined __MSVCRT__ && ! defined __STRICT_ANSI__
/* Type long long analogues for MSVCRT.DLL specific type long functions;
 * none are actually provided by any version of MSVCRT.DLL, with names as
 * specified here, but rather as called by the inline functions used to
 * implement them, (i.e. the REMAPPED name specified in each__JMPSTUB__
 * function reference respectively).
 *
 * FIXME: Not one of these is specified by ISO-C99, nor by POSIX, either;
 * is there really any justification for us to specify them at all?  For
 * the time being, declare as deprecated; perhaps remove later?
 */
long long  __cdecl __MINGW_NOTHROW __MINGW_ATTRIB_DEPRECATED wtoll (const wchar_t *);
char* __cdecl __MINGW_NOTHROW __MINGW_ATTRIB_DEPRECATED lltoa (long long, char *, int);
char* __cdecl __MINGW_NOTHROW __MINGW_ATTRIB_DEPRECATED ulltoa (unsigned long long , char *, int);
wchar_t* __cdecl __MINGW_NOTHROW __MINGW_ATTRIB_DEPRECATED lltow (long long, wchar_t *, int);
wchar_t* __cdecl __MINGW_NOTHROW __MINGW_ATTRIB_DEPRECATED ulltow (unsigned long long, wchar_t *, int);

#ifndef __NO_INLINE__
/* None of these functions would exist at all, without either these inline
 * implementations, or their respective __JMPSTUB__ equivalents.
 */
__CRT_INLINE __JMPSTUB__(( FUNCTION = lltoa, REMAPPED = _i64toa ))
char* __cdecl __MINGW_NOTHROW lltoa (long long __n, char * __c, int __i)
{ return _i64toa (__n, __c, __i); }

__CRT_INLINE __JMPSTUB__(( FUNCTION = ulltoa, REMAPPED = _ui64toa ))
char* __cdecl __MINGW_NOTHROW ulltoa (unsigned long long __n, char * __c, int __i)
{ return _ui64toa (__n, __c, __i); }

__CRT_INLINE __JMPSTUB__(( FUNCTION = wtoll, REMAPPED = _wtoi64 ))
long long __cdecl __MINGW_NOTHROW wtoll (const wchar_t * __w){ return _wtoi64 (__w); }

__CRT_INLINE __JMPSTUB__(( FUNCTION = lltow, REMAPPED = _i64tow ))
wchar_t* __cdecl __MINGW_NOTHROW lltow (long long __n, wchar_t * __w, int __i)
{ return _i64tow (__n, __w, __i); }

__CRT_INLINE __JMPSTUB__(( FUNCTION = ulltow, REMAPPED = _ui64tow ))
wchar_t* __cdecl __MINGW_NOTHROW ulltow (unsigned long long __n, wchar_t * __w, int __i)
{ return _ui64tow (__n, __w, __i); }

#endif  /* ! __NO_INLINE__ */
#endif  /* __MSVCRT__ && ! __STRICT_ANSI__ */

/* POSIX/BSD extensions in libmingwex.a; these should be exposed only on
 * the basis of appropriate POSIX or BSD specific feature tests...
 *
 * mkstemp(3) function support; added per feature request #2003.
 * POSIX wants _XOPEN_SOURCE >= 500, (implying _POSIX_C_SOURCE >= 200112L).
 */
#if _POSIX_C_SOURCE >= 200112L

int __cdecl __MINGW_NOTHROW mkstemp( char * );
int __cdecl __MINGW_NOTHROW __mingw_mkstemp( int, char * );

/* On POSIX platforms, programmers may adopt an idiom such as:
 *
 *   if( mkstemp( template ) >= 0 )
 *   { unlink( template );
 *     . . .
 *   }
 *
 * to ensure that a temporary file does NOT persist after it is
 * closed; MS-Windows does not allow such use of unlink(2), while
 * the file remains open.  Thus, MS-Windows programmers must take
 * extra care, to close and unlink temporary files AFTER use, if
 * similar behaviour is desired.
 *
 * To mitigate this MS-Windows limitation, we provide support for
 * an alternative, MinGW specific idiom:
 *
 *   #include <fcntl.h>
 *
 *   _MKSTEMP_SETMODE( _O_TEMPORARY );
 *   if( mkstemp( template ) >= 0 )
 *   {
 *     . . .
 *   }
 *
 * to achieve a similar effect to that of the above POSIX idiom; the
 * following macros are a MinGW specific extension, to facilite such
 * use of _O_TEMPORARY, (in addition to the POSIX required attributes),
 * when creating the temporary file.  Note that they require <fcntl.h>,
 * which <stdlib.h> should NOT automatically include; we leave it to
 * the user to explicitly include it, if using _MKSTEMP_SETMODE.
 */
#define _MKSTEMP_INVOKE       0
#define _MKSTEMP_DEFAULT     _O_CREAT | _O_EXCL | _O_RDWR
#define _MKSTEMP_SETMODE(M) __mingw_mkstemp( _MKSTEMP_DEFAULT | (M), NULL )

#ifndef _NO_OLDNAMES
#define MKSTEMP_SETMODE(M)  __mingw_mkstemp( _MKSTEMP_DEFAULT | (M), NULL )
#endif

__CRT_ALIAS __LIBIMPL__(( FUNCTION = mkstemp ))
int __cdecl __MINGW_NOTHROW mkstemp( char *__filename_template )
{ return __mingw_mkstemp( _MKSTEMP_INVOKE, __filename_template ); }

#endif  /* _POSIX_C_SOURCE >= 200112L (for mkstemp()) */

/* mkdtemp(3) function support: added as adjunct to feature request #2003.
 * POSIX wants _XOPEN_SOURCE >= 700, (implying _POSIX_C_SOURCE >= 200809L).
 */
#if _POSIX_C_SOURCE >= 200809L

char * __cdecl __MINGW_NOTHROW mkdtemp( char * );
char * __cdecl __MINGW_NOTHROW __mingw_mkdtemp( char * );

__CRT_ALIAS __JMPSTUB__(( FUNCTION = mkdtemp ))
char * __cdecl __MINGW_NOTHROW mkdtemp( char *__dirname_template )
{ return __mingw_mkdtemp( __dirname_template ); }

#endif  /* _POSIX_C_SOURCE >= 200809L (for mkdtemp()) */

_END_C_DECLS

#endif	/* ! RC_INVOKED */
#endif	/* ! _STDLIB_H: $RCSfile$: end of file */
