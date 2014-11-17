/*
 * ofmt.c
 *
 * Implement universally available replacement wrappers for each of
 * Microsoft's _get_output_format()/_set_output_format(), and their
 * _get_printf_count_output()/_set_printf_count_output() APIs.
 *
 * $Id$
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2014, MinGW.org Project
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
 *
 * This source file provides a generic implementation for each of the two
 * functions, __mingw_get_output_format() and __mingw_set_output_format(),
 * which serve as universally available fallbacks for each of Microsoft's
 * _get_output_format() and _set_output_format() API functions, which were
 * introduced in MSVCR80.DLL, and are unavailable in MSVCRT.DLL prior to
 * the release accompanying Windows-Vista; compile it with:
 *
 *   gcc -c -O2 -D__varofmt__ -o varofmt.o ofmt.c
 *   gcc -c -O2 -D__crtofmt__ -o crtofmt.o ofmt.c
 *   gcc -c -O2 -D__getofmt__ -o getofmt.o ofmt.c
 *   gcc -c -O2 -D__setofmt__ -o setofmt.o ofmt.c
 *
 * for each of these two implementation cases respectively, to provide the
 * capability for any application which #includes stdio.h to invoke either
 * _get_output_format() or _set_output_format() in total safety, regardless
 * of whether the underlying platform MSVCRT.DLL supports this API or not;
 * if the API is available, it will be invoked by the wrappers, otherwise
 * it will be emulated within the wrappers themselves.
 *
 * Additionally provided are wrappers for the _get_printf_count_output() and
 * _set_printf_count_output() functions, the respective invocations of which
 * may be compiled with:
 *
 *   gcc -c -O2 -D__crtnfmt__ -o crtnfmt.o ofmt.c
 *   gcc -c -O2 -D__getnfmt__ -o getnfmt.o ofmt.c
 *   gcc -c -O2 -D__setnfmt__ -o setnfmt.o ofmt.c
 *
 * to provide similar fallback handlers for the respective API functions; in
 * the case of this pair of functions, the respective API will be invoked if
 * available, otherwise the call will become a no-op, always returning zero.
 *
 * All of these functions are provided in libmingwex.a, where each of them
 * serves as a wrapper for their corresponding Microsoft runtime functions;
 * each may be called safely, even when running on a version of MS-Windows
 * where the native MSVCRT.DLL implementation lacks the corresponding API
 * function, in which case a suitable fallback implementation is provided;
 * in cases where the native implementation IS available, each wrapper
 * simply delegates to the MSVCRT.DLL implementation.
 *
 * Note that each of these wrapper functions depends upon the MinGW.org
 * implementation of the POSIX dlsym() function, which is also provided
 * in libmingwex.a, and prototyped in dlfcn.h
 *
 */
#include <dlfcn.h>
#include <stdio.h>

/* Storage for recorded output format state, when the MSVCRT functions
 * aren't available; we need it to be public so that it may be shared by
 * our two separately compiled API functions, but we keep it privately
 * declared; users should NEVER access this, other than via our two
 * accessor functions.
 */
extern unsigned int __mingw_output_format_flag;

#if defined __varofmt__
/*
 * Here, we actually allocate the storage for recording the preferred
 * formatting style; although POSIX might lead us to prefer an initial
 * default of _TWO_DIGIT_EXPONENT, we choose to assign a default which
 * is consistent with Microsoft's preference.
 */
unsigned int __mingw_output_format_flag = _THREE_DIGIT_EXPONENT;

#elif defined __crtofmt__
/*
 * Here we implement the common part of the fallback API, retrieving
 * the value stored in __mingw_output_format_flag.  Note that this is
 * sufficient for both _get_output_format() and _set_output_format(),
 * with the set action being completed in the calling wrapper.
 */
extern unsigned int __mingw_get_output_format_fallback( void );
unsigned int __mingw_get_output_format_fallback( void )
{
  /* Our replacement function simply returns the current setting of
   * the assigned formatting style...
   */
  return __mingw_output_format_flag;
}
/* ...and, in the case of _set_output_format(), we simply map the
 * requisite name to the common function implementation.
 */
extern unsigned int __mingw_set_output_format_fallback( unsigned int )
__attribute__((__alias__("__mingw_get_output_format_fallback")));

