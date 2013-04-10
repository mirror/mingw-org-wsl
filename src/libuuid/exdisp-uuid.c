/**
 * @file exdisp-uuid.c
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

/* All CLSIDs defined in this file were extracted from
 * HKEY_CLASSES_ROOT\CLSID\ */

#define INITGUID
#include <basetyps.h>
// Microsoft Web Browser CLSID
DEFINE_GUID(CLSID_WebBrowser,0x8856f961,0x340a,0x11d0,0xa9,0x6b,0x0,0xc0,0x4f,0xd7,0x5,0xa2);
DEFINE_GUID(DIID_DWebBrowserEvents,0xeab22ac2,0x30c1,0x11cf,0xa7,0xeb,0x0,0x0,0xc0,0x5b,0xae,0x0b);
DEFINE_GUID(DIID_DWebBrowserEvents2,0x34a715a0,0x6587,0x11d0,0x92,0x4a,0x0,0x20,0xaf,0xc7,0xac,0x4d);
DEFINE_GUID(IID_IWebBrowser,0xeab22ac1,0x30c1,0x11cf,0xa7,0xeb,0x0,0x0,0xc0,0x5b,0xae,0x0b);
DEFINE_GUID(IID_IWebBrowser2,0xd30c1661,0xcdaf,0x11d0,0x8a,0x3e,0x0,0xc0,0x4f,0xc9,0xe2,0x6e);
DEFINE_GUID(IID_IWebBrowserApp,0x2df05,0x0,0x0,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0x46);
