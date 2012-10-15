/**
 * @file rpcdce.h
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
#ifndef _RPCDCE_H
#define _RPCDCE_H
#pragma GCC system_header
#include <_mingw.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef RPCRTAPI
#ifdef _RPCRT4_
#define RPCRTAPI
#else
#define RPCRTAPI DECLSPEC_IMPORT
#endif
#endif

#ifndef ___RPC_ENTRY__
#define ___RPC_ENTRY__ RPCRTAPI RPC_STATUS RPC_ENTRY
#endif
#ifndef ___RPC_VOID__
#define ___RPC_VOID__ RPCRTAPI void RPC_ENTRY
#endif
#ifndef ___RPC_INT__
#define ___RPC_INT__ RPCRTAPI int RPC_ENTRY
#endif
#ifndef ___RPC_USHORT__
#define ___RPC_USHORT__ RPCRTAPI unsigned short RPC_ENTRY
#endif
#ifndef ___RPC_LONG__
#define ___RPC_LONG__ RPCRTAPI long RPC_ENTRY
#endif
#ifndef ___RPC_ULONG__
#define ___RPC_ULONG__ RPCRTAPI unsigned long RPC_ENTRY
#endif

#ifndef _NO_W32_PSEUDO_MODIFIERS
#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif
#ifndef OPTIONAL
#define OPTIONAL
#endif
#endif /* ! _NO_W32_PSEUDO_MODIFIERS */

#ifndef DECLSPEC_NORETURN
#ifndef MIDL_PASS
#define DECLSPEC_NORETURN __declspec(noreturn)
#endif /* !MIDL_PASS */
#endif /* !DECLSPEC_NORETURN */

#include <specstrings.h>

typedef unsigned char * RPC_CSTR;

#if defined(RPC_USE_NATIVE_WCHAR) && defined(_NATIVE_WCHAR_T_DEFINED)
typedef wchar_t * RPC_WSTR;
typedef const wchar_t * RPC_CWSTR;
#else
typedef unsigned short * RPC_WSTR;
typedef const unsigned short * RPC_CWSTR;
#endif

typedef I_RPC_HANDLE RPC_BINDING_HANDLE;
typedef RPC_BINDING_HANDLE handle_t;
#define rpc_binding_handle_t RPC_BINDING_HANDLE

#ifndef GUID_DEFINED
#include <guiddef.h>
#endif

#ifndef UUID_DEFINED
#define UUID_DEFINED
typedef GUID UUID;
#ifndef uuid_t
#define uuid_t UUID
#endif
#endif

typedef struct _RPC_BINDING_VECTOR {
  unsigned long Count;
  RPC_BINDING_HANDLE BindingH[1];
} RPC_BINDING_VECTOR;
#ifndef rpc_binding_vector_t
#define rpc_binding_vector_t RPC_BINDING_VECTOR
#endif

typedef struct _UUID_VECTOR {
  unsigned long Count;
  UUID *Uuid[1];
} UUID_VECTOR;
#ifndef uuid_vector_t
#define uuid_vector_t UUID_VECTOR
#endif

typedef void *RPC_IF_HANDLE;

#ifndef IFID_DEFINED
#define IFID_DEFINED
typedef struct _RPC_IF_ID {
	UUID Uuid;
	unsigned short VersMajor;
	unsigned short VersMinor;
} RPC_IF_ID;
#endif

#define RPC_C_BINDING_INFINITE_TIMEOUT 10
#define RPC_C_BINDING_MIN_TIMEOUT 0
#define RPC_C_BINDING_DEFAULT_TIMEOUT 5
#define RPC_C_BINDING_MAX_TIMEOUT 9
#define RPC_C_CANCEL_INFINITE_TIMEOUT (-1)
#define RPC_C_LISTEN_MAX_CALLS_DEFAULT 1234
#define RPC_C_PROTSEQ_MAX_REQS_DEFAULT 10
#define RPC_C_BIND_TO_ALL_NICS 1
#define RPC_C_USE_INTERNET_PORT        0x1
#define RPC_C_USE_INTRANET_PORT        0x2
#define RPC_C_DONT_FAIL                0x4
#define RPC_C_RPCHTTP_USE_LOAD_BALANCE 0x8

#if (_WIN32_WINNT < _WIN32_WINNT_VISTA)
#define RPC_C_MQ_TEMPORARY                 0x0000
#define RPC_C_MQ_PERMANENT                 0x0001
#define RPC_C_MQ_CLEAR_ON_OPEN             0x0002
#define RPC_C_MQ_USE_EXISTING_SECURITY     0x0004
#define RPC_C_MQ_AUTHN_LEVEL_NONE          0x0000
#define RPC_C_MQ_AUTHN_LEVEL_PKT_INTEGRITY 0x0008
#define RPC_C_MQ_AUTHN_LEVEL_PKT_PRIVACY   0x0010
#define RPC_C_MQ_EXPRESS                  0
#define RPC_C_MQ_RECOVERABLE              1
#define RPC_C_MQ_JOURNAL_NONE             0
#define RPC_C_MQ_JOURNAL_DEADLETTER       1
#define RPC_C_MQ_JOURNAL_ALWAYS           2
#define RPC_C_OPT_MQ_DELIVERY             1
#define RPC_C_OPT_MQ_PRIORITY             2
#define RPC_C_OPT_MQ_JOURNAL              3
#define RPC_C_OPT_MQ_ACKNOWLEDGE          4
#define RPC_C_OPT_MQ_AUTHN_SERVICE        5
#define RPC_C_OPT_MQ_AUTHN_LEVEL          6
#define RPC_C_OPT_MQ_TIME_TO_REACH_QUEUE  7
#define RPC_C_OPT_MQ_TIME_TO_BE_RECEIVED  8
#endif /* (_WIN32_WINNT < _WIN32_WINNT_VISTA) */

#define RPC_C_OPT_BINDING_NONCAUSAL       9
#define RPC_C_OPT_SECURITY_CALLBACK      10
#define RPC_C_OPT_UNIQUE_BINDING         11

#if (_WIN32_WINNT < _WIN32_WINNT_WIN2K)
#define RPC_C_OPT_MAX_OPTIONS            12
#elif (_WIN32_WINNT < _WIN32_WINNT_WS03)
#define RPC_C_OPT_CALL_TIMEOUT           12
#define RPC_C_OPT_DONT_LINGER            13
#define RPC_C_OPT_MAX_OPTIONS            14
#else /* ! < WIN2K && ! < WS03 */
#define RPC_C_OPT_TRANS_SEND_BUFFER_SIZE  5
#define RPC_C_OPT_CALL_TIMEOUT           12
#define RPC_C_OPT_DONT_LINGER            13
#define RPC_C_OPT_TRUST_PEER             14
#define RPC_C_OPT_ASYNC_BLOCK            15
#define RPC_C_OPT_OPTIMIZE_TIME          16
#define RPC_C_OPT_MAX_OPTIONS            17
#endif /* (_WIN32_WINNT < _WIN32_WINNT_WIN2K) */

#define RPC_C_FULL_CERT_CHAIN 0x0001

#define RPC_MGR_EPV void
#define RPC_C_PARAM_MAX_PACKET_LENGTH 1
#define RPC_C_PARAM_BUFFER_LENGTH 2

