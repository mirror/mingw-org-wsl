/**
 * @file winscard.h
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
#ifndef _WINSCARD_H
#define _WINSCARD_H
#pragma GCC system_header
#include <_mingw.h>

#include <wtypes.h>
#include <winioctl.h>
#include <winsmcrd.h>
#ifndef SCARD_S_SUCCESS
#include <scarderr.h>
#endif /* ndef SCARD_S_SUCCESS */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _LPCBYTE_DEFINED
#define _LPCBYTE_DEFINED
typedef const BYTE *LPCBYTE;
#endif /* ndef _LPCBYTE_DEFINED */

#ifndef _LPCVOID_DEFINED
#define _LPCVOID_DEFINED
typedef const VOID *LPCVOID;
#endif /* ndef _LPCVOID_DEFINED */

#ifndef WINSCARDAPI
#define WINSCARDAPI
#endif /* ndef WINSCARDAPI */

#ifndef WINSCARDDATA
#define WINSCARDDATA __MINGW_IMPORT
#endif /* ndef WINSCARDDATA */

#ifndef _M_CEE_PURE
WINSCARDDATA extern const SCAR_IO_REQUEST, g_rgSCardT0Pci, g_rgSCardT1Pci;
WINSCARDDATA extern const g_rgSCardRawPci;
#define SCARD_PCI_T0 (&g_rgSCardT0Pci)
#define SCARD_PCI_T1 (&g_rgSCardT1Pci)
#define SCARD_PCI_RAW (&g_rgSCardRawPci)
#endif /* ndef _M_CEE_PURE */

typedef ULONG_PTR SCARDCONTEXT;
typedef SCARDCONTEXT *PSCARDCONTEXT, *LPSCARDCONTEXT;
typedef ULONG_PTR SCARDHANDLE;
typedef SCARDHANDLE *PSCARDHANDLE, *LPSCARDHANDLE;

#define SCARD_AUTOALLOCATE (DWORD)(-1)
#define SCARD_SCOPE_USER     0
#define SCARD_SCOPE_TERMINAL 1
#define SCARD_SCOPE_SYSTEM   2

#define ___EAPI_LONG__ extern WINSCARDAPI LONG WINAPI
#define ___EAPI_HANDLE__ extern WINSCARDAPI HANDLE WINAPI
#define ___EAPI_VOID__ extern WINSCARDAPI void WINAPI

___EAPI_LONG__ SCardExtablishContext(DWORD, LPCVOID, LPCVOID, LPSCARDCONTEXT);
___EAPI_LONG__ SCardReleaseContext(SCARDCONTEXT);
___EAPI_LONG__ SCardIsValidContext(SCARDCONTEXT);

#define SCARD_ALL_READERS     TEXT("SCard$AllReaders\000")
#define SCARD_DEFAULT_READERS TEXT("SCard$DefaultReaders\000")
#define SCARD_LOCAL_READERS   TEXT("SCard$LocalReaders\000")
#define SCARD_SYSTEM_READERS  TEXT("SCard$SystemReaders\000")

#define SCARD_PROVIDER_PRIMARY  1
#define SCARD_PROVIDER_CSP      2
#define SCARD_PROVIDER_KSP      3

___EAPI_LONG__ SCardListReaderGroupsA(SCARDCONTEXT, LPSTR, LPDWORD);
___EAPI_LONG__ SCardListReaderGroupsW(SCARDCONTEXT, LPWSTR, LPDWORD);
#define SCardListReaderGroups __AW(SCardListReaderGroups)

___EAPI_LONG__ SCardListReadersA(SCARDCONTEXT, LPCBYTE, LPCGUID, DWORD, LPSTR);
___EAPI_LONG__ SCardListReadersW(SCARDCONTEXT, LPCBYTE, LPCGUID, DWORD, LPWSTR);
#define SCardListReaders __AW(SCardListReaders)

___EAPI_LONG__ SCardListCardsA(SCARDCONTEXT, LPCBYTE, LPCGUID, DWORD, LPSTR, LPDWORD);
___EAPI_LONG__ SCardListCardsW(SCARDCONTEXT, LPCBYTE, LPCGUID, DWORD, LPWSTR, LPDWORD);
#define SCardListCards __AW(SCardListCards)
#define SCardListCardTypes SCardListCards

