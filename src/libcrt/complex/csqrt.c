/**
 * @file csqrt.c
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

double complex  csqrt (double complex Z)
{
  double complex Res;
  double t;
  double x = __real__ Z;
  double y = __imag__ Z;

  if (y == 0.0)
    {
      if (x < 0.0)
        {
 	  __real__ Res = 0.0;
	  __imag__ Res = sqrt (-x);
        }
      else
        {
 	  __real__ Res = sqrt (x);
	  __imag__ Res = 0.0;
        }
    }

  else if (x == 0.0)
    {
      t = sqrt(0.5 * fabs (y));
      __real__ Res = t;
      __imag__ Res = y > 0 ? t : -t;
    }

  else
    {
      t = sqrt (2.0  * (_hypot (x, y) + fabs (x)));
      double u = t / 2.0;
      if ( x > 0.0)
        {	
          __real__ Res = u;
          __imag__ Res = y / t;
        }
      else
        {
	  __real__ Res = fabs ( y / t);
	  __imag__ Res = y < 0.0 ? -u : u;
        }
    }

  return Res;
}