#define RPC_C_STATS_CALLS_IN  0
#define RPC_C_STATS_CALLS_OUT 1
#define RPC_C_STATS_PKTS_IN   2
#define RPC_C_STATS_PKTS_OUT  3
#define RPC_IF_AUTOLISTEN		    0x0001
#define RPC_IF_OLE			    0x0002
#define RPC_IF_ALLOW_UNKNOWN_AUTHORITY	    0x0004
#define RPC_IF_ALLOW_SECURE_ONLY	    0x0008
#define RPC_IF_ALLOW_CALLBACKS_WITH_NO_AUTH 0x0010
#define RPC_IF_ALLOW_LOCAL_ONLY		    0x0020
#define RPC_IF_SEC_NO_CACHE		    0x0040
#define RPC_C_MGMT_INQ_IF_IDS         0
#define RPC_C_MGMT_INQ_PRINC_NAME     1
#define RPC_C_MGMT_INQ_STATS          2
#define RPC_C_MGMT_IS_SERVER_LISTEN   3
#define RPC_C_MGMT_STOP_SERVER_LISTEN 4
#define RPC_C_EP_ALL_ELTS      0
#define RPC_C_EP_MATCH_BY_IF   1
#define RPC_C_EP_MATCH_BY_OBJ  2
#define RPC_C_EP_MATCH_BY_BOTH 3
#define RPC_C_VERS_ALL        1
#define RPC_C_VERS_COMPATIBLE 2
#define RPC_C_VERS_EXACT      3
#define RPC_C_VERS_MAJOR_ONLY 4
#define RPC_C_VERS_UPTO       5
#define DCE_C_ERROR_STRING_LEN 256
#define RPC_C_PARM_MAX_PACKET_LENGTH 1
#define RPC_C_PARM_BUFFER_LENGTH     2
#define RPC_C_AUTHN_LEVEL_DEFAULT       0
#define RPC_C_AUTHN_LEVEL_NONE          1
#define RPC_C_AUTHN_LEVEL_CONNECT       2
#define RPC_C_AUTHN_LEVEL_CALL          3
#define RPC_C_AUTHN_LEVEL_PKT           4
#define RPC_C_AUTHN_LEVEL_PKT_INTEGRITY 5
#define RPC_C_AUTHN_LEVEL_PKT_PRIVACY   6
#define RPC_C_IMP_LEVEL_ANONYMOUS   1
#define RPC_C_IMP_LEVEL_IDENTIFY    2
#define RPC_C_IMP_LEVEL_IMPERSONATE 3
#define RPC_C_IMP_LEVEL_DELEGATE    4
#define RPC_C_QOS_IDENTITY_STATIC  0
#define RPC_C_QOS_IDENTITY_DYNAMIC 1
#define RPC_C_QOS_CAPABILITIES_DEFAULT     0
#define RPC_C_QOS_CAPABILITIES_MUTUAL_AUTH 1
#define RPC_C_PROTECT_LEVEL_DEFAULT(RPC_C_AUTHN_LEVEL_DEFAULT)
#define RPC_C_PROTECT_LEVEL_NONE(RPC_C_AUTHN_LEVEL_NONE)
#define RPC_C_PROTECT_LEVEL_CONNECT(RPC_C_AUTHN_LEVEL_CONNECT)
#define RPC_C_PROTECT_LEVEL_CALL(RPC_C_AUTHN_LEVEL_CALL)
#define RPC_C_PROTECT_LEVEL_PKT(RPC_C_AUTHN_LEVEL_PKT)
#define RPC_C_PROTECT_LEVEL_PKT_INTEGRITY(RPC_C_AUTHN_LEVEL_PKT_INTEGRITY)
#define RPC_C_PROTECT_LEVEL_PKT_PRIVACY(RPC_C_AUTHN_LEVEL_PKT_PRIVACY)
#define RPC_C_AUTHN_NONE            0
#define RPC_C_AUTHN_DCE_PRIVATE     1
#define RPC_C_AUTHN_DCE_PUBLIC      2
#define RPC_C_AUTHN_DEC_PUBLIC      4
#define RPC_C_AUTHN_GSS_NEGOTIATE   9
#define RPC_C_AUTHN_WINNT          10
#define RPC_C_AUTHN_GSS_SCHANNEL   14
#define RPC_C_AUTHN_GSS_KERBEROS   16
#define RPC_C_AUTHN_DPA            17
#define RPC_C_AUTHN_MSN            18
#define RPC_C_AUTHN_NEGO_EXTENDER  30
#define RPC_C_AUTHN_PKU2U          31
#define PRC_C_AUTHN_MQ            100
#define RPC_C_AUTHN_DEFAULT 0xFFFFFFFFL
#define RPC_C_NO_CREDENTIALS ((RPC_AUTH_IDENTITY_HANDLE) MAXUINT_PTR)
#define RPC_C_SECURITY_QOS_VERSION   1L
#define RPC_C_SECURITY_QOS_VERSION_1 1L

#define RPC_C_AUTHZ_NONE 0
#define RPC_C_AUTHZ_NAME 1
#define RPC_C_AUTHZ_DCE  2
#define RPC_C_AUTHZ_DEFAULT 0xFFFFFFFF

___RPC_ENTRY__ RpcImpersonateClient(RPC_BINDING_HANDLE);
___RPC_ENTRY__ RpcRevertToSelf(void);
___RPC_ENTRY__ RpcRevertToSelfEx(RPC_BINDING_HANDLE);

typedef struct _RPC_POLICY {
	unsigned int Length ;
	unsigned long EndpointFlags ;
	unsigned long NICFlags ;
} RPC_POLICY,*PRPC_POLICY ;

typedef void __RPC_USER RPC_OBJECT_INQ_FN(UUID*,UUID*,RPC_STATUS*);
typedef RPC_STATUS RPC_ENTRY RPC_IF_CALLBACK_FN(RPC_IF_HANDLE,void*);
typedef void RPC_ENTRY RPC_SECURITY_CALLBACK_FN(void *);

typedef struct {
	unsigned int Count;
	unsigned long Stats[1];
} RPC_STATS_VECTOR;

typedef struct {
	unsigned long Count;
	RPC_IF_ID*IfId[1];
} RPC_IF_ID_VECTOR;

typedef void *RPC_AUTH_IDENTITY_HANDLE;
typedef void *RPC_AUTHZ_HANDLE;

typedef struct _RPC_SECURITY_QOS {
	unsigned long Version;
	unsigned long Capabilities;
	unsigned long IdentityTracking;
	unsigned long ImpersonationType;
} RPC_SECURITY_QOS,*PRPC_SECURITY_QOS;

#ifndef _AUTH_IDENTITY_DEFINED
#define _AUTH_IDENTITY_DEFINED

#define SEC_WINNT_AUTH_IDENTITY_ANSI    0x1
#define SEC_WINNT_AUTH_IDENTITY_UNICODE 0x2

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
#define _AUTH_IDENTITY_A_DEFINED
#endif

typedef struct _SEC_WINNT_AUTH_IDENTITY_A {
	RPC_CSTR User;
	unsigned long UserLength;
	RPC_CSTR Domain;
	unsigned long DomainLength;
	RPC_CSTR Password;
	unsigned long PasswordLength;
	unsigned long Flags;
} SEC_WINNT_AUTH_IDENTITY_A,*PSEC_WINNT_AUTH_IDENTITY_A;

typedef struct _SEC_WINNT_AUTH_IDENTITY_W {
	RPC_WSTR User;
	unsigned long UserLength;
	RPC_WSTR Domain;
	unsigned long DomainLength;
	RPC_WSTR Password;
	unsigned long PasswordLength;
	unsigned long Flags;
} SEC_WINNT_AUTH_IDENTITY_W,*PSEC_WINNT_AUTH_IDENTITY_W;

