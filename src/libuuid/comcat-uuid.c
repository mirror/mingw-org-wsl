/**
 * @file comcat-uuid.c
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
/* comcat-uuid.c */
/* Generate GUIDs for COMCAT interfaces */

/* All IIDs defined in this file were extracted from
 * HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Interface\ */

/* All CLSIDs defined in this file were extracted from
 * HKEY_CLASSES_ROOT\CLSID\ */

#define INITGUID
#include <basetyps.h>
DEFINE_OLEGUID(IID_IEnumGUID,0x2e000,0,0);
DEFINE_OLEGUID(IID_ICatInformation,0x2e013,0,0);
DEFINE_OLEGUID(IID_ICatRegister,0x2e012,0,0);
DEFINE_OLEGUID(IID_IEnumCATEGORYINFO,0x2e011,0,0);
// Component Catagories Manager CLSID
DEFINE_OLEGUID(CLSID_StdComponentCategoriesMgr,0x2e005,0,0);
// Implemented Categories under Outlook Express MsgTable Object CLSID
DEFINE_GUID(CATID_Insertable,0x40fc6ed3,0x2438,0x11cf,0xa3,0xdb,0x8,0,0x36,0xf1,0x25,0x2);
DEFINE_GUID(CATID_Control,0x40fc6ed4,0x2438,0x11cf,0xa3,0xdb,0x8,0,0x36,0xf1,0x25,0x2);
// Implemented Categories under Microsoft PowerPoint Slide CLSID
DEFINE_GUID(CATID_DocObject,0x40fc6ed8,0x2438,0x11cf,0xa3,0xdb,0x8,0,0x36,0xf1,0x25,0x2);
// Implemented Categories under Microsoft Toolbar Control CLSID
DEFINE_GUID(CATID_Programmable,0x40fc6ed5,0x2438,0x11cf,0xa3,0xdb,0x8,0,0x36,0xf1,0x25,0x2);
// Implemented Categories under SSCommand Control CLSID
DEFINE_GUID(CATID_Printable,0x40fc6ed9,0x2438,0x11cf,0xa3,0xdb,0x8,0,0x36,0xf1,0x25,0x2);
DEFINE_GUID(CATID_PersistsToStorage,0xde86a52,0x2baa,0x11cf,0xa2,0x29,0,0xaa,0,0x3d,0x73,0x52);
DEFINE_GUID(CATID_PersistsToPropertyBag,0xde86a57,0x2baa,0x11cf,0xa2,0x29,0,0xaa,0,0x3d,0x73,0x52);
DEFINE_GUID(CATID_PersistsToStream,0xde86a54,0x2baa,0x11cf,0xa2,0x29,0,0xaa,0,0x3d,0x73,0x52);
DEFINE_GUID(CATID_PersistsToStreamInit,0xde86a53,0x2baa,0x11cf,0xa2,0x29,0,0xaa,0,0x3d,0x73,0x52);
