/*
 * parts/winioctl.h
 *
 * Internal header file, declaring elements of the <winioctl.h> header
 * which are also expected to be exposed when including certain of the
 * device driver development kit headers.
 *
 * $Id$
 *
 * Written by Keith Marshall  <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2015, MinGW.org Project.
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
#undef __need_ddk_winddk_includes
#undef __need_ddk_ntddstor_includes
#undef __need_ddk_ntdddisk_includes

#undef __FAKE_WINIOCTL_H_SOURCED

#ifdef _WINIOCTL_H
/* The client has included <winioctl.h>; we need to ensure that all
 * of the separate fragments of this file are processed.
 */
# define __need_ddk_ntdddisk_includes ! defined __have_ddk_ntdddisk_includes
# define __need_ddk_ntddstor_includes ! defined __have_ddk_ntddstor_includes
# define __need_ddk_winddk_includes ! defined __have_ddk_winddk_includes

#else
/* The client has not (yet) included <winioctl.h>, but has included
 * at least one of the Windows DDK headers which is dependent on one
 * or more fragments of this file; we must select whichever of these
 * fragments may be required.
 */
# ifdef _DDK_WINDDK_H
  /* The <ddk/winddk.h> header has been included; fake inclusion from
   * <winioctl.h>, as expected, and select the <ddk/windkk.h> fragment.
   */
#  define __FAKE_WINIOCTL_H_SOURCED
#  define __need_ddk_winddk_includes ! defined __have_ddk_winddk_includes
# endif

# ifdef _DDK_NTDDSTOR_H
  /* The <ddk/ntddstor.h> header has been included; fake inclusion from
   * <winioctl.h>, as expected, and select the <ddk/ntddstor.h> fragment.
   */
#  define __FAKE_WINIOCTL_H_SOURCED
#  define __need_ddk_ntddstor_includes ! defined __have_ddk_ntddstor_includes
# endif

# ifdef _DDK_NTDDDISK_H
  /* The <ddk/ntdddisk.h> header has been included; fake inclusion from
   * <winioctl.h>, as expected, and select the <ddk/ntdddisk.h> fragment.
   */
#  define __FAKE_WINIOCTL_H_SOURCED
#  define __need_ddk_ntdddisk_includes ! defined __have_ddk_ntdddisk_includes
# endif

# ifndef __FAKE_WINIOCTL_H_SOURCED
  /* This file has been included by an unexpected client; refuse to
   * process this unauthorized request.
   */
#  error "Never include <parts/winioctl.h> directly; use <winioctl.h> instead"
# endif
# undef __FAKE_WINIOCTL_H_SOURCED
#endif

#if __need_ddk_winddk_includes
/* This fragment provides content common to both <winioctl.h> and
 * <ddk/winddk.h>; since both <ddk/ntddstor.h> and <ddk/ntdddisk.h>
 * also (indirectly) include <ddk/winddk.h>, this fragment is always
 * processed before any other, regardless of how this file comes to
 * be included.
 */
#define CTL_CODE(DT,FN,M,A)		(((DT)<<16)|((FN)<<2)|((A)<<14)|(M))
#define DEVICE_TYPE_FROM_CTL_CODE(C)	(((ULONG)((C) & (0xFFFF0000)) >> 16)

