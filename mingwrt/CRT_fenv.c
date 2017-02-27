/*
 * CRT_fenv.c
 *
 * Specifies the default FPU configuration, in terms of one of the
 * predefined floating point environments defined in <fenv.h>, via
 * a global variable assignment, whence the specified selection will
 * be copied to FE_DFL_ENV at application start-up.
 *
 * $Id$
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2017, MinGW.org Project.
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
 * This file replaces the two original files CRT_fp8.c, and CRT_fp10.c;
 * compile it using each of the two commands:
 *
 *   gcc -c -D_CRT_FE_DFL_ENV=8  CRT_fenv.c -o CRT_fp8.o
 *   gcc -c -D_CRT_FE_DFL_ENV=10 CRT_fenv.c -o CRT_fp10.o
 *
 * to create the complementary pair of object files, reproducing the
 * intended effect of the original similarly named object file pair.
 *
 */
#include <fenv.h>

#ifndef _CRT_FE_DFL_ENV
/* If the user neglects to specify this, assume that the intention is
 * to reproduce, in FE_DFL_ENV, the effect of the original CRT_fp10.o
 * object file.
 */
# define _CRT_FE_DFL_ENV  10
#endif

/* Initialize the "_CRT_fenv" global variable, based on compile time
 * selection, to map FE_DFL_ENV to FE_PC53_env, (precision configured
 * to 53-bits), or to FE_PC64_ENV, (precision configured to 64-bits),
 * via initial FPU configuration to FE_PD53_ENV, (precision default
 * 53-bits), or FE_PD64_ENV, (precision default 64-bits).
 */
const fenv_t *_CRT_fenv = (_CRT_FE_DFL_ENV == 8) ? FE_PD53_ENV : FE_PD64_ENV;

/* $RCSfile$: end of file */
