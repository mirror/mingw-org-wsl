/**
 * @file pformat.h
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
#ifndef PFORMAT_H
/*
 * pformat.h
 *
 * $Id: pformat.h,v 1.1 2008/07/28 23:24:20 keithmarshall Exp $
 *
 * A private header, defining the `pformat' API; it is to be included
 * in each compilation unit implementing any of the `printf' family of
 * functions, but serves no useful purpose elsewhere.
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 *
 * This is free software.  You may redistribute and/or modify it as you
 * see fit, without restriction of copyright.
 *
 * This software is provided "as is", in the hope that it may be useful,
 * but WITHOUT WARRANTY OF ANY KIND, not even any implied warranty of
 * MERCHANTABILITY, nor of FITNESS FOR ANY PARTICULAR PURPOSE.  At no
 * time will the author accept any form of liability for any damages,
 * however caused, resulting from the use of this software.
 */
#define PFORMAT_H

/* The following macros reproduce definitions from _mingw.h,
 * so that compilation will not choke, if using any compiler
 * other than the MinGW implementation of GCC.
 */
#ifndef __cdecl
# ifdef __GNUC__
#  define __cdecl __attribute__((__cdecl__))
# else
#  define __cdecl
# endif
#endif

#ifndef __MINGW_GNUC_PREREQ
# if defined __GNUC__ && defined __GNUC_MINOR__
#  define __MINGW_GNUC_PREREQ( major, minor )\
     (__GNUC__ > (major) || (__GNUC__ == (major) && __GNUC_MINOR__ >= (minor)))
# else
#  define __MINGW_GNUC_PREREQ( major, minor )
# endif
#endif

#ifndef  __MINGW_NOTHROW
# if __MINGW_GNUC_PREREQ( 3, 3 )
#  define __MINGW_NOTHROW  __attribute__((__nothrow__))
# else
#  define __MINGW_NOTHROW
# endif
#endif

/* This isn't currently defined therein,
 * but is a potential candidate for inclusion in _mingw.h
 */
#ifdef __MINGW32__
# define __stringify__(NAME)    #NAME
# define __mingw_quoted(NAME)  __stringify__(__mingw_##NAME)
# define __mingw_alias(NAME)   __attribute__((alias(__mingw_quoted(NAME)))) NAME
#else
# define __mingw_alias(NAME)   NAME
#endif

/* The following are the declarations specific to the `pformat' API...
 */
#define PFORMAT_TO_FILE     0x1000
#define PFORMAT_NOLIMIT     0x2000

#ifdef __MINGW32__
 /*
  * Map MinGW specific function names, for use in place of the generic
  * implementation defined equivalent function names.
  */
# define __pformat        __mingw_pformat

# define __printf         __mingw_printf
# define __fprintf        __mingw_fprintf
# define __sprintf        __mingw_sprintf
# define __snprintf       __mingw_snprintf

# define __vprintf        __mingw_vprintf
# define __vfprintf       __mingw_vfprintf
# define __vsprintf       __mingw_vsprintf
# define __vsnprintf      __mingw_vsnprintf

#endif

int __cdecl __pformat( int, void *, int, const char *, va_list ) __MINGW_NOTHROW;

#endif /* !defined PFORMAT_H: $RCSfile: pformat.h,v $Revision: 1.1 $: end of file */