typedef ULONG DEVICE_TYPE;
enum
{ FILE_DEVICE_BEEP			= 0x00000001UL,
  FILE_DEVICE_CD_ROM			= 0x00000002UL,
  FILE_DEVICE_CD_ROM_FILE_SYSTEM	= 0x00000003UL,
  FILE_DEVICE_CONTROLLER		= 0x00000004UL,
  FILE_DEVICE_DATALINK			= 0x00000005UL,
  FILE_DEVICE_DFS			= 0x00000006UL,
  FILE_DEVICE_DISK			= 0x00000007UL,
  FILE_DEVICE_DISK_FILE_SYSTEM		= 0x00000008UL,
  FILE_DEVICE_FILE_SYSTEM		= 0x00000009UL,
  FILE_DEVICE_INPORT_PORT		= 0x0000000AUL,
  FILE_DEVICE_KEYBOARD			= 0x0000000BUL,
  FILE_DEVICE_MAILSLOT			= 0x0000000CUL,
  FILE_DEVICE_MIDI_IN			= 0x0000000DUL,
  FILE_DEVICE_MIDI_OUT			= 0x0000000EUL,
  FILE_DEVICE_MOUSE			= 0x0000000FUL,
  FILE_DEVICE_MULTI_UNC_PROVIDER	= 0x00000010UL,
  FILE_DEVICE_NAMED_PIPE		= 0x00000011UL,
  FILE_DEVICE_NETWORK			= 0x00000012UL,
  FILE_DEVICE_NETWORK_BROWSER		= 0x00000013UL,
  FILE_DEVICE_NETWORK_FILE_SYSTEM	= 0x00000014UL,
  FILE_DEVICE_NULL			= 0x00000015UL,
  FILE_DEVICE_PARALLEL_PORT		= 0x00000016UL,
  FILE_DEVICE_PHYSICAL_NETCARD		= 0x00000017UL,
  FILE_DEVICE_PRINTER			= 0x00000018UL,
  FILE_DEVICE_SCANNER			= 0x00000019UL,
  FILE_DEVICE_SERIAL_MOUSE_PORT 	= 0x0000001AUL,
  FILE_DEVICE_SERIAL_PORT		= 0x0000001BUL,
  FILE_DEVICE_SCREEN			= 0x0000001CUL,
  FILE_DEVICE_SOUND			= 0x0000001DUL,
  FILE_DEVICE_STREAMS			= 0x0000001EUL,
  FILE_DEVICE_TAPE			= 0x0000001FUL,
  FILE_DEVICE_TAPE_FILE_SYSTEM		= 0x00000020UL,
  FILE_DEVICE_TRANSPORT 		= 0x00000021UL,
  FILE_DEVICE_UNKNOWN			= 0x00000022UL,
  FILE_DEVICE_VIDEO			= 0x00000023UL,
  FILE_DEVICE_VIRTUAL_DISK		= 0x00000024UL,
  FILE_DEVICE_WAVE_IN			= 0x00000025UL,
  FILE_DEVICE_WAVE_OUT			= 0x00000026UL,
  FILE_DEVICE_8042_PORT			= 0x00000027UL,
  FILE_DEVICE_NETWORK_REDIRECTOR	= 0x00000028UL,
  FILE_DEVICE_BATTERY			= 0x00000029UL,
  FILE_DEVICE_BUS_EXTENDER		= 0x0000002AUL,
  FILE_DEVICE_MODEM			= 0x0000002BUL,
  FILE_DEVICE_VDM			= 0x0000002CUL,
  FILE_DEVICE_MASS_STORAGE		= 0x0000002DUL,
  FILE_DEVICE_SMB			= 0x0000002EUL,
  FILE_DEVICE_KS			= 0x0000002FUL,
  FILE_DEVICE_CHANGER			= 0x00000030UL,
  FILE_DEVICE_SMARTCARD 		= 0x00000031UL,
  FILE_DEVICE_ACPI			= 0x00000032UL,
  FILE_DEVICE_DVD			= 0x00000033UL,
  FILE_DEVICE_FULLSCREEN_VIDEO		= 0x00000034UL,
  FILE_DEVICE_DFS_FILE_SYSTEM		= 0x00000035UL,
  FILE_DEVICE_DFS_VOLUME		= 0x00000036UL,
  FILE_DEVICE_SERENUM			= 0x00000037UL,
  FILE_DEVICE_TERMSRV			= 0x00000038UL,
  FILE_DEVICE_KSEC			= 0x00000039UL,
  FILE_DEVICE_FIPS			= 0x0000003AUL
};

enum
{ FILE_ANY_ACCESS			= 0x00000000UL,
  FILE_SPECIAL_ACCESS			= FILE_ANY_ACCESS,
  FILE_READ_ACCESS			= 0x00000001UL,
  FILE_WRITE_ACCESS			= 0x00000002UL
};

enum
{ METHOD_BUFFERED			= 0,
  METHOD_IN_DIRECT			= 1,
  METHOD_OUT_DIRECT			= 2,
  METHOD_NEITHER			= 3
};

/* Some derived convenience macros; Microsoft do not specify these,
 * but they help to keep the CTL_CODE specifications tidy.
 */
#define __FILE_RW_ACCESS	(FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define __FILE_AM_BUFFERED	 METHOD_BUFFERED, FILE_ANY_ACCESS
#define __FILE_RD_BUFFERED	 METHOD_BUFFERED, FILE_READ_ACCESS
#define __FILE_RW_BUFFERED	 METHOD_BUFFERED, __FILE_RW_ACCESS