___EAPI_LONG__ SCardListInterfacesA(SCARDCONTEXT, LPCSTR, LPGUID, LPDWORD);
___EAPI_LONG__ SCardListInterfacesW(SCARDCONTEXT, LPCWSTR, LPGUID, LPDWORD);
#define SCardListInterfaces __AW(SCArdListInterfaces)

___EAPI_LONG__ SCardGetProviderIdA(SCARDCONTEXT, LPCSTR, LPGUID);
___EAPI_LONG__ SCardGetProviderIdW(SCARDCONTEXT, LPCWSTR, LPGUID);
#define SCardGetProviderId __AW(SCardGetProviderId)

___EAPI_LONG__ SCardGetCardTypeProviderNameA(SCARDCONTEXT, LPCSTR, DWORD, LPSTR, LPDWORD);
___EAPI_LONG__ SCardGetCardTypeProviderNameW(SCARDCONTEXT, LPCWSTR, DWORD, LPWSTR, LPDWORD);
#define SCardGetCardTypeProviderName __AW(SCardGetCardTypeProviderName)

___EAPI_LONG__ SCardIntroduceReaderGroupA(SCARDCONTEXT, LPCSTR);
___EAPI_LONG__ SCardIntroduceReaderGroupW(SCARDCONTEXT, LPCWSTR);
#define SCardIntroduceReaderGroup __AW(SCardIntroduceReaderGroup)

___EAPI_LONG__ SCardForgetReaderGroupA(SCARDCONTEXT, LPCSTR);
___EAPI_LONG__ SCardForgetReaderGroupW(SCARDCONTEXT, LPCWSTR);
#define SCardForgetReaderGroup __AW(SCardForgetReaderGroup)

___EAPI_LONG__ SCardIntroduceReaderA(SCARDCONTEXT, LPCSTR, LPCSTR);
___EAPI_LONG__ SCardIntroduceReaderW(SCARDCONTEXT, LPCWSTR, LPCWSTR);
#define SCardIntroduceReader __AW(SCardIntroduceReader)

___EAPI_LONG__ SCardForgetReaderA(SCARDCONTEXT, LPCSTR);
___EAPI_LONG__ SCardForgetReaderW(SCARDCONTEXT, LPCWSTR);
#define SCardForgetReader __AW(SCardForgetReader)

___EAPI_LONG__ SCardAddReaderToGroupA(SCARDCONTEXT, LPCSTR, LPCSTR);
___EAPI_LONG__ SCardAddReaderToGroupW(SCARDCONTEXT, LPCWSTR, LPCWSTR);
#define SCardAddReaderToGroup __AW(SCardAddReaderToGroup)

___EAPI_LONG__ SCardREmoveReaderFromGroupA(SCARDCONTEXT, LPCSTR, LPCSTR);
___EAPI_LONG__ SCardREmoveReaderFromGroupW(SCARDCONTEXT, LPCWSTR, LPCWSTR);
#define SCardRemoveReaderFromGroup __AW(SCardRemoveReaderFromGroup)

___EAPI_LONG__ SCardIntroduceCardTypeA(SCARDCONTEXT, LPCSTR, LPCGUID, LPCGUID, DWORD, LPCBYTE, LPCBYTE, DWORD);
___EAPI_LONG__ SCardIntroduceCardTypeW(SCARDCONTEXT, LPCWSTR, LPCGUID, LPCGUID, DWORD, LPCBYTE, LPCBYTE, DWORD);
#define SCardIntroduceCardType __AW(SCardIntroduceCardType)
#define PCScardIntroduceCardType(a, b, c, d, e, f, g, h) \
 SCardIntroduceCardType(a, b, f, g, h, c, d, e)

___EAPI_LONG__ SCardSetCardTypeProviderNameA(SCARDCONTEXT, LPCSTR, DWORD, LPCSTR);
___EAPI_LONG__ SCardSetCardTypeProviderNameW(SCARDCONTEXT, LPCWSTR, DWORD, LPCWSTR);
#define SCardSetCardTypeProviderName __AW(SCardSetCardTypeProviderName)

