/**
 * @file cacosf.c
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

#if 0
/* cacos (Z) = -I * clog(Z + I * csqrt(1 - Z * Z)) */

float complex cacos (float  complex Z)
{
  float complex Res;
  float x, y;

  x = __real__ Z;
  y = __imag__ Z;

  if (y == 0.0f)
    {
      __real__ Res = acosf (x);
      __imag__ Res = 0.0f;
    }

  else
    {
      float complex ZZ;
      /* Z * Z = ((x - y) * (x + y)) + (2.0 * x * y) * I */
      /* caculate 1 - Z * Z */
      __real__ ZZ = 1.0f - (x - y) * (x + y);
      __imag__ ZZ = -2.0f * x * y;

       
       Res = csqrtf(ZZ);

      /* calculate ZZ + I * sqrt (ZZ) */
    
      __real__ ZZ = x - __imag__ Res;
      __imag__ ZZ = y + __real__ Res;
       
      ZZ = clog(ZZ);

      /* mult by -I */

      __real__ Res  =  __imag__ ZZ;
      __imag__ Res = - __real__ ZZ;
    }
  return Res;
}

#else

/* cacos ( Z ) =  pi/2 - casin ( Z ) */

float complex cacosf (float complex Z)
{
  float complex Res  = casinf (Z);
  __real__ Res = M_PI_2 - __real__ Res;
  __imag__ Res = - __imag__ Res;
  return Res;
}
#endif
