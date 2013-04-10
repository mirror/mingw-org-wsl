/**
 * @file oleidl-uuid.c
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

/* Generate GUIDs for OLE IDL interfaces */

/* All IIDs defined in this file were extracted from
 * HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Interface\ */

#define INITGUID
#include <basetyps.h>
DEFINE_OLEGUID(IID_IOleCache,0x11e,0,0);
DEFINE_OLEGUID(IID_IOleCache2,0x128,0,0);
DEFINE_OLEGUID(IID_IOleCacheControl,0x129,0,0);
DEFINE_OLEGUID(IID_IViewObject,0x10d,0,0);
DEFINE_OLEGUID(IID_IViewObject2,0x127,0,0);
DEFINE_OLEGUID(IID_IDropSource,0x121,0,0);
DEFINE_OLEGUID(IID_IDropTarget,0x122,0,0);
DEFINE_OLEGUID(IID_IOleAdviseHolder,0x111,0,0);
DEFINE_OLEGUID(IID_IOleInPlaceUIWindow,0x115,0,0);
DEFINE_OLEGUID(IID_IOleInPlaceObject,0x113,0,0);
DEFINE_OLEGUID(IID_IOleInPlaceActiveObject,0x117,0,0);
DEFINE_OLEGUID(IID_IOleInPlaceFrame,0x116,0,0);
DEFINE_OLEGUID(IID_IOleInPlaceSite,0x119,0,0);
DEFINE_OLEGUID(IID_IOleContainer,0x11b,0,0);
DEFINE_OLEGUID(IID_IOleItemContainer,0x11c,0,0);
DEFINE_OLEGUID(IID_IOleClientSite,0x118,0,0);
DEFINE_OLEGUID(IID_IOleObject,0x112,0,0);
DEFINE_OLEGUID(IID_IOleWindow,0x114,0,0);
DEFINE_OLEGUID(IID_IParseDisplayName,0x11a,0,0);
