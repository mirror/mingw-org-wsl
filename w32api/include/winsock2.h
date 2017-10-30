/*
 * winsock2.h
 *
 * Definitions for WinSock Version 2 API; provides the additional definitions
 * which are required by WinSock v2, to augment those which are already defined
 * in <winsock.h>, and are common to WinSock Versions 1.1 and 2.
 *
 *
 * $Id$
 *
 * Contributed by the WINE Project.
 * Adaptation by Mumit Khan <khan@xraylith.wisc.edu>
 * Copyright (C) 1998-2005, 2011, 2016, 2017, MinGW.org Project
 *
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
 * Portions Copyright (C) 1980, 1983, 1988, 1993
 * The Regents of the University of California.  All rights reserved.
 *
 * Portions Copyright (C) 1993 by Digital Equipment Corporation.
 *
 */
#if !(defined _WINSOCK2_H || defined _WINSOCK_H)
#define _WINSOCK2_H
#define _WINSOCK_H /* to prevent later inclusion of winsock.h */
#pragma GCC system_header

#define _GNU_H_WINDOWS32_SOCKETS
#define __WINSOCK_H_SOURCED__ 1

#include <windows.h>
#include <winerror.h>
#include <sys/bsdtypes.h>
#include <sys/time.h>

#undef __WINSOCK_H_SOURCED__

#ifndef WINSOCK_API_LINKAGE
#ifdef __W32API_USE_DLLIMPORT__
#define WINSOCK_API_LINKAGE DECLSPEC_IMPORT
#else
#define WINSOCK_API_LINKAGE
#endif
#endif

_BEGIN_C_DECLS

/* Names common to Winsock1.1 and Winsock2
 */
typedef u_int  SOCKET;

#ifndef FD_SETSIZE
#define FD_SETSIZE				  64
#endif

/* shutdown() how types */
#define SD_RECEIVE				0x00
#define SD_SEND 				0x01
#define SD_BOTH 				0x02

#ifndef _SYS_TYPES_FD_SET
/* fd_set may have been defined by the newlib <sys/types.h>, if the
 * internal __USE_W32_SOCKETS feature test has not been enabled.
 */
#undef fd_set
typedef
struct fd_set
{ u_int 	fd_count;
  SOCKET	fd_array[FD_SETSIZE];
} fd_set;

int PASCAL __WSAFDIsSet (SOCKET, fd_set *);

#ifndef FD_CLR
#define FD_CLR( fd, set )  do					\
  { u_int __i;							\
    for (__i = 0; __i < ((fd_set *)(set))->fd_count ; __i++)	\
    { if (((fd_set *)(set))->fd_array[__i] == (fd))		\
      { while (__i < ((fd_set *)(set))->fd_count-1)		\
	{ ((fd_set *)(set))->fd_array[__i]			\
	    = ((fd_set *)(set))->fd_array[__i + 1]; __i++;	\
	}							\
	((fd_set *)(set))->fd_count--;				\
	break;							\
      } 							\
    }								\
  } while (0)
#endif	/* ! defined FD_CLR */

#ifndef FD_SET
/* FIXME: this differs from the original definition in <winsock.h>, and also
 * from the corresponding definition in Cygwin's <sys/types.h>, (which isn't
 * compatible with the WinSock fd_set type); which is correct?
 */
#define FD_SET( fd, set )  do					\
  { u_int __i;							\
    for (__i = 0; __i < ((fd_set *)(set))->fd_count ; __i++)	\
      if (((fd_set *)(set))->fd_array[__i] == (fd)) break;	\
    if (__i == ((fd_set *)(set))->fd_count)			\
    { if (((fd_set *)(set))->fd_count < FD_SETSIZE)		\
      { ((fd_set *)(set))->fd_array[__i] = (fd);		\
	((fd_set *)(set))->fd_count++;				\
      } 							\
    }								\
  } while (0)
#endif	/* ! defined FD_SET */

#ifndef FD_ZERO
#define FD_ZERO( set )  (((fd_set *)(set))->fd_count = 0)
#endif	/* ! defined FD_ZERO */

#ifndef FD_ISSET
#define FD_ISSET( fd, set )  __WSAFDIsSet((SOCKET)(fd), (fd_set *)(set))
#endif	/* ! defined FD_ISSET */

#elif ! defined USE_SYS_TYPES_FD_SET
/* Definitions from <sys/types.h> probably aren't what the user wants;
 * if they know what they are doing, and they are sure that this really
 * is what they want, then they may enable the USE_SYS_TYPES_FD_SET
 * feature test macro, to suppress this warning.
 */
#warning "fd_set and associated macros have been defined in <sys/types.h>"
#warning "Your <sys/types.h> may cause runtime problems with W32 sockets."
#endif	/* !_SYS_TYPES_FD_SET */

#if ! (defined __INSIDE_CYGWIN__ || defined __INSIDE_MSYS__)

struct hostent
{ char		 *h_name;
  char		**h_aliases;
  short 	  h_addrtype;
  short 	  h_length;
# define	  h_addr  h_addr_list[0]
  char		**h_addr_list;
};

struct linger
{ u_short	  l_onoff;
  u_short	  l_linger;
};

#endif	/* ! (__INSIDE_CYGWIN__ || __INSIDE_MSYS__) */

#define IOCPARM_MASK			      0x7F
#define IOC_VOID			0x20000000
#define IOC_OUT 			0x40000000
#define IOC_IN				0x80000000
#define IOC_INOUT		    (IOC_IN | IOC_OUT)

#if ! (defined __INSIDE_CYGWIN__ || defined __INSIDE_MSYS__)

#define _IO(x,y)	(IOC_VOID|((x)<<8)|(y))
#define _IOR(x,y,t)	(IOC_OUT|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))
#define _IOW(x,y,t)	(IOC_IN|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))

#define FIONBIO 		_IOW('f', 126, u_long)

#endif	/* ! (__INSIDE_CYGWIN__ || __INSIDE_MSYS__) */

#define FIONREAD		_IOR('f', 127, u_long)
#define FIOASYNC		_IOW('f', 125, u_long)
#define SIOCSHIWAT		_IOW('s',  0, u_long)
#define SIOCGHIWAT		_IOR('s',  1, u_long)
#define SIOCSLOWAT		_IOW('s',  2, u_long)
#define SIOCGLOWAT		_IOR('s',  3, u_long)
#define SIOCATMARK		_IOR('s',  7, u_long)

#if ! ( defined __INSIDE_CYGWIN__ || defined __INSIDE_MSYS__)

struct netent
{ char		 *n_name;
  char		**n_aliases;
  short 	  n_addrtype;
  u_long	  n_net;
};

struct servent
{ char		 *s_name;
  char		**s_aliases;
  short 	  s_port;
  char		 *s_proto;
};

struct protoent
{ char		 *p_name;
  char		**p_aliases;
  short 	  p_proto;
};

#endif	/* ! (__INSIDE_CYGWIN__ || __INSIDE_MSYS__) */

#define IPPROTO_IP				   0
#define IPPROTO_ICMP				   1
#define IPPROTO_IGMP				   2
#define IPPROTO_GGP				   3
#define IPPROTO_TCP				   6
#define IPPROTO_PUP				  12
#define IPPROTO_UDP				  17
#define IPPROTO_IDP				  22
#define IPPROTO_ND				  77

#define IPPROTO_RAW				 255
#define IPPROTO_MAX				 256

/* IPv6 options */
#define IPPROTO_HOPOPTS 			   0  /* IPv6 Hop-by-Hop options */
#define IPPROTO_IPV6				  41  /* IPv6 header */
#define IPPROTO_ROUTING 			  43  /* IPv6 Routing header */
#define IPPROTO_FRAGMENT			  44  /* IPv6 fragmentation header */
#define IPPROTO_ESP				  50  /* encapsulating security payload */
#define IPPROTO_AH				  51  /* authentication header */
#define IPPROTO_ICMPV6				  58  /* ICMPv6 */
#define IPPROTO_NONE				  59  /* IPv6 no next header */
#define IPPROTO_DSTOPTS 			  60  /* IPv6 Destination options */

#define IPPORT_ECHO				   7
#define IPPORT_DISCARD				   9
#define IPPORT_SYSTAT				  11
#define IPPORT_DAYTIME				  13
#define IPPORT_NETSTAT				  15
#define IPPORT_FTP				  21
#define IPPORT_TELNET				  23
#define IPPORT_SMTP				  25
#define IPPORT_TIMESERVER			  37
#define IPPORT_NAMESERVER			  42
#define IPPORT_WHOIS				  43
#define IPPORT_MTP				  57
#define IPPORT_TFTP				  69
#define IPPORT_RJE				  77
#define IPPORT_FINGER				  79
#define IPPORT_TTYLINK				  87
#define IPPORT_SUPDUP				  95
#define IPPORT_EXECSERVER			 512
#define IPPORT_LOGINSERVER			 513
#define IPPORT_CMDSERVER			 514
#define IPPORT_EFSSERVER			 520
#define IPPORT_BIFFUDP				 512
#define IPPORT_WHOSERVER			 513
#define IPPORT_ROUTESERVER			 520
#define IPPORT_RESERVED 			1024

