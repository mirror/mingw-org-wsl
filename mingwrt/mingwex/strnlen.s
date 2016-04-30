/*
 * strnlen.s
 *
 * Implementation of POSIX.1-2008 conforming strnlen(), and a wrapper
 * extending it to conform with ISO-C11 TR-24731-1 strnlen_s().
 *
 * $Id$
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2016, MinGW.org Project
 *
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
 *
 *
 * This file implements a POSIX.1-2008 conforming strnlen() function, under
 * the alternative public name of __mingw_strnlen(), (to avoid any possible
 * conflict with Microsoft's DLL implementations, or a replacement function
 * implemented by the user).
 *
 * Note that POSIX does not prescribe any error returns for its strnlen()
 * function; in particular, it does not specify handling of a NULL pointer,
 * passed as the string argument to count, and thus, a segmentation fault
 * is a plausible outcome.  This is consistent with the behaviour exhibited
 * by Microsoft's implementation, and this implementation acts likewise.
 *
 * OTOH, ISO-C11 TR-24731-1 prescribes that strnlen_s() shall return zero,
 * when passed a NULL pointer as the string argument; the alternative entry
 * point, __mingw_strnlen_s(), checks for this anomaly, and acts accordingly,
 * before continuing as for __mingw_strnlen(), when passed a valid pointer
 * to a string argument; (this is consistent with the documented behaviour
 * of Microsoft's strnlen_s() implementation).
 *
 * Note that I've chosen to implement this in assembly language to enable
 * sharing of common code between two distinct entry points, with subtly
 * differing behaviours, while avoiding the overhead of an extra function
 * call to invoke such shared code; this also allows the code to exploit
 * the CUP's string scanning instructions, (which GCC does not), and so
 * achieves a more compact, (and likely more efficient), implementation.
 *
 */
.text
.align	4
.globl	___mingw_strnlen
.def	___mingw_strnlen;	.scl	2;	.type	32;	.endef

___mingw_strnlen:
/* Implements: size_t __mingw_strnlen (const char *string, size_t maxlen );
 *
 * Scans at most maxlen chars, returning the lesser of strlen (string) and
 * maxlen; does NOT check for string == NULL, which may thus induce failure
 * with a segmentation fault.  Note that initialization of return count to
 * zero, in EAX, also serves as the NUL char reference for SCASB, in AL.
 */
	pushl	%edi		/* must preserve this */
	xorl	%eax, %eax	/* initialize return count to zero */
	movl	8(%esp), %edx	/* load address of string argument */
.L1:
	movl	12(%esp), %ecx	/* load maxlen ... */
	jecxz	.L4		/* and jump to end, if it's zero */
.L2:
	cld			/* scan string from low-->high address */
	movl	%edx, %edi	/* using this as the scan pointer ... */
	repne	scasb		/* as required by this CPU scan */
	mov	%edi, %eax	/* note where we stopped ... */
	jz	.L3		/* but if we found NUL, we've overrun ... */
	decl	%eax		/* so we need to adjust one byte backward */
.L3:
	sub	%edx, %eax	/* compute effective count to return */
.L4:
	popl	%edi		/* restore saved register ... */
	ret			/* and we're done */

.align	4
.globl	___mingw_strnlen_s
.def	___mingw_strnlen_s;	.scl	2;	.type	32;	.endef

___mingw_strnlen_s:
/* Implements: size_t __mingw_strnlen_s (const char *string, size_t maxlen );
 *
 * Exhibits identical behaviour to __mingw_strnlen(), EXCEPT that it DOES
 * check for string == NULL, returning zero when found.
 */
	pushl	%edi		/* must preserve this */
	xorl	%eax, %eax	/* initialize return count to zero */
	movl	8(%esp), %edx	/* load address of string argument ... */
	testl	%edx, %edx	/* checking for NULL pointer, and ... */
	jnz	.L1		/* proceeding as strnlen(), if not ... */
	popl	%edi		/* otherwise restore saved register ... */
	ret			/* and return zero count value */

/* $RCSfile$: end of file */
