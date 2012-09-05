/**
 * @file wctype.c
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
  wctype.c
  7.25.2.2.2 The wctype function

  Contributed by: Danny Smith  <dannysmith@usesr.sourcefoge.net>
		  2005-02-24
   
  This source code is placed in the PUBLIC DOMAIN. It is modified
  from the Q8 package created by Doug Gwyn <gwyn@arl.mil>  

  The wctype function constructs a value with type wctype_t that
  describes a class of wide characters identified by the string
  argument property.

  In particular, we map the property strings so that:

  iswctype(wc, wctype("alnum")) == iswalnum(wc) 
  iswctype(wc, wctype("alpha")) == iswalpha(wc)
  iswctype(wc, wctype("cntrl")) == iswcntrl(wc)
  iswctype(wc, wctype("digit")) == iswdigit(wc)
  iswctype(wc, wctype("graph")) == iswgraph(wc)
  iswctype(wc, wctype("lower")) == iswlower(wc)
  iswctype(wc, wctype("print")) == iswprint(wc)
  iswctype(wc, wctype("punct")) == iswpunct(wc)
  iswctype(wc, wctype("space")) == iswspace(wc)
  iswctype(wc, wctype("upper")) == iswupper(wc)
  iswctype(wc, wctype("xdigit")) == iswxdigit(wc)

*/

#include	<string.h>
#include	<wctype.h>

/* Using the bit-OR'd ctype character classification flags as return
   values achieves compatibility with MS iswctype().  */
static const struct {
  const char *name;
  wctype_t flags;} cmap[] = {
    {"alnum", _ALPHA|_DIGIT},
    {"alpha", _ALPHA},
    {"cntrl", _CONTROL},
    {"digit", _DIGIT},
    {"graph", _PUNCT|_ALPHA|_DIGIT},
    {"lower", _LOWER},
    {"print", _BLANK|_PUNCT|_ALPHA|_DIGIT},
    {"punct", _PUNCT},
    {"space", _SPACE},
    {"upper", _UPPER},
    {"xdigit", _HEX}
  };

#define NCMAP	(sizeof cmap / sizeof cmap[0])
wctype_t wctype (const char *property)
{
  int i;
  for (i = 0; i < NCMAP; ++i)
    if (strcmp (property, cmap[i].name) == 0)
      return cmap[i].flags;
  return 0;
}