#define IMPLINK_IP				 155
#define IMPLINK_LOWEXPER			 156
#define IMPLINK_HIGHEXPER			 158

struct in_addr
#define s_addr				      S_un.S_addr
#define s_host				      S_un.S_un_b.s_b2
#define s_net				      S_un.S_un_b.s_b1
#define s_imp				      S_un.S_un_w.s_w2
#define s_impno 			      S_un.S_un_b.s_b4
#define s_lh				      S_un.S_un_b.s_b3
{ union
  { struct { u_char s_b1,s_b2,s_b3,s_b4; }	S_un_b;
    struct { u_short s_w1,s_w2; }		S_un_w;
    u_long					S_addr;
  }					      S_un;
};

#define IN_CLASSA(i)	    (((long)(i) & 0x80000000) == 0)
#define IN_CLASSA_NET			  0xFF000000
#define IN_CLASSA_NSHIFT			  24
#define IN_CLASSA_HOST			  0x00FFFFFF
#define IN_CLASSA_MAX				 128
#define IN_CLASSB(i)	    (((long)(i) & 0xC0000000) == 0x80000000)
#define IN_CLASSB_NET			  0xFFFF0000
#define IN_CLASSB_NSHIFT			  16
#define IN_CLASSB_HOST			  0x0000FFFF
#define IN_CLASSB_MAX			       65536
#define IN_CLASSC(i)	    (((long)(i) & 0xE0000000) == 0xC0000000)
#define IN_CLASSC_NET			  0xFFFFFF00
#define IN_CLASSC_NSHIFT		           8
#define IN_CLASSC_HOST			        0xFF
#define INADDR_ANY			  (u_long)(0)
#define INADDR_LOOPBACK 		  0x7F000001
#define INADDR_BROADCAST	 (u_long)(0xFFFFFFFF)
#define INADDR_NONE			  0xFFFFFFFF

struct sockaddr_in
{ short 		 sin_family;
  u_short		 sin_port;
  struct in_addr	 sin_addr;
  char			 sin_zero[8];
};

#define WSADESCRIPTION_LEN			 256
#define WSASYS_STATUS_LEN			 128

typedef
struct WSAData
{ WORD			 wVersion;
  WORD			 wHighVersion;
  char			 szDescription[WSADESCRIPTION_LEN+1];
  char			 szSystemStatus[WSASYS_STATUS_LEN+1];
  unsigned short	 iMaxSockets;
  unsigned short	 iMaxUdpDg;
  char			*lpVendorInfo;
} WSADATA, *LPWSADATA;

#if ! (defined __INSIDE_CYGWIN__ || defined __INSIDE_MSYS__)

#define IP_OPTIONS				   1
#define SO_DEBUG				   1
#define SO_ACCEPTCONN				   2
#define SO_REUSEADDR				   4
#define SO_KEEPALIVE				   8
#define SO_DONTROUTE				  16
#define SO_BROADCAST				  32
#define SO_USELOOPBACK				  64
#define SO_LINGER				 128
#define SO_OOBINLINE				 256

#define SO_DONTLINGER			 (u_int)(~SO_LINGER)
#define SO_EXCLUSIVEADDRUSE		((u_int)(~SO_REUSEADDR))

#define SO_SNDBUF			      0x1001
#define SO_RCVBUF			      0x1002
#define SO_SNDLOWAT			      0x1003
#define SO_RCVLOWAT			      0x1004
#define SO_SNDTIMEO			      0x1005
#define SO_RCVTIMEO			      0x1006
#define SO_ERROR			      0x1007
#define SO_TYPE 			      0x1008

#endif	/* ! (__INSIDE_CYGWIN__ || __INSIDE_MSYS__) */

#define INVALID_SOCKET			 (SOCKET)(~0)
#define SOCKET_ERROR				 (-1)
#define SOCK_STREAM				   1
#define SOCK_DGRAM				   2
#define SOCK_RAW				   3
#define SOCK_RDM				   4
#define SOCK_SEQPACKET				   5
#define TCP_NODELAY			      0x0001
#define AF_UNSPEC				   0
#define AF_UNIX 				   1
#define AF_INET 				   2
#define AF_IMPLINK				   3
#define AF_PUP					   4
#define AF_CHAOS				   5
#define AF_IPX					   6
#define AF_NS					   6
#define AF_ISO					   7

#define AF_OSI				      AF_ISO

#define AF_ECMA 				   8
#define AF_DATAKIT				   9
#define AF_CCITT				  10
#define AF_SNA					  11
#define AF_DECnet				  12
#define AF_DLI					  13
#define AF_LAT					  14
#define AF_HYLINK				  15
#define AF_APPLETALK				  16
#define AF_NETBIOS				  17
#define AF_VOICEVIEW				  18
#define AF_FIREFOX				  19
#define AF_UNKNOWN1				  20
#define AF_BAN					  21
#define AF_ATM					  22
#define AF_INET6				  23

#define AF_CLUSTER				  24
#define AF_12844				  25
#define AF_IRDA 				  26
#define AF_NETDES				  28

#ifndef __INSIDE_MSYS__

#define AF_MAX					  29

struct sockaddr
{ u_short		 sa_family;
  char			 sa_data[14];
};

/* Portable IPv6/IPv4 version of sockaddr.  Based on RFC 2553.
 * Pad to force 8 byte alignment and maximum size of 128 bytes.
 *
 * Desired design of maximum size and alignment
 */
#define _SS_MAXSIZE				 128
#define _SS_ALIGNSIZE			sizeof(__int64)

/* Definitions used for sockaddr_storage structure padding.
 */
#define _SS_PAD1SIZE   (_SS_ALIGNSIZE - sizeof(short))
#define _SS_PAD2SIZE   (_SS_MAXSIZE - (sizeof(short) + _SS_PAD1SIZE + _SS_ALIGNSIZE))

struct sockaddr_storage
{ short 		ss_family;
  char		      __ss_pad1[_SS_PAD1SIZE];	/* pad to 8 */
  __int64	      __ss_align;		/* force alignment */
  char		      __ss_pad2[_SS_PAD2SIZE];	/*  pad to 128 */
};

#endif	/* !__INSIDE_MSYS__ */

struct sockproto
{ u_short		 sp_family;
  u_short		 sp_protocol;
};

#define PF_UNSPEC			   AF_UNSPEC
#define PF_UNIX 			     AF_UNIX
#define PF_INET 			     AF_INET
#define PF_IMPLINK			  AF_IMPLINK
#define PF_PUP				      AF_PUP
#define PF_CHAOS			    AF_CHAOS
#define PF_NS				       AF_NS
#define PF_IPX				      AF_IPX
#define PF_ISO				      AF_ISO
#define PF_OSI				      AF_OSI
#define PF_ECMA 			     AF_ECMA
#define PF_DATAKIT			  AF_DATAKIT
#define PF_CCITT			    AF_CCITT
#define PF_SNA				      AF_SNA
#define PF_DECnet			   AF_DECnet
#define PF_DLI				      AF_DLI
#define PF_LAT				      AF_LAT
#define PF_HYLINK			   AF_HYLINK
#define PF_APPLETALK			AF_APPLETALK
#define PF_VOICEVIEW			AF_VOICEVIEW
#define PF_FIREFOX			  AF_FIREFOX
#define PF_UNKNOWN1			 AF_UNKNOWN1
#define PF_BAN				      AF_BAN
#define PF_ATM				      AF_ATM
#define PF_INET6			    AF_INET6
#define PF_MAX				      AF_MAX

#define SOL_SOCKET			      0xFFFF

#if ! (defined __INSIDE_CYGWIN__ || defined __INSIDE_MSYS__)

#define SOMAXCONN			  0x7FFFFFFF /* (5) in WinSock1.1 */

#define MSG_OOB 				   1
#define MSG_PEEK				   2
#define MSG_DONTROUTE				   4

#endif  /* ! (__INSIDE_CYGWIN__ || __INSIDE_MSYS__) */

#define MSG_MAXIOVLEN				  16
#define MSG_PARTIAL			      0x8000
#define MAXGETHOSTSTRUCT			1024

