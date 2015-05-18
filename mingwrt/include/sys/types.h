/*
 * sys/types.h
 *
 * Definitions of (primarily POSIX) system data types.
 *
 * $Id$
 *
 * Written by Rob Savoye <rob@cygnus.com>
 * Copyright (C) 1997-1999, 2001, 2003, 2004, 2008, 2011, 2014-2015,
 *   MinGW.org Project.
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
#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H
#pragma GCC system_header

/* All the headers include this file. */
#include <_mingw.h>

#ifndef RC_INVOKED

#define __need_size_t
#define __need_ptrdiff_t
#define __need_wchar_t
#include <stddef.h>

#define __need_time_t
#define _FAKE_TIME_H_SOURCED 1
#include <parts/time.h>


#ifndef	_OFF_T_
#define	_OFF_T_
typedef long _off_t;

#ifndef	_NO_OLDNAMES
typedef _off_t	off_t;
#endif
#endif	/* Not _OFF_T_ */


#ifndef _DEV_T_
#define	_DEV_T_
#ifdef __MSVCRT__
typedef unsigned int _dev_t;
#else
typedef short _dev_t;
#endif

#ifndef	_NO_OLDNAMES
typedef _dev_t	dev_t;
#endif
#endif	/* Not _DEV_T_ */


#ifndef _INO_T_
#define	_INO_T_
typedef short _ino_t;

#ifndef	_NO_OLDNAMES
typedef _ino_t	ino_t;
#endif
#endif	/* Not _INO_T_ */


#ifndef _PID_T_
#define	_PID_T_
typedef int	_pid_t;

#ifndef	_NO_OLDNAMES
typedef _pid_t	pid_t;
#endif
#endif	/* Not _PID_T_ */


#ifndef _MODE_T_
#define	_MODE_T_
typedef unsigned short _mode_t;

#ifndef	_NO_OLDNAMES
typedef _mode_t	mode_t;
#endif
#endif	/* Not _MODE_T_ */


#ifndef _SIGSET_T_
#define	_SIGSET_T_
typedef int	_sigset_t;

#ifndef	_NO_OLDNAMES
typedef _sigset_t	sigset_t;
#endif
#endif	/* Not _SIGSET_T_ */

#ifndef _SSIZE_T_
#define _SSIZE_T_
typedef int _ssize_t;

#ifndef	_NO_OLDNAMES
typedef _ssize_t ssize_t;
#endif
#endif /* Not _SSIZE_T_ */

#ifndef _FPOS64_T_
#define _FPOS64_T_
typedef long long fpos64_t;
#endif

#ifndef _OFF64_T_
#define _OFF64_T_
typedef long long off64_t;
#endif

#if _POSIX_C_SOURCE
/* useconds_t is an obsolete POSIX data type; we continue to define
 * it here, for backward compatibility, but we flag it as deprecated,
 * due to its obsolete status.
 */
typedef unsigned long useconds_t __MINGW_ATTRIB_DEPRECATED;
#endif

#endif	/* ! RC_INVOKED */
#endif	/* ! _SYS_TYPES_H: $RCSfile$: end of file */
