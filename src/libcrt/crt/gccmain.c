/**
 * @file gccmain.c
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
 * A separate version of __main, __do_global_ctors and __do_global_dtors for
 * Mingw32 for use with Cygwin32 b19. Hopefully this object file will only
 * be linked if the libgcc.a doesn't include __main, __do_global_dtors and
 * __do_global_ctors.
 */

/* Needed for the atexit prototype. */
#include <stdlib.h>

typedef void (*func_ptr) (void);
extern func_ptr __CTOR_LIST__[];
extern func_ptr __DTOR_LIST__[];

void
__do_global_dtors (void)
{
  static func_ptr *p = __DTOR_LIST__ + 1;

  /*
   * Call each destructor in the destructor list until a null pointer
   * is encountered.
   */
  while (*p)
    {
      (*(p)) ();
      p++;
    }
}

void
__do_global_ctors (void)
{
  unsigned long nptrs = (unsigned long) __CTOR_LIST__[0];
  unsigned i;

  /*
   * If the first entry in the constructor list is -1 then the list
   * is terminated with a null entry. Otherwise the first entry was
   * the number of pointers in the list.
   */
  if (nptrs == -1)
    {
      for (nptrs = 0; __CTOR_LIST__[nptrs + 1] != 0; nptrs++)
	;
    }

  /* 
   * Go through the list backwards calling constructors.
   */
  for (i = nptrs; i >= 1; i--)
    {
      __CTOR_LIST__[i] ();
    }

  /*
   * Register the destructors for processing on exit.
   */
  atexit (__do_global_dtors);
}

static int initialized = 0;

void
__main (void)
{
  if (!initialized)
    {
      initialized = 1;
      __do_global_ctors ();
    }
}

