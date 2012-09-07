/**
 * @file cpow.c
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

/* cpow(X, Y) = cexp(X * clog(Y)) */

/* Use dll version of pow */
extern double  (*_imp__pow) (double, double);
#define pow (*_imp__pow)

double complex cpow (double complex X, double complex Y)
{
  double complex Res;
  double i;
  double r = hypot (__real__ X, __imag__ X);
  if (r == 0.0)
    {
       __real__ Res = __imag__ Res = 0.0;
    }
  else
    {
      double rho;
      double theta;
      i = carg (X);
      theta = i * __real__ Y;
 
      if (__imag__ Y == 0.0)
	/* This gives slightly more accurate results in these cases. */
   	rho = pow (r, __real__ Y);
      else
	{
          r = log (r);
	  /* rearrangement of cexp(X * clog(Y)) */
	  theta += r * __imag__ Y;
	  rho = exp (r * __real__ Y - i * __imag__ Y);
	}

      __real__ Res = rho * cos (theta);
      __imag__ Res = rho * sin (theta);
    }
  return  Res;
}