#define FD_READ_BIT		       0
#define FD_READ 		      (1 << FD_READ_BIT)
#define FD_WRITE_BIT		       1
#define FD_WRITE		      (1 << FD_WRITE_BIT)
#define FD_OOB_BIT		       2
#define FD_OOB			      (1 << FD_OOB_BIT)
#define FD_ACCEPT_BIT		       3
#define FD_ACCEPT		      (1 << FD_ACCEPT_BIT)
#define FD_CONNECT_BIT		       4
#define FD_CONNECT		      (1 << FD_CONNECT_BIT)
#define FD_CLOSE_BIT		       5
#define FD_CLOSE		      (1 << FD_CLOSE_BIT)
/* WinSock v1.1 defines no further events, beyond FD_CLOSE (32);
 * the following are specific to WinSock v2.
 */
#define FD_QOS_BIT		       6
#define FD_QOS			      (1 << FD_QOS_BIT)
#define FD_GROUP_QOS_BIT	       7
#define FD_GROUP_QOS		      (1 << FD_GROUP_QOS_BIT)
#define FD_ROUTING_INTERFACE_CHANGE_BIT 8
#define FD_ROUTING_INTERFACE_CHANGE   (1 << FD_ROUTING_INTERFACE_CHANGE_BIT)
#define FD_ADDRESS_LIST_CHANGE_BIT     9
#define FD_ADDRESS_LIST_CHANGE	      (1 << FD_ADDRESS_LIST_CHANGE_BIT)

#define FD_MAX_EVENTS			 10
#define FD_ALL_EVENTS			((1 << FD_MAX_EVENTS) - 1)

#define WSANO_ADDRESS			WSANO_DATA

#if ! (defined __INSIDE_CYGWIN__ || defined __INSIDE_MSYS__)

#define h_errno 			WSAGetLastError()
#define HOST_NOT_FOUND			WSAHOST_NOT_FOUND
#define TRY_AGAIN			WSATRY_AGAIN
#define NO_RECOVERY			WSANO_RECOVERY
#define NO_DATA 			WSANO_DATA
#define NO_ADDRESS			WSANO_ADDRESS

#endif	/* ! (__INSIDE_CYGWIN__ || __INSIDE_MSYS__) */

WINSOCK_API_LINKAGE SOCKET PASCAL accept (SOCKET, struct sockaddr *, int *);

WINSOCK_API_LINKAGE int PASCAL bind (SOCKET, const struct sockaddr *, int);
WINSOCK_API_LINKAGE int PASCAL closesocket (SOCKET);
WINSOCK_API_LINKAGE int PASCAL connect (SOCKET, const struct sockaddr *, int);
WINSOCK_API_LINKAGE int PASCAL ioctlsocket (SOCKET, long, u_long *);
WINSOCK_API_LINKAGE int PASCAL getpeername (SOCKET, struct sockaddr *, int *);
WINSOCK_API_LINKAGE int PASCAL getsockname (SOCKET, struct sockaddr *, int *);
WINSOCK_API_LINKAGE int PASCAL getsockopt (SOCKET, int, int, char *, int *);

WINSOCK_API_LINKAGE unsigned long PASCAL inet_addr (const char *);

WINSOCK_API_LINKAGE DECLARE_STDCALL_P (char *) inet_ntoa (struct in_addr);

WINSOCK_API_LINKAGE int PASCAL listen (SOCKET, int);
WINSOCK_API_LINKAGE int PASCAL recv (SOCKET, char *, int, int);
WINSOCK_API_LINKAGE int PASCAL recvfrom (SOCKET, char *, int, int, struct sockaddr *, int *);
WINSOCK_API_LINKAGE int PASCAL send (SOCKET, const char *, int, int);
WINSOCK_API_LINKAGE int PASCAL sendto (SOCKET, const char *, int, int, const struct sockaddr *, int);
WINSOCK_API_LINKAGE int PASCAL setsockopt (SOCKET, int, int, const char *, int);
WINSOCK_API_LINKAGE int PASCAL shutdown (SOCKET, int);

WINSOCK_API_LINKAGE SOCKET PASCAL socket (int, int, int);

WINSOCK_API_LINKAGE DECLARE_STDCALL_P (struct hostent *)  gethostbyaddr (const char *, int, int);
WINSOCK_API_LINKAGE DECLARE_STDCALL_P (struct hostent *)  gethostbyname (const char *);
WINSOCK_API_LINKAGE DECLARE_STDCALL_P (struct servent *)  getservbyport (int, const char *);
WINSOCK_API_LINKAGE DECLARE_STDCALL_P (struct servent *)  getservbyname (const char *, const char *);
WINSOCK_API_LINKAGE DECLARE_STDCALL_P (struct protoent *) getprotobynumber (int);
WINSOCK_API_LINKAGE DECLARE_STDCALL_P (struct protoent *) getprotobyname (const char *);


typedef SOCKET (PASCAL *LPFN_ACCEPT) (SOCKET, struct sockaddr *, int *);

typedef int (PASCAL *LPFN_BIND) (SOCKET, const struct sockaddr *, int);
typedef int (PASCAL *LPFN_CLOSESOCKET) (SOCKET);
typedef int (PASCAL *LPFN_CONNECT) (SOCKET, const struct sockaddr *, int);
typedef int (PASCAL *LPFN_IOCTLSOCKET) (SOCKET, long, u_long *);
typedef int (PASCAL *LPFN_GETPEERNAME) (SOCKET, struct sockaddr *, int *);
typedef int (PASCAL *LPFN_GETSOCKNAME) (SOCKET, struct sockaddr *, int *);
typedef int (PASCAL *LPFN_GETSOCKOPT) (SOCKET, int, int, char *, int *);

typedef u_long (PASCAL *LPFN_HTONL) (u_long);
typedef u_short (PASCAL *LPFN_HTONS) (u_short);

typedef unsigned long (PASCAL *LPFN_INET_ADDR) (const char *);

typedef char *(PASCAL *LPFN_INET_NTOA) (struct in_addr);

typedef int (PASCAL *LPFN_LISTEN) (SOCKET, int);

typedef u_long (PASCAL *LPFN_NTOHL) (u_long);
typedef u_short (PASCAL *LPFN_NTOHS) (u_short);

typedef int (PASCAL *LPFN_RECV) (SOCKET, char *, int, int);
typedef int (PASCAL *LPFN_RECVFROM) (SOCKET, char *, int, int, struct sockaddr *, int *);
typedef int (PASCAL *LPFN_SELECT) (int, fd_set *, fd_set *, fd_set *, const struct timeval *);
typedef int (PASCAL *LPFN_SEND) (SOCKET, const char *, int, int);
typedef int (PASCAL *LPFN_SENDTO) (SOCKET, const char *, int, int, const struct sockaddr *, int);
typedef int (PASCAL *LPFN_SETSOCKOPT) (SOCKET, int, int, const char *, int);
typedef int (PASCAL *LPFN_SHUTDOWN) (SOCKET, int);

typedef SOCKET (PASCAL *LPFN_SOCKET) (int, int, int);

typedef struct hostent *(PASCAL *LPFN_GETHOSTBYADDR) ( const char *, int, int);
typedef struct hostent *(PASCAL *LPFN_GETHOSTBYNAME) ( const char *);

typedef int (PASCAL *LPFN_GETHOSTNAME) (char *, int);

typedef struct servent *(PASCAL *LPFN_GETSERVBYPORT) (int, const char *);
typedef struct servent *(PASCAL *LPFN_GETSERVBYNAME) (const char *, const char *);
typedef struct protoent *(PASCAL *LPFN_GETPROTOBYNUMBER) (int);
typedef struct protoent *(PASCAL *LPFN_GETPROTOBYNAME) (const char *);

WINSOCK_API_LINKAGE int PASCAL WSAStartup (WORD, LPWSADATA);
WINSOCK_API_LINKAGE int PASCAL WSACleanup (void);
WINSOCK_API_LINKAGE void PASCAL WSASetLastError (int);
WINSOCK_API_LINKAGE int PASCAL WSAGetLastError (void);

WINSOCK_API_LINKAGE typedef int (PASCAL *LPFN_WSASTARTUP) (WORD, LPWSADATA);
typedef int (PASCAL *LPFN_WSACLEANUP) (void);
typedef int (PASCAL *LPFN_WSAGETLASTERROR) (void);
typedef void (PASCAL *LPFN_WSASETLASTERROR) (int);

/* Pseudo-blocking functions are deprecated in WinSock v2.
 * Use threads instead of these!
 */