#define SEC_WINNT_AUTH_IDENTITY __AW(SEC_WINNT_AUTH_IDENTITY_)
#define PSEC_WINNT_AUTH_IDENTITY __AW(PSEC_WINNT_AUTH_IDENTITY_)
#define _SEC_WINNT_AUTH_IDENTITY __AW(_SEC_WINNT_AUTH_IDENTITY_)

#if (_WIN32_WINNT >= _WIN32_WINNT_WINXP)
#define RPC_C_SECURITY_QOS_VERSION_2 2L
#define RPC_C_AUTHN_INFO_TYPE_HTTP 1
#define RPC_C_HTTP_AUTHN_TARGET_SERVER 1
#define RPC_C_HTTP_AUTHN_SCHEME_BASIC     0x00000001
#define RPC_C_HTTP_AUTHN_SCHEME_NTLM      0x00000002
#define RPC_C_HTTP_AUTHN_SCHEME_PASSPORT  0x00000004
#define RPC_C_HTTP_AUTHN_SCHEME_DIGEST    0x00000008
#define RPC_C_HTTP_AUTHN_SCHEME_NEGOTIATE 0x00000010
#define RPC_C_HTTP_FLAG_USE_SSL 1
#define RPC_C_HTTP_FLAG_USE_FIRST_AUTH_SCHEME 2

typedef struct _RPC_HTTP_TRANSPORT_CREDENTIALS_A {
  SEC_WINNT_AUTH_IDENTITY_A *TrasportCredentials;
  unsigned long Flags;
  unsigned long AuthenticationTarget;
  unsigned long NumberOfAuthnSchemes;
  unsigned long *AuthnSchemes;
  RPC_CSTR ServerCertificateSubject;
} RPC_HTTP_TRANSPORT_CREDENTIALS_A, *PRPC_HTTP_TRANSPORT_CREDENTIALS_A

typedef struct _RPC_HTTP_TRANSPORT_CREDENTIALS_W {
  SEC_WINNT_AUTH_IDENTITY_W *TrasportCredentials;
  unsigned long Flags;
  unsigned long AuthenticationTarget;
  unsigned long NumberOfAuthnSchemes;
  unsigned long *AuthnSchemes;
  RPC_WSTR ServerCertificateSubject;
} RPC_HTTP_TRANSPORT_CREDENTIALS_W, *PRPC_HTTP_TRANSPORT_CREDENTIALS_W

#define RPC_HTTP_TRANSPORT_CREDENTIALS __AW(RPC_HTTP_TRANSPORT_CREDENTIALS_)
#define PRPC_HTTP_TRANSPORT_CREDENTIALS __AW(PRPC_HTTP_TRANSPORT_CREDENTIALS_)
#define _RPC_HTTP_TRANSPORT_CREDENTIALS __AW(_RPC_HTTP_TRANSPORT_CREDENTIALS_)

typedef struct _RPC_SECURITY_QOS_V2_A {
  unsigned long Version;
  unsigned long Capabilities;
  unsigned long IdentityTracking;
  unsigned long ImpersonationType;
  unsigned long AdditionalSecurityInfoType;
  union {
    RPC_HTTP_TRANSPORT_CREDENITIALS_A *HttpCredentials;
  } u
} RPC_SECURITY_QOS_V2_A *PRPC_SECURITY_QOS_V2_A;

typedef struct _RPC_SECURITY_QOS_V2_W {
  unsigned long Version;
  unsigned long Capabilities;
  unsigned long IdentityTracking;
  unsigned long ImpersonationType;
  unsigned long AdditionalSecurityInfoType;
  union {
    RPC_HTTP_TRANSPORT_CREDENITIALS_W *HttpCredentials;
  } u
} RPC_SECURITY_QOS_V2_W *PRPC_SECURITY_QOS_V2_W;

#define RPC_SECURITY_QOS_V2 __AW(RPC_SECURITY_QOS_V2_)
#define PRPC_SECURITY_QOS_V2 __AW(PRPC_SECURITY_QOS_V2_)
#define _RPC_SECURITY_QOS_V2 __AW(_RPC_SECURITY_QOS_V2_)

typedef void (__RPC_USER * RPC_HTTP_PROXY_FREE_STRING) (RPC_WSTR String);

#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WINXP) */

#if (_WIN32_WINNT >= _WIN32_WINNT_WS03)
#define RPC_C_HTTP_AUTHN_SCHEME_CERT      0x00010000
#define RPC_C_HTTP_FLAG_IGNORE_CERT_CN_INVALID 8
#define RPC_C_SECURITY_QOS_VERSION_3 3L

typedef struct _RPC_SECURITY_QOS_V3_A {
  unsigned long Version;
  unsigned long Capabilities;
  unsigned long IdentityTracking;
  unsigned long ImpersonationType;
  unsigned long AdditionalSecurityInfoType;
  union {
    RPC_HTTP_TRANSPORT_CREDENITIALS_A *HttpCredentials;
  } u
  void *Sid;
} RPC_SECURITY_QOS_V3_A *PRPC_SECURITY_QOS_V3_A;

typedef struct _RPC_SECURITY_QOS_V3_W {
  unsigned long Version;
  unsigned long Capabilities;
  unsigned long IdentityTracking;
  unsigned long ImpersonationType;
  unsigned long AdditionalSecurityInfoType;
  union {
    RPC_HTTP_TRANSPORT_CREDENITIALS_W *HttpCredentials;
  } u
  void *Sid;
} RPC_SECURITY_QOS_V3_W *PRPC_SECURITY_QOS_V3_W;

#define RPC_SECURITY_QOS_V3 __AW(RPC_SECURITY_QOS_V3_)
#define PRPC_SECURITY_QOS_V3 __AW(PRPC_SECURITY_QOS_V3_)
#define _RPC_SECURITY_QOS_V3 __AW(_RPC_SECURITY_QOS_V3_)

typedef enum _RPC_HTTP_REDIRECTOR_STAGE {
  RPCHTTP_RS_REDIRECT = 1,
  RPCHTTP_RS_ACCESS_1,
  RPCHTTP_RS_SESSION,
  RPCHTTP_RS_ACCESS_2,
  RPCHTTP_RS_INTERFACE
} RPC_HTTP_REDIRECTORY_STAGE;

typedef RPC_STATUS (__RPC_USER * RPC_NEW_HTTP_PROXY_CHANNEL) (
  RPC_HTTP_REDIRECTOR_STAGE RedirectorStage,
  RPC_WSTR ServerName,
  RPC_WSTR ServerPort,
  RPC_WSTR RemoteUser,
  RPC_WSTR AuthType,
  void * SessionId,
  void * Interface,
  void * Reserved,
  unsigned long Flags,
  RPC_WSTR * NewServerName,
  RPC_WSTR * NewServerPort
);

#else

typedef RPC_STATUS (__RPC_USER * RPC_NEW_HTTP_PROXY_CHANNEL) (
  RPC_WSTR ServerName,
  RPC_WSTR ServerPort,
  RPC_CSTR RemoteUser,
  RPC_WSTR * NewServerName
);

#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WS03) */

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
#define RPC_C_HTTP_AUTHN_TARGET_PROXY  2
#define RPC_C_HTTP_FLAG_ENABLE_CERT_REVOCATION_CHECK 16
#define RPC_C_SECURITY_QOS_VERSION_4 4L

