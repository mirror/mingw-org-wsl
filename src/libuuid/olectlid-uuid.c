/**
 * @file olectlid-uuid.c
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

/* Generate GUIDs for OLECTLID interfaces */

/* All IIDs defined in this file were extracted from
 * HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Interface\ */

/* All CLSIDs defined in this file were extracted from
 * HKEY_CLASSES_ROOT\CLSID\ */

#define INITGUID
#include <basetyps.h>
DEFINE_OLEGUID(IID_IDispatch,0x20400,0,0);
DEFINE_OLEGUID(IID_IEnumUnknown,0x100,0,0);
DEFINE_OLEGUID(IID_IEnumString,0x101,0,0);
DEFINE_OLEGUID(IID_IEnumMoniker,0x102,0,0);
DEFINE_OLEGUID(IID_IEnumFORMATETC,0x103,0,0);
DEFINE_OLEGUID(IID_IEnumOLEVERB,0x104,0,0);
DEFINE_OLEGUID(IID_IEnumSTATDATA,0x105,0,0);
DEFINE_OLEGUID(IID_IEnumSTATSTG,0xd,0,0);
DEFINE_OLEGUID(IID_IOleLink,0x11d,0,0);
DEFINE_OLEGUID(IID_IDebug,0x123,0,0);
DEFINE_OLEGUID(IID_IDebugStream,0x124,0,0);
// Font Property Page CLSID
DEFINE_GUID(CLSID_CFontPropPage, 0x0be35200,0x8f91,0x11ce,0x9d,0xe3,0x00,0xaa,0x00,0x4b,0xb8,0x51);
// Color Property Page CLSID
DEFINE_GUID(CLSID_CColorPropPage,0xbe35201,0x8f91,0x11ce,0x9d,0xe3,0,0xaa,0,0x4b,0xb8,0x51);
// Picture Property Page CLSID
DEFINE_GUID(CLSID_CPicturePropPage,0xbe35202,0x8f91,0x11ce,0x9d,0xe3,0,0xaa,0,0x4b,0xb8,0x51);
// Standard Font CLSID
DEFINE_GUID(CLSID_StdFont,0xbe35203,0x8f91,0x11ce,0x9d,0xe3,0,0xaa,0,0x4b,0xb8,0x51);
// Standard Picture CLSID
DEFINE_GUID(CLSID_StdPicture,0xbe35204,0x8f91,0x11ce,0x9d,0xe3,0,0xaa,0,0x4b,0xb8,0x51);
// Picture (Metafile) CLSID
DEFINE_OLEGUID(CLSID_Picture_Metafile,0x315,0,0);
// Picture (Device Independent Bitmap) CLSID
DEFINE_OLEGUID(CLSID_Picture_Dib,0x316,0,0);
