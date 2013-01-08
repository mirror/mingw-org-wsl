/**
 * @file test.c
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
/* Perform simple test of headers to avoid typos and such */
#define __USE_W32_SOCKETS
#include <w32api.h>
#include <windows.h>

#ifdef __OBJC__
#define BOOL WINBOOL
#endif
#include <windowsx.h>
#include <commctrl.h>
#include <largeint.h>
#include <mmsystem.h>
#include <mciavi.h>
#include <mcx.h>
#include <sql.h>
#include <sqlext.h>
#include <imm.h>
#include <lm.h>
#include <zmouse.h>
#include <scrnsave.h>
#include <cpl.h>
#include <cplext.h>
#include <wincrypt.h>
#include <pbt.h>
#include <wininet.h>
#include <regstr.h>
#include <custcntl.h>
#include <mapi.h>

#include <dbt.h>
#include <gdiplus.h>
#include <httpext.h>
#include <icm.h>
#include <imagehlp.h>
#include <ipexport.h>
#include <iphlpapi.h>
#include <ipifcons.h>
#include <iprtrmib.h>
#include <iptypes.h>
#include <isguids.h>
#include <lmbrowsr.h>
#include <mswsock.h>
#include <nddeapi.h>
#include <ntdef.h>
#include <ntsecapi.h>
#include <odbcinst.h>
#include <powrprof.h>
#include <psapi.h>
#include <ras.h>
#include <rasdlg.h>
#include <raserror.h>
#include <rassapi.h>
#include <richedit.h>
#include <rpcdce2.h>
#include <subauth.h>
#include <tlhelp32.h>
#include <userenv.h>
#include <winioctl.h>
#include <winresrc.h>
#include <winsock.h>
#ifdef _WINSOCK2_H
#include <ws2tcpip.h>
#include <ws2spi.h>
#include <wsahelp.h>
#endif
#include <wsipx.h>
#include <wsnetbs.h>
#include <svcguid.h>
#include <setupapi.h>
#include <aclapi.h>
#include <security.h>
#include <secext.h>
#include <schnlsp.h>
#include <ntldap.h>
#include <winber.h>
#include <winldap.h>
#include <shlwapi.h>
#include <snmp.h>
#include <winsnmp.h>
#include <mgmtapi.h>
#include <vfw.h>
#include <uxtheme.h>
#include <tmschema.h>
#include <dhcpcsdk.h>
#include <errorrep.h>
#include <windns.h>
#include <usp10.h>

#ifndef _OBJC_NO_COM
#include <initguid.h>
#include <ole2.h>
#include <comcat.h>
#include <shlobj.h>
#include <intshcut.h>
#include <ocidl.h>
#include <ole2ver.h>
#include <oleacc.h>
#include <winable.h>
#include <olectl.h>
#include <oledlg.h>
#include <docobj.h>
#include <idispids.h>
#include <rapi.h>
#include <richole.h>
#include <rpcproxy.h>
#include <exdisp.h>
#include <mshtml.h>
#include <servprov.h>
#include <aclui.h>
#include <mlang.h>
#endif

#ifdef __OBJC__
#undef BOOL

@interface class1 {
   int e;
}
@end

@implementation class1
@end
#endif

int main()
{
  return 0;
}
