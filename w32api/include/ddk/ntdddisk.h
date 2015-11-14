/*
 * ddk/ntdddisk.h
 *
 * Driver Development Kit -- Disk IOCTL interface.
 *
 * Written by Casper S. Hornstrup  <chorns@users.sourceforge.net>
 * Copyright (C) 2002-2004, 2015, MinGW.org Project.
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, this permission notice, and the following
 * disclaimer shall be included in all copies or substantial portions of
 * the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OF OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */
#ifndef _DDK_NTDDDISK_H
#define _DDK_NTDDDISK_H
#pragma GCC system_header

#include "ntddk.h"
#include "ntddstor.h"

#include <parts/winioctl.h>

_BEGIN_C_DECLS

#define DD_DISK_DEVICE_NAME		     "\\Device\\UNKNOWN"
#define DD_DISK_DEVICE_NAME_U		    L"\\Device\\UNKNOWN"

#define IOCTL_DISK_CONTROLLER_NUMBER	  __IOCTL_DISK_(0x0011,__FILE_AM_BUFFERED)
#define IOCTL_DISK_INTERNAL_SET_VERIFY	  __IOCTL_DISK_(0x0100,__FILE_AM_BUFFERED)
#define IOCTL_DISK_INTERNAL_CLEAR_VERIFY  __IOCTL_DISK_(0x0101,__FILE_AM_BUFFERED)

#define SMART_GET_VERSION		  __IOCTL_DISK_(0x0020,__FILE_RD_BUFFERED)
#define SMART_RCV_DRIVE_DATA		  __IOCTL_DISK_(0x0022,__FILE_RW_BUFFERED)
#define SMART_SEND_DRIVE_COMMAND	  __IOCTL_DISK_(0x0021,__FILE_RW_BUFFERED)

#define IsFTPartition( PartitionType ) \
 (((PartitionType) & PARTITION_NTFT) && IsRecognizedPartition(PartitionType))

DEFINE_GUID( WMI_DISK_GEOMETRY_GUID,
    0x25007f51L, 0x57c2, 0x11d1, 0xa5, 0x28, 0x0, 0xa0, 0xc9, 0x6, 0x29, 0x10
  );

typedef USHORT BAD_TRACK_NUMBER;
typedef USHORT *PBAD_TRACK_NUMBER;

typedef
struct _DISK_CONTROLLER_NUMBER
{ ULONG 		ControllerNumber;
  ULONG 		DiskNumber;
} DISK_CONTROLLER_NUMBER, *PDISK_CONTROLLER_NUMBER;

typedef SET_PARTITION_INFORMATION SET_PARTITION_INFORMATION_MBR;
typedef PARTITION_INFORMATION_GPT SET_PARTITION_INFORMATION_GPT;

typedef
struct _SET_PARTITION_INFORMATION_EX
{ PARTITION_STYLE			PartitionStyle;
  _ANONYMOUS_UNION union
  { SET_PARTITION_INFORMATION_MBR	Mbr;
    SET_PARTITION_INFORMATION_GPT	Gpt;
  } DUMMYUNIONNAME;
} SET_PARTITION_INFORMATION_EX, *PSET_PARTITION_INFORMATION_EX;

/* GETVERSIONINPARAMS.fCapabilities constants
 */
#define CAP_ATA_ID_CMD                    1
#define CAP_ATAPI_ID_CMD                  2
#define CAP_SMART_CMD                     4

typedef
struct _GETVERSIONINPARAMS
{ UCHAR 		bVersion;
  UCHAR 		bRevision;
  UCHAR 		bReserved;
  UCHAR 		bIDEDeviceMap;
  ULONG 		fCapabilities;
  ULONG 		dwReserved[4];
} GETVERSIONINPARAMS, *PGETVERSIONINPARAMS, *LPGETVERSIONINPARAMS;

/* IDEREGS.bCommandReg constants
 */
#define ATAPI_ID_CMD                      0xA1
#define ID_CMD                            0xEC
#define SMART_CMD                         0xB0

#define SMART_CYL_LOW                     0x4F
#define SMART_CYL_HI                      0xC2

typedef
struct _IDEREGS
{ UCHAR 		bFeaturesReg;
  UCHAR 		bSectorCountReg;
  UCHAR 		bSectorNumberReg;
  UCHAR 		bCylLowReg;
  UCHAR 		bCylHighReg;
  UCHAR 		bDriveHeadReg;
  UCHAR 		bCommandReg;
  UCHAR 		bReserved;
} IDEREGS, *PIDEREGS, *LPIDEREGS;

#include <pshpack1.h>
typedef
struct _SENDCMDINPARAMS
{ ULONG 		cBufferSize;
  IDEREGS		irDriveRegs;
  UCHAR 		bDriveNumber;
  UCHAR 		bReserved[3];
  ULONG 		dwReserved[4];
  UCHAR 		bBuffer[1];
} SENDCMDINPARAMS, *PSENDCMDINPARAMS, *LPSENDCMDINPARAMS;
#include <poppack.h>

/* DRIVERSTATUS.bDriverError constants
 */
#define SMART_NO_ERROR                    0
#define SMART_IDE_ERROR                   1
#define SMART_INVALID_FLAG                2
#define SMART_INVALID_COMMAND             3
#define SMART_INVALID_BUFFER              4
#define SMART_INVALID_DRIVE               5
#define SMART_INVALID_IOCTL               6
#define SMART_ERROR_NO_MEM                7
#define SMART_INVALID_REGISTER            8
#define SMART_NOT_SUPPORTED               9
#define SMART_NO_IDE_DEVICE               10

#define SMART_OFFLINE_ROUTINE_OFFLINE     0
#define SMART_SHORT_SELFTEST_OFFLINE      1
#define SMART_EXTENDED_SELFTEST_OFFLINE   2
#define SMART_ABORT_OFFLINE_SELFTEST      127
#define SMART_SHORT_SELFTEST_CAPTIVE      129
#define SMART_EXTENDED_SELFTEST_CAPTIVE   130

typedef
struct _DRIVERSTATUS
{ UCHAR 		bDriverError;
  UCHAR 		bIDEError;
  UCHAR 		bReserved[2];
  ULONG 		dwReserved[2];
} DRIVERSTATUS, *PDRIVERSTATUS, *LPDRIVERSTATUS;

#define READ_ATTRIBUTE_BUFFER_SIZE        512
#define IDENTIFY_BUFFER_SIZE              512
#define READ_THRESHOLD_BUFFER_SIZE        512
#define SMART_LOG_SECTOR_SIZE             512

#include <pshpack1.h>
typedef
struct _SENDCMDOUTPARAMS
{ ULONG 		cBufferSize;
  DRIVERSTATUS		DriverStatus;
  UCHAR 		bBuffer[1];
} SENDCMDOUTPARAMS, *PSENDCMDOUTPARAMS, *LPSENDCMDOUTPARAMS;
#include <poppack.h>

#define READ_ATTRIBUTES                   0xD0
#define READ_THRESHOLDS                   0xD1
#define ENABLE_DISABLE_AUTOSAVE           0xD2
#define SAVE_ATTRIBUTE_VALUES             0xD3
#define EXECUTE_OFFLINE_DIAGS             0xD4
#define SMART_READ_LOG                    0xD5
#define SMART_WRITE_LOG                   0xd6
#define ENABLE_SMART                      0xD8
#define DISABLE_SMART                     0xD9
#define RETURN_SMART_STATUS               0xDA
#define ENABLE_DISABLE_AUTO_OFFLINE       0xDB

_END_C_DECLS

#endif /* _DDK_NTDDDISK_H: $RCSfile$: end of file */
