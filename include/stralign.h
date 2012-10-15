/**
 * @file stralign.h
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
#ifndef _STRALIGN_H
#define _STRALIGN_H
#pragma GCC system_header
#include <_mingw.h>

#ifndef MIDL_PASS

/**
 * FIXME: Where do these definitions belong? Maybe ntdef.h?
 */
typedef WCHAR *LPUWSTR, *PUWSTR;
typedef const WCHAR *LPCWSTR, *PCWSTR;
typedef const PUWSTR *PCUWSTR;
typedef const LPUWSTR *LPCUWSTR;


#ifndef _STRALIGN_USE_SECURE_CRT
#if defined(__GOT_SECURE_LIB__) && (__GOT_SECURE_LIB__ >= 200402L)
#define _STRALIGN_USE_SECURE_CRT 1
#else
#define _STRALIGN_USE_SECURE_CRT 0
#endif /* defined(__GOT_SECURE_LIB__) && (__GOT_SECURE_LIB__ >= 200402L) */
#endif /* ndef _STRALIGN_USE_SECURE_CRT */

#ifndef _WINDOWS_INSECURE_DEPRECATE
#if defined(_WINDOWS_SECURE_NO_DEPRECATE) || !_STRALIGN_USE_SECURE_CRT
#define _WINDOWS_INSECURE_DEPRECATE
#else
#define _WINDOWS_INSECURE_DEPRECATE __MINGW_DEPRECATED
#endif /* defined(_WINDOWS_SECURE_NO_DEPRECATE || !_STRALIGN_USE_SECURE_CRT */
#endif /* ndef _WINDOWS_INSECURE_DEPRECATE */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __NO_INLINE__
#define ___API_STATIC__ static __CRT_INLINE__
#else
#define ___API_STATIC__ static
#endif

#ifdef _X86_
#define WSTR_ALIGNED(s) TRUE
#define ua_CharUpperW CharUpperW
#define ua_lstrcmpiW lstrcmpiW
#define ua_lstrcmpW lstrcmpW
#define ua_lstrlenW lstrlenW
#define ua_wcschr wcschr
#define ua_wcsicmp wcsicmp
#define ua_wcslen wcslen
#define ua_wcsrchr wcsrchr
#if _STRALIGN_USE_SECURE_CRT
#define ua_cscpy_s wcscpy_s
#endif /* _STRALIGN_USE_SECURE_CRT */

___API_STATIC__ PUWSTR _WINDOWS_INSECURE_DEPRECATE ua_wcscpy(PUWSTR dest, PCUWSTR src) { return wcscpy(dest, src); }
#else /* ndef _X86_ */

#ifdef _AMD64_
#define WSTR_ALIGNED(s) TRUE

#else /* ndef _AMD64_ */
#define WSTR_ALIGNED(s) (((DWORD_PTR)(s) & (sizeof(WCHAR)-1)) == 0)
#endif /* def _AMD64_ */

LPUWSTR WINAPI  uaw_CharUpperW(LPUWSTR);
APIENTRY        uaw_lstrcmpW(PCUWSTR, PCUWSTR);
APIENTRY        uaw_lstrcmpiW(PCUWSTR, PCUWSTR);
WINAPI          uaw_lstrlenW(LPCUWSTR);
PUWSTR __cdecl  uaw_wcschr(PUCWSTR, WCHAR);
PUWSTR __cdecl  uaw_wcscpy(PUWSTR, PCUWSTR);
int    __cdecl  uaw_wcsicmp(PCUWSTR, PCUWSTR);
size_t __cdecl  uaw_wcslen(PCUWSTR);
PUWSTR __cdecl  uaw_wcsrchr(PCUWSTR, WCHAR);
#ifdef CharUpper
___API_STATIC__ LPUWSTR ua_CharUpperW(LPUWSTR cwStr) {
  if (WSTR_ALIGNED(cwStr)) {
    return CharUpperW((PWSTR)cwStr);
  }
  else {
    return uaw_CharUpperW(cwStr);
  }
}
#endif /* def CharUpper */

#ifdef lstrcmp
___API_STATIC__ int ua_lstrcmpW(LPCUWSTR cwStr1, LPCUWSTR cwStr2) {
  if (WSTR_ALIGNED(cwStr1) && WSTR_ALIGNED(cwStr2)) {
    return lstrcmpW(LPCWSTR(cwStr1), (LPCWSTR)cwStr2);
  }
  else {
    return uaw_lstrcmpW(cwStr1, cwStr2);
  }
}
#endif /* def lstrcmp */