___EAPI_LONG__ SCardForgetCardTypeA(SCARDCONTEXT, LPCSTR);
___EAPI_LONG__ SCardForgetCardTypeW(SCARDCONTEXT, LPCWSTR);
#define SCardForgetCardType __AW(SCardForgetCardType)

___EAPI_LONG__ SCardFreeMemory(SCARDCONTEXT, LPCVOID);

typedef struct {
  LPCSTR szReader;
  LPVOID pvUserData;
  DWORD  dwCurrentState;
  DWORD  dwEventState;
  DWORD  cbAtr;
  BYTE   rgbAtr[36];
} SCARD_READERSTATEA, *PSCARD_READERSTATEA, *LPSCARD_READERSTATEA;

typedef struct {
  LPCWSTR szReader;
  LPVOID pvUserData;
  DWORD  dwCurrentState;
  DWORD  dwEventState;
  DWORD  cbAtr;
  BYTE   rgbAtr[36];
} SCARD_READERSTATEW, *PSCARD_READERSTATEW, *LPSCARD_READERSTATEW;

typedef __AW(SCARD_READERSTATE) SCARD_READERSTATE;
typedef __AW(PSCARD_READERSTATE) PSCARD_READERSTATE;
typedef __AW(LPSCARD_READERSTATE) LPSCARD_READERSTATE;

#define SCARD_READERSTATE_A SCARD_READERSTATEA
#define SCARD_READERSTATE_W SCARD_READERSTATEW
#define PSCARD_READERSTATE_A PSCARD_READERSTATEA
#define PSCARD_READERSTATE_W PSCARD_READERSTATEW
#define LPSCARD_READERSTATE_A LPSCARD_READERSTATEA
#define LPSCARD_READERSTATE_W LPSCARD_READERSTATEW

#define SCARD_STATE_UNAWARE     0x00000000
#define SCARD_STATE_IGNORE      0x00000001
#define SCARD_STATE_CHANGED     0x00000002
#define SCARD_STATE_UNKNOWN     0x00000004
#define SCARD_STATE_UNAVAILABLE 0x00000008
#define SCARD_STATE_EMPTY       0x00000010
#define SCARD_STATE_PRESENT     0x00000020
#define SCARD_STATE_AIRMATCH    0x00000040
#define SCARD_STATE_EXCLUSIVE   0x00000080
#define SCARD_STATE_INUSE       0x00000100
#define SCARD_STATE_MUTE        0x00000200
#define SCARD_STATE_UNPOWERED   0x00000400

___EAPI_LONG__ SCardLocateCardsA(SCARDCONTEXT, LPCSTR, LPSCARD_READERSTATEA, DWORD);
___EAPI_LONG__ SCardLocateCardsW(SCARDCONTEXT, LPCWSTR, LPSCARD_READERSTATEW, DWORD);
#define SCardLocateCards __AW(SCardLocateCards)

___EAPI_LONG__ SCardGetStatusChangeA(SCARDCONTEXT, DWORD, LPSCARD_READERSTATEA, DWORD);
___EAPI_LONG__ SCardGetStatusChangeW(SCARDCONTEXT, DWORD, LPSCARD_READERSTATEW, DWORD);
#define SCardGetStatusChange __AW(SCardGetStatusChange)

___EAPI_LONG__ SCardCancel(SCARDCONTEXT);

#define SCARD_SHARE_EXCLUSIVE 1
#define SCARD_SHARE_SHARED    2
#define SCARD_SHARE_DIRECT    3

#define SCARD_LEAVE_CARD      0
#define SCARD_RESET_CARD      1
#define SCARD_UNPOWER_CARD    2
#define SCARD_EJECT_CARD      3

___EAPI_LONG__ SCardConnectA(SCARDCONTEXT, LPCSTR, DWORD, DWORD, LPSCARDHANDLE, LPDWORD);
___EAPI_LONG__ SCardConnectW(SCARDCONTEXT, LPCWSTR, DWORD, DWORD, LPSCARDHANDLE, LPDWORD);
#define SCardConnet __AW(SCardConnect)

