/**
 * @file CRTglob.c
 * Copyright (C) 2004, 2012, MinGW.org Project
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
 
/* ---------------------------------------------------------------------------
 *
 * This file is implicitly linked into any executable using libmingwex.a; it
 * defines the global variable, _CRT_glob, with a default value which enables
 * globbing of command line arguments, using mingw32's basic implementation
 * of the POSIX globbing algorithm.  To override this default behaviour:
 *
 * - Explicitly include the object module CRTnoglob.o in your link command;
 *   this defines _CRT_glob = 0, so disabling command line globbing.
 *
 * - Alternatively, explicitly define _CRT_glob as a global variable in one
 *   of your own source modules, assigning any of the related values defined
 *   in _mingw.h, to enable alternative globbing algorithms and/or features,
 *   or zero to disable globbing.
 *
 */
#include <_mingw.h>

int _CRT_glob = __CRT_GLOB_USE_MINGW__;
