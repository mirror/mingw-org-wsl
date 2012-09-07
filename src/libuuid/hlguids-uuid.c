/**
 * @file hlguids-uuid.c
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

/* Generate GUIDs for HyperLink GUID interfaces */

/* All IIDs defined in this file were extracted from
 * HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Interface\ */

/* All CLSIDs defined in this file were extracted from
 * HKEY_CLASSES_ROOT\CLSID\ */

#define INITGUID
#include <basetyps.h>
// StdHlink CLSID
DEFINE_GUID(CLSID_StdHlink,0x79eac9d0,0xbaf9,0x11ce,0x8c,0x82,0,0xaa,0,0x4b,0xa9,0xb);
// StdHlinkBrowseContext CLSID
DEFINE_GUID(CLSID_StdHlinkBrowseContext,0x79eac9d1,0xbaf9,0x11ce,0x8c,0x82,0,0xaa,0,0x4b,0xa9,0xb);
