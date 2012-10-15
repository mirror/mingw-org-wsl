/**
 * @file winefs.h
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
#ifndef _WINEFS_H
#define _WINEFS_H
#pragma GCC system_header
#include <_mingw.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ___API_DWORD__ WINADVAPI DWORD WINAPI
#define ___API_BOOL__  WINADVAPI BOOL  WINAPI
#define ___API_VOID__  WINADVAPI VOID  WINAPI
#define ___API_DWORD_DEPRECATED__ __MINGW_DEPRECATED (WINADVAPI DWORD WINAPI)
#define ___API_VOID_DEPRECATED__  __MINGW_DEPRECATED WINADVAPI VOID  WINAPI

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN2K)
#define WINEFS_SETUSERKEY_SET_CAPABILITIES 0x00000001

typedef struct _CERTIFICATE_BLOB {
  DWORD dwCertEncodingType;
#ifdef MIDL_PASS
  [range(0,32768)]
#endif
  DWORD cbData;
#ifdef MIDL_PASS
  [size_is(cbData)]
#endif
  PBYTE pbData;
} EFS_CERTIFICATE_BLOB, *PEFS_CERTIFICATE_BLOB;

typedef struct _EFS_HASH_BLOB {
#ifdef MIDL_PASS
  [range(0,100)]
#endif
  DWORD cbData;
#ifdef MIDL_PASS
  [size_is(dbData)]
#endif
  PBYTE pbData;
} EFS_HASH_BLOB, *PEFS_HASH_BLOB;

typedef struct _ENCRYPTION_CERTIFICATE {
  DWORD cbTotalLength;
  SID * PUserSid;
  PEFS_CERTIFICATE_BLOB pCertBlob;
} ENCRYPTION_CERTIFICATE, *PENCRYPTION_CERTIFICATE;

#define MAX_SID_SIZE 256

typedef struct _ENCRYPTION_CERTIFICATE_HASH {
  DWORD cbTotalLength;
  SID * pUserSid;
  PEFS_HASH_BLOB pHash;
#ifdef MIDL_PASS
  [string]
#endif
  LPWSTR lpDisplayInformation;
} ENCRYPTION_CERTIFICATE_HASH, *PENCRYPTION_CERTIFICATE_HASH;

typedef struct _ENCRYPTION_CERTIFICATE_HASH_LIST {
#ifdef MIDL_PASS
  [range(0,500)]
#endif
  DWORD nCert_Hash;
#ifdef MIDL_PASS
  [size_is(nCert_Hash)]
#endif
  PENCRYPTION_CERTIFICATE_HASH * pUsers;
} ENCRYPTION_CERTIFICATE_HASH_LIST, *PENCRYPTION_CERTIFICATE_HASH_LIST;

typedef struct _ENCRYPTION_CERTIFICATE_LIST {
#ifdef MIDL_PASS
  [range(0,500)]
#endif
  DWORD nUsers;
#ifdef MIDL_PASS
  [size_is(nUsers)]
#endif
  PENCRYPTION_CERTIFICATE * pUsers;
} ENCRYPTION_CERTIFICATE_LIST, *PENCRYPTION_CERTIFICATE_LIST;

___API_DWORD__ QueryUsersOnEncryptedFile(LPCWSTR, PENCRYPTION_CERTIFICATE_HASH_LIST);
___API_DWORD__ QueryRecoveryAgentsOnEncryptedFile(LPCWSTR, PENCRYPTION_CERTIFICATE_HASH_LIST);
___API_DWORD__ RemoveUsersFromEncryptedFile(LPCWSTR, PENCRYPTION_CERTIFICATE_HASH_LIST);
___API_DWORD__ AddUsersToEncryptedFile(LPCWSTR, PENCRYPTION_CERTIFICATE_HASH_LIST);
___API_DWORD__ SetUserFileEncryptionKey(PENCRYPTION_CERTIFICATE);
___API_VOID__  FreeEncryptionCertificateHashList(PENCRYPTION_CERTIFICATE_HASH_LIST);
___API_BOOL__  EncryptionDisable(LPCWSTR, BOOL);

#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WIN2K) */

