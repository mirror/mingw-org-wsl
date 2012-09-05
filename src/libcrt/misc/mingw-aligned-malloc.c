/**
 * @file mingw-aligned-malloc.c
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
  __mingw_aligned_malloc and friends, implemented using Microsoft's public
  interfaces and with the help of the algorithm description provided
  by Wu Yongwei: http://sourceforge.net/mailarchive/message.php?msg_id=3847075

  I hereby place this implementation in the public domain.
               -- Steven G. Johnson (stevenj@alum.mit.edu)
*/

#include <stdlib.h>
#include <errno.h>
#include <stddef.h>		/* ptrdiff_t */
#include <string.h>		/* memmove */

#ifdef HAVE_STDINT_H
#  include <stdint.h>		/* uintptr_t */
#else
#  define uintptr_t size_t
#endif

#define NOT_POWER_OF_TWO(n) (((n) & ((n) - 1)))
#define UI(p) ((uintptr_t) (p))
#define CP(p) ((char *) p)

#define PTR_ALIGN(p0, alignment, offset)				\
            ((void *) (((UI(p0) + (alignment + sizeof(void*)) + offset)	\
			& (~UI(alignment - 1)))				\
		       - offset))

/* Pointer must sometimes be aligned; assume sizeof(void*) is a power of two. */
#define ORIG_PTR(p) (*(((void **) (UI(p) & (~UI(sizeof(void*) - 1)))) - 1))

void *
__mingw_aligned_offset_malloc (size_t size, size_t alignment, size_t offset)
{
  void *p0, *p;

  if (NOT_POWER_OF_TWO (alignment))
    {
      errno = EINVAL;
      return ((void *) 0);
    }
  if (size == 0)
    return ((void *) 0);
  if (alignment < sizeof (void *))
    alignment = sizeof (void *);

  /* Including the extra sizeof(void*) is overkill on a 32-bit
     machine, since malloc is already 8-byte aligned, as long
     as we enforce alignment >= 8 ...but oh well.  */

  p0 = malloc (size + (alignment + sizeof (void *)));
  if (!p0)
    return ((void *) 0);
  p = PTR_ALIGN (p0, alignment, offset);
  ORIG_PTR (p) = p0;
  return p;
}

void *
__mingw_aligned_malloc (size_t size, size_t alignment)
{
  return __mingw_aligned_offset_malloc (size, alignment, 0);
}

void
__mingw_aligned_free (void *memblock)
{
  if (memblock)
    free (ORIG_PTR (memblock));
}

void *
__mingw_aligned_offset_realloc (void *memblock, size_t size,
				size_t alignment, size_t offset)
{
  void *p0, *p;
  ptrdiff_t shift;

  if (!memblock)
    return __mingw_aligned_offset_malloc (size, alignment, offset);
  if (NOT_POWER_OF_TWO (alignment))
    goto bad;
  if (size == 0)
    {
      __mingw_aligned_free (memblock);
      return ((void *) 0);
    }
  if (alignment < sizeof (void *))
    alignment = sizeof (void *);

  p0 = ORIG_PTR (memblock);
  /* It is an error for the alignment to change. */
  if (memblock != PTR_ALIGN (p0, alignment, offset))
    goto bad;
  shift = CP (memblock) - CP (p0);

  p0 = realloc (p0, size + (alignment + sizeof (void *)));
  if (!p0)
    return ((void *) 0);
  p = PTR_ALIGN (p0, alignment, offset);

  /* Relative shift of actual data may be different from before, ugh.  */
  if (shift != CP (p) - CP (p0))
    /* ugh, moves more than necessary if size is increased.  */
    memmove (CP (p), CP (p0) + shift, size);

  ORIG_PTR (p) = p0;
  return p;

bad:
  errno = EINVAL;
  return ((void *) 0);
}

void *
__mingw_aligned_realloc (void *memblock, size_t size, size_t alignment)
{
  return __mingw_aligned_offset_realloc (memblock, size, alignment, 0);
}