typedef
struct _DRIVE_LAYOUT_INFORMATION_MBR
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552668(v=vs.85).aspx */
{ ULONG 	 Signature;
} DRIVE_LAYOUT_INFORMATION_MBR, *PDRIVE_LAYOUT_INFORMATION_MBR;

typedef
struct _DRIVE_LAYOUT_INFORMATION_GPT
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552664(v=vs.85).aspx */
{ GUID		 DiskId;
  LARGE_INTEGER  StartingUsableOffset;
  LARGE_INTEGER  UsableLength;
  ULONG		 MaxPartitionCount;
} DRIVE_LAYOUT_INFORMATION_GPT, *PDRIVE_LAYOUT_INFORMATION_GPT;

typedef
struct _PARTITION_INFORMATION_MBR
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff563767(v=vs.85).aspx */
{ UCHAR 	PartitionType;
  BOOLEAN	BootIndicator;
  BOOLEAN	RecognizedPartition;
  ULONG 	HiddenSectors;
} PARTITION_INFORMATION_MBR, *PPARTITION_INFORMATION_MBR;

typedef
enum _PARTITION_STYLE
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff563773(v=vs.85).aspx */
{ PARTITION_STYLE_MBR		= 0,
  PARTITION_STYLE_GPT		= 1,
  PARTITION_STYLE_RAW		= 2
} PARTITION_STYLE;

typedef
struct _CREATE_DISK_MBR
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552490(v=vs.85).aspx */
{ ULONG 	Signature;
} CREATE_DISK_MBR, *PCREATE_DISK_MBR;

typedef
struct _CREATE_DISK_GPT
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552486(v=vs.85).aspx */
{ GUID		DiskId;
  ULONG 	MaxPartitionCount;
} CREATE_DISK_GPT, *PCREATE_DISK_GPT;

typedef
struct _CREATE_DISK
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552490(v=vs.85).aspx */
{ PARTITION_STYLE	  PartitionStyle;
  _ANONYMOUS_UNION union
  { CREATE_DISK_MBR	  Mbr;
    CREATE_DISK_GPT	  Gpt;
  } DUMMYUNIONNAME;
} CREATE_DISK, *PCREATE_DISK;

# ifndef _WINIOCTL_H
  /* When not sourced from <winioctrl.h>, this fragment is intended to
   * be sourced exclusively from <ddk/winddk.h>; in this latter case, we
   * explicitly DO NOT want to process fragments which relate to either
   * the <ddk/ntddstor.h> or <ddk/nfdddisk.h> header files, (for which
   * the respective fragments appear later in this file).
   */
#  undef __need_ddk_ntddstor_includes
#  undef __need_ddk_ntdddisk_includes
# endif
# define __have_ddk_winddk_includes
#endif

#if __need_ddk_ntddstor_includes
/* This fragment provides content common to both <winioctl.h> and
 * <ddk/ntddstor.h>; since <ddk/ntddstor.h> includes <ddk/winddk.h>,
 * and is itself included by <ddk/ntdddisk.h>, this fragment will be
 * processed between the fragment associated with <ddk/winddk.h>,
 * and that associated with <ddk/ntdddisk.h>
 */
#define __IOCTL_STORAGE_(FN,M,A)	    CTL_CODE(IOCTL_STORAGE_BASE,(FN),(M),(A))