typedef struct _RPC_HTTP_TRANSPORT_CREDENTIALS_V2_A {
  SEC_WINNT_AUTH_IDENTITY_A *TrasportCredentials;
  unsigned long Flags;
  unsigned long AuthenticationTarget;
  unsigned long NumberOfAuthnSchemes;
  unsigned long *AuthnSchemes;
  RPC_CSTR ServerCertificateSubject;
  SEC_WINNT_AUTH_IDENTITY_A *ProxyCredentials;
  unsigned long NumberOfProxyAuthnSchemes;
  unsigned long *ProxyAuthnSchemes;
} RPC_HTTP_TRANSPORT_CREDENTIALS_V2_A, *PRPC_HTTP_TRANSPORT_CREDENTIALS_V2_A

typedef struct _RPC_HTTP_TRANSPORT_CREDENTIALS_V2_W {
  SEC_WINNT_AUTH_IDENTITY_W *TrasportCredentials;
  unsigned long Flags;
  unsigned long AuthenticationTarget;
  unsigned long NumberOfAuthnSchemes;
  unsigned long *AuthnSchemes;
  RPC_WSTR ServerCertificateSubject;
  SEC_WINNT_AUTH_IDENTITY_W *ProxyCredentials;
  unsigned long NumberOfProxyAuthnSchemes;
  unsigned long *ProxyAuthnSchemes;
} RPC_HTTP_TRANSPORT_CREDENTIALS_V2_W, *PRPC_HTTP_TRANSPORT_CREDENTIALS_V2_W

#define RPC_HTTP_TRANSPORT_CREDENTIALS_V2 __AW(RPC_HTTP_TRANSPORT_CREDENTIALS_V2_)
#define PRPC_HTTP_TRANSPORT_CREDENTIALS_V2 __AW(PRPC_HTTP_TRANSPORT_CREDENTIALS_V2_)
#define _RPC_HTTP_TRANSPORT_CREDENTIALS_V2 __AW(_RPC_HTTP_TRANSPORT_CREDENTIALS_V2_)

typedef struct _RPC_SECURITY_QOS_V4_A {
  unsigned long Version;
  unsigned long Capabilities;
  unsigned long IdentityTracking;
  unsigned long ImpersonationType;
  unsigned long AdditionalSecurityInfoType;
  union {
    RPC_HTTP_TRANSPORT_CREDENITIALS_A *HttpCredentials;
  } u
  void *Sid;
  unsigned int EffectiveOnly;
} RPC_SECURITY_QOS_V4_A *PRPC_SECURITY_QOS_V4_A;

typedef struct _RPC_SECURITY_QOS_V4_W {
  unsigned long Version;
  unsigned long Capabilities;
  unsigned long IdentityTracking;
  unsigned long ImpersonationType;
  unsigned long AdditionalSecurityInfoType;
  union {
    RPC_HTTP_TRANSPORT_CREDENITIALS_W *HttpCredentials;
  } u
  void *Sid;
  unsigned int EffectiveOnly;
} RPC_SECURITY_QOS_V4_W *PRPC_SECURITY_QOS_V4_W;

#define RPC_SECURITY_QOS_V4 __AW(RPC_SECURITY_QOS_V4_)
#define PRPC_SECURITY_QOS_V4 __AW(PRPC_SECURITY_QOS_V4_)
#define _RPC_SECURITY_QOS_V4 __AW(_RPC_SECURITY_QOS_V4_)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_VISTA) */

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN7)
typedef struct _RPC_HTTP_TRANSPORT_CREDENTIALS_V3_A {
  SEC_WINNT_AUTH_IDENTITY_A *TrasportCredentials;
  unsigned long Flags;
  unsigned long AuthenticationTarget;
  unsigned long NumberOfAuthnSchemes;
  unsigned long *AuthnSchemes;
  RPC_CSTR ServerCertificateSubject;
  RPC_AUTH_IDENTITY_HANDLE ProxyCredentials;
  unsigned long NumberOfProxyAuthnSchemes;
  unsigned long *ProxyAuthnSchemes;
} RPC_HTTP_TRANSPORT_CREDENTIALS_V3_A, *PRPC_HTTP_TRANSPORT_CREDENTIALS_V3_A

typedef struct _RPC_HTTP_TRANSPORT_CREDENTIALS_V3_W {
  SEC_WINNT_AUTH_IDENTITY_W *TrasportCredentials;
  unsigned long Flags;
  unsigned long AuthenticationTarget;
  unsigned long NumberOfAuthnSchemes;
  unsigned long *AuthnSchemes;
  RPC_WSTR ServerCertificateSubject;
  RPC_AUTH_IDENTITY_HANDLE ProxyCredentials;
  unsigned long NumberOfProxyAuthnSchemes;
  unsigned long *ProxyAuthnSchemes;
} RPC_HTTP_TRANSPORT_CREDENTIALS_V3_W, *PRPC_HTTP_TRANSPORT_CREDENTIALS_V3_W

#define RPC_HTTP_TRANSPORT_CREDENTIALS_V3 __AW(RPC_HTTP_TRANSPORT_CREDENTIALS_V3_)
#define PRPC_HTTP_TRANSPORT_CREDENTIALS_V3 __AW(PRPC_HTTP_TRANSPORT_CREDENTIALS_V3_)
#define _RPC_HTTP_TRANSPORT_CREDENTIALS_V3 __AW(_RPC_HTTP_TRANSPORT_CREDENTIALS_V3_)
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WIN7) */

#endif /* !_AUTH_IDENTITY_DEFINED */

#if (_WIN32_WINNT >= _WIN32_WINNT_WINXP)
typedef struct {
	unsigned char *UserName;
	unsigned char *ComputerName;
	unsigned short Privilege;
	unsigned long AuthFlags;
} RPC_CLIENT_INFORMATION1, *PRPC_CLIENT_INFORMATION1;
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WINXP) */

typedef I_RPC_HANDLE *RPC_EP_INQ_HANDLE;
typedef int(__RPC_API *RPC_MGMT_AUTHORIZATION_FN)(RPC_BINDING_HANDLE, unsigned long, RPC_STATUS *);

