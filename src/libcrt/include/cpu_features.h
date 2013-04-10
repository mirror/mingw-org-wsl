/**
 * @file cpu_features.h
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
#ifndef _CPU_FEATURES_H
#define _CPU_FEATURES_H

#include <stdbool.h>

#define  _CRT_CMPXCHG8B		0x0001
#define  _CRT_CMOV		0x0002
#define  _CRT_MMX		0x0004
#define  _CRT_FXSR		0x0008
#define  _CRT_SSE		0x0010
#define  _CRT_SSE2		0x0020
#define  _CRT_SSE3		0x0040
#define  _CRT_CMPXCHG16B	0x0080
#define  _CRT_3DNOW		0x0100
#define  _CRT_3DNOWP		0x0200

extern unsigned int __cpu_features;

/* Currently we use this in fpenv  functions */
#define __HAS_SSE  __cpu_features & _CRT_SSE


#endif
