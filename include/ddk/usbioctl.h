/**
 * @file usbioctl.h
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
 * USB IOCTL interface.
 */

#ifndef __USBIOCTL_H
#define __USBIOCTL_H
#pragma GCC system_header

#ifdef __cplusplus
extern "C" {
#endif

#include "ntddk.h"
#include "usb100.h"
#include "usbiodef.h"

#define USBD_PORT_ENABLED                 1
#define USBD_PORT_CONNECTED               2

#define IOCTL_INTERNAL_USB_CYCLE_PORT \
  CTL_CODE(FILE_DEVICE_USB, USB_CYCLE_PORT, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_INTERNAL_USB_ENABLE_PORT \
  CTL_CODE(FILE_DEVICE_USB, USB_ENABLE_PORT, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_INTERNAL_USB_GET_BUS_INFO \
  CTL_CODE(FILE_DEVICE_USB, USB_GET_BUS_INFO, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_INTERNAL_USB_GET_BUSGUID_INFO \
  CTL_CODE(FILE_DEVICE_USB, USB_GET_BUSGUID_INFO, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_INTERNAL_USB_GET_CONTROLLER_NAME \
  CTL_CODE(FILE_DEVICE_USB, USB_GET_CONTROLLER_NAME, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_INTERNAL_USB_GET_DEVICE_HANDLE \
  CTL_CODE(FILE_DEVICE_USB, USB_GET_DEVICE_HANDLE, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_INTERNAL_USB_GET_HUB_COUNT \
  CTL_CODE(FILE_DEVICE_USB, USB_GET_HUB_COUNT, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_INTERNAL_USB_GET_HUB_NAME \
  CTL_CODE(FILE_DEVICE_USB, USB_GET_HUB_NAME, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_INTERNAL_USB_GET_PARENT_HUB_INFO \
  CTL_CODE(FILE_DEVICE_USB, USB_GET_PARENT_HUB_INFO, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_INTERNAL_USB_GET_PORT_STATUS \
  CTL_CODE(FILE_DEVICE_USB, USB_GET_PORT_STATUS, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_INTERNAL_USB_RESET_PORT \
  CTL_CODE(FILE_DEVICE_USB, USB_RESET_PORT, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_INTERNAL_USB_GET_ROOTHUB_PDO \
  CTL_CODE(FILE_DEVICE_USB, USB_GET_ROOTHUB_PDO, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_INTERNAL_USB_SUBMIT_IDLE_NOTIFICATION \
  CTL_CODE(FILE_DEVICE_USB, USB_IDLE_NOTIFICATION, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_INTERNAL_USB_SUBMIT_URB  \
  CTL_CODE(FILE_DEVICE_USB, USB_SUBMIT_URB, METHOD_NEITHER, FILE_ANY_ACCESS)


#define IOCTL_USB_DIAG_IGNORE_HUBS_ON \
  CTL_CODE(FILE_DEVICE_USB, USB_DIAG_IGNORE_HUBS_ON, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_USB_DIAG_IGNORE_HUBS_OFF \
  CTL_CODE(FILE_DEVICE_USB, USB_DIAG_IGNORE_HUBS_OFF, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_USB_DIAGNOSTIC_MODE_OFF \
  CTL_CODE(FILE_DEVICE_USB, HCD_DIAGNOSTIC_MODE_OFF, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_USB_DIAGNOSTIC_MODE_ON \
  CTL_CODE(FILE_DEVICE_USB, HCD_DIAGNOSTIC_MODE_ON, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION \
  CTL_CODE(FILE_DEVICE_USB, USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_USB_GET_HUB_CAPABILITIES \
  CTL_CODE(FILE_DEVICE_USB, USB_GET_HUB_CAPABILITIES, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_USB_GET_ROOT_HUB_NAME \
  CTL_CODE(FILE_DEVICE_USB, HCD_GET_ROOT_HUB_NAME, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_GET_HCD_DRIVERKEY_NAME \
  CTL_CODE(FILE_DEVICE_USB, HCD_GET_DRIVERKEY_NAME, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_USB_GET_NODE_INFORMATION \
  CTL_CODE(FILE_DEVICE_USB, USB_GET_NODE_INFORMATION, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_USB_GET_NODE_CONNECTION_INFORMATION \
  CTL_CODE(FILE_DEVICE_USB, USB_GET_NODE_CONNECTION_INFORMATION, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_USB_GET_NODE_CONNECTION_ATTRIBUTES \
  CTL_CODE(FILE_DEVICE_USB, USB_GET_NODE_CONNECTION_ATTRIBUTES, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_USB_GET_NODE_CONNECTION_NAME \
  CTL_CODE(FILE_DEVICE_USB, USB_GET_NODE_CONNECTION_NAME, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_USB_GET_NODE_CONNECTION_DRIVERKEY_NAME \
  CTL_CODE(FILE_DEVICE_USB, USB_GET_NODE_CONNECTION_DRIVERKEY_NAME, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_USB_HCD_DISABLE_PORT \
  CTL_CODE(FILE_DEVICE_USB, HCD_DISABLE_PORT, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_USB_HCD_ENABLE_PORT \
  CTL_CODE(FILE_DEVICE_USB, HCD_ENABLE_PORT, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_USB_HCD_GET_STATS_1 \
  CTL_CODE(FILE_DEVICE_USB, HCD_GET_STATS_1, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_USB_HCD_GET_STATS_2 \
  CTL_CODE(FILE_DEVICE_USB, HCD_GET_STATS_2, METHOD_BUFFERED, FILE_ANY_ACCESS)


typedef struct _USB_HUB_CAPABILITIES {
  ULONG  HubIs2xCapable : 1;
} USB_HUB_CAPABILITIES, *PUSB_HUB_CAPABILITIES;

typedef enum _USB_CONNECTION_STATUS {
	NoDeviceConnected,
	DeviceConnected,
	DeviceFailedEnumeration,
	DeviceGeneralFailure,
	DeviceCausedOvercurrent,
	DeviceNotEnoughPower,
	DeviceNotEnoughBandwidth,
	DeviceHubNestedTooDeeply,
	DeviceInLegacyHub
} USB_CONNECTION_STATUS, *PUSB_CONNECTION_STATUS;

#include <pshpack1.h>

typedef struct _USB_DESCRIPTOR_REQUEST {
	ULONG  ConnectionIndex;
	struct {
		UCHAR  bmRequest;
		UCHAR  bRequest;
		USHORT  wValue;
		USHORT  wIndex;
		USHORT  wLength;
	} SetupPacket;
	UCHAR  Data[0];
} USB_DESCRIPTOR_REQUEST, *PUSB_DESCRIPTOR_REQUEST;

typedef struct _USB_HCD_DRIVERKEY_NAME {
	ULONG  ActualLength;
	WCHAR  DriverKeyName[1];
} USB_HCD_DRIVERKEY_NAME, *PUSB_HCD_DRIVERKEY_NAME;

typedef struct _HCD_ISO_STAT_COUNTERS {
	USHORT  LateUrbs;
	USHORT  DoubleBufferedPackets;
	USHORT  TransfersCF_5ms;
	USHORT  TransfersCF_2ms;
	USHORT  TransfersCF_1ms;
	USHORT  MaxInterruptLatency;
	USHORT  BadStartFrame;
	USHORT  StaleUrbs;
	USHORT  IsoPacketNotAccesed;
	USHORT  IsoPacketHWError;
	USHORT  SmallestUrbPacketCount;
	USHORT  LargestUrbPacketCount;
	USHORT  IsoCRC_Error;
	USHORT  IsoOVERRUN_Error;
	USHORT  IsoINTERNAL_Error;
	USHORT  IsoUNKNOWN_Error;
	ULONG  IsoBytesTransferred;
	USHORT  LateMissedCount;
	USHORT  HWIsoMissedCount;
	ULONG  Reserved7[8];
} HCD_ISO_STAT_COUNTERS, *PHCD_ISO_STAT_COUNTERS;

typedef struct _HCD_STAT_COUNTERS {
	ULONG  BytesTransferred;
	USHORT  IsoMissedCount;
	USHORT  DataOverrunErrorCount;
	USHORT  CrcErrorCount;
	USHORT  ScheduleOverrunCount;
	USHORT  TimeoutErrorCount;
	USHORT  InternalHcErrorCount;
	USHORT  BufferOverrunErrorCount;
	USHORT  SWErrorCount;
	USHORT  StallPidCount;
	USHORT  PortDisableCount;
} HCD_STAT_COUNTERS, *PHCD_STAT_COUNTERS;

typedef struct _HCD_STAT_INFORMATION_1 {
	ULONG  Reserved1;
	ULONG  Reserved2;
	ULONG  ResetCounters;
	LARGE_INTEGER  TimeRead;
	HCD_STAT_COUNTERS  Counters;
} HCD_STAT_INFORMATION_1, *PHCD_STAT_INFORMATION_1;

typedef struct _HCD_STAT_INFORMATION_2 {
	ULONG  Reserved1;
	ULONG  Reserved2;
	ULONG  ResetCounters;
	LARGE_INTEGER  TimeRead;
	LONG  LockedMemoryUsed;
	HCD_STAT_COUNTERS  Counters;
	HCD_ISO_STAT_COUNTERS  IsoCounters;
} HCD_STAT_INFORMATION_2, *PHCD_STAT_INFORMATION_2;

typedef struct _USB_HUB_INFORMATION {
	USB_HUB_DESCRIPTOR  HubDescriptor;
	BOOLEAN  HubIsBusPowered;
} USB_HUB_INFORMATION, *PUSB_HUB_INFORMATION;

typedef struct _USB_HUB_NAME {
	ULONG  ActualLength;
	WCHAR  HubName[1];
} USB_HUB_NAME, *PUSB_HUB_NAME;

typedef enum _USB_HUB_NODE {
	UsbHub,
	UsbMIParent
} USB_HUB_NODE;

typedef VOID STDCALL
(*USB_IDLE_CALLBACK)(
  PVOID  Context);

typedef struct _USB_IDLE_CALLBACK_INFO {
	USB_IDLE_CALLBACK  IdleCallback;
	PVOID  IdleContext;
} USB_IDLE_CALLBACK_INFO, *PUSB_IDLE_CALLBACK_INFO;

typedef struct _USB_NODE_CONNECTION_ATTRIBUTES {
	ULONG  ConnectionIndex;
	USB_CONNECTION_STATUS  ConnectionStatus;
	ULONG  PortAttributes;
} USB_NODE_CONNECTION_ATTRIBUTES, *PUSB_NODE_CONNECTION_ATTRIBUTES;

typedef struct _USB_NODE_CONNECTION_DRIVERKEY_NAME {
	ULONG  ConnectionIndex;
	ULONG  ActualLength;
	WCHAR  DriverKeyName[1];
} USB_NODE_CONNECTION_DRIVERKEY_NAME, *PUSB_NODE_CONNECTION_DRIVERKEY_NAME;

typedef struct _USB_PIPE_INFO {
	USB_ENDPOINT_DESCRIPTOR  EndpointDescriptor;
	ULONG  ScheduleOffset;
} USB_PIPE_INFO, *PUSB_PIPE_INFO;

typedef struct _USB_NODE_CONNECTION_INFORMATION {
	ULONG  ConnectionIndex;
	USB_DEVICE_DESCRIPTOR  DeviceDescriptor;
	UCHAR  CurrentConfigurationValue;
	BOOLEAN  LowSpeed;
	BOOLEAN  DeviceIsHub;
	USHORT  DeviceAddress;
	ULONG  NumberOfOpenPipes;
	USB_CONNECTION_STATUS  ConnectionStatus;
	USB_PIPE_INFO  PipeList[0];
} USB_NODE_CONNECTION_INFORMATION, *PUSB_NODE_CONNECTION_INFORMATION;

typedef struct _USB_NODE_CONNECTION_NAME {
	ULONG  ConnectionIndex;
	ULONG  ActualLength;
	WCHAR  NodeName[1];
} USB_NODE_CONNECTION_NAME, *PUSB_NODE_CONNECTION_NAME;

typedef struct _USB_MI_PARENT_INFORMATION {
  ULONG  NumberOfInterfaces;
} USB_MI_PARENT_INFORMATION, *PUSB_MI_PARENT_INFORMATION;

typedef struct _USB_NODE_INFORMATION {
	USB_HUB_NODE  NodeType;
	union {
		USB_HUB_INFORMATION  HubInformation;
		USB_MI_PARENT_INFORMATION  MiParentInformation;
	} u;
} USB_NODE_INFORMATION, *PUSB_NODE_INFORMATION;

#define WMI_USB_DRIVER_INFORMATION        0
#define WMI_USB_DRIVER_NOTIFICATION       1
#define WMI_USB_POWER_DEVICE_ENABLE       2

typedef enum _USB_NOTIFICATION_TYPE {
	EnumerationFailure = 0,
	InsufficentBandwidth,
	InsufficentPower,
	OverCurrent,
	ResetOvercurrent,
	AcquireBusInfo,
	AcquireHubName,
	AcquireControllerName,
	HubOvercurrent,
	HubPowerChange,
	HubNestedTooDeeply,
	ModernDeviceInLegacyHub
} USB_NOTIFICATION_TYPE;

typedef struct _USB_ACQUIRE_INFO {
	USB_NOTIFICATION_TYPE  NotificationType;
	ULONG  TotalSize;
	WCHAR  Buffer[1];
} USB_ACQUIRE_INFO, *PUSB_ACQUIRE_INFO;

typedef struct _USB_NOTIFICATION {
  USB_NOTIFICATION_TYPE  NotificationType;
} USB_NOTIFICATION, *PUSB_NOTIFICATION;

typedef struct _USB_BUS_NOTIFICATION {
	USB_NOTIFICATION_TYPE  NotificationType;
	ULONG  TotalBandwidth;
	ULONG  ConsumedBandwidth;
	ULONG  ControllerNameLength;
} USB_BUS_NOTIFICATION, *PUSB_BUS_NOTIFICATION;

typedef struct _USB_CONNECTION_NOTIFICATION {
	USB_NOTIFICATION_TYPE  NotificationType;
	ULONG  ConnectionNumber;
	ULONG  RequestedBandwidth;     
	ULONG  EnumerationFailReason;
	ULONG  PowerRequested;
	ULONG  HubNameLength;
} USB_CONNECTION_NOTIFICATION, *PUSB_CONNECTION_NOTIFICATION;

typedef struct _USB_ROOT_HUB_NAME {
	ULONG  ActualLength;
	WCHAR  RootHubName[1];
} USB_ROOT_HUB_NAME, *PUSB_ROOT_HUB_NAME;

#include <poppack.h>

#ifdef __cplusplus
}
#endif

#endif /* __USBIOCTL_H */
