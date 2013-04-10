/**
 * @file @FILENAME@
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
#include <stdio.h>

static __inline__ double __fast_log (double x)
{
   double res;
   asm __volatile__
     ("fldln2\n\t"
      "fxch\n\t"
      "fyl2x"
       : "=t" (res) : "0" (x) : "st(1)");
   return res;
}

static __inline__ double __fast_log1p (double x)
{
  double res;
  /* fyl2xp1 accurate only for |x| <= 1.0 - 0.5 * sqrt (2.0) */
  if (fabs (x) >= 1.0 - 0.5 * 1.41421356237309504880)
    res = __fast_log (1.0 + x);
  else
    asm __volatile__
      ("fldln2\n\t"
       "fxch\n\t"
       "fyl2xp1"
       : "=t" (res) : "0" (x) : "st(1)");
   return res;
}

static __inline__ double __fast_sqrt (double x)
{
  double res;
  asm __volatile__ ("fsqrt" : "=t" (res) : "0" (x));
  return res;
}


do_test(double a) {
  const int prec = 17;
  double r = asinh(a);
  printf("asinh(%.*g)=%.*g\n", prec, a, prec, r);

{ double z;
  z = fabs (a);
  z = __fast_log1p (z + z * z / (__fast_sqrt (z * z + 1.0L) + 1.0L));
  z = copysign(z, a);
  printf("..... z=%.17g\n", z);
}
}

do_testl(long double a) {
  const int prec = 25;
  long double r = asinhl(a);
  printf("asinhl(%.*Lg)=%.*Lg\n", prec, a, prec, r);
}

do_testf(float a) {
  const int prec = 9;
  float r = asinhf(a);
  printf("asinhf(%.*g)=%.*g\n", prec, (double)a, prec, (double)r);
}

int
main() {
  printf("=== sizeof(double)=%d\n", sizeof(double));
  do_test(1.0000000000000002e+299);
  do_test(-1.0000000000000002e+299);
  do_test(1.7976931348623157e+308);	/*max double*/
  do_test(-1.7976931348623157e+308);
  do_test(3.40282347e+38F);		/*max loat*/
  do_test(-3.40282347e+38F);
  do_test(0.0);
  do_test(-0.0);

  printf("=== sizeof(long double)=%d\n", sizeof(long double));
  do_testl(1.18973149535723176502e+4932L);	/*max ong double*/
  do_testl(-1.18973149535723176502e+4932L);
  do_testl(1.7976931348623157e+308);		/*max double*/
  do_testl(-1.7976931348623157e+308);
  do_testl(3.40282347e+38F);			/*max loat*/
  do_testl(-3.40282347e+38F);
  do_testl(0.0);
  do_testl(-0.0);

  printf("=== sizeof(float)=%d\n", sizeof(float));
  do_testf(3.40282347e+38F);	/*max float*/
  do_testf(-3.40282347e+38F);
  do_testf(0.0);
  do_testf(-0.0);
  return(0);
}