#define IOCTL_STORAGE_BASE		    FILE_DEVICE_MASS_STORAGE
#define IOCTL_STORAGE_CHECK_VERIFY	  __IOCTL_STORAGE_(0x0200,__FILE_RD_BUFFERED)
#define IOCTL_STORAGE_CHECK_VERIFY2	  __IOCTL_STORAGE_(0x0200,__FILE_AM_BUFFERED)
#define IOCTL_STORAGE_MEDIA_REMOVAL	  __IOCTL_STORAGE_(0x0201,__FILE_RD_BUFFERED)
#define IOCTL_STORAGE_EJECT_MEDIA	  __IOCTL_STORAGE_(0x0202,__FILE_RD_BUFFERED)
#define IOCTL_STORAGE_LOAD_MEDIA	  __IOCTL_STORAGE_(0x0203,__FILE_RD_BUFFERED)
#define IOCTL_STORAGE_LOAD_MEDIA2	  __IOCTL_STORAGE_(0x0203,__FILE_AM_BUFFERED)
#define IOCTL_STORAGE_RESERVE		  __IOCTL_STORAGE_(0x0204,__FILE_RD_BUFFERED)
#define IOCTL_STORAGE_RELEASE		  __IOCTL_STORAGE_(0x0205,__FILE_RD_BUFFERED)
#define IOCTL_STORAGE_FIND_NEW_DEVICES	  __IOCTL_STORAGE_(0x0206,__FILE_RD_BUFFERED)
#define IOCTL_STORAGE_EJECTION_CONTROL	  __IOCTL_STORAGE_(0x0250,__FILE_AM_BUFFERED)
#define IOCTL_STORAGE_MCN_CONTROL	  __IOCTL_STORAGE_(0x0251,__FILE_AM_BUFFERED)
#define IOCTL_STORAGE_GET_MEDIA_TYPES	  __IOCTL_STORAGE_(0x0300,__FILE_AM_BUFFERED)
#define IOCTL_STORAGE_GET_MEDIA_TYPES_EX  __IOCTL_STORAGE_(0x0301,__FILE_AM_BUFFERED)
#define IOCTL_STORAGE_RESET_BUS		  __IOCTL_STORAGE_(0x0400,__FILE_RW_BUFFERED)
#define IOCTL_STORAGE_RESET_DEVICE	  __IOCTL_STORAGE_(0x0401,__FILE_RW_BUFFERED)
#define IOCTL_STORAGE_GET_DEVICE_NUMBER   __IOCTL_STORAGE_(0x0420,__FILE_AM_BUFFERED)
#define IOCTL_STORAGE_PREDICT_FAILURE	  __IOCTL_STORAGE_(0x0440,__FILE_AM_BUFFERED)

typedef
enum _STORAGE_BUS_TYPE
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff566356(v=vs.85).aspx */
{ BusTypeUnknown		= 0x00,
  BusTypeScsi			= 0x01,
  BusTypeAtapi			= 0x02,
  BusTypeAta			= 0x03,
  BusType1394			= 0x04,
  BusTypeSsa			= 0x05,
  BusTypeFibre			= 0x06,
  BusTypeUsb			= 0x07,
  BusTypeRAID			= 0x08,
  BusTypeiScsi			= 0x09,
  BusTypeSas			= 0x0A,
  BusTypeSata			= 0x0B,
  BusTypeSd			= 0x0C,
  BusTypeMmc			= 0x0D,
  BusTypeVirtual		= 0x0E,
  BusTypeFileBackedVirtual	= 0x0F,
  BusTypeSpaces 		= 0x10,
  BusTypeMax			/* variant; number of bus types */,
  BusTypeMaxReserved		= 0x7F
} STORAGE_BUS_TYPE, *PSTORAGE_BUS_TYPE;

# ifndef _WINIOCTL_H
  /* When not sourced from <winioctrl.h>, this fragment is intended to
   * be sourced exclusively from <ddk/ntddstor.h>; in this latter case,
   * the preceding fragment, associated with <ddk/winddk.h> has already
   * been processed, since <ddk/ntddstor.h> has included <ddk/winddk.h>
   * (via <ddk/ntddk.h>) before including this fragment.  At this time,
   * we explicitly DO NOT want to process the following fragment, which
   * relates to the <ddk/nfdddisk.h> header file, but we no longer need
   * to make any specific provision to ignore the fragment relating to
   * <ddk/winddk.h>, which has been processed already.
   */
#  undef __need_ddk_ntdddisk_includes
# endif
# define __have_ddk_ntddstor_includes
#endif

#if __need_ddk_ntdddisk_includes
/* This fragment provides content common to both <winioctl.h> and
 * <ddk/ntdddisk.h>; since both  <ddk/winddk.h> and <ddk/ntddstor.h>
 * are included by <ddk/ntdddisk.h>, this fragment is processed after
 * each of the two fragments associated with each of those two files
 * respectively, (in respective order).
 */
#define __IOCTL_DISK_(FN,M,A)			  CTL_CODE(IOCTL_DISK_BASE,(FN),(M),(A))

