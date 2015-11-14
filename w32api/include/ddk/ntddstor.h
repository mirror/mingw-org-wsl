/*
 * ddk/ntddstor.h
 *
 * Windows Device Driver Kit -- storage class IOCTL interface.
 *
 * $Id$
 *
 * Written by Casper S. Hornstrup  <chorns@users.sourceforge.net>
 * Copyright (C) 2002, 2004, 2015, MinGW.org Project.
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
#ifndef _DDK_NTDDSTOR_H
#define _DDK_NTDDSTOR_H
#pragma GCC system_header

#include "ntddk.h"

/* The majority of the IOCTL_STORAGE control code generator macros,
 * structural type STORAGE_BUS_TYPE, and its associated pointer type,
 * are also required to be defined by <winioctl.h>; for convenience
 * of maintenance, share these definitions via <parts/winioctl.h>
 */
#include <parts/winioctl.h>

_BEGIN_C_DECLS

#define IOCTL_STORAGE_GET_MEDIA_SERIAL_NUMBER  __IOCTL_STORAGE_(0x0304,__FILE_AM_BUFFERED)
#define IOCTL_STORAGE_QUERY_PROPERTY	       __IOCTL_STORAGE_(0x0500,__FILE_AM_BUFFERED)

DEFINE_GUID( GUID_DEVINTERFACE_DISK,
    0x53f56307L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b
  );
DEFINE_GUID( GUID_DEVINTERFACE_CDROM,
    0x53f56308L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b
  );
DEFINE_GUID( GUID_DEVINTERFACE_PARTITION,
    0x53f5630aL, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b
  );
DEFINE_GUID( GUID_DEVINTERFACE_TAPE,
    0x53f5630bL, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b
  );
DEFINE_GUID( GUID_DEVINTERFACE_WRITEONCEDISK,
    0x53f5630cL, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b
  );
DEFINE_GUID( GUID_DEVINTERFACE_VOLUME,
    0x53f5630dL, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b
  );
DEFINE_GUID( GUID_DEVINTERFACE_MEDIUMCHANGER,
    0x53f56310L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b
  );
DEFINE_GUID( GUID_DEVINTERFACE_FLOPPY,
    0x53f56311L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b
  );
DEFINE_GUID( GUID_DEVINTERFACE_CDCHANGER,
    0x53f56312L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b
  );
DEFINE_GUID( GUID_DEVINTERFACE_STORAGEPORT,
    0x2accfe60L, 0xc130, 0x11d2, 0xb0, 0x82, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b
  );

typedef
enum _STORAGE_MEDIA_TYPE
{ DDS_4mm		= 0x20,
  MiniQic		= 0x21,
  Travan		= 0x22,
  QIC			= 0x23,
  MP_8mm		= 0x24,
  AME_8mm		= 0x25,
  AIT1_8mm		= 0x26,
  DLT			= 0x27,
  NCTP			= 0x28,
  IBM_3480		= 0x29,
  IBM_3490E		= 0x2A,
  IBM_Magstar_3590	= 0x2B,
  IBM_Magstar_MP	= 0x2C,
  STK_DATA_D3		= 0x2D,
  SONY_DTF		= 0x2E,
  DV_6mm		= 0x2F,
  DMI			= 0x30,
  SONY_D2		= 0x31,
  CLEANER_CARTRIDGE	= 0x32,
  CD_ROM		= 0x33,
  CD_R			= 0x34,
  CD_RW			= 0x35,
  DVD_ROM		= 0x36,
  DVD_R			= 0x37,
  DVD_RW		= 0x38,
  MO_3_RW		= 0x39,
  MO_5_WO		= 0x3A,
  MO_5_RW		= 0x3B,
  MO_5_LIMDOW		= 0x3C,
  PC_5_WO		= 0x3D,
  PC_5_RW		= 0x3E,
  PD_5_RW		= 0x3F,
  ABL_5_WO		= 0x40,
  PINNACLE_APEX_5_RW	= 0x41,
  SONY_12_WO		= 0x42,
  PHILIPS_12_WO		= 0x43,
  HITACHI_12_WO		= 0x44,
  CYGNET_12_WO		= 0x45,
  KODAK_14_WO		= 0x46,
  MO_NFR_525		= 0x47,
  NIKON_12_RW		= 0x48,
  IOMEGA_ZIP		= 0x49,
  IOMEGA_JAZ		= 0x4A,
  SYQUEST_EZ135		= 0x4B,
  SYQUEST_EZFLYER	= 0x4C,
  SYQUEST_SYJET		= 0x4D,
  AVATAR_F2		= 0x4E,
  MP2_8mm		= 0x4F,
  DST_S			= 0x50,
  DST_M			= 0x51,
  DST_L			= 0x52,
  VXATape_1		= 0x53,
  VXATape_2		= 0x54,
  STK_9840		= 0x55,
  LTO_Ultrium		= 0x56,
  LTO_Accelis		= 0x57,
  DVD_RAM		= 0x58,
  AIT_8mm		= 0x59,
  ADR_1			= 0x5A,
  ADR_2			= 0x5B
} STORAGE_MEDIA_TYPE, *PSTORAGE_MEDIA_TYPE;


/* DEVICE_MEDIA_INFO.DeviceSpecific.DiskInfo.MediaCharacteristics constants
 */
#define MEDIA_ERASEABLE           0x00000001
#define MEDIA_WRITE_ONCE          0x00000002
#define MEDIA_READ_ONLY           0x00000004
#define MEDIA_READ_WRITE          0x00000008
#define MEDIA_WRITE_PROTECTED     0x00000100
#define MEDIA_CURRENTLY_MOUNTED   0x80000000

