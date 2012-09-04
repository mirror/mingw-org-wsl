#ifndef _MPEGTYPE_H
#define _MPEGTYPE_H
#pragma GCC system_header

#include <strmif.h>

#ifdef __cplusplus
extern "C" {
#endif

/*--- DirectShow Reference - DirectShow Structures */
typedef struct tagAM_MPEGSTREAMTYPE {
	DWORD dwStreamID;
	DWORD dwReserved;
	AM_MEDIA_TYPE mt;
	BYTE bFormat[1];
} AM_MPEGSTREAMTYPE;
typedef struct tagAM_MPEGSYSTEMTYPE {
	DWORD dwBitRate;
	DWORD cStreams;
	AM_MPEGSTREAMTYPE Streams[1];
} AM_MPEGSYSTEMTYPE;

#ifdef __cplusplus
}
#endif
#endif
