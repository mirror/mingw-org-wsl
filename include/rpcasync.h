/**
 * @file rpcasync.h
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
#ifndef _RPCASYNC_H
#define _RPCASYNC_H
#pragma GCC system_header
#include <_mingw.h>
#include <sdkddkver.h>

#if defined(__RPC_WIN64__)
__PSHPACK8
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <windef.h>

#define ___RPC_ENTRY__ RPCRTAPI RPC_STATUS RPC_ENTRY
#define RPC_ASYNC_VERSION_1_0 sizeof(RPC_ASYNC_STATE)

typedef enum _RPC_NOTIFICATION_TYPES {
  RpcNotificationTypeNone,
  RpcNotificationTypeEvent,
  RpcNotificationTypeApc,
  RpcNotificationTypeIoc,
  RpcNotificationTypeHwnd,
  RpcNotificationTypeCallback
} RPC_NOTIFICATION_TYPES;

#if !(_WIN32_WINNT >= _WIN32_WINNT_VISTA)
typedef enum _RPC_ASYNC_EVENT {
  RpcCallComplete,
  RpcSendComplete,
  RpcReceiveComplete,
  RpcClientDisconnect
} RPC_ASYNC_EVENT;

#define RPC_CALL_ATTRIBUTES_VERSION 1
#define RPC_QUERY_SERVER_PRINCIPAL_NAME 2
#define RPC_QUERY_CLIENT_PRINCIPAL_NAME 4
#endif

struct _RPC_ASYNC_STATE;

typedef void RPC_ENTRY RPCNOTIFICATION_ROUTINE (
  struct _RPC_ASYNC_STATE *pAsync,
  void *Context,
  RPC_ASYNC_EVENT Event
);
typedef RPCNOTIFICATION_ROUTINE *PFN_RPCNOTIFICATION_ROUTINE;

typedef union _RPC_ASYNC_NOTIFICATION_INFO {
  struct {
    PFN_RPCNOTIFICATION_ROUTINE NotificationRoutine;
    HANDLE hThread;
  } APC;

#if !defined(RPC_NO_WINDOWS_H) || defined (_WINBASE_H)
  struct {
    HANDLE hIOPort;
    DWORD dwNumberOfBytesTransferred;
    DWORD_PTR dwCompletionKey;
    LPOVERLAPPED lpOverlapped;
  } IOC;
#endif

#if !defined(RPC_NO_WINDOWS_H)
  struct {
    HWND hWnd;
    UINT Msg;
  } HWND;
#endif

  HANDLE hEvent;

  PFN_RPCNOTIFICATION_ROUTINE NotificationRoutine;
} RPC_ASYNC_NOTIFICATION_INFO, *PRPC_ASYNC_NOTIFICATION_INFO;

typedef struct _RPC_ASYNC_STATE {
  unsigned int   Size;
  unsigned long  Signature;
  long           Lock;
  unsigned long  Flags;
  void          *StubInfo;
  void          *UserInfo;
  void          *RuntimeInfo;
} RPC_ASYNC_STATE, *PRPC_ASYNC_STATE;

#define RPC_C_NOTIFY_ON_SEND_COMPLETE 0x1
#define RPC_C_INFINITE_TIMEOUT INFINITE
#define RpcAsyncGetCallHandle(pAsync) (((PRPC_ASYNC_STATE) pAsync)->RuntimeInfo)

___RPC_ENTRY__ RpcAsyncInitializeHandle(PRPC_ASYNC_STATE, unsigned int);
___RPC_ENTRY__ RpcAsyncGetCallStatus(PRPC_ASYNC_STATE);
___RPC_ENTRY__ RpcAsyncCompleteCall(PRPC_ASYNC_STATE, void *);
___RPC_ENTRY__ RpcAsyncAbortCall(PRPC_ASYNC_STATE, unsigned long);
___RPC_ENTRY__ RpcAsyncCancelCall(PRPC_ASYNC_STATE, BOOL);

#if (_WIN32_WINNT >= _WIN32_WINNT_WINXP)

#if !defined(RPC_NO_WINDOWS_H) || defined(_WINBASE_H)
typedef enum tagExtendedErrorParamTypes {
  eeptAnsiString = 1,
  eeptUnicodeString,
  eeptLongVal,
  eeptShortVal,
  eeptPointerVal,
  eeptNone,
  eeptBinary
} ExtendedErrorParamTypes;

#define MaxNumberOfEEInfoParams 4
#define RPC_EEINFO_VERSION 1

typedef struct tagBinaryParam {
  void *Buffer;
  short Size;
} BinaryParam;

typedef struct tagRPC_EE_INFO_PARAM {
  ExtendedErrorParamTypes;
  union {
    LPSTR AnsiString;
    LPWSTR UnicodeString;
    long LVal;
    short SVal;
    ULONGLONG PVal;
    BinaryParam BVal;
  } u;
} RPC_EE_INFO_PARAM;

#define EEInfoPreviousRecordsMission  1
#define EEInfoNextRecordsMissing      2
#define EEInfoUseFileTime             4
#define EEInfoGCCOM                  11

typedef struct tagRPC_EXTENDED_ERROR_INFO
  ULONG Version;
  LPWSTR ComputerName;
  ULONG ProcessID;
  union {
    SYSTEMTIME SystemTime;
    FILETIME FileTime;
  } u;
  ULONG GeneratingComponent;
  ULONG Status;
  USHORT DetectionLocation;
  USHORT Flags;
  int NumberOfParameters;
  RPC_EE_INFO_PARAM Parameters[MaxNumberOfEEInfoParams];
} RPC_EXTENDED_ERROR_INFO;

typedef struct tagRPC_ERROR_ENUM_HANDLE {
  ULONG Signature;
  void *CurrentPos;
  void *Head;
} RPC_ERROR_ENUM_HANDLE;

___RPC_ENTRY__ RpcErrorStartEnumeration(RPC_ERROR_ENUM_HANDLE *);
___RPC_ENTRY__ RpcErrorGetNextRecord(RPC_ERROR_ENUM_HANDLE *, BOOL, RPC_EXTENDED_ERROR_INFO *);
___RPC_ENTRY__ RpcErrorEndEnumeration(RPC_ERROR_ENUM_HANDLE *);
___RPC_ENTRY__ RpcErrorResetEnumeration(RPC_ERROR_ENUM_HANDLE *);
___RPC_ENTRY__ RpcErrorGetNumberOfRecords(RPC_ERROR_ENUM_HANDLE *, int *);
___RPC_ENTRY__ RpcErrorSaveErrorInfo(RPC_ERROR_ENUM_HANDLE *, PVOID *, size_t *);
___RPC_ENTRY__ RpcErrorLoadErrorInfo(PVOID, size_t, RPC_ERROR_ENUM_HANDLE *);
___RPC_ENTRY__ RpcErrorAddRecord(RPC_EXTENDED_ERROR_INFO *);
___RPC_ENTRY__ RpcErrorClearInformation(void);

#endif /* !defined(RPC_NO_WINDOWS_H) || defined(_WINBASE_H) */