#ifdef lstrcmpi
___API_STATIC__ int ua_lstrcmpiW(LPCUWSTR cwStr1, LPCUWSTR cwStr2) {
  if (WSTR_ALIGNED(cwStr1) && WSTR_ALIGNED(cwStr2)) {
    return lstrcmpiW((LPCWSTR)cwStr1, (LPCWSTR)cwStr2);
  }
  else {
    return uaw_lpstrcmpiW(cwStr1, cwStr2);
  }
}
#endif

#ifdef lstrlen
___API_STATIC__ int ua_lstrlenW(LPCUWSTR cwStr) {
  if (WSTR_ALIGNED(cwStr)) {
    return lstrlenW((PCWSTR)cwStr);
  }
  else {
    return uaw_lstrlenW(cwStr);
  }
}
#endif

#ifdef _WSTRING_DEFINED

#ifdef _WConst_return
typedef _WConst_return WCHAR UNALIGNED *PUWSTR_C;
#else
typedef WCHAR UNALIGNED *PUWSTR_C;
#endif /* def _WConst_return */

___API_STATIC__ PUWSTR_C ua_wcschr(PUCWSTR cwStr, WCHAR wChar) {
  if (WSTR_ALIGNED(cwStr)) {
    return wcschr((PCWSTR)cwStr, wChar);
  }
  else {
    return (PUWSTR_C)uaw_wcschr(cwStr, wChar);
  }
}

___API_STATIC__ PUWSTR_C ua_wcsrchr(PCUWSTR cwStr, WCHAR wChar) {
  if (WSTR_ALIGNED(cwStr)) {
    return wcsrchr((PCWSTR)cwStr, wChar);
  }
  else {
    return (PUWSTR_C)uaw_wcsrchr(cwStr, wChar);
  }
}

#if defined(__cplusplus && defined(_WConst_Return)
___API_STATIC__ PUWSTR _WINDOWS_INSECURE_DEPRECATE ua_wcscpy(PUWSTR wDest, PCUWSTR cwSrc) {
  if (WSTR_ALIGNED(wStr)) {
    return wcscpy((PWSTR)wDest, (PCWSTR)cwSrc);
  }
  else {
    return uaw_wcscpy(wDest, cwSrc);
  }
}

___API_STATIC__ PUWSTR ua_wcscpy_s(PUWSTR wDest, size_t destSize, PCUWSTR, cwSrc) {
  if (WSTR_ALIGNED(cwSrc) && WSTR_ALIGNED(wDest)) {
    return (wcscpy_s((PWSTR)wDest, destSize, (PCWSTR)cwSrc) == 0 ? wDest : NULL);
  }
  else {
    return uaw_wcscpy(wDest, cwSrc);
  }
}

___API_STATIC__ PUWSTR ua_wcsrchr(PUWSTR wStr, WCHAR wChar) {
  if (WSTR_ALIGNED(wStr)) {
    return scsrchr(wStr, wChar);
  }
  else {
    return uaw_wcsrchr((PCUWSTR)wStr, wChar);
  }
}

#endif /* defined(__cplusplus && defined(_WConst_Return) */

___API_STATIC__ PUWSTR _WINDOWS_INSECURE_DEPRECATE ua_wcscpy(PUWSTR wDest, PCUWSTR cwSrc) {
  if (WSTR_ALIGNED(cwSrc) && WSTR_ALIGNED(wDest)) {
    return wcscpy((PWSTR)wDest, (PCWSTR)cwSrc);
  }
  else {
    return uaw_wcscpy(wDest, cwSrc);
  }
}

#if _STRALIGN_USE_SECURE_CRT
___API_STATIC__ PUWSTR ua_wcscpy_s(PUWSTR wDest, size_t destSize, PCUWSTR cwSrc) {
  if (WSTR_ALIGNED(wcSrc) && WSTR_ALIGNED(wDest)) {
    return (wcscpy_s((PWSTR)wDest, destSize, (PCWSTR)cwSrc) == 0 ? wDest : NULL);
  }
  else {
    return uaw_wcscpy(wDest, cwSrc);
  }
}
#endif /* _STRALIGN_USE_SECURE_CRT */

