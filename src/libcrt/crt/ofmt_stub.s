/**
 * @file ofmt_stub.s
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
 * A trivial stub, to replace the _get_output_format() function.
 *
 * _pformat() requires this function, which is provided by MSVCRT runtimes
 * from msvcr80.dll onwards; add this stub to the import libraries for earlier
 * versions of MSVCRT, (those which do not already advertise availability of
 * any exported _get_output_format() function); this will permit _pformat()
 * to transparently interoperate with all supported versions of MSVCRT.
 */
	.text
	.p2align 1,,4

.globl __get_output_format
	.def	__get_output_format;	.scl	2;	.type	32;	.endef

__get_output_format:
/*
 * int _get_output_format( void );
 *
 * Implementation is trivial: we immediately return zero, thus matching the
 * default behaviour of Microsoft's own implementation, in the absence of any
 * preceding call to _set_output_format(); (if we are using this stub, then
 * that entire API is unsupported, so no such prior call is possible).
 */
	xorl	%eax, %eax
	ret

/* $RCSfile: ofmt_stub.s,v $Revision: 1.1 $: end of file */