#ifdef RPC_UNICODE_SUPPORTED
typedef struct _RPC_PROTSEQ_VECTORA {
	unsigned int Count;
	unsigned char*Protseq[1];
} RPC_PROTSEQ_VECTORA;
typedef struct _RPC_PROTSEQ_VECTORW {
	unsigned int Count;
	unsigned short*Protseq[1];
} RPC_PROTSEQ_VECTORW;
___RPC_ENTRY__ RpcBindingFromStringBindingA(unsigned char *, RPC_BINDING_HANDLE *);
___RPC_ENTRY__ RpcBindingFromStringBindingW(unsigned short *, RPC_BINDING_HANDLE *);
___RPC_ENTRY__ RpcBindingToStringBindingA(RPC_BINDING_HANDLE, RPC_CSTR *);
___RPC_ENTRY__ RpcBindingToStringBindingW(RPC_BINDING_HANDLE, RPC_WSTR *);
___RPC_ENTRY__ RpcStringBindingComposeA(RPC_CSTR, RPC_CSTR, RPC_CSTR, RPC_CSTR, RPC_CSTR, RPC_CSTR *);
___RPC_ENTRY__ RpcStringBindingComposeW(RPC_WSTR, RPC_WSTR, RPC_WSTR, RPC_WSTR, RPC_WSTR, RPC_WSTR *);
___RPC_ENTRY__ RpcStringBindingParseA(RPC_CSTR, RPC_CSTR *, RPC_CSTR *, RPC_CSTR *, RPC_CSTR *, RPC_CSTR *);
___RPC_ENTRY__ RpcStringBindingParseW(RPC_WSTR, RPC_WSTR *, RPC_WSTR *, RPC_WSTR *, RPC_WSTR *, RPC_WSTR *);
___RPC_ENTRY__ RpcStringFreeA(RPC_CSTR *);
___RPC_ENTRY__ RpcStringFreeW(RPC_WSTR *);
___RPC_ENTRY__ RpcNetworkIsProtseqValidA(RPC_CSTR);
___RPC_ENTRY__ RpcNetworkIsProtseqValidW(RPC_WSTR);
___RPC_ENTRY__ RpcNetworkInqProtseqsA(RPC_PROTSEQ_VECTORA**);
___RPC_ENTRY__ RpcNetworkInqProtseqsW(RPC_PROTSEQ_VECTORW**);
___RPC_ENTRY__ RpcProtseqVectorFreeA(RPC_PROTSEQ_VECTORA**);
___RPC_ENTRY__ RpcProtseqVectorFreeW(RPC_PROTSEQ_VECTORW**);
___RPC_ENTRY__ RpcServerUseProtseqA(RPC_CSTR, unsigned int, void *);
___RPC_ENTRY__ RpcServerUseProtseqW(RPC_WSTR, unsigned int, void *);
___RPC_ENTRY__ RpcServerUseProtseqExA(RPC_CSTR, unsigned int, void *, PRPC_POLICY);
___RPC_ENTRY__ RpcServerUseProtseqExW(RPC_WSTR, unsigned int, void *, PRPC_POLICY);
___RPC_ENTRY__ RpcServerUseProtseqEpA(RPC_CSTR, unsigned int, RPC_CSTR, void *);
___RPC_ENTRY__ RpcServerUseProtseqEpW(RPC_WSTR, unsigned int, RPC_WSTR, void *);
___RPC_ENTRY__ RpcServerUseProtseqEpExA(RPC_CSTR, unsigned int, RPC_CSTR, void *, PRPC_POLICY);
___RPC_ENTRY__ RpcServerUseProtseqEpExW(RPC_WSTR, unsigned int, RPC_WSTR, void *, PRPC_POLICY);
___RPC_ENTRY__ RpcServerUseProtseqIfA(RPC_CSTR, unsigned int, RPC_IF_HANDLE, void *);
___RPC_ENTRY__ RpcServerUseProtseqIfW(RPC_WSTR, unsigned int, RPC_IF_HANDLE, void *);
___RPC_ENTRY__ RpcServerUseProtseqIfExA(RPC_CSTR, unsigned int, RPC_IF_HANDLE, void *, PRPC_POLICY);
___RPC_ENTRY__ RpcServerUseProtseqIfExW(RPC_WSTR, unsigned int, RPC_IF_HANDLE, void *, PRPC_POLICY);
___RPC_ENTRY__ RpcMgmtInqServerPrincNameA(RPC_BINDING_HANDLE, unsigned long, RPC_CSTR *);
___RPC_ENTRY__ RpcMgmtInqServerPrincNameW(RPC_BINDING_HANDLE, unsigned long, RPC_WSTR *);
___RPC_ENTRY__ RpcServerInqDefaultPrincNameA(unsigned long, RPC_CSTR *);
___RPC_ENTRY__ RpcServerInqDefaultPrincNameW(unsigned long, RPC_WSTR *);
___RPC_ENTRY__ RpcNsBindingInqEntryNameA(RPC_BINDING_HANDLE, unsigned long, RPC_CSTR *);
___RPC_ENTRY__ RpcNsBindingInqEntryNameW(RPC_BINDING_HANDLE, unsigned long, RPC_WSTR *);
___RPC_ENTRY__ RpcBindingInqAuthClientA(RPC_BINDING_HANDLE, RPC_AUTHZ_HANDLE *, RPC_CSTR *, unsigned long *, unsigned long *, unsigned long *);
___RPC_ENTRY__ RpcBindingInqAuthClientW(RPC_BINDING_HANDLE, RPC_AUTHZ_HANDLE *, RPC_WSTR *, unsigned long *, unsigned long *, unsigned long *);

#define RpcBindingInqAuthClient __AW(RpcBindingInqAuthClient)

___RPC_ENTRY__ RpcBindingInqAuthClientExA(RPC_BINDING_HANDLE, RPC_AUTHZ_HANDLE *, RPC_CSTR *, unsigned long *, unsigned long *, unsigned long *, unsigned long);
___RPC_ENTRY__ RpcBindingInqAuthClientExW(RPC_BINDING_HANDLE, RPC_AUTHZ_HANDLE *, RPC_WSTR *, unsigned long *, unsigned long *, unsigned long *, unsigned long);

#define RpcBindingInqAuthClientEx __AW(RpcBindingInqAuthClientEx)

___RPC_ENTRY__ RpcBindingInqAuthInfoA(RPC_BINDING_HANDLE, RPC_CSTR *, unsigned long *, unsigned long *, RPC_AUTH_IDENTITY_HANDLE *, unsigned long *);
___RPC_ENTRY__ RpcBindingInqAuthInfoW(RPC_BINDING_HANDLE, RPC_WSTR *, unsigned long *, unsigned long *, RPC_AUTH_IDENTITY_HANDLE *, unsigned long *);

#define RpcBindingInqAuthInfo __AW(RpcBindingInqAuthInfo)

___RPC_ENTRY__ RpcBindingInqAuthInfoExA(RPC_BINDING_HANDLE, RPC_CSTR *, unsigned long *, unsigned long *, RPC_AUTH_IDENTITY_HANDLE *, unsigned long *, unsigned long, RPC_SECURITY_QOS *);
___RPC_ENTRY__ RpcBindingInqAuthInfoExW(RPC_BINDING_HANDLE, RPC_WSTR *, unsigned long *, unsigned long *, RPC_AUTH_IDENTITY_HANDLE *, unsigned long *, unsigned long, RPC_SECURITY_QOS *);

#define RpcBindingInqAuthInfoEx __AW(RpcBindingInqAuthInfoEx)

___RPC_ENTRY__ RpcBindingSetAuthInfoA(RPC_BINDING_HANDLE, RPC_CSTR, unsigned long, unsigned long, RPC_AUTH_IDENTITY_HANDLE, unsigned long);
___RPC_ENTRY__ RpcBindingSetAuthInfoW(RPC_BINDING_HANDLE, RPC_WSTR, unsigned long, unsigned long, RPC_AUTH_IDENTITY_HANDLE, unsigned long);

#define RpcBindingSetAuthInfo __AW(RpcBindingSetAuthInfo)

___RPC_ENTRY__ RpcBindingSetAuthInfoExA(RPC_BINDING_HANDLE, RPC_CSTR, unsigned long, unsigned long, RPC_AUTH_IDENTITY_HANDLE, unsigned long, RPC_SECURITY_QOS *);
___RPC_ENTRY__ RpcBindingSetAuthInfoExW(RPC_BINDING_HANDLE, RPC_WSTR, unsigned long, unsigned long, RPC_AUTH_IDENTITY_HANDLE, unsigned long, RPC_SECURITY_QOS *);

#define RpcBindingSetAuthInfoEx __AW(RpcBindingSetAuthInfoEx)