WINSOCK_API_LINKAGE BOOL PASCAL WSAIsBlocking (void);
WINSOCK_API_LINKAGE int PASCAL WSAUnhookBlockingHook (void);
WINSOCK_API_LINKAGE FARPROC PASCAL WSASetBlockingHook (FARPROC);
WINSOCK_API_LINKAGE int PASCAL WSACancelBlockingCall (void);

typedef BOOL (PASCAL *LPFN_WSAISBLOCKING) (void);
typedef int (PASCAL *LPFN_WSAUNHOOKBLOCKINGHOOK) (void);
typedef FARPROC (PASCAL *LPFN_WSASETBLOCKINGHOOK) (FARPROC);
typedef int (PASCAL *LPFN_WSACANCELBLOCKINGCALL) (void);

WINSOCK_API_LINKAGE HANDLE PASCAL WSAAsyncGetServByName (HWND, u_int, const char *, const char *, char *, int);
WINSOCK_API_LINKAGE HANDLE PASCAL WSAAsyncGetServByPort (HWND, u_int, int, const char *, char *, int);
WINSOCK_API_LINKAGE HANDLE PASCAL WSAAsyncGetProtoByName (HWND, u_int, const char *, char *, int);
WINSOCK_API_LINKAGE HANDLE PASCAL WSAAsyncGetProtoByNumber (HWND, u_int, int, char *, int);
WINSOCK_API_LINKAGE HANDLE PASCAL WSAAsyncGetHostByName (HWND, u_int, const char *, char *, int);
WINSOCK_API_LINKAGE HANDLE PASCAL WSAAsyncGetHostByAddr (HWND, u_int, const char *, int, int, char *, int);

WINSOCK_API_LINKAGE int PASCAL WSACancelAsyncRequest (HANDLE);
WINSOCK_API_LINKAGE int PASCAL WSAAsyncSelect (SOCKET, HWND, u_int, long);

typedef HANDLE (PASCAL *LPFN_WSAASYNCGETSERVBYNAME) (HWND, u_int, const char *, const char *, char *, int);
typedef HANDLE (PASCAL *LPFN_WSAASYNCGETSERVBYPORT) (HWND, u_int, int, const char *, char *, int);
typedef HANDLE (PASCAL *LPFN_WSAASYNCGETPROTOBYNAME) (HWND, u_int, const char*, char*, int);
typedef HANDLE (PASCAL *LPFN_WSAASYNCGETPROTOBYNUMBER) (HWND, u_int, int, char*, int);
typedef HANDLE (PASCAL *LPFN_WSAASYNCGETHOSTBYADDR) (HWND, u_int, const char*, int, int, char*, int);

typedef int (PASCAL *LPFN_WSACANCELASYNCREQUEST) (HANDLE);
typedef int (PASCAL *LPFN_WSAASYNCSELECT) (SOCKET, HWND, u_int, long);

#if ! (defined __INSIDE_CYGWIN__ || defined __INSIDE_MSYS__)

WINSOCK_API_LINKAGE u_long PASCAL htonl (u_long);
WINSOCK_API_LINKAGE u_long PASCAL ntohl (u_long);
WINSOCK_API_LINKAGE u_short PASCAL htons (u_short);
WINSOCK_API_LINKAGE u_short PASCAL ntohs (u_short);
WINSOCK_API_LINKAGE int PASCAL select (int nfds, fd_set *, fd_set *, fd_set *, const struct timeval *);

#endif	/* ! (__INSIDE_CYGWIN__ || __INSIDE_MSYS__) */

int PASCAL gethostname (char *, int);

#define WSAMAKEASYNCREPLY(b,e)			MAKELONG(b,e)
#define WSAMAKESELECTREPLY(e,error)		MAKELONG(e,error)
#define WSAGETASYNCBUFLEN(l)			LOWORD(l)
#define WSAGETASYNCERROR(l)			HIWORD(l)
#define WSAGETSELECTEVENT(l)			LOWORD(l)
#define WSAGETSELECTERROR(l)			HIWORD(l)

typedef struct sockaddr SOCKADDR, *PSOCKADDR, *LPSOCKADDR;
typedef struct sockaddr_storage SOCKADDR_STORAGE, *PSOCKADDR_STORAGE;
typedef struct sockaddr_in SOCKADDR_IN, *PSOCKADDR_IN, *LPSOCKADDR_IN;
typedef struct linger LINGER, *PLINGER, *LPLINGER;
typedef struct in_addr IN_ADDR, *PIN_ADDR, *LPIN_ADDR;
typedef struct fd_set FD_SET, *PFD_SET, *LPFD_SET;
typedef struct hostent HOSTENT, *PHOSTENT, *LPHOSTENT;
typedef struct servent SERVENT, *PSERVENT, *LPSERVENT;
typedef struct protoent PROTOENT, *PPROTOENT, *LPPROTOENT;
typedef struct timeval TIMEVAL, *PTIMEVAL, *LPTIMEVAL;

/* winsock2 additions */
#define __WINSOCK2_H_SOURCED__

/* We need a definition for the BLOB data type; although an incomplete
 * type definition would suffice here, other related headers, <nspapi.h>
 * in particular, require the full definition, so we may just as well
 * incorporate that here, by selective inclusion from "wtypes.h", by
 * way of indirect inclusion from "nspapi.h"
 */
#include "nspapi.h"

#define ADDR_ANY			  INADDR_ANY

#define IN_CLASSD(i)	    (((long)(i) & 0xF0000000) == 0xE0000000)
#define IN_CLASSD_NET			  0xF0000000
#define IN_CLASSD_NSHIFT			  28
#define IN_CLASSD_HOST			  0x0FFFFFFF
#define IN_MULTICAST(i) 		 IN_CLASSD(i)

#define FROM_PROTOCOL_INFO			 (-1)

#define SO_GROUP_ID			      0x2001
#define SO_GROUP_PRIORITY		      0x2002
#define SO_MAX_MSG_SIZE 		      0x2003

#define SO_PROTOCOL_INFO	__AW_SUFFIXED__(SO_PROTOCOL_INFO)
#define SO_PROTOCOL_INFOA		      0x2004
#define SO_PROTOCOL_INFOW		      0x2005

#define PVD_CONFIG			      0x3001

#define MSG_INTERRUPT				0x10

#define WSAAPI				      WINAPI
#define WSAEVENT			      HANDLE
#define LPWSAEVENT			    LPHANDLE
#define WSAOVERLAPPED			  OVERLAPPED

typedef	struct _OVERLAPPED  *LPWSAOVERLAPPED;

#define WSA_IO_PENDING			(ERROR_IO_PENDING)
#define WSA_IO_INCOMPLETE		(ERROR_IO_INCOMPLETE)
#define WSA_INVALID_HANDLE		(ERROR_INVALID_HANDLE)
#define WSA_INVALID_PARAMETER		(ERROR_INVALID_PARAMETER)
#define WSA_NOT_ENOUGH_MEMORY		(ERROR_NOT_ENOUGH_MEMORY)
#define WSA_OPERATION_ABORTED		(ERROR_OPERATION_ABORTED)

#define WSA_INVALID_EVENT		((WSAEVENT)NULL)
#define WSA_MAXIMUM_WAIT_EVENTS 	(MAXIMUM_WAIT_OBJECTS)
#define WSA_WAIT_FAILED 		((DWORD)-1L)
#define WSA_WAIT_EVENT_0		(WAIT_OBJECT_0)
#define WSA_WAIT_IO_COMPLETION		(WAIT_IO_COMPLETION)
#define WSA_WAIT_TIMEOUT		(WAIT_TIMEOUT)
#define WSA_INFINITE			(INFINITE)

typedef
struct _WSABUF
{ unsigned long 	 len;
  char			*buf;
} WSABUF, *LPWSABUF;

typedef enum
{ BestEffortService,
  ControlledLoadService,
  PredictiveService,
  GuaranteedDelayService,
  GuaranteedService
} GUARANTEE;

/* FIXME: FLOWSPEC and related definitions belong in qos.h */

/* Windows Sockets 2 Application Programming Interface,
 * revision 2.2.2 (1997) uses the type uint32 for SERVICETYPE
 * and the elements of _flowspec, but the type uint32 is not defined
 * or used anywhere else in the w32api. For now, just use
 * unsigned int, which is 32 bits on _WIN32 and _WIN64.
 */
typedef unsigned int  SERVICETYPE;

typedef
struct _flowspec
{ unsigned int		 TokenRate;
  unsigned int		 TokenBucketSize;
  unsigned int		 PeakBandwidth;
  unsigned int		 Latency;
  unsigned int		 DelayVariation;
  SERVICETYPE		 ServiceType;
  unsigned int		 MaxSduSize;
  unsigned int		 MinimumPolicedSize;
} FLOWSPEC, *PFLOWSPEC, *LPFLOWSPEC;