typedef struct _DEVICE_MEDIA_INFO
{ union
  { struct
    { LARGE_INTEGER		  Cylinders;
      STORAGE_MEDIA_TYPE	  MediaType;
      ULONG			  TracksPerCylinder;
      ULONG			  SectorsPerTrack;
      ULONG			  BytesPerSector;
      ULONG			  NumberMediaSides;
      ULONG			  MediaCharacteristics;
    }				DiskInfo;
    struct
    { LARGE_INTEGER		  Cylinders;
      STORAGE_MEDIA_TYPE	  MediaType;
      ULONG			  TracksPerCylinder;
      ULONG			  SectorsPerTrack;
      ULONG			  BytesPerSector;
      ULONG			  NumberMediaSides;
      ULONG			  MediaCharacteristics;
    }				RemovableDiskInfo;
    struct
    { STORAGE_MEDIA_TYPE	  MediaType;
      ULONG			  MediaCharacteristics;
      ULONG			  CurrentBlockSize;
      STORAGE_BUS_TYPE		  BusType;
      union
      { struct
	{ UCHAR			      MediumType;
          UCHAR			      DensityCode;
        }			    ScsiInformation;
      }				  BusSpecificData;
    }				TapeInfo;
  }			      DeviceSpecific;
} DEVICE_MEDIA_INFO, *PDEVICE_MEDIA_INFO;

typedef
struct _GET_MEDIA_TYPES
{ ULONG 		DeviceType;
  ULONG 		MediaInfoCount;
  DEVICE_MEDIA_INFO	MediaInfo[1];
} GET_MEDIA_TYPES, *PGET_MEDIA_TYPES;

typedef
struct _STORAGE_ADAPTER_DESCRIPTOR
{ ULONG 		Version;
  ULONG 		Size;
  ULONG 		MaximumTransferLength;
  ULONG 		MaximumPhysicalPages;
  ULONG 		AlignmentMask;
  BOOLEAN		AdapterUsesPio;
  BOOLEAN		AdapterScansDown;
  BOOLEAN		CommandQueueing;
  BOOLEAN		AcceleratedTransfer;
  STORAGE_BUS_TYPE	BusType;
  USHORT		BusMajorVersion;
  USHORT		BusMinorVersion;
} STORAGE_ADAPTER_DESCRIPTOR, *PSTORAGE_ADAPTER_DESCRIPTOR;

typedef
struct _STORAGE_BUS_RESET_REQUEST
{ UCHAR 		PathId;
} STORAGE_BUS_RESET_REQUEST, *PSTORAGE_BUS_RESET_REQUEST;

typedef
struct _STORAGE_DESCRIPTOR_HEADER
{ ULONG 		Version;
  ULONG 		Size;
} STORAGE_DESCRIPTOR_HEADER, *PSTORAGE_DESCRIPTOR_HEADER;

typedef
struct _STORAGE_DEVICE_DESCRIPTOR
{ ULONG 		Version;
  ULONG 		Size;
  UCHAR 		DeviceType;
  UCHAR 		DeviceTypeModifier;
  BOOLEAN		RemovableMedia;
  BOOLEAN		CommandQueueing;
  ULONG 		VendorIdOffset;
  ULONG 		ProductIdOffset;
  ULONG 		ProductRevisionOffset;
  ULONG 		SerialNumberOffset;
  STORAGE_BUS_TYPE	BusType;
  ULONG 		RawPropertiesLength;
  UCHAR 		RawDeviceProperties[1];
} STORAGE_DEVICE_DESCRIPTOR, *PSTORAGE_DEVICE_DESCRIPTOR;

typedef
struct _STORAGE_DEVICE_ID_DESCRIPTOR
{ ULONG 		Version;
  ULONG 		Size;
  ULONG 		NumberOfIdentifiers;
  UCHAR 		Identifiers[1];
} STORAGE_DEVICE_ID_DESCRIPTOR, *PSTORAGE_DEVICE_ID_DESCRIPTOR;

typedef
struct _STORAGE_DEVICE_NUMBER
{ DEVICE_TYPE		DeviceType;
  ULONG 		DeviceNumber;
  ULONG 		PartitionNumber;
} STORAGE_DEVICE_NUMBER, *PSTORAGE_DEVICE_NUMBER;

typedef
struct _STORAGE_PREDICT_FAILURE
{ ULONG 		PredictFailure;
  UCHAR 		VendorSpecific[512];
} STORAGE_PREDICT_FAILURE, *PSTORAGE_PREDICT_FAILURE;

typedef
enum _STORAGE_PROPERTY_ID
{ StorageDeviceProperty 	= 0,
  StorageAdapterProperty	= 1,
  StorageDeviceIdProperty	= 2
} STORAGE_PROPERTY_ID, *PSTORAGE_PROPERTY_ID;

typedef
enum _STORAGE_QUERY_TYPE
{ PropertyStandardQuery 	= 0,
  PropertyExistsQuery		= 1,
  PropertyMaskQuery		= 2,
  PropertyQueryMaxDefined	= 3
} STORAGE_QUERY_TYPE, *PSTORAGE_QUERY_TYPE;

typedef
struct _STORAGE_PROPERTY_QUERY
{ STORAGE_PROPERTY_ID	PropertyId;
  STORAGE_QUERY_TYPE	QueryType;
  UCHAR 		AdditionalParameters[1];
} STORAGE_PROPERTY_QUERY, *PSTORAGE_PROPERTY_QUERY;

_END_C_DECLS

#endif  /* _DDK_NTDDSTOR_H: $RCSfile$: end of file */
