/*
 * fesetenv.c
 *
 * Implements the fesetenv(3) function, per ISO-C99 section 7.6.4.3
 *
 * $Id$
 *
 * Written by Danny Smith  <dannysmith@users.sourceforge.net>
 * Copyright (C) 2002, 2005, 2006, 2017, MinGW.org Project.
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
#define __USE_CRTIMP

#include <fenv.h>
#include <float.h>
#include "cpu_features.h"

int fesetenv( const fenv_t *fenvp )
{
  /* Specified by ISO-C99 section 7.6.4.3
   *
   * The fesetenv() function establishes the floating-point environment
   * represented by the object pointed to by "envp".  The argument "envp"
   * points to an object set by a call to fegetenv() or feholdexcept(), or
   * equals the macro, FE_DFL_ENV, or an implementation-defined environment
   * macro.  Note that fesetenv() merely sets the state of the exception
   * flags represented through its argument; it does not raise these
   * exceptions.
   *
   *
   * The following static variable stores the predefined environment
   * which is associated with FE_DFL_ENV; initialize it to represent
   * the Intel X87 default configuration.
   */
  static const fenv_t *fenv_default = FE_PC64_ENV;

  /* Before anything else, establish a default exception handling
   * policy for SSE instructions, to be used in conjunction with the
   * predefined FPU state macros, (establishing an effective default
   * MXCSR status value of 0x1F80, so masking all exceptions, while
   * leaving all other bits as zero), in the event that SSE support
   * is available.
   */
  unsigned fenv_mxcsr = FE_ALL_EXCEPT << __MXCSR_EXCEPT_MASK_SHIFT;

  if( fenvp == FE_PD64_ENV )
    /* This is a request to both initialize the FPU state, to the
     * FE_PC64_ENV predefined state, and to store that state as the
     * application default.
     */
    fenvp = fenv_default = FE_PC64_ENV;

  else if( fenvp == FE_PD53_ENV )
    /* Conversely, this requests initialization of FPU state to the
     * FE_PC53_ENV predefined state, and to store that state as the
     * new application default.
     */
    fenvp = fenv_default = FE_PC53_ENV;

  else if( fenvp == FE_DFL_ENV )
    /* This simply requests initialization of FPU state to whichever
     * of the two preceding predefined states has been previously set
     * as the application default.
     */
    fenvp = fenv_default;

  if( fenvp == FE_PC64_ENV )
    /* The FPU's "fninit" instruction initializes the FPU control
     * word register to 0x37F, the status register to zero and the
     * tag word to 0xFFFF.  The other registers are unaffected.
     */
    __asm__( "fninit" );

  else if( fenvp == FE_PC53_ENV )
    /* Microsoft's _fpreset() does the same, EXCEPT that it sets
     * the control word to 0x27F (53-bit precison).  Here, we want
     * to force a call to _fpreset() in MSVCRT.DLL
     */
    _fpreset();

  else
  { /* The requested FPU state is not represented by any of the
     * predefined state macros; assume it is a properly constructed
     * fenv_t structure, and load it to the FPU as is.
     */
    __asm__( "fldenv %0" :: "m" (*fenvp) );

    /* Also, in the event that SSE instructions may be supported,
     * extract the MXCSR flags from this same structure, to be used
     * instead of the defaults which have been established for use
     * in conjunction with the predefined state macros, noting that
     * attempting to set any of the reserved high-order flags will
     * induce a segmentation fault, so mask them off.
     */
    fenv_mxcsr = fenvp->__mxcsr & 0xFFFF;
  }

  if( __HAS_SSE )
    /* Finally, if SSE instructions are supported, set the MXCSR
     * exception handling policy flags...
     */
    __asm__( "ldmxcsr %0" :: "m" (fenv_mxcsr) );

  /* ...and we are done; there is no mechanism for us to detect
   * failure, so simply return zero, indicating success.
   */
  return 0;
}

/* $RCSfile$: end of file */