typedef void (__RPC_USER * RPC_AUTH_KEY_RETRIEVAL_FN)(void *, RPC_WSTR, unsigned long, void **, RPC_STATUS *);

___RPC_ENTRY__ RpcServerCompleteSecurityCallback(RPC_BINDING_HANDLE, RPC_STATUS);
___RPC_ENTRY__ RpcServerRegisterAuthInfoA(RPC_CSTR, unsigned long, RPC_AUTH_KEY_RETRIEVAL_FN, void *);
___RPC_ENTRY__ RpcServerRegisterAuthInfoW(RPC_WSTR, unsigned long, RPC_AUTH_KEY_RETRIEVAL_FN, void *);

#define RpcServerRegisterAuthInfo __AW(RpcServerRegisterAuthInfo)

___RPC_ENTRY__ UuidToStringA(UUID *, RPC_CSTR *);
___RPC_ENTRY__ UuidToStringW(UUID *, RPC_WSTR *);
#define UuidToString __AW(UuidToString)

___RPC_ENTRY__ UuidFromStringA(RPC_CSTR, UUID *);
___RPC_ENTRY__ UuidFromStringW(RPC_WSTR, UUID *);
#define UuidFromString __AW(UuidFromString)

___RPC_ENTRY__ RpcEpRegisterNoReplaceA(RPC_IF_HANDLE, RPC_BINDING_VECTOR *, UUID_VECTOR *, RPC_CSTR);
___RPC_ENTRY__ RpcEpRegisterNoReplaceW(RPC_IF_HANDLE, RPC_BINDING_VECTOR *, UUID_VECTOR *, RPC_WSTR);
#define RpcEpRegisterNoReplace __AW(RpcEpRegisterNoReplace)

___RPC_ENTRY__ RpcEpRegisterA(RPC_IF_HANDLE, RPC_BINDING_VECTOR *, UUID_VECTOR *, RPC_CSTR);
___RPC_ENTRY__ RpcEpRegisterW(RPC_IF_HANDLE, RPC_BINDING_VECTOR *, UUID_VECTOR *, RPC_WSTR);
#define RpcEpRegister __AW(RpcEpRegister)

___RPC_ENTRY__ DceErrorInqTextA(RPC_STATUS, RPC_CSTR);
___RPC_ENTRY__ DceErrorInqTextW(RPC_STATUS, RPC_WSTR);
#define DceErrorInqText __AW(DceErrorInqText)

___RPC_ENTRY__ RpcMgmtEpEltInqNextA(RPC_EP_INQ_HANDLE, RPC_IF_ID *, RPC_BINDING_HANDLE *, UUID *, RPC_CSTR *);
___RPC_ENTRY__ RpcMgmtEpEltInqNextW(RPC_EP_INQ_HANDLE, RPC_IF_ID *, RPC_BINDING_HANDLE *, UUID *, RPC_WSTR *);
#define RpcMgmtEpEltInqNext __AW(RpcMgmtEpEltInqNext)

#define RPC_PROTSEQ_VECTOR __AW(RPC_PROTSEQ_VECTOR)
#define RpcBindingFromStringBinding __AW(RpcBindingFromStringBinding)
#define RpcBindingToStringBinding __AW(RpcBindingToStringBinding)
#define RpcStringBindingCompose __AW(RpcStringBindingCompose)
#define RpcStringBindingParse __AW(RpcStringBindingParse)
#define RpcStringFree __AW(RpcStringFree)
#define RpcNetworkIsProtseqValid __AW(RpcNetworkIsProtseqValid)
#define RpcNetworkInqProtseqs __AW(RpcNetworkInqProtseqs)
#define RpcProtseqVectorFree __AW(RpcProtseqVectorFree)
#define RpcServerUseProtseq __AW(RpcServerUseProtseq)
#define RpcServerUseProtseqEx __AW(RpcServerUseProtseqEx)
#define RpcServerUseProtseqEp __AW(RpcServerUseProtseqEp)
#define RpcServerUseProtseqEpEx __AW(RpcServerUseProtseqEpEx)
#define RpcServerUseProtseqIf __AW(RpcServerUseProtseqIf)
#define RpcServerUseProtseqIfEx __AW(RpcServerUseProtseqIfEx)
#define RpcMgmtInqServerPrincName __AW(RpcMgmtInqServerPrincName)
#define RpcServerInqDefaultPrincName __AW(RpcServerInqDefaultPrincName)
#define RpcNsBindingInqEntryName __AW(RpcNsBindingInqEntryName)

#else /* RPC_UNICODE_SUPPORTED */
typedef struct _RPC_PROTSEQ_VECTOR {
	unsigned int Count;
	unsigned char* Protseq[1];
} RPC_PROTSEQ_VECTOR;
___RPC_ENTRY__ RpcBindingFromStringBinding(unsigned char *, RPC_BINDING_HANDLE *);
___RPC_ENTRY__ RpcBindingToStringBinding(RPC_BINDING_HANDLE, RPC_CSTR *);
___RPC_ENTRY__ RpcStringBindingCompose(RPC_CSTR, RPC_CSTR, RPC_CSTR, RPC_CSTR, RPC_CSTR, RPC_CSTR *);
___RPC_ENTRY__ RpcStringBindingParse(RPC_CSTR, RPC_CSTR *, RPC_CSTR *, RPC_CSTR *, RPC_CSTR *, RPC_CSTR *);
___RPC_ENTRY__ RpcStringFree(RPC_CSTR *);
___RPC_ENTRY__ RpcNetworkIsProtseqValid(RPC_CSTR);
___RPC_ENTRY__ RpcNetworkInqProtseqs(RPC_PROTSEQ_VECTOR **);
___RPC_ENTRY__ RpcProtseqVectorFree(RPC_PROTSEQ_VECTOR **);
___RPC_ENTRY__ RpcServerUseProtseq(RPC_CSTR, unsigned int, void *);
___RPC_ENTRY__ RpcServerUseProtseqEx(RPC_CSTR, unsigned int, void *, PRPC_POLICY);
___RPC_ENTRY__ RpcServerUseProtseqEp(RPC_CSTR, unsigned int, RPC_CSTR, void *);
___RPC_ENTRY__ RpcServerUseProtseqEpEx(RPC_CSTR, unsigned int, RPC_CSTR, void *, PRPC_POLICY);
___RPC_ENTRY__ RpcServerUseProtseqIf(RPC_CSTR, unsigned int, RPC_IF_HANDLE, void *);
___RPC_ENTRY__ RpcServerUseProtseqIfEx(RPC_CSTR, unsigned int, RPC_IF_HANDLE, void *, PRPC_POLICY);
___RPC_ENTRY__ RpcMgmtInqServerPrincName(RPC_BINDING_HANDLE, unsigned long, RPC_CSTR *);
___RPC_ENTRY__ RpcServerInqDefaultPrincName(unsigned long, RPC_CSTR *);
___RPC_ENTRY__ RpcNsBindingInqEntryName(RPC_BINDING_HANDLE, unsigned long, RPC_CSTR *);
___RPC_ENTRY__ RpcBindingInqAuthClient(RPC_BINDING_HANDLE, RPC_AUTHZ_HANDLE *, RPC_CSTR *, unsigned long *, unsigned long *, unsigned long *);
___RPC_ENTRY__ RpcBindingInqAuthClientEx(RPC_BINDING_HANDLE, RPC_AUTHZ_HANDLE *, RPC_CSTR *, unsigned long *, unsigned long *, unsigned long *, unsigned long);
RPC_STATUS RPC_ENTRY RpcBindingInqAuthInfo(RPC_BINDING_HANDLE,unsigned char **,unsigned long *,unsigned long *,RPC_AUTH_IDENTITY_HANDLE *,unsigned long *);
RPC_STATUS RPC_ENTRY RpcBindingSetAuthInfo(RPC_BINDING_HANDLE,unsigned char *,unsigned long,unsigned long,RPC_AUTH_IDENTITY_HANDLE,unsigned long);

