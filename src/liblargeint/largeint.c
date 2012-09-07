/**
 * @file largeint.c
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
#define __COMPILING_LARGEINT

#include <largeint.h>

__int64 WINAPI
LargeIntegerAdd (__int64 i1, __int64 i2)
{
  return i1 + i2;
}

__int64 WINAPI
LargeIntegerSubtract (__int64 i1, __int64 i2)
{
  return i1 - i2;
}

__int64 WINAPI
LargeIntegerArithmeticShift (__int64 i, int n)
{
  return i >> n;
}

__int64 WINAPI
LargeIntegerShiftLeft (__int64 i, int n)
{
  return i << n;
}

__int64 WINAPI
LargeIntegerShiftRight (__int64 i, int n)
{
  return i >> n;
}

__int64 WINAPI
LargeIntegerNegate (__int64 i)
{
  return -i;
}

__int64 WINAPI
ConvertLongToLargeInteger (LONG l)
{
  return (__int64) l;
}

__int64 WINAPI
ConvertUlongToLargeInteger (ULONG ul)
{
  return _toi(_toui(ul));
}

__int64 WINAPI
EnlargedIntegerMultiply (LONG l1, LONG l2)
{
  return _toi(l1) * _toi(l2);
}

__int64 WINAPI
EnlargedUnsignedMultiply (ULONG ul1, ULONG ul2)
{
  return _toi(_toui(ul1) * _toui(ul2));
}

__int64 WINAPI
ExtendedIntegerMultiply (__int64 i, LONG l)
{
  return i * _toi(l);
}

__int64 WINAPI
LargeIntegerMultiply (__int64 i1, __int64 i2)
{
  return i1 * i2;
}

__int64 WINAPI LargeIntegerDivide (__int64 i1, __int64 i2, __int64 *remainder)
{
  if (remainder)
    *remainder = i1 % i2;
  return i1 / i2;
}

ULONG WINAPI
EnlargedUnsignedDivide (unsigned __int64 i1, ULONG i2, PULONG remainder)
{
  if (remainder)
    *remainder = i1 % _toi(i2);
  return i1 / _toi(i2);
}
__int64 WINAPI
ExtendedLargeIntegerDivide (__int64 i1, ULONG i2, PULONG remainder)
{
  if (remainder)
    *remainder = i1 % _toi(i2);
  return i1 / _toi(i2);
}

/* FIXME: what is this function supposed to do? */
__int64 WINAPI ExtendedMagicDivide (__int64 i1, __int64 i2, int n)
{
  return 0;
}