___EAPI_LONG__ SCardReconnect(SCARDHANDLE, DWORD, DWORD, DWORD, LPDWORD);
___EAPI_LONG__ SCardDisconnect(SCARDHANDLE, DWORD);
___EAPI_LONG__ SCardBeginTransaction(SCARDHANDLE);
___EAPI_LONG__ SCardEndTransaction(SCARDHANDLE, DWORD);
___EAPI_LONG__ SCardCancelTransaction(SCARDHANDLE);
___EAPI_LONG__ SCardState(SCARDHANDLE, LPDWORD, LPDWORD, LPBYTE, LPDWORD);
___EAPI_LONG__ SCardStatusA(SCARDHANDLE, LPSTR, LPDWORD, LPDWORD, LPDWORD, LPBYTE, LPDWORD);
___EAPI_LONG__ SCardStatusW(SCARDHANDLE, LPWSTR, LPDWORD, LPDWORD, LPDWORD, LPBYTE, LPDWORD);
#define SCardStatus __AW(SCardStatus)
___EAPI_LONG__ SCardTransmit(SCARDHANDLE, LPCSCARD_IO_REQUEST, LPCBYTE, DWORD, LPSCARD_IO_REQUEST, LPBYTE, LPDWORD);
___EAPI_LONG__ SCardControl(SCARDHANDLE, DWORD, LPCVOID, DWORD, LPVOID, DWORD, LPDWORD);
___EAPI_LONG__ SCardGetAttrib(SCARDHANDLE, DWORD, LPBYTE, LPDWORD);
#define SCrdGetReaderCapabilities SCardGetAttrib
___EAPI_LONG__ SCardSetAttrib(SCARDHANDLE, DWORD, LPCBYTE, DWORD);
#define SCardSetReaderCapabilities SCardSetAttrib

#define SC_DLG_MINIMAL_UI   0x01
#define SC_DLG_NO_UI        0x02
#define SC_DLG_FORCE_UI     0x04

#define SCERR_NOCARDNAME    0x4000
#define SCERR_NOGUIDS       0x8000

typedef SCARDHANDLE (WINAPI *LPOCNCONNPROCA) (SCARDCONTEXT, LPSTR, LPSTR, PVOID);
typedef SCARDHANDLE (WINAPI *LPOCNCONNPROCW) (SCARDCONTEXT, LPWSTR, LPWSTR, PVOID);
#define LPOCNCONNPROC __AW(LPOCNCONNPROC)
typedef BOOL (WINAPI *LPOCNCHKPROC) (SCARDCONTEXT, SCARDHANDLE, PVOID);
typedef void (WINAPI *LPOCNDSCPROC) (SCARDCONTEXT, SCARDHANDLE, PVOID);

typedef struct {
  DWORD           dwStructSize;
  LPSTR           lpstrGroupNames;
  DWORD           nMaxGroupNames;
  LPCGUID         rgguidInterfaces;
  DWORD           cguidInterfaces;
  LPSTR           lpstrCardNames;
  DWORD           nMaxCardNames;
  LPOCNCHKPROC    lpfnCheck;
  LPOCNCONNPROCA  lpfnConnect;
  LPOCNDSCPROC    lpfnDisconnect;
  LPVOID          pvUserData;
  DWORD           dwShareMode;
  DWORD           dwPreferredProtocols;
} OPENCARD_SEARCH_CRITERIAA, *POPENCARD_SEARCH_CRITERIAA, *LPOPENCARD_SEARCH_CRITERIAA;

typedef struct {
  DWORD           dwStructSize;
  LPWSTR          lpstrGroupNames;
  DWORD           nMaxGroupNames;
  LPCGUID         rgguidInterfaces;
  DWORD           cguidInterfaces;
  LPWSTR          lpstrCardNames;
  DWORD           nMaxCardNames;
  LPOCNCHKPROC    lpfnCheck;
  LPOCNCONNPROCW  lpfnConnect;
  LPOCNDSCPROC    lpfnDisconnect;
  LPVOID          pvUserData;
  DWORD           dwShareMode;
  DWORD           dwPreferredProtocols;
} OPENCARD_SEARCH_CRITERIAW, *POPENCARD_SEARCH_CRITERIAW, *LPOPENCARD_SEARCH_CRITERIAW;

