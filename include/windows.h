/**
 * @file windows.h
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
/* Written by Anders Norlander <anorland@hem2.passagen.se> */
#ifndef _WINDOWS_H
#define _WINDOWS_H
#pragma GCC system_header
#include <_mingw.h>

#ifdef RC_INVOKED && !defined(NOWINRES)
/* winresrc.h includes the necessary headers */
#include <winresrc.h>
#else
#ifdef RC_INVOKED
#define NOATOM
#define NOCOMM
#define NOCRYPT
#define NOGDI
#define NOGDICAPMASKS
#define NOKANJI
#define NOMCX
#define NOMETAFILE
#define NOMINMAX
#define NOMSG
#define NOOPENFILE
#define NOWH
#define NORASTEROPS
#define NOSCROLL
#define NOSOUND
#define NOSYSMETRICS
#define NOTEXTMETRIC
#endif /* def RC_INVOKED */
#endif /* def RC_INVOKED && !defined(NOWINRES) */

#ifndef RC_INVOKED
#include <excpt.h>
#include <stdarg.h>
#endif /* ndef RC_INVOKED */

#include <windef.h>
#include <winbase.h>
#include <wingdi.h>
#include <winuser.h>
#include <winnls.h>
#include <wincon.h>
#include <winver.h>
#include <winreg.h>
#include <winnetwk.h>

#ifndef WIN32_LEAN_AND_MEAN
#include <cderr.h>
#include <dde.h>
#include <ddeml.h>
#include <dlgs.h>
#include <lzexpand.h>
#include <mmsystem.h>
#include <nb30.h>
#include <rpc.h>
#include <basetyps.h>
#include <shellapi.h>
#include <winperf.h>
#include <winsock.h>

#ifndef NOCRYPT
#include <wincrypt.h>
#include <winefs.h>
#include <winscard.h>
#endif /* ndef NOCRYPT */

#ifndef NOGDI
#include <winspool.h>

/* In older versions we disallowed COM declarations in __OBJC__
   because of conflicts with @interface directive.  Define _OBJC_NO_COM
   to keep this behaviour.  */ 
#ifndef _OBJC_NO_COM

#ifdef INC_OLE1
#include <ole.h>
#else /* ndef INC_OLE1 */

#include <ole2.h>
#endif /* def INC_OLE1 */

#endif /* ndef _OBJC_NO_COM */

#include <commdlg.h>
#endif /* ndef NOGDI */

#endif /* WIN32_LEAN_AND_MEAN */

#include <stralign.h>

#ifdef INC_OLE2
#include <ole2.h>
#endif /* def INC_OLE2 */

#ifndef NOSERVICE
#include <winsvc.h>
#endif /* ndef NOSERVICE */

#ifndef NOMCX
#include <mcx.h>
#endif /* ndef NOMCX */

#ifndef NOIME
#include <imm.h>
#endif /* ndef NOIME */

#ifdef __OBJC__
/* FIXME: Not undefining BOOL here causes all BOOLs to be WINBOOL (int),
   but undefining it causes trouble as well if a file is included after
   windows.h
*/
#undef BOOL
#endif

#endif