#define IOCTL_DISK_BASE 			  FILE_TYPE_DISK
#define IOCTL_DISK_GET_DRIVE_GEOMETRY		__IOCTL_DISK_(0x0000,__FILE_AM_BUFFERED)
#define IOCTL_DISK_GET_PARTITION_INFO		__IOCTL_DISK_(0x0001,__FILE_RD_BUFFERED)
#define IOCTL_DISK_SET_PARTITION_INFO		__IOCTL_DISK_(0x0002,__FILE_RW_BUFFERED)
#define IOCTL_DISK_GET_DRIVE_LAYOUT		__IOCTL_DISK_(0x0003,__FILE_RD_BUFFERED)
#define IOCTL_DISK_SET_DRIVE_LAYOUT		__IOCTL_DISK_(0x0004,__FILE_RW_BUFFERED)
#define IOCTL_DISK_VERIFY			__IOCTL_DISK_(0x0005,__FILE_AM_BUFFERED)
#define IOCTL_DISK_FORMAT_TRACKS		__IOCTL_DISK_(0x0006,__FILE_RW_BUFFERED)
#define IOCTL_DISK_REASSIGN_BLOCKS		__IOCTL_DISK_(0x0007,__FILE_RW_BUFFERED)
#define IOCTL_DISK_PERFORMANCE			__IOCTL_DISK_(0x0008,__FILE_AM_BUFFERED)
#define IOCTL_DISK_IS_WRITABLE			__IOCTL_DISK_(0x0009,__FILE_AM_BUFFERED)
#define IOCTL_DISK_FORMAT_TRACKS_EX		__IOCTL_DISK_(0x000B,__FILE_RW_BUFFERED)
#define IOCTL_DISK_GET_PARTITION_INFO_EX	__IOCTL_DISK_(0x0012,__FILE_AM_BUFFERED)
#define IOCTL_DISK_SET_PARTITION_INFO_EX	__IOCTL_DISK_(0x0013,__FILE_RW_BUFFERED)
#define IOCTL_DISK_GET_DRIVE_LAYOUT_EX		__IOCTL_DISK_(0x0014,__FILE_AM_BUFFERED)
#define IOCTL_DISK_SET_DRIVE_LAYOUT_EX		__IOCTL_DISK_(0x0015,__FILE_RW_BUFFERED)
#define IOCTL_DISK_CREATE_DISK			__IOCTL_DISK_(0x0016,__FILE_RW_BUFFERED)
#define IOCTL_DISK_GET_LENGTH_INFO		__IOCTL_DISK_(0x0017,__FILE_RD_BUFFERED)
#define IOCTL_DISK_PERFORMANCE_OFF		__IOCTL_DISK_(0x0018,__FILE_AM_BUFFERED)
#define IOCTL_DISK_GET_DRIVE_GEOMETRY_EX	__IOCTL_DISK_(0x0028,__FILE_AM_BUFFERED)
#define IOCTL_DISK_UPDATE_DRIVE_SIZE		__IOCTL_DISK_(0x0032,__FILE_RW_BUFFERED)
#define IOCTL_DISK_GROW_PARTITION		__IOCTL_DISK_(0x0034,__FILE_RW_BUFFERED)
#define IOCTL_DISK_GET_CACHE_INFORMATION	__IOCTL_DISK_(0x0035,__FILE_RD_BUFFERED)
#define IOCTL_DISK_SET_CACHE_INFORMATION	__IOCTL_DISK_(0x0036,__FILE_RW_BUFFERED)
#define IOCTL_DISK_DELETE_DRIVE_LAYOUT		__IOCTL_DISK_(0x0040,__FILE_RW_BUFFERED)
#define IOCTL_DISK_CHECK_VERIFY			__IOCTL_DISK_(0x0200,__FILE_RD_BUFFERED)
#define IOCTL_DISK_RESERVE			__IOCTL_DISK_(0x0204,__FILE_RD_BUFFERED)
#define IOCTL_DISK_FIND_NEW_DEVICES		__IOCTL_DISK_(0x0206,__FILE_RD_BUFFERED)
#define IOCTL_DISK_GET_MEDIA_TYPES		__IOCTL_DISK_(0x0300,__FILE_AM_BUFFERED)

enum
{ PARTITION_ENTRY_UNUSED	= 0x00,
  PARTITION_FAT_12		= 0x01,
  PARTITION_XENIX_1		= 0x02,
  PARTITION_XENIX_2		= 0x03,
  PARTITION_FAT_16		= 0x04,
  PARTITION_EXTENDED		= 0x05,
  PARTITION_HUGE		= 0x06,
  PARTITION_IFS 		= 0x07,
  PARTITION_OS2BOOTMGR		= 0x0A,
  PARTITION_FAT32		= 0x0B,
  PARTITION_FAT32_XINT13	= 0x0C,
  PARTITION_XINT13		= 0x0E,
  PARTITION_XINT13_EXTENDED	= 0x0F,
  PARTITION_PREP		= 0x41,
  PARTITION_LDM 		= 0x42,
  PARTITION_UNIX		= 0x63,
  PARTITION_NTFT		= 0x80,
  VALID_NTFT			= 0xC0
};