typedef
struct _QualityOfService
{ FLOWSPEC		 SendingFlowspec;
  FLOWSPEC		 ReceivingFlowspec;
  WSABUF		 ProviderSpecific;
} QOS, *LPQOS;

#define CF_ACCEPT			      0x0000
#define CF_REJECT			      0x0001
#define CF_DEFER			      0x0002

typedef unsigned int  GROUP;

#define SG_UNCONSTRAINED_GROUP			0x01
#define SG_CONSTRAINED_GROUP			0x02

typedef
struct _WSANETWORKEVENTS
{ long			 lNetworkEvents;
  int			 iErrorCode[FD_MAX_EVENTS];
} WSANETWORKEVENTS, *LPWSANETWORKEVENTS;

#define MAX_PROTOCOL_CHAIN			   7

#define BASE_PROTOCOL				   1
#define LAYERED_PROTOCOL			   0

typedef
enum _WSAESETSERVICEOP
{ RNRSERVICE_REGISTER				=  0,
  RNRSERVICE_DEREGISTER,
  RNRSERVICE_DELETE
} WSAESETSERVICEOP, *PWSAESETSERVICEOP, *LPWSAESETSERVICEOP;

typedef
struct _AFPROTOCOLS
{ INT			 iAddressFamily;
  INT			 iProtocol;
} AFPROTOCOLS, *PAFPROTOCOLS, *LPAFPROTOCOLS;

typedef
enum _WSAEcomparator
{ COMP_EQUAL					=  0,
  COMP_NOTLESS
} WSAECOMPARATOR, *PWSAECOMPARATOR, *LPWSAECOMPARATOR;

typedef
struct _WSAVersion
{ DWORD 		 dwVersion;
  WSAECOMPARATOR	 ecHow;
} WSAVERSION, *PWSAVERSION, *LPWSAVERSION;

typedef
struct _SOCKET_ADDRESS_LIST
{ INT			 iAddressCount;
  SOCKET_ADDRESS	 Address[1];
} SOCKET_ADDRESS_LIST, *LPSOCKET_ADDRESS_LIST;

typedef
struct _WSAQuerySetA
{ DWORD 		 dwSize;
  LPSTR 		 lpszServiceInstanceName;
  LPGUID		 lpServiceClassId;
  LPWSAVERSION		 lpVersion;
  LPSTR 		 lpszComment;
  DWORD 		 dwNameSpace;
  LPGUID		 lpNSProviderId;
  LPSTR 		 lpszContext;
  DWORD 		 dwNumberOfProtocols;
  LPAFPROTOCOLS 	 lpafpProtocols;
  LPSTR 		 lpszQueryString;
  DWORD 		 dwNumberOfCsAddrs;
  LPCSADDR_INFO 	 lpcsaBuffer;
  DWORD 		 dwOutputFlags;
  LPBLOB		 lpBlob;
} WSAQUERYSETA, *PWSAQUERYSETA, *LPWSAQUERYSETA;

typedef
struct _WSAQuerySetW
{ DWORD 		 dwSize;
  LPWSTR		 lpszServiceInstanceName;
  LPGUID		 lpServiceClassId;
  LPWSAVERSION		 lpVersion;
  LPWSTR		 lpszComment;
  DWORD 		 dwNameSpace;
  LPGUID		 lpNSProviderId;
  LPWSTR		 lpszContext;
  DWORD 		 dwNumberOfProtocols;
  LPAFPROTOCOLS 	 lpafpProtocols;
  LPWSTR		 lpszQueryString;
  DWORD 		 dwNumberOfCsAddrs;
  LPCSADDR_INFO 	 lpcsaBuffer;
  DWORD 		 dwOutputFlags;
  LPBLOB		 lpBlob;
} WSAQUERYSETW, *PWSAQUERYSETW, *LPWSAQUERYSETW;

typedef __AW_ALIAS__( WSAQUERYSET );
typedef __AW_ALIAS__( PWSAQUERYSET );
typedef __AW_ALIAS__( LPWSAQUERYSET );

#define LUP_DEEP			      0x0001
#define LUP_CONTAINERS			      0x0002
#define LUP_NOCONTAINERS		      0x0004
#define LUP_NEAREST			      0x0008
#define LUP_RETURN_NAME 		      0x0010
#define LUP_RETURN_TYPE 		      0x0020
#define LUP_RETURN_VERSION		      0x0040
#define LUP_RETURN_COMMENT		      0x0080
#define LUP_RETURN_ADDR 		      0x0100
#define LUP_RETURN_BLOB 		      0x0200
#define LUP_RETURN_ALIASES		      0x0400
#define LUP_RETURN_QUERY_STRING 	      0x0800
#define LUP_RETURN_ALL			      0x0FF0
#define LUP_RES_SERVICE 		      0x8000
#define LUP_FLUSHCACHE			      0x1000
#define LUP_FLUSHPREVIOUS		      0x2000

typedef
struct _WSANSClassInfoA
{ LPSTR 		 lpszName;
  DWORD 		 dwNameSpace;
  DWORD 		 dwValueType;
  DWORD 		 dwValueSize;
  LPVOID		 lpValue;
} WSANSCLASSINFOA, *PWSANSCLASSINFOA, *LPWSANSCLASSINFOA;

typedef
struct _WSANSClassInfoW
{ LPWSTR		 lpszName;
  DWORD 		 dwNameSpace;
  DWORD 		 dwValueType;
  DWORD 		 dwValueSize;
  LPVOID		 lpValue;
} WSANSCLASSINFOW, *PWSANSCLASSINFOW, *LPWSANSCLASSINFOW;

typedef __AW_ALIAS__( WSANSCLASSINFO );
typedef __AW_ALIAS__( PWSANSCLASSINFO );
typedef __AW_ALIAS__( LPWSANSCLASSINFO );

typedef
struct _WSAServiceClassInfoA
{ LPGUID		 lpServiceClassId;
  LPSTR 		 lpszServiceClassName;
  DWORD 		 dwCount;
  LPWSANSCLASSINFOA	 lpClassInfos;
} WSASERVICECLASSINFOA, *PWSASERVICECLASSINFOA, *LPWSASERVICECLASSINFOA;

typedef
struct _WSAServiceClassInfoW
{ LPGUID		 lpServiceClassId;
  LPWSTR		 lpszServiceClassName;
  DWORD 		 dwCount;
  LPWSANSCLASSINFOW	 lpClassInfos;
} WSASERVICECLASSINFOW, *PWSASERVICECLASSINFOW, *LPWSASERVICECLASSINFOW;

typedef __AW_ALIAS__( WSASERVICECLASSINFO );
typedef __AW_ALIAS__( PWSASERVICECLASSINFO );
typedef __AW_ALIAS__( LPWSASERVICECLASSINFO );

typedef
struct _WSANAMESPACE_INFOA
{ GUID			 NSProviderId;
  DWORD 		 dwNameSpace;
  BOOL			 fActive;
  DWORD 		 dwVersion;
  LPSTR 		 lpszIdentifier;
} WSANAMESPACE_INFOA, *PWSANAMESPACE_INFOA, *LPWSANAMESPACE_INFOA;

typedef
struct _WSANAMESPACE_INFOW
{ GUID			 NSProviderId;
  DWORD 		 dwNameSpace;
  BOOL			 fActive;
  DWORD 		 dwVersion;
  LPWSTR		 lpszIdentifier;
} WSANAMESPACE_INFOW, *PWSANAMESPACE_INFOW, *LPWSANAMESPACE_INFOW;

typedef __AW_ALIAS__( WSANAMESPACE_INFO );
typedef __AW_ALIAS__( PWSANAMESPACE_INFO );
typedef __AW_ALIAS__( LPWSANAMESPACE_INFO );

typedef
struct _WSAPROTOCOLCHAIN
{ int			 ChainLen;
  DWORD 		 ChainEntries[MAX_PROTOCOL_CHAIN];
} WSAPROTOCOLCHAIN, *LPWSAPROTOCOLCHAIN;

#define WSAPROTOCOL_LEN 			 255

typedef
struct _WSAPROTOCOL_INFOA
{ DWORD 		 dwServiceFlags1;
  DWORD 		 dwServiceFlags2;
  DWORD 		 dwServiceFlags3;
  DWORD 		 dwServiceFlags4;
  DWORD 		 dwProviderFlags;
  GUID			 ProviderId;
  DWORD 		 dwCatalogEntryId;
  WSAPROTOCOLCHAIN	 ProtocolChain;
  int			 iVersion;
  int			 iAddressFamily;
  int			 iMaxSockAddr;
  int			 iMinSockAddr;
  int			 iSocketType;
  int			 iProtocol;
  int			 iProtocolMaxOffset;
  int			 iNetworkByteOrder;
  int			 iSecurityScheme;
  DWORD 		 dwMessageSize;
  DWORD 		 dwProviderReserved;
  CHAR			 szProtocol[WSAPROTOCOL_LEN+1];
} WSAPROTOCOL_INFOA, *LPWSAPROTOCOL_INFOA;