typedef void (__RPC_USER * RPC_AUTH_KEY_RETRIEVAL_FN)(void *, RPC_CSTR, unsigned long, void **, RPC_STATUS *);

___RPC_ENTRY__ RpcServerRegisterAuthInfo(RPC_CSTR, unsigned long, RPC_AUTH_KEY_RETRIEVAL_FN, void *);

___RPC_ENTRY__ UuidToString(UUID *, RPC_CSTR *);
___RPC_ENTRY__ UuidFromString(RPC_CSTR, UUID *);
___RPC_ENTRY__ RpcEpRegister(RPC_IF_HANDLE, RPC_BINDING_VECTOR *, UUID_VECTOR *, RPC_CSTR);
___RPC_ENTRY__ RpcEpRegisterNoReplace(RPC_IF_HANDLE, RPC_BINDING_VECTOR *, UUID_VECTOR *, RPC_CSTR);
___RPC_ENTRY__ DceErrorInqText(RPC_STATUS, RPC_CSTR);
___RPC_ENTRY__ RpcMgmtEpEltInqNext(RPC_EP_INQ_HANDLE, RPC_IF_ID *, RPC_BINDING_HANDLE *, UUID *, RPC_CSTR *);
#endif /* RPC_UNICODE_SUPPORTED */

___RPC_ENTRY__ RpcBindingCopy(RPC_BINDING_HANDLE, RPC_BINDING_HANDLE *);
___RPC_ENTRY__ RpcBindingFree(RPC_BINDING_HANDLE *);
___RPC_ENTRY__ RpcBindingSetOption(RPC_BINDING_HANDLE, unsigned long, ULONG_PTR);
___RPC_ENTRY__ RpcBindingInqOption(RPC_BINDING_HANDLE, unsigned long, ULONG_PTR);
___RPC_ENTRY__ RpcSsGetContextBinding(void *, RPC_BINDING_HANDLE *);
___RPC_ENTRY__ RpcBindingInqObject(RPC_BINDING_HANDLE, UUID *);
___RPC_ENTRY__ RpcBindingReset(RPC_BINDING_HANDLE);
___RPC_ENTRY__ RpcBindingSetObject(RPC_BINDING_HANDLE, UUID *);
___RPC_ENTRY__ RpcMgmtInqDefaultProtectLevel(unsigned long, unsigned long *);

___RPC_ENTRY__ RpcBindingVectorFree(RPC_BINDING_VECTOR * *);
___RPC_ENTRY__ RpcIfInqId(RPC_IF_HANDLE, RPC_IF_ID *);
___RPC_ENTRY__ RpcMgmtInqComTimeout(RPC_BINDING_HANDLE, unsigned int *);
___RPC_ENTRY__ RpcMgmtSetComTimeout(RPC_BINDING_HANDLE, unsigned int);
___RPC_ENTRY__ RpcMgmtSetCancelTimeout(long);
___RPC_ENTRY__ RpcObjectInqType(UUID *, UUID *);
___RPC_ENTRY__ RpcObjectSetInqFn(RPC_OBJECT_INQ_FN *);
___RPC_ENTRY__ RpcObjectSetType(UUID *, UUID *);
___RPC_ENTRY__ RpcServerInqBindings(RPC_BINDING_VECTOR **);
___RPC_ENTRY__ RpcServerInqIf(RPC_IF_HANDLE, UUID *, RPC_MGR_EPV **);
___RPC_ENTRY__ RpcServerListen(unsigned int, unsigned int, unsigned int);
___RPC_ENTRY__ RpcServerRegisterIf(RPC_IF_HANDLE, UUID *, RPC_MGR_EPV *);
___RPC_ENTRY__ RpcServerRegisterIfEx(RPC_IF_HANDLE, UUID *, RPC_MGR_EPV *, unsigned int, unsigned int, RPC_IF_CALLBACK_FN *);
___RPC_ENTRY__ RpcServerRegisterIf2(RPC_IF_HANDLE, UUID *, RPC_MGR_EPV *, unsigned int, unsigned int, unsigned int, RPC_IF_CALLBACK_FN *);
___RPC_ENTRY__ RpcServerUnregisterIf(RPC_IF_HANDLE, UUID *, unsigned int);
___RPC_ENTRY__ RpcServerUnregisterIfEx(RPC_IF_HANDLE, UUID *, int);
___RPC_ENTRY__ RpcServerUseAllProtseqs(unsigned int, void *);
___RPC_ENTRY__ RpcServerUseAllProtseqsEx(unsigned int, void *, PRPC_POLICY);
___RPC_ENTRY__ RpcServerUseAllProtseqsIf(unsigned int, RPC_IF_HANDLE, void *);
___RPC_ENTRY__ RpcServerUseAllProtseqsIfEx(unsigned int, RPC_IF_HANDLE, void *, PRPC_POLICY);
___RPC_VOID__  RpcServerYield(void);
___RPC_ENTRY__ RpcMgmtStatsVectorFree(RPC_STATS_VECTOR **);
___RPC_ENTRY__ RpcMgmtInqStats(RPC_BINDING_HANDLE, RPC_STATS_VECTOR **);
___RPC_ENTRY__ RpcMgmtIsServerListening(RPC_BINDING_HANDLE);
___RPC_ENTRY__ RpcMgmtStopServerListening(RPC_BINDING_HANDLE);
___RPC_ENTRY__ RpcMgmtWaitServerListen(void);
___RPC_ENTRY__ RpcMgmtSetServerStackSize(unsigned long);
___RPC_VOID__  RpcSsDontSerializeContext(void);
___RPC_ENTRY__ RpcMgmtEnableIdleCleanup(void);
___RPC_ENTRY__ RpcMgmtInqIfIds(RPC_BINDING_HANDLE, RPC_IF_ID_VECTOR **);
___RPC_ENTRY__ RpcIfIdVectorFree(RPC_IF_ID_VECTOR **);
___RPC_ENTRY__ RpcEpResolveBinding(RPC_BINDING_HANDLE, RPC_IF_HANDLE);
___RPC_ENTRY__ RpcBindingServerFromClient(RPC_BINDING_HANDLE, RPC_BINDING_HANDLE *);
___RPC_VOID__  DECLSPEC_NORETURN RpcRaiseException(RPC_STATUS);
___RPC_ENTRY__ RpcTestCancel(void);
___RPC_ENTRY__ RpcServerTestCancle(RPC_BINDING_HANDLE);
___RPC_ENTRY__ RpcCancelThread(void *);
___RPC_ENTRY__ RpcCancelThreadEx(void *, long);
___RPC_ENTRY__ UuidCreate(UUID *);
___RPC_ENTRY__ UuidCreateSequential(UUID *);
___RPC_INT__   UuidCompare(UUID *, UUID *, RPC_STATUS *);
___RPC_ENTRY__ UuidCreateNil(UUID *);
___RPC_INT__    UuidEqual(UUID *, UUID *, RPC_STATUS *);
___RPC_USHORT__ UuidHash(UUID *, RPC_STATUS *);
___RPC_INT__    UuidIsNil(UUID *, RPC_STATUS *);
___RPC_ENTRY__  RpcEpUnregister(RPC_IF_HANDLE,RPC_BINDING_VECTOR*,UUID_VECTOR*);
___RPC_ENTRY__  RpcMgmtEpEltInqBegin(RPC_BINDING_HANDLE, unsigned long, RPC_IF_ID *, unsigned long, UUID *, RPC_EP_INQ_HANDLE *);
___RPC_ENTRY__ RpcMgmtEpEltInqDone(RPC_EP_INQ_HANDLE *);
___RPC_ENTRY__ RpcMgmtEpUnregister(RPC_BINDING_HANDLE, RPC_IF_ID *, RPC_BINDING_HANDLE, UUID *);
___RPC_ENTRY__ RpcMgmtSetAuthorizationFn(RPC_MGMT_AUTHORIZATION_FN);