#define IsRecognizedPartition( TYPE ) \
 (   (((TYPE) & PARTITION_NTFT) && (((TYPE) & ~VALID_NTFT) == PARTITION_FAT_12))\
  || (((TYPE) & PARTITION_NTFT) && (((TYPE) & ~VALID_NTFT) == PARTITION_HUGE))\
  || (((TYPE) & PARTITION_NTFT) && (((TYPE) & ~VALID_NTFT) == PARTITION_IFS))\
  || (((TYPE) & PARTITION_NTFT) && (((TYPE) & ~VALID_NTFT) == PARTITION_FAT32))\
  || (((TYPE) & PARTITION_NTFT) && (((TYPE) & ~VALID_NTFT) == PARTITION_FAT32_XINT13))\
  || (((TYPE) & PARTITION_NTFT) && (((TYPE) & ~VALID_NTFT) == PARTITION_XINT13))\
  || ((TYPE) == PARTITION_FAT32) || ((TYPE) == PARTITION_FAT32_XINT13)\
  || ((TYPE) == PARTITION_FAT_12) || ((TYPE) == PARTITION_FAT_16)\
  || ((TYPE) == PARTITION_HUGE) || ((TYPE) == PARTITION_IFS)\
  || ((TYPE) == PARTITION_XINT13)\
 )
#define IsContainerPartition( TYPE ) \
 (((TYPE) == PARTITION_EXTENDED) || ((TYPE) == PARTITION_XINT13_EXTENDED))

typedef
enum _MEDIA_TYPE
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff562216(v=vs.85).aspx */
{ Unknown			= 0x00,
  F5_1Pt2_512			= 0x01,
  F3_1Pt44_512			= 0x02,
  F3_2Pt88_512			= 0x03,
  F3_20Pt8_512			= 0x04,
  F3_720_512			= 0x05,
  F5_360_512			= 0x06,
  F5_320_512			= 0x07,
  F5_320_1024			= 0x08,
  F5_180_512			= 0x09,
  F5_160_512			= 0x0A,
  RemovableMedia		= 0x0B,
  FixedMedia			= 0x0C,
  F3_120M_512			= 0x0D,
  F3_640_512			= 0x0E,
  F5_640_512			= 0x0F,
  F5_720_512			= 0x10,
  F3_1Pt2_512			= 0x11,
  F3_1Pt23_1024 		= 0x12,
  F5_1Pt23_1024 		= 0x13,
  F3_128Mb_512			= 0x14,
  F3_230Mb_512			= 0x15,
  F8_256_128			= 0x16,
  F3_200Mb_512			= 0x17,
  F3_240M_512			= 0x18,
  F3_32M_512			= 0x19
} MEDIA_TYPE, *PMEDIA_TYPE;

typedef
enum _DETECTION_TYPE
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552516%28v=vs.85%29.aspx */
{ DetectNone			= 0,
  DetectInt13			= 1,
  DetectExInt13			= 2
} DETECTION_TYPE;

typedef
struct _DISK_INT13_INFO
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552624(v=vs.85).aspx */
{ USHORT	DriveSelect;
  ULONG 	MaxCylinders;
  USHORT	SectorsPerTrack;
  USHORT	MaxHeads;
  USHORT	NumberDrives;
} DISK_INT13_INFO, *PDISK_INT13_INFO;

typedef
struct _DISK_EX_INT13_INFO
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552610(v=vs.85).aspx */
{ USHORT	ExBufferSize;
  USHORT	ExFlags;
  ULONG 	ExCylinders;
  ULONG 	ExHeads;
  ULONG 	ExSectorsPerTrack;
  ULONG64	ExSectorsPerDrive;
  USHORT	ExSectorSize;
  USHORT	ExReserved;
} DISK_EX_INT13_INFO, *PDISK_EX_INT13_INFO;

typedef
struct _DISK_DETECTION_INFO
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552601(v=vs.85).aspx */
{ ULONG 		      SizeOfDetectInfo;
  DETECTION_TYPE	      DetectionType;
  _ANONYMOUS_UNION union
  { _ANONYMOUS_STRUCT struct
    { DISK_INT13_INFO	      Int13;
      DISK_EX_INT13_INFO      ExInt13;
    } DUMMYSTRUCTNAME;
  } DUMMYUNIONNAME;
} DISK_DETECTION_INFO, *PDISK_DETECTION_INFO;

