/**
 * @file cpowl.c
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

long double complex cpowl (long double complex X, long double complex Y)
{
  long double complex Res;
  long double i;
  long double r = hypotl (__real__ X, __imag__ X);
  if (r == 0.0L)
    {
       __real__ Res = __imag__ Res = 0.0L;
    }
  else
    {
      long double rho;
      long double theta;
      i = cargl (X);
      theta = i * __real__ Y;
 
      if (__imag__ Y == 0.0L)
	/* This gives slightly more accurate results in these cases. */
   	rho = powl (r, __real__ Y);
      else
	{
          r = logl (r);
	  /* rearrangement of cexp(X * clog(Y)) */
	  theta += r * __imag__ Y;
	  rho = expl (r * __real__ Y - i * __imag__ Y);
	}

      __real__ Res = rho * cosl (theta);
      __imag__ Res = rho * sinl (theta);
    }
  return  Res;
}
