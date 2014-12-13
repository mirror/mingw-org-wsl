#ifndef _UNISTD_H
/*
 * This file is part of the Mingw32 package.
 *
 * unistd.h maps (roughly) to io.h
 * Other headers included by unistd.h may be selectively processed;
 * __UNISTD_H_SOURCED__ enables such selective processing.
 */
#define _UNISTD_H
#define __UNISTD_H_SOURCED__ 1

#include <io.h>
#include <process.h>
#include <getopt.h>

/* These are also defined in stdio.h. */
#ifndef	SEEK_SET
#define SEEK_SET 0
#endif

#ifndef	SEEK_CUR
#define SEEK_CUR 1
#endif

#ifndef SEEK_END
#define SEEK_END 2
#endif

_BEGIN_C_DECLS

#if !defined __NO_ISOCEXT
#include <sys/types.h> /* For useconds_t. */

int __cdecl __MINGW_NOTHROW usleep(useconds_t useconds);
#endif  /* Not __NO_ISOCEXT */

/* This is defined both as a real library function, to allow autoconf
 * to verify its existence, and as a potentially inline implementation.
 */
int ftruncate(int, off_t);
#ifndef __NO_INLINE__
__CRT_INLINE __JMPSTUB__(( FUNCTION = ftruncate, REMAPPED = _chsize ))
int ftruncate(int __fd, off_t __length)
{ return _chsize (__fd, __length); }
#endif

_END_C_DECLS

#undef __UNISTD_H_SOURCED__
#endif /* _UNISTD_H */