#elif defined __crtnfmt__
/*
 * Here, we implement a generic fallback hook, suitable for use as the
 * fallback for _get_printf_count_output()/_set_printf_count_output().
 */
int __mingw_get_printf_count_output_fallback( void )
__attribute__((__alias__("__mingw_set_printf_count_output_fallback")));

int __mingw_set_printf_count_output_fallback( int );
int __mingw_set_printf_count_output_fallback( int mode )
{ return 0; }

#else
/* We want _get_output_format() to serve as our default compilation
 * option, so deal with the "%n" availability controls, as provided by
 * _get_printf_count_output() and _set_printf_count_output(), and also
 * _set_output_format() compilation options first.
 */
#if defined __setnfmt__
/*
 * Here, we are wrapping the _set_printf_count_output() function...
 */
# define RTNTYPE   int
# define ARGTYPE   int
# define FUNCTION _set_printf_count_output
# define ARGLIST   mode

#define api_helper_result api_helper( mode )
extern int __mingw_set_printf_count_output_fallback( int );

#elif defined __getnfmt__
/*
 * ...while here, it is _get_printf_count_output().
 */
# define RTNTYPE   int
# define ARGTYPE   void
# define FUNCTION _get_printf_count_output
# define ARGLIST

#define api_helper_result api_helper()
extern int __mingw_get_printf_count_output_fallback( void );

#elif defined __setofmt__
/*
 * This is our implementation for the _set_output_format() function,
 * which will be called when there is no MSVCRT implementation.
 */
# define RTNTYPE   unsigned int
# define FUNCTION _set_output_format
# define ARGTYPE   unsigned int
# define ARGLIST   style

/* Our replacement function emulates the documented behaviour of
 * its MSVCRT counterpart, assigning a new value for the recorded
 * formatting style, then returning the previous setting.
 */
#define api_helper_result api_invoke( api_helper, style )
static __inline__ __attribute__((__always_inline__)) unsigned int
api_invoke( unsigned int (*api_helper)(unsigned int), unsigned int style )
{
  /* Note that we implement this, predominantly, inline within
   * the wrapper code, using the fallback function pointer only
   * to retrieve the previous value for return; thus it is able
   * to use a handler in common with _get_output_format()...
   */
  unsigned int retval = api_helper( style );
  __mingw_output_format_flag = style;
  return retval;
}
/* ...while declaring its formal prototype as external.
 */
extern unsigned int __mingw_set_output_format_fallback( unsigned int );

#else /* __getofmt__, either explicitly defined, or by default */
/*
 * When not explicitly requested to implement _set_output_format(),
 * assume __getofmt__ is implied, and implement _get_output_format(),
 * for use when there is no MSVCRT implementation.
 */
# define RTNTYPE   unsigned int
# define FUNCTION _get_output_format
# define ARGTYPE   void
# define ARGLIST

#define api_helper_result __mingw_output_format_flag = api_helper()
extern unsigned int __mingw_get_output_format_fallback( void );
#endif

/* Macros to facilitate a generic implementation for our replacement
 * interface functions.
 */
#define __mingw_(FUNCTION)  __construct_name__(__mingw,FUNCTION)
#define __fallback_(FUNCTION)  __construct_name__(FUNCTION,_fallback)
#define __construct_name__(prefix,suffix)  prefix##suffix

/* Macros to map replacement function names to their equivalent
 * symbol names, for lookup in the MSVCRT export table.
 */
#define __api_name__(FUNCTION)  __stringify__(FUNCTION)
#define __stringify__(TEXT) #TEXT

RTNTYPE __mingw_(FUNCTION)( ARGTYPE ARGLIST )
{
  /* Our generic interface maps an indirect call to the API...
   */
  static RTNTYPE (*api_helper)( ARGTYPE ARGLIST ) = NULL;

  /* ...such that it will prefer an MSVCRT implementation...
   */
  if(  (api_helper == NULL)
  &&  ((api_helper = dlsym( RTLD_DEFAULT, __api_name__(FUNCTION) )) == NULL)  )
    /*
     * ...but substituting our replacement, when necessary...
     */
    api_helper = __mingw_(__fallback_(FUNCTION));

  /* ...and ultimately, invoking the selected API function.
   */
  return api_helper_result;
}
#endif

/* $RCSfile$: end of file */
