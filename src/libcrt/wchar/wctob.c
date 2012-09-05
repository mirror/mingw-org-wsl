/**
 * @file wctob.c
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
#include "mb_wc_common.h"
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

/* Return just the first byte after translating to multibyte.  */
int wctob (wint_t wc )
{
    wchar_t w = wc;
    char c;
    int invalid_char = 0;
    if (!WideCharToMultiByte (get_codepage(), 
			      0 /* Is this correct flag? */,
			      &w, 1, &c, 1, NULL, &invalid_char)
         || invalid_char)
      return EOF;
    return (int) c;
}