#if (_WIN32_WINNT >= _WIN32_WINNT_WS03 && _WIN32_WINNT < _WIN32_WINNT_WINXP)
___API_DWORD__ DuplicateEncryptionInfoFile(LPCWSTR, LPCWSTR, DWORD, DWORD, CONST LPSECURITY_ATTRIBUTES);
#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WS03 && _WIN32_WINNT < _WIN32_WINNT_WINXP) */

#if (_WIN32_WINNT >= _WIN32_WINNT_WINXP)
#ifndef ALGIDDEF
#define ALGIDDEF
typedef unsigned int ALG_ID;
#endif /* ndef ALGIDDEF */

typedef struct _EFS_RPC_BLOB {
#ifdef MIDL_PASS
  [range(0,266240)]
#endif
  DWORD cbData;
#ifdef MIDL_PASS
  PBYTE pbData;
#endif
} EFS_RPC_BLOB, *PEFS_RPC_BLOB;

typedef struct _EFS_KEY_INFO {
  DWORD  dwVersion;
  ULONG  Entropy;
  ALG_ID Algorithm;
  ULONG  KeyLength;
} EFS_KEY_INFO, *PEFS_KEY_INFO;

___API_DWORD__ DuplicateEncryptionInfoFile(LPCWSTR, LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES);

#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WINXP) */

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
typedef struct _EFS_PIN_BLOB {
#ifdef MIDL_PASS
  [range(0,8)]
#endif
  DWORD cbPadding;
#ifdef MIDL_PASS
  [range(0,2048)]
#endif
  DWORD cbData;
#ifdef MIDL_PASS
  [size_is(cbData+cbPadding)]
#endif
  PBYTE pbData;
} EFS_PIN_BLOB, *PEFS_PIN_BLOB;

typedef struct _EFS_DECRYPTION_STATUS_INFO {
  DWORD dwDecryptionError;
  DWORD dwHashOffset;
  DWORD cbHash;
} EFS_DECRYPTION_STATUS_INFO, *PEFS_DECRYPTION_STATUS_INFO;

typedef struct _EFS_ENCRYPTION_STATUS_INFO {
  BOOL  bHasCurrentKey;
  DWORD dwEncryptionError;
} EFS_ENCRYPTION_STATUS_INFO, *PEFS_ENCRYPTION_STATUS_INFO;

#define EFS_METADATA_ADD_USER	  0x00000001
#define EFS_METADATA_REMOVE_USER  0x00000002
#define EFS_METADATA_REPLACE_USER 0x00000004
#define EFS_METADATA_GENERAL_OP	  0x00000008

typedef struct _ENCRYPTED_FILE_METADATA_SIGNATURE {
  DWORD	                            dwEfsAccessType;
  PENCRYPTION_CERTIFICATE_HASH_LIST pCertificatesAdded;
  PENCRYPTION_CERTIFICATE           pEncryptionCertificate;
  PEFS_RPC_BLOB	                    pEfsStreamSignature;
} ENCRYPTED_FILE_METADATA_SIGNATURE, *PENCRYPTED_FILE_METADATA_SIGNATURE;

___API_DWORD__ SetUserFileEncryptionKeyEx(PENCRYPTION_CERTIFICATE, DWORD, DWORD, LPVOID);

___API_DWORD_DEPRECATED__ GetEncryptedFileMetadata(LPCWSTR, PDWORD, PBYTE);
___API_DWORD_DEPRECATED__ SetEncryptedFileMetadata(LPCWSTR, PBYTE, PBYTE, PENCRYPTION_CERTIFICATE_HASH, DWORD, PENCRYPTION_CERTIFICATE_HASH_LIST);
___API_VOID_DEPRICATED__  FreeEncryptedFileMetadata(PBYTE);

#endif /* (_WIN32_WINNT >= _WIN32_WINNT_VISTA) */

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN7)
typedef struct _EFS_COMPATIBILITY_INFO {
  DWORD EfsVersion;
} EFS_COMPATIBILITY_INFO, *PEFS_COMPATIBILITY_INFO;

#endif /* (_WIN32_WINNT >= _WIN32_WINNT_WIN7) */

#undef ___API_DWORD__
#undef ___API_BOOL__
#undef ___API_VOID__
#undef ___API_DWORD_DEPRECATED__
#undef ___API_VOID_DEPRECATED__

#ifdef __cplusplus
}
#endif

#endif /* ndef _WINEFS_H */
