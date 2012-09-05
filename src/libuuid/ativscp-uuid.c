/**
 * @file ativscp-uuid.c
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
/* ativscp-uuid.c */
/* Generate GUIDs for ActiveScript interfaces */

/* All IIDs defined in this file were extracted from
 * HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Interface\ */

/* All CLSIDs defined in this file were extracted from
 * HKEY_CLASSES_ROOT\CLSID\ */

#define INITGUID
#include <basetyps.h>
DEFINE_GUID(IID_IActiveScript,0xbb1a2ae1,0xa4f9,0x11cf,0x8f,0x20,0,0x80,0x5f,0x2c,0xd0,0x64);
DEFINE_GUID(IID_IActiveScriptError,0xeae1ba61,0xa4ed,0x11cf,0x8f,0x20,0,0x80,0x5f,0x2c,0xd0,0x64);
DEFINE_GUID(IID_IActiveScriptParse,0xbb1a2ae2,0xa4f9,0x11cf,0x8f,0x20,0,0x80,0x5f,0x2c,0xd0,0x64);
DEFINE_GUID(IID_IActiveScriptSite,0xdb01a1e3,0xa42b,0x11cf,0x8f,0x20,0,0x80,0x5f,0x2c,0xd0,0x64);
DEFINE_GUID(IID_IActiveScriptSiteWindow,0xd10f6761,0x83e9,0x11cf,0x8f,0x20,0,0x80,0x5f,0x2c,0xd0,0x64);