typedef __AW(OPENCARD_SEARCH_CRITERIA) OPENCARD_SEARCH_CRITERIA;
typedef __AW(POPENCARD_SEARCH_CRITERIA) POPENCARD_SEARCH_CRITERIA;
typedef __AW(LPOPENCARD_SEARCH_CRITERIA) LPOPENCARD_SEARCH_CRITERIA;

typedef struct {
  DWORD           dwStructSize;
  SCARDCONTEXT    hSCardContext;
  HWND            hwndOwner;
  DWORD           dwFlags;
  LPCSTR          lpstrTitle;
  LPCSTR          lpstrSearchDesc;
  HICON           hIcon;
  POPENCARD_SEARCH_CRITERIAA pOpenCardSearchCriteria;
  LPOCNCONNPROCA  lpfnConnect;
  LPVOID          pvUserData;
  DWORD           dwShareMode;
  DWORD           dwPreferredProtocols;
  LPSTR           lpstrRdr;
  DWORD           nMaxRdr;
  DWORD           dwActiveProtocol;
  SCARDHANDLE     hCardHandle;
} OPENCARDNAME_EXA, *POPENCARDNAME_EXA, *LPOPENCARDNAME_EXA;

typedef struct {
  DWORD           dwStructSize;
  SCARDCONTEXT    hSCardContext;
  HWND            hwndOwner;
  DWORD           dwFlags;
  LPCWSTR         lpstrTitle;
  LPCWSTR         lpstrSearchDesc;
  HICON           hIcon;
  POPENCARD_SEARCH_CRITERIAA pOpenCardSearchCriteria;
  LPOCNCONNPROCW  lpfnConnect;
  LPVOID          pvUserData;
  DWORD           dwShareMode;
  DWORD           dwPreferredProtocols;
  LPWSTR          lpstrRdr;
  DWORD           nMaxRdr;
  DWORD           dwActiveProtocol;
  SCARDHANDLE     hCardHandle;
} OPENCARDNAME_EXW, *POPENCARDNAME_EXW, *LPOPENCARDNAME_EXW;

typedef __AW(OPENCARDNAME_EX) OPENCARDNAME_EX;
typedef __AW(POPENCARDNAME_EX) POPENCARDNAME_EX;
typedef __AW(LPOPENCARDNAME_EX) LPOPENCARDNAME_EX;

#define OPENCARDNAMEA_EX OPENCARDNAME_EXA
#define OPENCARDNAMEW_EX OPENCARDNAME_EXW
#define POPENCARDNAMEA_EX POPENCARDNAME_EXA
#define POPENCARDNAMEW_EX POPENCARDNAME_EXW
#define LPOPENCARDNAMEA_EX LPOPENCARDNAME_EXA
#define LPOPENCARDNAMEW_EX LPOPENCARDNAME_EXW

___EAPI_LONG__ SCardUIDlgSelectCardA(LPOPENCARDNAME_EXA);
___EAPI_LONG__ SCardUIDlgSelectCardW(LPOPENCARDNAME_EXW);
#define SCardUIDlgSelectCard __AW(SCardUIDlgSelectCard)

typedef struct {
  DWORD           dwStructSize;
  HWND            hwndOwner;
  SCARDCONTEXT    hSCardContext;
  LPSTR           lpstrGroupNames;
  DWORD           nMaxGroupNames;
  LPSTR           lpstrCardNames;
  DWORD           nMaxCardNames;
  LPCGUID         rgguidInterfaces;
  DWORD           cguidInterfaces;
  LPSTR           lpstrRdr;
  DWORD           nMaxRdr;
  LPSTR           lpstrCard;
  DWORD           nMaxCard;
  LPCSTR          lpstrTitle;
  DWORD           dwFlags;
  LPVOID          pvUserData;
  DWORD           dwShareMode;
  DWORD           dwPreferredProtocols;
  DWORD           dwActiveProtocol;
  LPOCNCONNPROCA  lpfnConnect;
  LPOCNCHKPROC    lpfnCheck;
  LPOCNDSCPROC    lpfnDisconnect;
  SCARDHANDLE     hCardHandle;
} OPENCARDNAMEA, *POPENCARDNAMEA, *LPOPENCARDNAMEA;

