/**
 * @file log2l.S
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
/*
 * Written by J.T. Conklin <jtc@netbsd.org>.
 * Adapted for use as log2 by Ulrich Drepper <drepper@cygnus.com>.
 * Public domain.
 *
 * Changed to use fyl2xp1 for values near 1, <drepper@cygnus.com>.
 */

	.file	"log2l.S"
	.text
	.align 4
one:	.double 1.0
	/* It is not important that this constant is precise.  It is only
	   a value which is known to be on the safe side for using the
	   fyl2xp1 instruction.  */
limit:	.double 0.29

	.text
	.align 4
.globl _log2l
	.def	_log2l;	.scl	2;	.type	32;	.endef
_log2l:
	fldl	one
	fldt	4(%esp)		/* x : 1 */
	fxam
	fnstsw
	fld	%st		/* x : x : 1 */
	sahf
	jc	3f		/* in case x is NaN or ±Inf */
4:	fsub	%st(2), %st	/* x-1 : x : 1 */
	fld	%st		/* x-1 : x-1 : x : 1 */
	fabs			/* |x-1| : x-1 : x : 1 */
	fcompl	limit		/* x-1 : x : 1 */
	fnstsw			/* x-1 : x : 1 */
	andb	$0x45, %ah
	jz	2f
	fstp	%st(1)		/* x-1 : 1 */
	fyl2xp1			/* log(x) */
	ret

2:	fstp	%st(0)		/* x : 1 */
	fyl2x			/* log(x) */
	ret

3:	jp	4b		/* in case x is ±Inf */
	fstp	%st(1)
	fstp	%st(1)
	ret