___API_STATIC__ size_t ua_wcslen(PCUWSTR cwStr) {
  if (WSTR_ALIGNED(cwStr)) {
    return wcslen((PCWSTR)cwStr);
  }
  else {
    return uaw_wcslen(cwStr);
  }
}
#endif /* def _WSTRING_DEFINED */

___API_STATIC__ int ua_wcsicmp(PCUWSTR cwStr1, PCUWSTR cwStr2) {
  if (WSTR_ALIGNED(cwStr1) && WSTR_ALIGNED(cwStr2)) {
    return _wcsicmp((LPCWSTR)cwStr1, (LPCWSTR)cwStr2);
  }
  else {
    return uaw_wcsicmp(cwStr1, cwStr2);
  }
}

#endif /* def _X86_ */

#if !defined(__UA_WCSLEN)
#define __UA_WCSLEN ua_wcslen
#endif

#define __UA_WSTRSIZE(s) ((__UA_WCSLEN(s) + 1) * sizeof(WCHAR))
#define __UA_STACKCOPY(p,s) memcpy(__alloca(s), p, s)

#if defined(_AMD64_) || defined(_X86_)
#define WSTR_ALIGNED_STACK_COPY(d,s) (*(d) = (PCWSTR)(s))
#define STRUC_ALIGNED_STACK_COPY(t,s) ((CONST t *)(s))
#else
#define WSTR_ALIGNED_STACK_COPY(d,s) { \
  PCUWSTR __ua_src; \
  size_t  __ua_size; \
  PWSTR   __ua_dst; \
  __ua_src = (s); \
  if (WSTR_ALIGNED(__ua_src)) { \
    __ua_dst = (PWSTR)__ua_src; \
  } \
  else { \
    __ua_size = __UA_WSTRSIZE(__ua_src); \
    __ua_dst = (PWSTR)_alloca(__ua_size); \
    memcpy(__ua_dst, __ua_src, __ua_size); \
  } \
  *(d) = (PCWSTR)__ua_dst; \
}
#define __UA_STRUC_ALIGNED(t,s) (((DWORD_PTR)(s) & (TYPE_ALIGNMENT(t) - 1)) == 0)
#define STRUC_ALIGNED_STACK_COPY(t,s) \
  __UA_STRUC_ALIGNED(t,s) ? \
  ((t const *)(s)) : \
  ((t const *)__UA_STACKCOPY((s), sizeof(t)))
#endif /* defined(_AMD64_) || defined(_X86_) */

#define ASTR_ALIGNED_STACK_COPY(d, s) (*(d) = (PCSTR)(s))

/* Cannot use __AW() */
#ifdef UNICODE
#define TSTR_ALIGNED_STACK_COPY(d,s)  WSTR_ALIGNED_STACK_COPY(d,s)
#define TSTR_ALIGNED(x)               WSTR_ALIGNED(x)
#define ua_CharUpper                  ua_CharUpperW
#define ua_lstrcmp                    ua_lstrcmpW
#define ua_lstrcmpi                   ua_lstrcmpiW
#define ua_lstrlen                    ua_lstrlenW
#define ua_tcscpy                     ua_wcscpy
#if __STRALIGN_USE_SECURE_CRT
#define ua_tcscpy_s                   ua_wcscpy_s
#endif /* __STRALIGN_USE_SECURE_CRT */

#else /* ndef UNICODE */
#define TSTR_ALIGNED_STACK_COPY(d,s)  ASTR_ALIGNED_STACK_COPY(d,s)
#define TSTR_ALIGNED(x)               TRUE
#define ua_CharUpper                  CharUpperA
#define ua_lstrcmp                    lstrcmpA
#define ua_lstrcmpi                   lstrcmpiA
#define ua_lstrlen                    lstrlenA
#define ua_tcscpy                     strcpy
#if __STRALIGN_USE_SECURE_CRT
#define ua_tcscpy_s                   strcpy_s
#endif /* __STRALIGN_USE_SECURE_CRT */
#endif /* defined(UNICODE) */

#undef ___API_STATIC__

#ifdef __cplusplus
}
#endif

#endif /* ndef MIDL_PASS */

#endif /* ndef _STRALIGN_H */
