/**
 * @file ctanf.c
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


/* ctan (x + I * y) = (sin (2 * x)  +  I * sinh(2 * y))
		      / (cos (2 * x)  +  cosh (2 * y)) */

float complex ctanf (float complex Z)
{
  float complex Res;
  float two_I = 2.0f * __imag__ Z;
  float two_R = 2.0f * __real__ Z;
  float denom = cosf (two_R) + coshf (two_I);
  if (denom == 0.0f)
    {
      errno = ERANGE;
      __real__ Res = HUGE_VALF;
      __imag__ Res = HUGE_VALF;
    }
  else if (isinf (denom))
    {
      errno = ERANGE;
      __real__ Res = 0.0;
      __imag__ Res = two_I > 0 ? 1.0f : -1.0f;
    }
  else
    {
      __real__ Res = sinf (two_R) / denom;
      __imag__ Res = sinhf (two_I) / denom;
    }
  return Res;
}

