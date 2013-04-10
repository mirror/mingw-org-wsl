/**
 * @file rpc.h
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
/**
 * Must include windows.h before defining the header guard to avoid circular
 * dependency issues.
 */
#ifndef RPC_NO_WINDOWS_H
#include <windows.h>
#endif /* RPC_NO_WINDOWS_H */

#ifndef _RPC_H
#define _RPC_H
#pragma GCC system_header
#include <_mingw.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <basetsd.h>

#if defined(_WIN64)
# define __RPC_WIN64__
#else
# define __RPC_WIN32__
#endif

#if defined(__RPC_WIN64__)
__PSHPACK8
#endif

#ifndef __MIDL_USER_DEFINED
#define midl_user_allocate MIDL_user_allocate
#define midl_user_free     MIDL_user_free
#define __MIDL_USER_DEFINED
#endif

typedef void *I_RPC_HANDLE;
typedef long RPC_STATUS;

#define RPC_UNICODE_SUPPORTED

#define __RPC_FAR
#define __RPC_API  __stdcall
#define __RPC_USER __stdcall
#define __RPC_STUB __stdcall
#define RPC_ENTRY  __stdcall

#ifndef DECLSPEC_IMPORT
#ifndef MIDL_PASS
#define DECLSPEC_IMPORT __declspec(dllimport)
#else
#define DECLSPEC_IMPORT
#endif
#endif

#ifndef DECLSPEC_EXPORT
#ifndef MIDL_PASS
#define DECLSPEC_EXPORT __declspec(dllexport)
#else
#define DECLSPEC_EXPORT
#endif
#endif

#ifdef _RPCRT4_
#define RPCRTAPI
#else
#define RPCRTAPI DECLSPEC_IMPORT
#endif

#include <rpcdce.h>
#include <rpcnsi.h>
#include <rpcnterr.h>
#include <excpt.h>
#include <winerror.h>

/* FIXME: These should be defined regardless */
/* SEH is not supported */
#if 0
#include <excpt.h>
#define RpcTryExcept __try {
#define RpcExcept(x) } __except (x) {
#define RpcEndExcept }
#define RpcTryFinally __try {
#define RpcFinally } __finally {
#define RpcEndFinally }
#define RpcExceptionCode() GetExceptionCode()
#define RpcAbnormalTermination() AbnormalTermination()
#endif /* 0 */

#if !defined(RPC_NO_WINDOWS_H) || defined(RPC_NEED_RPCASYNC_H)
#include <rpcasync.h>
#endif

#if defined(__RPC_WIN64__)
__POPPACK8
#endif

#ifdef __cplusplus
}
#endif

#endif