typedef
struct _DISK_GEOMETRY
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552613(v=vs.85).aspx */
{ LARGE_INTEGER 	Cylinders;
  MEDIA_TYPE		MediaType;
  ULONG 		TracksPerCylinder;
  ULONG 		SectorsPerTrack;
  ULONG 		BytesPerSector;
} DISK_GEOMETRY, *PDISK_GEOMETRY;

typedef
struct _DISK_GEOMETRY_EX
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552618(v=vs.85).aspx */
{ DISK_GEOMETRY 	Geometry;
  LARGE_INTEGER 	DiskSize;
  UCHAR 		Data[1];
} DISK_GEOMETRY_EX, *PDISK_GEOMETRY_EX;

/* Note: although declared as an array of only one byte, the Data area within
 * the DISK_GEOMETRY_EX structure represents a variable size region containing
 * a DISK_PARTITION_INFO structure followed by a DISK_DETECTION_INFO structure;
 * the above <ddk/ntdddisk.h> reference defines the following pair of macros,
 * for obtaining pointers to the embedded structures, given a pointer to the
 * containing DISK_GEOMETRY_EX structure itself; (the corresponding reference
 * for <winioctl.h> refers to these macros, without defining them).
 */
#if NTDDI_VERSION < NTDDI_WS03
 /* FIXME: given the above definition for DISK_GEOMETRY_EX, this pair of
  * macro definitions makes no sense at all...
  */
# define DiskGeometryGetPartition(Geometry) \
   ((PDISK_PARTITION_INFO)((Geometry) + 1))

# define DiskGeometryGetDetect(Geometry) \
   ((PDISK_DETECTION_INFO)(((PBYTE)DiskGeometryGetPartition(Geometry) + \
       DiskGeometryGetPartition(Geometry)->SizeOfPartitionInfo)))
#else
 /* ...whereas this pair would seem to be appropriate, regardless of the
  * underlying NTDDI_VERSION.
  */
# define DiskGeometryGetPartition(Geometry) \
   ((PDISK_PARTITION_INFO)((Geometry)->Data))

# define DiskGeometryGetDetect(Geometry) \
   ((PDISK_DETECTION_INFO)(((ULONG_PTR)DiskGeometryGetPartition(Geometry) + \
       DiskGeometryGetPartition(Geometry)->SizeOfPartitionInfo)))
#endif

typedef
struct _PARTITION_INFORMATION
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff563751(v=vs.85).aspx */
{ LARGE_INTEGER 	StartingOffset;
  LARGE_INTEGER 	PartitionLength;
  ULONG 		HiddenSectors;
  ULONG 		PartitionNumber;
  UCHAR 		PartitionType;
  BOOLEAN		BootIndicator;
  BOOLEAN		RecognizedPartition;
  BOOLEAN		RewritePartition;
} PARTITION_INFORMATION, *PPARTITION_INFORMATION;

typedef
struct _PARTITION_INFORMATION_GPT
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff563763(v=vs.85).aspx */
{ GUID			PartitionType;
  GUID			PartitionId;
  ULONG64		Attributes;
  WCHAR 		Name[36];
} PARTITION_INFORMATION_GPT, *PPARTITION_INFORMATION_GPT;

typedef
struct _DISK_PARTITION_INFO
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552629(v=vs.85).aspx */
{ ULONG 		  SizeOfPartitionInfo;
  PARTITION_STYLE	  PartitionStyle;
  _ANONYMOUS_UNION union
  { struct
    { ULONG		    Signature;
      ULONG		    CheckSum;
    }			  Mbr;
    struct
    { GUID		    DiskId;
    }			  Gpt;
  } DUMMYUNIONNAME;
} DISK_PARTITION_INFO, *PDISK_PARTITION_INFO;

typedef
struct _DISK_PERFORMANCE
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552633(v=vs.85).aspx */
{ LARGE_INTEGER 	BytesRead;
  LARGE_INTEGER 	BytesWritten;
  LARGE_INTEGER 	ReadTime;
  LARGE_INTEGER 	WriteTime;
  LARGE_INTEGER 	IdleTime;
  ULONG 		ReadCount;
  ULONG 		WriteCount;
  ULONG 		QueueDepth;
  ULONG 		SplitCount;
  LARGE_INTEGER 	QueryTime;
  ULONG 		StorageDeviceNumber;
  WCHAR 		StorageManagerName[8];
} DISK_PERFORMANCE, *PDISK_PERFORMANCE;

