/**
 * @file csqrtf.c
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
#include <math.h>
#include <complex.h>

float complex  csqrtf (float complex Z)
{
  float complex Res;
  float r;
  float x = __real__ Z;
  float y = __imag__ Z;

  if (y == 0.0f)
    {
      if (x < 0.0f)
        {
 	  __real__ Res = 0.0f;
	  __imag__ Res = sqrtf (-x);
        }
      else
        {
 	  __real__ Res = sqrtf (x);
	  __imag__ Res = 0.0f;
        }
    }

  else if (x == 0.0f)
    {
      r = sqrtf(0.5f * fabsf (y));
      __real__ Res = r;
      __imag__ Res = y > 0 ? r : -r;
    }

  else
    {
      float t = sqrtf (2 * (_hypot (__real__ Z, __imag__ Z) + fabsf (x)));
      float u = t / 2.0f;
      if ( x > 0.0f)
        {	
          __real__ Res = u;
          __imag__ Res = y / t;
        }
      else
        {
	  __real__ Res = fabsf (y / t);
	  __imag__ Res = y < 0 ? -u : u;
        }
    }

  return Res;
}