typedef struct {
  DWORD           dwStructSize;
  HWND            hwndOwner;
  SCARDCONTEXT    hSCardContext;
  LPWSTR          lpstrGroupNames;
  DWORD           nMaxGroupNames;
  LPWSTR          lpstrCardNames;
  DWORD           nMaxCardNames;
  LPCGUID         rgguidInterfaces;
  DWORD           cguidInterfaces;
  LPWSTR          lpstrRdr;
  DWORD           nMaxRdr;
  LPWSTR          lpstrCard;
  DWORD           nMaxCard;
  LPCWSTR         lpstrTitle;
  DWORD           dwFlags;
  LPVOID          pvUserData;
  DWORD           dwShareMode;
  DWORD           dwPreferredProtocols;
  DWORD           dwActiveProtocol;
  LPOCNCONNPROCW  lpfnConnect;
  LPOCNCHKPROC    lpfnCheck;
  LPOCNDSCPROC    lpfnDisconnect;
  SCARDHANDLE     hCardHandle;
} OPENCARDNAMEW, *POPENCARDNAMEW, *LPOPENCARDNAMEW;

typedef __AW(OPENCARDNAME) OPENCARDNAME;
typedef __AW(POPENCARDNAME) POPENCARDNAME;
typedef __AW(LPOPENCARDNAME) LPOPENCARDNAME;

___EAPI_LONG__ GetOpenCardNameA(LPOPENCARDNAMEA);
___EAPI_LONG__ GetOpenCardNameW(LPOPENCARDNAMEW);
#define GetOpenCardName __AW(GetOpenCardName)
___EAPI_LONG__ SCardDlgExtendedError(void);

#define OPENCARDNAME_A OPENCARDNAMEA
#define OPENCARDNAME_W OPENCARDNAMEW
#define POPENCARDNAME_A POPENCARDNAMEA
#define POPENCARDNAME_W POPENCARDNAMEW
#define LPOPENCARDNAME_A LPOPENCARDNAMEA
#define LPOPENCARDNAME_W LPOPENCARDNAMEW

#if (_WIN32_WINNT >= _WIN32_WINNT_WINXP)
___EAPI_HANDLE__ SCardAccessStartedEvent(void);
___EAPI_VOID__ SCardReleaseStartedEvent(void);

typedef struct _SCARD_AIRMASK {
  DWORD cbAtr;
  BYTE  rgbAtr[36];
  BYTE  rgbMask[36];
} SCARD_AIRMASK, *PSCARD_AIRMASK, *LPSCARD_AIRMASK;

___EAPI_LONG__ SCardLocateCardsByATRA(SCARDCONTEXT, LPSCARD, DWORD, LPSCARD_READERSTATEA, DWORD);
___EAPI_LONG__ SCardLocateCardsByATRW(SCARDCONTEXT, LPSCARD, DWORD, LPSCARD_READERSTATEW, DWORD);
#define SCardLocateCardsByATR __AW(SCardLocateCardsByATR)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WINXP) */

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
___EAPI_LONG__ SCardGetTransmitCount(SCARDHANDLE, LPDWORD);
___EAPI_LONG__ SCardReadCacheA(SCARDCONTEXT, UUID, DWORD, LPSTR, PBYTE, DWORD);
___EAPI_LONG__ SCardReadCacheW(SCARDCONTEXT, UUID, DWORD, LPWSTR, PBYTE, DWORD);
#define SCardReadCache __AW(SCardReadCache)
___EAPI_LONG__ SCardWriteCacheA(SCARDCONTEXT, UUID, DWORD, LPSTR, PBYTE, DWORD);
___EAPI_LONG__ SCardWriteCacheW(SCARDCONTEXT, UUID, DWORD, LPWSTR, PBYTE, DWORD);
#define SCardWriteCache __AW(SCardWriteCache)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_VISTA) */

#undef ___EAPI_LONG__
#undef ___EAPI_HANDLE__
#undef ___EAPI_VOID__

#ifdef __cplusplus
}
#endif

#endif /*ndef _WINSCARD_H */
