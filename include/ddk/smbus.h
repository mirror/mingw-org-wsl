/**
 * @file smbus.h
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

/*
 * System Management Bus driver interface
 */

#ifndef __SMBUS_H
#define __SMBUS_H
#pragma GCC system_header

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(SMBCLASS)
  #define SMBCLASSAPI DECLSPEC_IMPORT
#else
  #define SMBCLASSAPI DECLSPEC_EXPORT
#endif

#define SMB_BUS_REQUEST \
  CTL_CODE(FILE_DEVICE_UNKNOWN, 0, METHOD_NEITHER, FILE_ANY_ACCESS)

#define SMB_DEREGISTER_ALARM_NOTIFY \
  CTL_CODE(FILE_DEVICE_UNKNOWN, 2, METHOD_NEITHER, FILE_ANY_ACCESS)

#define SMB_REGISTER_ALARM_NOTIFY \
  CTL_CODE(FILE_DEVICE_UNKNOWN, 1, METHOD_NEITHER, FILE_ANY_ACCESS)


struct _SMB_CLASS;

#define SMB_MAX_DATA_SIZE                 32

/* SMB_REQUEST.Status constants */
#define SMB_STATUS_OK                     0x00
#define SMB_UNKNOWN_FAILURE               0x07
#define SMB_ADDRESS_NOT_ACKNOWLEDGED      0x10
#define SMB_DEVICE_ERROR                  0x11
#define SMB_COMMAND_ACCESS_DENIED         0x12
#define SMB_UNKNOWN_ERROR                 0x13
#define SMB_DEVICE_ACCESS_DENIED          0x17
#define SMB_TIMEOUT                       0x18
#define SMB_UNSUPPORTED_PROTOCOL          0x19
#define SMB_BUS_BUSY                      0x1A

/* SMB_REQUEST.Protocol constants */
#define SMB_WRITE_QUICK                   0x00
#define SMB_READ_QUICK                    0x01
#define SMB_SEND_BYTE                     0x02
#define SMB_RECEIVE_BYTE                  0x03
#define SMB_WRITE_BYTE                    0x04
#define SMB_READ_BYTE                     0x05
#define SMB_WRITE_WORD                    0x06
#define SMB_READ_WORD                     0x07
#define SMB_WRITE_BLOCK                   0x08
#define SMB_READ_BLOCK                    0x09
#define SMB_PROCESS_CALL                  0x0A
#define SMB_MAXIMUM_PROTOCOL              0x0A

typedef struct _SMB_REQUEST {
  UCHAR  Status;
  UCHAR  Protocol;
  UCHAR  Address;
  UCHAR  Command;
  UCHAR  BlockLength;
  UCHAR  Data[SMB_MAX_DATA_SIZE];
} SMB_REQUEST, *PSMB_REQUEST;

typedef VOID STDCALL
(*SMB_ALARM_NOTIFY)(
  PVOID  Context,
  UCHAR  Address,
  USHORT  Data);

typedef struct _SMB_REGISTER_ALARM {
  UCHAR  MinAddress;
  UCHAR  MaxAddress;
  SMB_ALARM_NOTIFY  NotifyFunction;
  PVOID  NotifyContext;
} SMB_REGISTER_ALARM, *PSMB_REGISTER_ALARM;

/* SMB_CLASS.XxxVersion constants */
#define SMB_CLASS_MAJOR_VERSION           0x0001
#define SMB_CLASS_MINOR_VERSION           0x0000

typedef NTSTATUS DDKAPI
(*SMB_RESET_DEVICE)(
  /*IN*/ struct _SMB_CLASS  *SmbClass,
  /*IN*/ PVOID  SmbMiniport);

typedef VOID DDKAPI
(*SMB_START_IO)(
  /*IN*/ struct _SMB_CLASS  *SmbClass,
  /*IN*/ PVOID  SmbMiniport);

typedef NTSTATUS DDKAPI
(*SMB_STOP_DEVICE)(
  /*IN*/ struct _SMB_CLASS  *SmbClass,
  /*IN*/ PVOID  SmbMiniport);

typedef struct _SMB_CLASS {
  USHORT  MajorVersion;
  USHORT  MinorVersion;
  PVOID  Miniport;
  PDEVICE_OBJECT  DeviceObject;
  PDEVICE_OBJECT  PDO;
  PDEVICE_OBJECT  LowerDeviceObject;
  PIRP  CurrentIrp;
  PSMB_REQUEST  CurrentSmb;
  SMB_RESET_DEVICE  ResetDevice;
  SMB_START_IO  StartIo;
  SMB_STOP_DEVICE  StopDevice;
} SMB_CLASS, *PSMB_CLASS;

SMBCLASSAPI
VOID
DDKAPI
SmbClassAlarm(
  /*IN*/ PSMB_CLASS  SmbClass,
  /*IN*/ UCHAR  Address,
  /*IN*/ USHORT  Data);

SMBCLASSAPI
VOID
DDKAPI
SmbClassCompleteRequest(
  /*IN*/ PSMB_CLASS  SmbClass);

typedef NTSTATUS DDKAPI
(*PSMB_INITIALIZE_MINIPORT)(
  /*IN*/ PSMB_CLASS  SmbClass,
  /*IN*/ PVOID  MiniportExtension,
  /*IN*/ PVOID  MiniportContext);

SMBCLASSAPI
NTSTATUS
DDKAPI
SmbClassCreateFdo(
  /*IN*/ PDRIVER_OBJECT  DriverObject,
  /*IN*/ PDEVICE_OBJECT  PDO,
  /*IN*/ ULONG  MiniportExtensionSize,
  /*IN*/ PSMB_INITIALIZE_MINIPORT  MiniportInitialize,
  /*IN*/ PVOID  MiniportContext,
  /*OUT*/ PDEVICE_OBJECT  *FDO);

SMBCLASSAPI
NTSTATUS
DDKAPI
SmbClassInitializeDevice(
  /*IN*/ ULONG  MajorVersion,
  /*IN*/ ULONG  MinorVersion,
  /*IN*/ PDRIVER_OBJECT  DriverObject);

SMBCLASSAPI
VOID
DDKAPI
SmbClassLockDevice(
  /*IN*/ PSMB_CLASS  SmbClass);

SMBCLASSAPI
VOID
DDKAPI
SmbClassUnlockDevice(
  /*IN*/ PSMB_CLASS  SmbClass);

#ifdef __cplusplus
}
#endif

#endif /* __SMBUS_H */
