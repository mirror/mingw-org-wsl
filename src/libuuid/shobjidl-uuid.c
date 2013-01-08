/**
 * @file shobjidl-uuid.c
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

/* Generate GUIDs for Object IDL interfaces */

/* All CLSIDs defined in this file were extracted from
 * HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Interface\ */

/* All IIDs defined in this file were extracted from
 * HKEY_CLASSES_ROOT\Interface\ */

#define INITGUID
#include <basetyps.h>
DEFINE_GUID(IID_ITaskbarList3,0xea1afb91,0x9e28,0x4b86,0x90,0xe9,0x9e,0x9f,0x8a,0x5e,0xef,0xaf);
DEFINE_GUID(CLSID_ITaskbarList,0x56FDF342L,0xFD6D,0x11d0,0x95,0x8A,0x00,0x60,0x97,0xC9,0xA0,0x90);
