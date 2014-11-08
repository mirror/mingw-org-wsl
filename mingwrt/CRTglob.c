/*
 * CRTglob.c
 *
 * This file is a part of the mingw-runtime package; it has no copyright
 * assigned and is placed in the Public Domain. No warranty is given; refer
 * to the file DISCLAIMER within the package.
 *
 * Link with this object file to set _CRT_glob to a state that will turn
 * on command line globbing by default, preferring the MinGW algorithm to
 * Microsoft's, but without enabling any of its additional features, as
 * described in include/_mingw.h.
 *
 * NOTE: this file is linked by default, via libmingw32.a, if _CRT_glob
 * is not defined elsewhere in explicitly linked object files.  To turn
 * globbing off, you may link explicitly with CRT_noglob.o, or you may
 * define _CRT_glob with a value of zero, as a global variable in one of
 * your own source files, (typically, the one which defines your main()
 * function).  To enable any of the additional globbing features described
 * in include/_mingw.h, you should define _CRT_glob yourself, initializing
 * it to the value formed by logical OR of __CRT_GLOB_USE_MINGW__ with the
 * additional feature descriptors you wish to enable, while to select
 * Microsoft's globbing algorithm in preference to MinGW's, you should
 * initialize _CRT_glob = __CRT_glob = __CRT_GLOB_USE_MSVCRT__
 *
 */
#include <_mingw.h>

int _CRT_glob = __CRT_GLOB_USE_MINGW__;

/* $RCSfile$: end of file */