typedef
struct _PARTITION_INFORMATION_EX
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff563754(v=vs.85).aspx */
{ PARTITION_STYLE		PartitionStyle;
  LARGE_INTEGER 		StartingOffset;
  LARGE_INTEGER 		PartitionLength;
  ULONG 			PartitionNumber;
  BOOLEAN			RewritePartition;
  _ANONYMOUS_UNION union
  { PARTITION_INFORMATION_MBR	Mbr;
    PARTITION_INFORMATION_GPT	Gpt;
  } DUMMYUNIONNAME;
} PARTITION_INFORMATION_EX, *PPARTITION_INFORMATION_EX;

typedef
struct _FORMAT_EX_PARAMETERS
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff553875(v=vs.85).aspx */
{ MEDIA_TYPE	MediaType;
  ULONG 	StartCylinderNumber;
  ULONG 	EndCylinderNumber;
  ULONG 	StartHeadNumber;
  ULONG 	EndHeadNumber;
  USHORT	FormatGapLength;
  USHORT	SectorsPerTrack;
  USHORT	SectorNumber[1];
} FORMAT_EX_PARAMETERS, *PFORMAT_EX_PARAMETERS;

typedef
struct _FORMAT_PARAMETERS
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff553878(v=vs.85).aspx */
{ MEDIA_TYPE	MediaType;
  ULONG 	StartCylinderNumber;
  ULONG 	EndCylinderNumber;
  ULONG 	StartHeadNumber;
  ULONG 	EndHeadNumber;
} FORMAT_PARAMETERS, *PFORMAT_PARAMETERS;

typedef
struct _GET_LENGTH_INFORMATION
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff554986(v=vs.85).aspx */
{ LARGE_INTEGER 	Length;
} GET_LENGTH_INFORMATION, *PGET_LENGTH_INFORMATION;

typedef
struct _REASSIGN_BLOCKS
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff563962(v=vs.85).aspx */
{ USHORT  	Reserved;
  USHORT  	Count;
  ULONG 	BlockNumber[1];
} REASSIGN_BLOCKS, *PREASSIGN_BLOCKS;

typedef
struct _SET_PARTITION_INFORMATION
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff566192(v=vs.85).aspx */
{ UCHAR 	PartitionType;
} SET_PARTITION_INFORMATION, *PSET_PARTITION_INFORMATION;

typedef
struct _VERIFY_INFORMATION
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff568005(v=vs.85).aspx */
{ LARGE_INTEGER 	StartingOffset;
  ULONG 		Length;
} VERIFY_INFORMATION, *PVERIFY_INFORMATION;

typedef enum
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552583(v=vs.85).aspx */
{ EqualPriority 		= 0,
  KeepPrefetchedData		= 1,
  KeepReadData			= 2
} DISK_CACHE_RETENTION_PRIORITY;

typedef
struct _DISK_CACHE_INFORMATION
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552580(v=vs.85).aspx */
{ BOOLEAN				ParametersSavable;
  BOOLEAN				ReadCacheEnabled;
  BOOLEAN				WriteCacheEnabled;
  DISK_CACHE_RETENTION_PRIORITY 	ReadRetentionPriority;
  DISK_CACHE_RETENTION_PRIORITY 	WriteRetentionPriority;
  USHORT				DisablePrefetchTransferLength;
  BOOLEAN				PrefetchScalar;
  _ANONYMOUS_UNION union
  { struct
    { USHORT				  Minimum;
      USHORT				  Maximum;
      USHORT				  MaximumBlocks;
    }					ScalarPrefetch;
    struct
    { USHORT				  Minimum;
      USHORT				  Maximum;
    }					BlockPrefetch;
  } DUMMYUNIONNAME;
} DISK_CACHE_INFORMATION, *PDISK_CACHE_INFORMATION;

typedef
struct _DISK_GROW_PARTITION
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552621(v=vs.85).aspx */
{ ULONG 		PartitionNumber;
  LARGE_INTEGER 	BytesToGrow;
} DISK_GROW_PARTITION, *PDISK_GROW_PARTITION;

# define __have_ddk_ntdddisk_includes
#endif

#undef __need_ddk_ntdddisk_includes
#undef __need_ddk_ntddstor_includes
#undef __need_ddk_winddk_includes

/* $RCSfile$: end of file */
