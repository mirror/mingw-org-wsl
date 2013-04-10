/**
 * @file vsscanf.c
 * Copyright 2012, 2013 MinGW.org project
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
#include <stdarg.h>
#include <stdio.h>


int vsscanf(const char * __restrict__ s, const char * __restrict__ format, va_list arg) {
  int ret;

  __asm__(

    // allocate stack (esp += frame - arg3 - (8[arg1,2] + 12))
    "movl	%%esp, %%ebx\n\t"
    "lea	0xFFFFFFEC(%%esp, %6), %%esp\n\t"
    "subl	%5, %%esp\n\t"

    // set up stack
    "movl	%1, 0xC(%%esp)\n\t"  // s
    "movl	%2, 0x10(%%esp)\n\t"  // format
    "lea	0x14(%%esp), %%edi\n\t"
    "movl	%%edi, (%%esp)\n\t"  // memcpy dest
    "movl	%5, 0x4(%%esp)\n\t"  // memcpy src
    "movl	%5, 0x8(%%esp)\n\t"
    "subl	%6, 0x8(%%esp)\n\t"  // memcpy len
    "call	_memcpy\n\t"
    "addl	$12, %%esp\n\t"

    // call sscanf
    "call	_sscanf\n\t"

    // restore stack
    "movl	%%ebx, %%esp\n\t"

    : "=a"(ret), "=c"(s), "=d"(format)
    : "1"(s), "2"(format), "S"(arg),
      "a"(&ret)
    : "ebx", "edi");

  return ret;
}
