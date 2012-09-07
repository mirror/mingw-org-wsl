/**
 * @file catanl.c
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
#include <math.h>
#include <complex.h>
#include <errno.h>

/* catan (z) = -I/2 * clog ((I + z) / (I - z)) */ 

#ifndef _M_PI_2L
#define _M_PI_2L 1.5707963267948966192313L
#endif

long double complex 
catanl (long double complex Z)
{
  long double complex Res;
  long double complex Tmp;
  long double x = __real__ Z;
  long double y = __imag__ Z;

  if ( x == 0.0L && (1.0L - fabsl (y)) == 0.0L)
    {
      errno = ERANGE;
      __real__ Res = HUGE_VALL;
      __imag__ Res = HUGE_VALL;
    }
   else if (isinf (hypotl (x, y)))
   {
     __real__ Res = (x > 0 ? _M_PI_2L : -_M_PI_2L);
     __imag__ Res = 0.0L;
   }
  else
    {
      __real__ Tmp = - x; 
      __imag__ Tmp = 1.0L - y;

      __real__ Res = x; 
      __imag__ Res = y + 1.0L;

      Tmp = clogl (Res/Tmp);	
      __real__ Res  = - 0.5L * __imag__ Tmp;
      __imag__ Res =  0.5L * __real__ Tmp;
    }

   return Res; 
}
