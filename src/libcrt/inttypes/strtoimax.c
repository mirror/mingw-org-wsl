/**
 * @file strtoimax.c
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
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <inttypes.h>

/* Helper macros */

/* convert digit character to number, in any base */
#define ToNumber(c)	(isdigit(c) ? (c) - '0' : \
			 isupper(c) ? (c) - 'A' + 10 : \
			 islower(c) ? (c) - 'a' + 10 : \
			 -1		/* "invalid" flag */ \
			)
/* validate converted digit character for specific base */
#define valid(n, b)	((n) >= 0 && (n) < (b))

intmax_t
strtoimax(nptr, endptr, base)
	register const char * __restrict__	nptr;
	char ** __restrict__			endptr;
	register int				base;
	{
	register uintmax_t	accum;	/* accumulates converted value */
	register int		n;	/* numeral from digit character */
	int			minus;	/* set iff minus sign seen */
	int			toobig;	/* set iff value overflows */

	if ( endptr != NULL )
		*endptr = (char *)nptr;	/* in case no conversion's performed */

	if ( base < 0 || base == 1 || base > 36 )
		{
		errno = EDOM;
		return 0;		/* unspecified behavior */
		}

	/* skip initial, possibly empty sequence of white-space characters */

	while ( isspace(*nptr) )
		++nptr;

	/* process subject sequence: */

	/* optional sign */
	if ( (minus = *nptr == '-') || *nptr == '+' )
		++nptr;

	if ( base == 0 ) {
		if ( *nptr == '0' ) {
			if ( nptr[1] == 'X' || nptr[1] == 'x' )
				base = 16;
			else
				base = 8;
		}
		else
				base = 10;
	}
	/* optional "0x" or "0X" for base 16 */

	if ( base == 16 && *nptr == '0' && (nptr[1] == 'X' || nptr[1] == 'x') )
		nptr += 2;		/* skip past this prefix */

	/* check whether there is at least one valid digit */

	n = ToNumber(*nptr);
	++nptr;

	if ( !valid(n, base) )
		return 0;		/* subject seq. not of expected form */

	accum = n;

	for ( toobig = 0; n = ToNumber(*nptr), valid(n, base); ++nptr )
		if ( accum > (uintmax_t)(INTMAX_MAX / base + 2) ) /* major wrap-around */
			toobig = 1;	/* but keep scanning */
		else
			accum = base * accum + n;

	if ( endptr != NULL )
		*endptr = (char *)nptr;	/* points to first not-valid-digit */

	if ( minus )
		{
		if ( accum > (uintmax_t)INTMAX_MAX + 1 )
			toobig = 1;
		}
	else
	if ( accum > (uintmax_t)INTMAX_MAX )
		toobig = 1;

	if ( toobig )
		{
		errno = ERANGE;
		return minus ? INTMAX_MIN : INTMAX_MAX;
		}
	else
		return (intmax_t)(minus ? -accum : accum);
	}

long long __attribute__ ((alias ("strtoimax")))
strtoll (const char* __restrict__ nptr, char ** __restrict__ endptr, int base);
