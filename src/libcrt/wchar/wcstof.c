/**
 * @file wcstof.c
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
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <mbstring.h>

#include "mb_wc_common.h"

float wcstof (const wchar_t * __restrict__ wcs, wchar_t ** __restrict__ wcse)
{
  char * cs;
  char * cse;
  unsigned int i;
  float ret;
  const unsigned int cp = get_codepage ();   

  /* Allocate enough room for (possibly) mb chars */
  cs = (char *) malloc ((wcslen(wcs)+1) * MB_CUR_MAX);

  if (cp == 0) /* C locale */
    {
      for (i = 0; (wcs[i] != 0) && wcs[i] <= 255; i++)
        cs[i] = (char) wcs[i];                                                                                                                                                                                                                                                                                                   
      cs[i]  = '\0';
    }
  else
    {
      int nbytes = -1;
      int mb_len = 0;
      /* loop through till we hit null or invalid character */
      for (i = 0; (wcs[i] != 0) && (nbytes != 0); i++)
	{
     	  nbytes = WideCharToMultiByte(cp, WC_COMPOSITECHECK | WC_SEPCHARS,
				       wcs + i, 1, cs + mb_len, MB_CUR_MAX,
				       NULL, NULL);
	  mb_len += nbytes;
	}
      cs[mb_len] = '\0';
    }

  ret =  strtof (cs, &cse);

  if (wcse)
    {
      /* Make sure temp mbstring cs has 0 at cse.  */ 
      *cse = '\0';
      i = _mbslen ((unsigned char*) cs); /* Number of chars, not bytes */
      *wcse = (wchar_t *) wcs + i;
    }
  free (cs);
 
  return ret;
}