___RPC_ENTRY__ RpcAsyncCleanupThread(DWORD);
___RPC_ENTRY__ RpcGetAuthorizationContextForClient(RPC_BINDING_HANDLE, PVOID, PLARGE_INTEGER, LUID, DWORD, PVOID, PVOID);
___RPC_ENTRY__ RpcFreeAuthorizationContext(PVOID *);
___RPC_ENTRY__ RpcSsContextLockExclusive(RPC_BINDING_HANDLE, PVOID);
___RPC_ENTRY__ RpcSsContextLockShared(RPC_BINDING_HANDLE, PVOID);

typedef struct tagRPC_CALL_ATTRIBUTES_V1_W {
  unsigned int Version;
  unsigned long Flags;
  unsigned long ServerPrincipalNameBufferLength;
  unsigned short *ServerPrincipalName;
  unsigned long ClientPrincipalNameBufferLength;
  unsigned short *ClientPrincipalName;
  unsigned long AuthenticationLevel;
  unsigned long AuthenticationService;
  BOOL NullSession;
} RPC_CALL_ATTRIBUTES_V1_W;

typedef struct tagRPC_CALL_ATTRIBUTES_V1_A {
  unsigned int Version;
  unsigned long Flags;
  unsigned long ServerPrincipalNameBufferLength;
  unsigned char *ServerPrincipalName;
  unsigned long ClientPrincipalNameBufferLength;
  unsigned char *ClientPrincipalName;
  unsigned long AuthenticationLevel;
  unsigned long AuthenticationService;
  BOOL NullSession;
} RPC_CALL_ATTRIBUTES_V1_A;

___RPC_ENTRY__ RpcServerInqCallAttributesW(RPC_BINDING_HANDLE, void *);
___RPC_ENTRY__ RpcServerInqCallAttributesA(RPC_BINDING_HANDLE, void *);
#define RPC_CALL_ATTRIBUTES_V1 __AW(RPC_CALL_ATTRIBUTES_V1_)
#define RpcServerInqCallAttributes __AW(RpcServerInqCallAttributes)

#if !(_WIN32_WINNT >= _WIN32_WINNT_VISTA)
typedef RPC_CALL_ATTRIBUTES_V1 RPC_CALL_ATTRIBUTES;
#endif

#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WINXP) */

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
typedef enum _RPC_ASYNC_EVENT {
  RpcCallComplete,
  RpcSendComplete,
  RpcReceiveComplete,
  RpcClientDisconnect,
  RpcClientCancel
} RPC_ASYNC_EVENT;

#define RPC_CALL_STATUS_CANCELLED    0x01
#define RPC_CALL_STATUS_DISCONNECTED 0x02

typedef enum tagRpcCallType {
  rctInvalid = 0,
  rctNormal,
  rctTraining,
  rctGuaranteed
} RpcCallType;

