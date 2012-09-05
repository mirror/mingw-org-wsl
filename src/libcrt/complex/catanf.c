/**
 * @file catanf.c
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
/* catanf.c */

/*
   Contributed by Danny Smith
   2004-12-24

   FIXME: This needs some serious numerical analysis.
*/

#include <math.h>
#include <complex.h>
#include <errno.h>

/* catan (z) = -I/2 * clog ((I + z) / (I - z)) */ 

float complex 
catanf (float complex Z)
{
  float complex Res;
  float complex Tmp;
  float x = __real__ Z;
  float y = __imag__ Z;

  if ( x == 0.0f && (1.0f - fabsf (y)) == 0.0f)
    {
      errno = ERANGE;
      __real__ Res = HUGE_VALF;
      __imag__ Res = HUGE_VALF;
    }
   else if (isinf (hypotf (x, y)))
   {
     __real__ Res = (x > 0 ? M_PI_2 : -M_PI_2);
     __imag__ Res = 0.0f;
   }
  else
    {
      __real__ Tmp = - x; 
      __imag__ Tmp = 1.0f - y;

      __real__ Res = x; 
      __imag__ Res = y + 1.0f;

      Tmp = clogf (Res/Tmp);	
      __real__ Res  = - 0.5f * __imag__ Tmp;
      __imag__ Res =  0.5f * __real__ Tmp;
    }

   return Res; 
}