typedef
struct _WSAPROTOCOL_INFOW
{ DWORD 		 dwServiceFlags1;
  DWORD 		 dwServiceFlags2;
  DWORD 		 dwServiceFlags3;
  DWORD 		 dwServiceFlags4;
  DWORD 		 dwProviderFlags;
  GUID			 ProviderId;
  DWORD 		 dwCatalogEntryId;
  WSAPROTOCOLCHAIN	 ProtocolChain;
  int			 iVersion;
  int			 iAddressFamily;
  int			 iMaxSockAddr;
  int			 iMinSockAddr;
  int			 iSocketType;
  int			 iProtocol;
  int			 iProtocolMaxOffset;
  int			 iNetworkByteOrder;
  int			 iSecurityScheme;
  DWORD 		 dwMessageSize;
  DWORD 		 dwProviderReserved;
  WCHAR 		 szProtocol[WSAPROTOCOL_LEN+1];
} WSAPROTOCOL_INFOW, *LPWSAPROTOCOL_INFOW;

typedef __AW_ALIAS__( WSAPROTOCOL_INFO );
typedef __AW_ALIAS__( LPWSAPROTOCOL_INFO );

typedef int (CALLBACK *LPCONDITIONPROC) (LPWSABUF, LPWSABUF, LPQOS, LPQOS, LPWSABUF, LPWSABUF, GROUP *, DWORD);
typedef void (WINAPI *LPWSAOVERLAPPED_COMPLETION_ROUTINE) (DWORD, DWORD, LPWSAOVERLAPPED, DWORD);

/* Needed for XP & .NET Server function WSANSPIoctl. */

typedef
enum _WSACOMPLETIONTYPE
{ NSP_NOTIFY_IMMEDIATELY			=  0,
  NSP_NOTIFY_HWND,
  NSP_NOTIFY_EVENT,
  NSP_NOTIFY_PORT,
  NSP_NOTIFY_APC
} WSACOMPLETIONTYPE, *PWSACOMPLETIONTYPE, *LPWSACOMPLETIONTYPE;

typedef
struct _WSACOMPLETION
{ WSACOMPLETIONTYPE				 Type;
  union
  { struct
    { HWND					     hWnd;
      UINT					     uMsg;
      WPARAM					     context;
    }						   WindowMessage;
    struct
    { LPWSAOVERLAPPED				     lpOverlapped;
    }						   Event;
    struct
    { LPWSAOVERLAPPED				     lpOverlapped;
      LPWSAOVERLAPPED_COMPLETION_ROUTINE	     lpfnCompletionProc;
    }						   Apc;
    struct
    { LPWSAOVERLAPPED				     lpOverlapped;
      HANDLE					     hPort;
      ULONG_PTR 				     Key;
    }						   Port;
  }						 Parameters;
} WSACOMPLETION, *PWSACOMPLETION, *LPWSACOMPLETION;

#define PFL_MULTIPLE_PROTO_ENTRIES	  0x00000001
#define PFL_RECOMMENDED_PROTO_ENTRY	  0x00000002
#define PFL_HIDDEN			  0x00000004
#define PFL_MATCHES_PROTOCOL_ZERO	  0x00000008
#define XP1_CONNECTIONLESS		  0x00000001
#define XP1_GUARANTEED_DELIVERY 	  0x00000002
#define XP1_GUARANTEED_ORDER		  0x00000004
#define XP1_MESSAGE_ORIENTED		  0x00000008
#define XP1_PSEUDO_STREAM		  0x00000010
#define XP1_GRACEFUL_CLOSE		  0x00000020
#define XP1_EXPEDITED_DATA		  0x00000040
#define XP1_CONNECT_DATA		  0x00000080
#define XP1_DISCONNECT_DATA		  0x00000100
#define XP1_SUPPORT_BROADCAST		  0x00000200
#define XP1_SUPPORT_MULTIPOINT		  0x00000400
#define XP1_MULTIPOINT_CONTROL_PLANE	  0x00000800
#define XP1_MULTIPOINT_DATA_PLANE	  0x00001000
#define XP1_QOS_SUPPORTED		  0x00002000
#define XP1_INTERRUPT			  0x00004000
#define XP1_UNI_SEND			  0x00008000
#define XP1_UNI_RECV			  0x00010000
#define XP1_IFS_HANDLES 		  0x00020000
#define XP1_PARTIAL_MESSAGE		  0x00040000

#define BIGENDIAN			      0x0000
#define LITTLEENDIAN			      0x0001

#define SECURITY_PROTOCOL_NONE		      0x0000
#define JL_SENDER_ONLY				0x01
#define JL_RECEIVER_ONLY			0x02
#define JL_BOTH 				0x04
#define WSA_FLAG_OVERLAPPED			0x01
#define WSA_FLAG_MULTIPOINT_C_ROOT		0x02
#define WSA_FLAG_MULTIPOINT_C_LEAF		0x04
#define WSA_FLAG_MULTIPOINT_D_ROOT		0x08
#define WSA_FLAG_MULTIPOINT_D_LEAF		0x10
#define IOC_UNIX			  0x00000000
#define IOC_WS2 			  0x08000000
#define IOC_PROTOCOL			  0x10000000
#define IOC_VENDOR			  0x18000000

#define _WSAIO(x,y)				(IOC_VOID|(x)|(y))
#define _WSAIOR(x,y)				(IOC_OUT|(x)|(y))
#define _WSAIOW(x,y)				(IOC_IN|(x)|(y))
#define _WSAIORW(x,y)				(IOC_INOUT|(x)|(y))

#define SIO_ASSOCIATE_HANDLE			_WSAIOW(IOC_WS2,1)
#define SIO_ENABLE_CIRCULAR_QUEUEING		_WSAIO(IOC_WS2,2)
#define SIO_FIND_ROUTE				_WSAIOR(IOC_WS2,3)
#define SIO_FLUSH				_WSAIO(IOC_WS2,4)
#define SIO_GET_BROADCAST_ADDRESS		_WSAIOR(IOC_WS2,5)
#define SIO_GET_EXTENSION_FUNCTION_POINTER	_WSAIORW(IOC_WS2,6)
#define SIO_GET_QOS				_WSAIORW(IOC_WS2,7)
#define SIO_GET_GROUP_QOS			_WSAIORW(IOC_WS2,8)
#define SIO_MULTIPOINT_LOOPBACK 		_WSAIOW(IOC_WS2,9)
#define SIO_MULTICAST_SCOPE			_WSAIOW(IOC_WS2,10)
#define SIO_SET_QOS				_WSAIOW(IOC_WS2,11)
#define SIO_SET_GROUP_QOS			_WSAIOW(IOC_WS2,12)
#define SIO_TRANSLATE_HANDLE			_WSAIORW(IOC_WS2,13)
#define SIO_ROUTING_INTERFACE_QUERY		_WSAIORW(IOC_WS2,20)
#define SIO_ROUTING_INTERFACE_CHANGE		_WSAIOW(IOC_WS2,21)
#define SIO_ADDRESS_LIST_QUERY			_WSAIOR(IOC_WS2,22)
#define SIO_ADDRESS_LIST_CHANGE 		_WSAIO(IOC_WS2,23)
#define SIO_QUERY_TARGET_PNP_HANDLE		_WSAIOR(IOC_WS2,24)
#define SIO_NSP_NOTIFY_CHANGE			_WSAIOW(IOC_WS2,25)
#define SIO_UDP_CONNRESET			_WSAIOW(IOC_VENDOR,12)

#define TH_NETDEV			  0x00000001
#define TH_TAPI 			  0x00000002

WINSOCK_API_LINKAGE SOCKET WINAPI WSAAccept (SOCKET, struct sockaddr *, LPINT, LPCONDITIONPROC, DWORD);

#define WSAAddressToString __AW_SUFFIXED__(WSAAddressToString)
WINSOCK_API_LINKAGE INT WINAPI WSAAddressToStringA (LPSOCKADDR, DWORD, LPWSAPROTOCOL_INFOA, LPSTR, LPDWORD);
WINSOCK_API_LINKAGE INT WINAPI WSAAddressToStringW (LPSOCKADDR, DWORD, LPWSAPROTOCOL_INFOW, LPWSTR, LPDWORD);