typedef enum tagRpcCallClientLocality {
  rcclInvalid = 0,
  rcclLocal,
  rcclRemote,
  rcclClientUnknownLocality
} RpcCallClientLocality;

typedef struct tagRPC_CALL_ATTRIBUTES_V2_W {
  unsigned int Version;
  unsigned long Flags;
  unsigned long ServerPrincipalNameBufferLength;
  unsigned short *ServerPrincipalName;
  unsigned long ClientPrincipalNameBufferLength;
  unsigned short *ClientPrincipalName;
  unsigned long AuthenticationLevel;
  unsigned long AuthenticationService;
  BOOL NullSession;
  BOOL KernelModeCaller;
  unsigned long ProtocolSequence;
  RpcCallClientLocality IsClientLocal;
  HANDLE ClientPID; 
  unsigned long CallStatus;
  RpcCallType CallType;
  RPC_CALL_LOCAL_ADDRESS_V1 *CallLocalAddress;
  unsigned short OpNum;
  UUID InterfaceUuid;        
} RPC_CALL_ATTRIBUTES_V2_W;
    
typedef struct tagRPC_CALL_ATTRIBUTES_V2_A {
  unsigned int Version;
  unsigned long Flags;
  unsigned long ServerPrincipalNameBufferLength;
  unsigned char *ServerPrincipalName;
  unsigned long ClientPrincipalNameBufferLength;
  unsigned char *ClientPrincipalName;
  unsigned long AuthenticationLevel;
  unsigned long AuthenticationService;
  BOOL NullSession;
  BOOL KernelModeCaller;
  unsigned long ProtocolSequence;
  unsigned long IsClientLocal;
  HANDLE ClientPID; 
  unsigned long CallStatus;
  RpcCallType CallType;
  RPC_CALL_LOCAL_ADDRESS_V1 *CallLocalAddress;
  unsigned short OpNum;
  UUID InterfaceUuid;    
} RPC_CALL_ATTRIBUTES_V2_A;

typedef enum tagRpcLocalAddressFormat {
  rlafInvalid = 0,
  rlafIPv4,
  rlafIPv6
} RpcLocalAddressFormat;

typedef struct _RPC_CALL_LOCAL_ADDRESS_V1 {
  unsigned int Version;
  void *Buffer;
  unsigned long BufferSize;
  RpcLocalAddressFormat AddressFormat;
} RPC_CALL_LOCAL_ADDRESS_V1, *PRPC_CALL_LOCAL_ADDRESS_V1;

#define RPC_CALL_ATTRIBUTES_VERSION 2
#define RPC_QUERY_SERVER_PRINCIPAL_NAME 0x02
#define RPC_QUERY_CLIENT_PRINCIPAL_NAME 0x04
#define RPC_QUERY_CALL_LOCAL_ADDRESS    0x08
#define RPC_QUERY_CLIENT_PID            0x10
#define RPC_QUERY_IS_CLIENT_LOCAL       0x20
#define RPC_QUERY_NO_AUTH_REQUIRED      0x40

typedef RPC_CALL_ATTRIBUTES_V2 RPC_CALL_ATTRIBUTES;

typedef enum _RPC_NOTIFICATIONS {
  RpcNotificationCallNone = 0,
  RpcNotificationClientDisconnect = 1,
  RpcNotificationCallCancel = 2
} RPC_NOTIFICATIONS;

#define RpcNotificationCallStatusChange    RpcNotificationClientDisconnect

___RPC_ENTRY__ RpcServerSubscribeForNotification(RPC_BINDING_HANDLE, RPC_NOTIFICATIONS, RPC_NOTIFICATION_TYPES, RPC_ASYNC_NOTIFICATION_INFO *);
___RPC_ENTRY__ RpcServerUnsubscribeForNotification(RPC_BINDING_HANDLE, RPC_NOTIFICATIONS, unsigned long *);
___RPC_ENTRY__ RpcBindingBind(PRPC_ASYNC_STATE, RPC_BINDING_HANDLE, RPC_IF_HANDLE);
___RPC_ENTRY__ RpcBindingUnbind(RPC_BINDING_HANDLE);

#if !defined(RPC_NO_WINDOWS_H) || defined(_WINBASE_H)
#define RPC_DE_USE_CURRENT_EEINFO 1
___RPC_ENTRY__ RpcDiagnoseError(RPC_BINDING_HANDLE, RPC_IF_HANDLE, RPC_STATUS, RPC_ERROR_ENUM_HANDLE *, ULONG, HWND);
#endif /* !defined(RPC_NO_WINDOWS_H) || defined(_WINBASE_H) */

#endif /* (_WIN32_WINNT >= _WIN32_WINNT_VISTA) */

#if (_WIN32_WINNT >= _WIN32_WINNT_WS03)
#define EEInfoGCFRS                  12
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WS03) */

#undef ___RPC_ENTRY__

#ifdef __cplusplus
extern }
#endif

#if defined(__RPC_WIN64__)
__POPPACK8
#endif

#endif /* !_RPCASYNC_H */
