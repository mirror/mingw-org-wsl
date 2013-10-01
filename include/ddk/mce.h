/**
 * @file @FILENAME@
 * Copyright 2013 MinGW.org project
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
 *
 * This license should reflect the terms of the file LICENSE as found in the
 * repository[1].  The LICENSE file as provided by the MinGW.org development
 * team dictate the license of this file.
 * [1] https://sf.net/
 */
#ifndef _MCE_H
#define _MCE_H

typedef enum {
   HAL_MCE_RECORD
  ,HAL_MCA_RECORD
} MCA_EXCEPTION_TYPE;

#if defined(_X86_) || defined(_AMD64_)
typedef union _MCI_ADDR{
  struct {
    ULONG Address;
    ULONG Reserved;
  } _dummystruct;
  ULONGLONG QuadPart;
} MCI_ADDR, *PMCI_ADDR;
typedef union _MCI_STATS {
  struct {
#if (NTDDI_VERSION > NTDDI_WINXP)
    USHORT McaErrorCode;
#else
    USHORT McaCud;
#endif
#if defined(_X86_)
    USHORT MsCud;
#else
    USHORT ModelErrorCode;
#endif
#if (NTDDI_VERSION > NTDDI_WINXP)
    ULONG OtherInformation : 25;
#else
    ULONG OtherInfo : 25;
#endif
#if (NTDDI_VERSION > NTDDI_WINXP)
    ULONG ContextCorrupt : 1;
#else
    ULONG Damage : 1;
#endif
    ULONG AddressValid : 1;
    ULONG MiscValid : 1;
#if (NTDDI_VERISON > NTDDI_WINXP)
    ULONG ErrorEnabled : 1;
    ULONG UncorrectedError : 1;
    ULONG StatusOverflow : 1;
#else
    ULONG Enabled : 1;
    ULONG Uncorrected : 1;
    ULONG Overflow : 1;
#endif
    ULONG Valid : 1;
  } MciStatus;
#if defined(_X86_)
  ULONGLONG QuadPart;
#else
  ULONG64 QuadPart;
#endif
} MCI_STATS, *PMCI_STATS;

/* Maximum number of x86 registers */
#define MCA_EXTREG_V2MAX 24

typedef struct _MCA_EXCEPTON {
  ULONG VersionNumber;
  MCA_EXCEPTION_TYPE ExceptionType;
  LARGE_INTEGER TimeStamp;
  ULONG ProcessNumber;
  ULONG Reserved1;
  union {
    struct {
      UCHAR BankNumber;
      UCHAR Reserved2[7];
      MCI_STATS Status;
      MCI_ADDR Address;
      ULONGLONG Misc;
    } Mca;
    struct {
      ULONGLONG Address;
      ULONGLONG Type;
    } Mce;
  } u;
#if (NTDDI_VERSION >= NTDDI_WINXP)
  ULONG ExtCnt;
  ULONG Reserved3;
  ULONGLONG ExtReg[MCA_EXTREG_V2MAX];
#endif /* (NTDDI_VERSION >= NTDDI_WINXP) */
} MCA_EXCEPTION, *PMCA_EXCEPTION;

typedef MCA_EXCEPTION CMC_EXCEPTION, *PCMC_EXCEPTION;
typedef MCA_EXCEPTION CPE_EXCEPTION, *PCPE_EXCEPTION;

#if (NTDDI_VERSION >= NTDDI_WINXP)
#define MCA_EXCEPTION_V1_SIZE FIELD_OFFSET(MCA_EXCEPTION, ExtCnt)
#define MCA_EXCEPTION_V2_SIZE sizeof(struct _MCA_EXCEPTION)
#endif /* (NTDDI_VERSION >= NTDDI_WINXP) */

#else
# error The architecture has not been coded.

#endif /* defined(_X86_) || defined(_AMD64_) */
#endif /* ndef _MCE_H */
