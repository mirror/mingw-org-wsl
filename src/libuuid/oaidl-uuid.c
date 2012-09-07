/**
 * @file oaidl-uuid.c
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

/* Generate GUIDs for OA IDL interfaces */

/* All IIDs defined in this file were extracted from
 * HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Interface\ */

#define INITGUID
#include <basetyps.h>
DEFINE_GUID(IID_IErrorInfo,0x1cf2b120,0x547d,0x101b,0x8e,0x65,0x8,0,0x2b,0x2b,0xd1,0x19);
DEFINE_GUID(IID_ICreateErrorInfo,0x22f03340,0x547d,0x101b,0x8e,0x65,0x8,0,0x2b,0x2b,0xd1,0x19);
DEFINE_GUID(IID_ISupportErrorInfo,0xdf0b3d60,0x548f,0x101b,0x8e,0x65,0x8,0,0x2b,0x2b,0xd1,0x19);
DEFINE_OLEGUID(IID_ICreateTypeInfo,0x20405,0,0);
DEFINE_OLEGUID(IID_ICreateTypeInfo2,0x2040e,0,0);
DEFINE_OLEGUID(IID_ICreateTypeLib,0x20406,0,0);
DEFINE_OLEGUID(IID_ICreateTypeLib2,0x2040F,0,0);
DEFINE_OLEGUID(IID_ITypeInfo,0x20401,0,0);
DEFINE_OLEGUID(IID_ITypeInfo2,0x20412,0,0);
DEFINE_OLEGUID(IID_ITypeLib,0x20402,0,0);
DEFINE_OLEGUID(IID_ITypeLib2,0x20411,0,0);
DEFINE_OLEGUID(IID_IEnumVARIANT,0x20404,0,0);