WINSOCK_API_LINKAGE BOOL WINAPI WSACloseEvent (WSAEVENT);
WINSOCK_API_LINKAGE int WINAPI WSAConnect (SOCKET, const struct sockaddr *, int, LPWSABUF, LPWSABUF, LPQOS, LPQOS);
WINSOCK_API_LINKAGE WSAEVENT WINAPI WSACreateEvent (void);

#define WSADuplicateSocket __AW_SUFFIXED__(WSADuplicateSocket)
WINSOCK_API_LINKAGE int WINAPI WSADuplicateSocketA (SOCKET, DWORD, LPWSAPROTOCOL_INFOA);
WINSOCK_API_LINKAGE int WINAPI WSADuplicateSocketW (SOCKET, DWORD, LPWSAPROTOCOL_INFOW);

#define WSAEnumNameSpaceProviders __AW_SUFFIXED__(WSAEnumNameSpaceProviders)
WINSOCK_API_LINKAGE INT WINAPI WSAEnumNameSpaceProvidersA (LPDWORD, LPWSANAMESPACE_INFOA);
WINSOCK_API_LINKAGE INT WINAPI WSAEnumNameSpaceProvidersW (LPDWORD, LPWSANAMESPACE_INFOW);

WINSOCK_API_LINKAGE int WINAPI WSAEnumNetworkEvents (SOCKET, WSAEVENT, LPWSANETWORKEVENTS);

#define WSAEnumProtocols __AW_SUFFIXED__(WSAEnumProtocols)
WINSOCK_API_LINKAGE int WINAPI WSAEnumProtocolsA (LPINT, LPWSAPROTOCOL_INFOA, LPDWORD);
WINSOCK_API_LINKAGE int WINAPI WSAEnumProtocolsW (LPINT, LPWSAPROTOCOL_INFOW, LPDWORD);

WINSOCK_API_LINKAGE int WINAPI WSAEventSelect (SOCKET, WSAEVENT, long);
WINSOCK_API_LINKAGE BOOL WINAPI WSAGetOverlappedResult (SOCKET, LPWSAOVERLAPPED, LPDWORD, BOOL, LPDWORD);
WINSOCK_API_LINKAGE BOOL WINAPI WSAGetQOSByName (SOCKET, LPWSABUF, LPQOS);

#define WSAGetServiceClassInfo __AW_SUFFIXED__(WSAGetServiceClassInfo)
WINSOCK_API_LINKAGE INT WINAPI WSAGetServiceClassInfoA (LPGUID, LPGUID, LPDWORD, LPWSASERVICECLASSINFOA);
WINSOCK_API_LINKAGE INT WINAPI WSAGetServiceClassInfoW (LPGUID, LPGUID, LPDWORD, LPWSASERVICECLASSINFOW);

#define WSAGetServiceClassNameByClassId __AW_SUFFIXED__(WSAGetServiceClassNameByClassId)
WINSOCK_API_LINKAGE INT WINAPI WSAGetServiceClassNameByClassIdA (LPGUID, LPSTR, LPDWORD);
WINSOCK_API_LINKAGE INT WINAPI WSAGetServiceClassNameByClassIdW (LPGUID, LPWSTR, LPDWORD);

WINSOCK_API_LINKAGE int WINAPI WSAHtonl (SOCKET, unsigned long, unsigned long *);
WINSOCK_API_LINKAGE int WINAPI WSAHtons (SOCKET, unsigned short, unsigned short *);

#define WSAInstallServiceClass __AW_SUFFIXED__(WSAInstallServiceClass)
WINSOCK_API_LINKAGE INT WINAPI WSAInstallServiceClassA (LPWSASERVICECLASSINFOA);
WINSOCK_API_LINKAGE INT WINAPI WSAInstallServiceClassW (LPWSASERVICECLASSINFOW);