/* FIXME: Not currently supported by MS */
RPC_STATUS RPC_ENTRY RpcMgmtInqParameter(unsigned int,unsigned long*);
RPC_STATUS RPC_ENTRY RpcMgmtSetParameter(unsigned int,unsigned long);
RPC_STATUS RPC_ENTRY RpcMgmtBindingInqParameter(RPC_BINDING_HANDLE,unsigned int,unsigned long*);
RPC_STATUS RPC_ENTRY RpcMgmtBindingSetParameter(RPC_BINDING_HANDLE,unsigned int,unsigned long);
/* End FIXME: Not currently supported by MS */

#if (_WIN32_WINNT >= _WIN32_WINNT_WINXP)
#define RPC_C_AUTHN_DIGEST 21
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WINXP) */

#if (_WIN32_WINNT >= _WIN32_WINNT_WS03)
#define RPC_C_QOS_CAPABILITIES_IGNORE_DELEGATE_FAILURE     0x08
#define RPC_C_QOS_CAPABILITIES_LOCAL_MA_HINT               0x10
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WS03) */

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
#define RPC_C_QOS_CAPABILITIES_SCHANNEL_FULL_AUTH_IDENTITY 0x20
#define RPC_PROTSEQ_TCP  0x1
#define RPC_PROTSEQ_NMP  0x2
#define RPC_PROTSEQ_LRPC 0x3
#define RPC_PROTSEQ_HTTP 0x4
#define RPC_BHT_OBJECT_UUID_VALID 0x1
#define RPC_BHO_NONCAUSAL                0x1
#define RPC_BHO_DONTLINGER               0x2
#define RPC_BHO_EXCLUSIVE_AND_GUARANTEED 0x4
#define RPC_IF_SEC_CACHE_PER_PROC     0x0080
#define RPC_IF_ASYNC_CALLBACK	      0x0100
#define RPC_FW_IF_FLAG_DCOM 0x0001

typedef struct _RPC_BINDING_HANDLE_TEMPLATE_V1_A {
  unsigned long Version;
  unsigned long Flags;
  unsigned long ProtocolSequence;
  RPC_CSTR NetworkAddress;
  RPC_CSTR StringEndpoint;
  union {
    unsigned short *Reserved;
  } u1;
  UUID Object Uuid;
} RPC_BINDING_HANDLE_TEMPLATE_V1_A, *PRPC_BINDING_HANDLE_TEMPLATE_V1_A;

typedef struct _RPC_BINDING_HANDLE_TEMPLATE_V1_W {
  unsigned long Version;
  unsigned long Flags;
  unsigned long ProtocolSequence;
  RPC_WSTR NetworkAddress;
  RPC_WSTR StringEndpoint;
  union {
    unsigned short *Reserved;
  } u1;
  UUID Object Uuid;
} RPC_BINDING_HANDLE_TEMPLATE_V1_W, *PRPC_BINDING_HANDLE_TEMPLATE_V1_W;

#define RPC_BINDING_HANDLE_TEMPLATE_V1 __AW(RPC_BINDING_HANDLE_TEMPLATE_V1_)
#define PRPC_BINDING_HANDLE_TEMPLATE_V1 __AW(PRPC_BINDING_HANDLE_TEMPLATE_V1_)
#define _RPC_BINDING_HANDLE_TEMPLATE_V1 __AW(_RPC_BINDING_HANDLE_TEMPLATE_V1_)

#ifdef _AUTH_IDENTITY_A_DEFINED
typedef struct _RPC_BINDING_HANDLE_SECURITY_V1_A {
  unsigned long Version;
  RPC_CSTR ServerPrincName;
  unsigned long AuthnLevel;
  unsigned long AuthnSvc;
  SEC_WINNT_AUTH_IDENTITY_A *AuthIdentiy;
  RPC_SECURITY_QOS * SecurityQos;
} RPC_BINDING_HANDLE_SECURITY_V1_A, *PRPC_BINDING_HANDLE_SECURITY_V1_A;
#endif /* def _AUTH_IDENTITY_A_DEFINED */

typedef struct _RPC_BINDING_HANDLE_SECURITY_V1_W {
  unsigned long Version;
  RPC_WSTR ServerPrincName;
  unsigned long AuthnLevel;
  unsigned long AuthnSvc;
  SEC_WINNT_AUTH_IDENTITY_W *AuthIdentiy;
  RPC_SECURITY_QOS * SecurityQos;
} RPC_BINDING_HANDLE_SECURITY_V1_W, *PRPC_BINDING_HANDLE_SECURITY_V1_W;

#define RPC_BINDING_HANDLE_SECURITY_V1 __AW(RPC_BINDING_HANDLE_SECURITY_V1_)
#define PRPC_BINDING_HANDLE_SECURITY_V1 __AW(PRPC_BINDING_HANDLE_SECURITY_V1_)
#define _RPC_BINDING_HANDLE_SECURITY_V1 __AW(_RPC_BINDING_HANDLE_SECURITY_V1_)

#ifdef _AUTH_IDENTITY_A_DEFINED
___RPC_ENTRY__ RpcBindingCreateA(RPC_BINDING_HANDLE_TEMPLATE_V1_A *, RPC_BINDING_HANDLE_SECURITY_V1_A *, RPC_BINDING_HANDLE_OPTIONS_V1 *, RPC_BINDING_HANDLE *);
#endif /* def _AUTH_IDENTITY_A_DEFINED */

___RPC_ENTRY__ RpcBindingCreateW(RPC_BINDING_HANDLE_TEMPLATE_V1_W *, RPC_BINDING_HANDLE_SECURITY_V1_W *, RPC_BINDING_HANDLE_OPTIONS_V1 *, RPC_BINDING_HANDLE *);

#define RpcBindingCreate __AW(RpcBindingCreate)

___RPC_ENTRY__ RpcBindingGetTrainingContextHandle(RPC_BINDING_HANDLE, void **);
___RPC_ENTRY__ RpcServerInqBindingHandle(RPC_BINDING_HANDLE *);
___RPC_INT__   RpcExceptionFilter(unsigned long);

#endif /* (_WIN32_WINNT >= _WIN32_WINNT_VISTA) */

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN7)
#define RPC_C_AUTHN_KERNEL 20
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WIN7) */

#include <rpcdcep.h>

#undef ___RPC_ENTRY__
#undef ___RPC_VOID__
#undef ___RPC_INT__
#undef ___RPC_USHORT__
#undef ___RPC_ULONG__

#ifdef __cplusplus
}
#endif

#endif /* ! _RPCDCE_H */
