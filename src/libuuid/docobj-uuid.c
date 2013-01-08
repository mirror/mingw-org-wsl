/**
 * @file docobj-uuid.c
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

/* All IIDs defined in this file were extracted from
 * HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Interface\ */

#define INITGUID
#include <basetyps.h>
DEFINE_GUID(IID_IContinueCallback,0xb722bcca,0x4e68,0x101b,0xa2,0xbc,0,0xaa,0,0x40,0x47,0x70);
DEFINE_GUID(IID_IEnumOleDocumentViews,0xb722bcc8,0x4e68,0x101b,0xa2,0xbc,0,0xaa,0,0x40,0x47,0x70);
DEFINE_GUID(IID_IPrint,0xb722bcc9,0x4e68,0x101b,0xa2,0xbc,0,0xaa,0,0x40,0x47,0x70);
DEFINE_GUID(IID_IOleDocument,0xb722bcc5,0x4e68,0x101b,0xa2,0xbc,0,0xaa,0,0x40,0x47,0x70);
DEFINE_GUID(IID_IOleDocumentView,0xb722bcc6,0x4e68,0x101b,0xa2,0xbc,0,0xaa,0,0x40,0x47,0x70);
DEFINE_GUID(IID_IOleDocumentSite,0xb722bcc7,0x4e68,0x101b,0xa2,0xbc,0,0xaa,0,0x40,0x47,0x70);
DEFINE_GUID(IID_IOleCommandTarget,0xb722bccb,0x4e68,0x101b,0xa2,0xbc,0,0xaa,0,0x40,0x47,0x70);