WINSOCK_API_LINKAGE int WINAPI WSAIoctl (SOCKET, DWORD, LPVOID, DWORD, LPVOID, DWORD, LPDWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
WINSOCK_API_LINKAGE SOCKET WINAPI WSAJoinLeaf (SOCKET, const struct sockaddr *, int, LPWSABUF, LPWSABUF, LPQOS, LPQOS, DWORD);

#define WSALookupServiceBegin __AW_SUFFIXED__(WSALookupServiceBegin)
WINSOCK_API_LINKAGE INT WINAPI WSALookupServiceBeginA (LPWSAQUERYSETA, DWORD, LPHANDLE);
WINSOCK_API_LINKAGE INT WINAPI WSALookupServiceBeginW (LPWSAQUERYSETW, DWORD, LPHANDLE);

#define WSALookupServiceNext __AW_SUFFIXED__(WSALookupServiceNext)
WINSOCK_API_LINKAGE INT WINAPI WSALookupServiceNextA (HANDLE, DWORD, LPDWORD, LPWSAQUERYSETA);
WINSOCK_API_LINKAGE INT WINAPI WSALookupServiceNextW (HANDLE, DWORD, LPDWORD, LPWSAQUERYSETW);

WINSOCK_API_LINKAGE INT WINAPI WSALookupServiceEnd (HANDLE);
WINSOCK_API_LINKAGE int WINAPI WSANSPIoctl (HANDLE, DWORD, LPVOID, DWORD, LPVOID, DWORD, LPDWORD, LPWSACOMPLETION); /* XP or .NET Server */
WINSOCK_API_LINKAGE int WINAPI WSANtohl (SOCKET, unsigned long, unsigned long *);
WINSOCK_API_LINKAGE int WINAPI WSANtohs (SOCKET, unsigned short, unsigned short *);
WINSOCK_API_LINKAGE int WINAPI WSARecv (SOCKET, LPWSABUF, DWORD, LPDWORD, LPDWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
WINSOCK_API_LINKAGE int WINAPI WSARecvDisconnect (SOCKET, LPWSABUF);
WINSOCK_API_LINKAGE int WINAPI WSARecvFrom (SOCKET, LPWSABUF, DWORD, LPDWORD, LPDWORD, struct sockaddr *, LPINT, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
WINSOCK_API_LINKAGE INT WINAPI WSARemoveServiceClass (LPGUID);
WINSOCK_API_LINKAGE BOOL WINAPI WSAResetEvent (WSAEVENT);
WINSOCK_API_LINKAGE int WINAPI WSASend (SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
WINSOCK_API_LINKAGE int WINAPI WSASendDisconnect (SOCKET, LPWSABUF);
WINSOCK_API_LINKAGE int WINAPI WSASendTo (SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, const struct sockaddr *, int, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
WINSOCK_API_LINKAGE BOOL WINAPI WSASetEvent (WSAEVENT);

#define WSASetService __AW_SUFFIXED__(WSASetService)
WINSOCK_API_LINKAGE INT WSAAPI WSASetServiceA (LPWSAQUERYSETA, WSAESETSERVICEOP, DWORD);
WINSOCK_API_LINKAGE INT WINAPI WSASetServiceW (LPWSAQUERYSETW, WSAESETSERVICEOP, DWORD);

#define WSASocket __AW_SUFFIXED__(WSASocket)
WINSOCK_API_LINKAGE SOCKET WINAPI WSASocketA (int, int, int, LPWSAPROTOCOL_INFOA, GROUP, DWORD);
WINSOCK_API_LINKAGE SOCKET WINAPI WSASocketW (int, int, int, LPWSAPROTOCOL_INFOW, GROUP, DWORD);

#define WSAStringToAddress __AW_SUFFIXED__(WSAStringToAddress)
WINSOCK_API_LINKAGE INT WINAPI WSAStringToAddressA (LPSTR, INT, LPWSAPROTOCOL_INFOA, LPSOCKADDR, LPINT);
WINSOCK_API_LINKAGE INT WINAPI WSAStringToAddressW (LPWSTR, INT, LPWSAPROTOCOL_INFOW, LPSOCKADDR, LPINT);

WINSOCK_API_LINKAGE DWORD WINAPI WSAWaitForMultipleEvents (DWORD, const WSAEVENT *, BOOL, DWORD, BOOL);

typedef SOCKET (WINAPI *LPFN_WSAACCEPT) (SOCKET, struct sockaddr *, LPINT, LPCONDITIONPROC, DWORD);

#define LPFN_WSAADDRESSTOSTRING __AW_SUFFIXED__(LPFN_WSAADDRESSTOSTRING)
typedef INT (WINAPI *LPFN_WSAADDRESSTOSTRINGA) (LPSOCKADDR, DWORD, LPWSAPROTOCOL_INFOA, LPSTR, LPDWORD);
typedef INT (WINAPI *LPFN_WSAADDRESSTOSTRINGW) (LPSOCKADDR, DWORD, LPWSAPROTOCOL_INFOW, LPWSTR, LPDWORD);

typedef BOOL (WINAPI *LPFN_WSACLOSEEVENT) (WSAEVENT);
typedef int (WINAPI *LPFN_WSACONNECT) (SOCKET, const struct sockaddr *, int, LPWSABUF, LPWSABUF, LPQOS, LPQOS);
typedef WSAEVENT (WINAPI *LPFN_WSACREATEEVENT) (void);

#define LPFN_WSADUPLICATESOCKET __AW_SUFFIXED__(LPFN_WSADUPLICATESOCKET)
typedef int (WINAPI *LPFN_WSADUPLICATESOCKETA) (SOCKET, DWORD, LPWSAPROTOCOL_INFOA);
typedef int (WINAPI *LPFN_WSADUPLICATESOCKETW) (SOCKET, DWORD, LPWSAPROTOCOL_INFOW);

#define LPFN_WSAENUMNAMESPACEPROVIDERS __AW_SUFFIXED__(LPFN_WSAENUMNAMESPACEPROVIDERS)
typedef INT (WINAPI *LPFN_WSAENUMNAMESPACEPROVIDERSA) (LPDWORD, LPWSANAMESPACE_INFOA);
typedef INT (WINAPI *LPFN_WSAENUMNAMESPACEPROVIDERSW) (LPDWORD, LPWSANAMESPACE_INFOW);

typedef int (WINAPI *LPFN_WSAENUMNETWORKEVENTS) (SOCKET, WSAEVENT, LPWSANETWORKEVENTS);

#define LPFN_WSAENUMPROTOCOLS __AW_SUFFIXED__(LPFN_WSAENUMPROTOCOLS)
typedef int (WINAPI *LPFN_WSAENUMPROTOCOLSA) (LPINT, LPWSAPROTOCOL_INFOA, LPDWORD);
typedef int (WINAPI *LPFN_WSAENUMPROTOCOLSW) (LPINT, LPWSAPROTOCOL_INFOW, LPDWORD);

typedef int (WINAPI *LPFN_WSAEVENTSELECT) (SOCKET, WSAEVENT, long);
typedef BOOL (WINAPI *LPFN_WSAGETOVERLAPPEDRESULT) (SOCKET, LPWSAOVERLAPPED, LPDWORD, BOOL, LPDWORD);
typedef BOOL (WINAPI *LPFN_WSAGETQOSBYNAME) (SOCKET, LPWSABUF, LPQOS);

#define LPFN_WSAGETSERVICECLASSINFO __AW_SUFFIXED__(LPFN_WSAGETSERVICECLASSINFO)
typedef INT (WINAPI *LPFN_WSAGETSERVICECLASSINFOA) (LPGUID, LPGUID, LPDWORD, LPWSASERVICECLASSINFOA);
typedef INT (WINAPI *LPFN_WSAGETSERVICECLASSINFOW) (LPGUID, LPGUID, LPDWORD, LPWSASERVICECLASSINFOW);

#define LPFN_WSAGETSERVICECLASSNAMEBYCLASSID __AW_SUFFIXED__(LPFN_WSAGETSERVICECLASSNAMEBYCLASSID)
typedef INT (WINAPI *LPFN_WSAGETSERVICECLASSNAMEBYCLASSIDA) (LPGUID, LPSTR, LPDWORD);
typedef INT (WINAPI *LPFN_WSAGETSERVICECLASSNAMEBYCLASSIDW) (LPGUID, LPWSTR, LPDWORD);

typedef int (WINAPI *LPFN_WSAHTONL) (SOCKET, unsigned long, unsigned long *);
typedef int (WINAPI *LPFN_WSAHTONS) (SOCKET, unsigned short, unsigned short *);

#define LPFN_WSAINSTALLSERVICECLASS __AW_SUFFIXED__(LPFN_WSAINSTALLSERVICECLASS)
typedef INT (WINAPI *LPFN_WSAINSTALLSERVICECLASSA) (LPWSASERVICECLASSINFOA);
typedef INT (WINAPI *LPFN_WSAINSTALLSERVICECLASSW) (LPWSASERVICECLASSINFOW);

typedef int (WINAPI *LPFN_WSAIOCTL) (SOCKET, DWORD, LPVOID, DWORD, LPVOID, DWORD, LPDWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
typedef SOCKET (WINAPI *LPFN_WSAJOINLEAF) (SOCKET, const struct sockaddr *, int, LPWSABUF, LPWSABUF, LPQOS, LPQOS, DWORD);

#define LPFN_WSALOOKUPSERVICEBEGIN __AW_SUFFIXED__(LPFN_WSALOOKUPSERVICEBEGIN)
typedef INT (WINAPI *LPFN_WSALOOKUPSERVICEBEGINA) (LPWSAQUERYSETA, DWORD, LPHANDLE);
typedef INT (WINAPI *LPFN_WSALOOKUPSERVICEBEGINW) (LPWSAQUERYSETW, DWORD, LPHANDLE);

#define LPFN_WSALOOKUPSERVICENEXT __AW_SUFFIXED__(LPFN_WSALOOKUPSERVICENEXT)
typedef INT (WINAPI *LPFN_WSALOOKUPSERVICENEXTA) (HANDLE, DWORD, LPDWORD, LPWSAQUERYSETA);
typedef INT (WINAPI *LPFN_WSALOOKUPSERVICENEXTW) (HANDLE, DWORD, LPDWORD, LPWSAQUERYSETW);

typedef INT (WINAPI *LPFN_WSALOOKUPSERVICEEND) (HANDLE);
typedef int (WINAPI *LPFN_WSANSPIoctl) (HANDLE, DWORD, LPVOID, DWORD, LPVOID, DWORD, LPDWORD, LPWSACOMPLETION);
typedef int (WINAPI *LPFN_WSANTOHL) (SOCKET, unsigned long, unsigned long *);
typedef int (WINAPI *LPFN_WSANTOHS) (SOCKET, unsigned short, unsigned short *);
typedef int (WINAPI *LPFN_WSARECV) (SOCKET, LPWSABUF, DWORD, LPDWORD, LPDWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
typedef int (WINAPI *LPFN_WSARECVDISCONNECT) (SOCKET, LPWSABUF);
typedef int (WINAPI *LPFN_WSARECVFROM) (SOCKET, LPWSABUF, DWORD, LPDWORD, LPDWORD, struct sockaddr *, LPINT, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
typedef INT (WINAPI *LPFN_WSAREMOVESERVICECLASS) (LPGUID);
typedef BOOL (WINAPI *LPFN_WSARESETEVENT) (WSAEVENT);
typedef int (WINAPI *LPFN_WSASEND) (SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
typedef int (WINAPI *LPFN_WSASENDDISCONNECT) (SOCKET, LPWSABUF);
typedef int (WINAPI *LPFN_WSASENDTO) (SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, const struct sockaddr *, int, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
typedef BOOL (WINAPI *LPFN_WSASETEVENT) (WSAEVENT);

#define LPFN_WSASETSERVICE  __AW_SUFFIXED__(LPFN_WSASETSERVICE)
typedef INT (WINAPI *LPFN_WSASETSERVICEA) (LPWSAQUERYSETA, WSAESETSERVICEOP, DWORD);
typedef INT (WINAPI *LPFN_WSASETSERVICEW) (LPWSAQUERYSETW, WSAESETSERVICEOP, DWORD);

#define LPFN_WSASOCKET __AW_SUFFIXED__(LPFN_WSASOCKET)
typedef SOCKET (WINAPI *LPFN_WSASOCKETA) (int, int, int, LPWSAPROTOCOL_INFOA, GROUP, DWORD);
typedef SOCKET (WINAPI *LPFN_WSASOCKETW) (int, int, int, LPWSAPROTOCOL_INFOW, GROUP, DWORD);

#define LPFN_WSASTRINGTOADDRESS __AW_SUFFIXED__(LPFN_WSASTRINGTOADDRESS)
typedef INT (WINAPI *LPFN_WSASTRINGTOADDRESSA) (LPSTR, INT, LPWSAPROTOCOL_INFOA, LPSOCKADDR, LPINT);
typedef INT (WINAPI *LPFN_WSASTRINGTOADDRESSW) (LPWSTR, INT, LPWSAPROTOCOL_INFOW, LPSOCKADDR, LPINT);

typedef DWORD (WINAPI *LPFN_WSAWAITFORMULTIPLEEVENTS) (DWORD, const WSAEVENT *, BOOL, DWORD, BOOL);

_END_C_DECLS

#undef __WINSOCK2_H_SOURCED__
#endif	/* _WINSOCK2_H: $RCSfile$: end of file */
