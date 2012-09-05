/**
 * @file wctrans.c
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
/*
   wctrans.c 
   7.25.3.2 Extensible wide-character case mapping functions

   Contributed by: Danny Smith  <dannysmith@usesr.sourcefoge.net>
   		   2005-02-24
   
  This source code is placed in the PUBLIC DOMAIN. It is modified
  from the Q8 package created by Doug Gwyn <gwyn@arl.mil>  

 */

#include <string.h>
#include <wctype.h>

/*
   This differs from the MS implementation of wctrans which
   returns 0 for tolower and 1 for toupper.  According to
   C99, a 0 return value indicates invalid input.

   These two function go in the same translation unit so that we
   can ensure that
     towctrans(wc, wctrans("tolower")) == towlower(wc) 
     towctrans(wc, wctrans("toupper")) == towupper(wc)
   It also ensures that
     towctrans(wc, wctrans("")) == wc
   which is not required by standard.
*/

static const struct {
  const char *name;
  wctrans_t val; } tmap[] = {
    {"tolower", _LOWER},
    {"toupper", _UPPER}
 };

#define	NTMAP	(sizeof tmap / sizeof tmap[0])

wctrans_t
wctrans (const char* property)
{
  int i;
  for ( i = 0; i < NTMAP; ++i )
    if (strcmp (property, tmap[i].name) == 0)
      return tmap[i].val;
   return 0;
}

wint_t towctrans (wint_t wc, wctrans_t desc)
{
  switch (desc)
    {
    case _LOWER:
      return towlower (wc);
    case _UPPER:
      return towupper (wc);
    default:
      return wc;
   }
}
