/*
 * mingw-fseek.c
 *
 * Workaround for limitations on Win9x where extended file content
 * is not zeroed out if you seek past the end and then write.
 *
 * $Id$
 *
 * Written by Mumit Khan  <khan@xraylith.wisc.edu>
 * Copyright (C) 1999, 2002-2005, 2011, 2015, MinGW.org Project.
 *
 * Abstracted from MinGW local patch to binutils/bfd/libbfd.c
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
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>
#include <io.h>
#include <stdlib.h>

#define ZEROBLOCKSIZE 512
static int __mingw_fseek_called;

/* The fseek in Win9x runtime does not zero out the file if seeking past
 * the end; if you don't want random stuff from your disk included in your
 * output DLL/executable, use this version instead. On WinNT/Win2k, it
 * just calls runtime fseek().
 *
 * CHECK/FIXME: Does this work for both text and binary modes??
 */
int
__mingw_fseek (FILE *fp, long offset, int whence)
{
# undef fseek
  __mingw_fseek_called = 1;
  return fseek (fp, offset, whence);
}

int
__mingw_fseeko64 (FILE *fp, __off64_t offset, int whence)
{
# undef fseeko64
  __mingw_fseek_called = 1;
  return fseeko64 (fp, offset, whence);
}

size_t
__mingw_fwrite (const void *buffer, size_t size, size_t count, FILE *fp)
{
# undef fwrite
  if ((_osver & 0x8000) &&  __mingw_fseek_called)
  {
    ULARGE_INTEGER actual_length;
    LARGE_INTEGER current_position = {{0LL}};
    __mingw_fseek_called = 0;
    fflush (fp);
    actual_length.u.LowPart = GetFileSize
      ( (HANDLE) _get_osfhandle (fileno (fp)), &actual_length.u.HighPart
      );
    if (actual_length.u.LowPart == 0xFFFFFFFF && GetLastError() != NO_ERROR )
      return -1;
    current_position.u.LowPart = SetFilePointer
      ( (HANDLE) _get_osfhandle (fileno (fp)), current_position.u.LowPart,
	&current_position.u.HighPart, FILE_CURRENT
      );
    if (current_position.u.LowPart == 0xFFFFFFFF && GetLastError() != NO_ERROR )
      return -1;

#   ifdef DEBUG
      printf( "__mingw_fwrite: current %I64u, actual %I64u\n",
	  current_position.QuadPart, actual_length.QuadPart
	);
#   endif /* DEBUG */
    if( current_position.QuadPart > actual_length.QuadPart )
    {
      static char __mingw_zeros[ZEROBLOCKSIZE];
      long long numleft;

      SetFilePointer( (HANDLE) _get_osfhandle (fileno (fp)), 0, 0, FILE_END );
      numleft = current_position.QuadPart - actual_length.QuadPart;

#     ifdef DEBUG
	printf( "__mingw_fwrite: Seeking %I64d bytes past end\n", numleft );
#     endif /* DEBUG */
      while( numleft > 0LL )
      {
	DWORD nzeros = (numleft > ZEROBLOCKSIZE)
	  ? ZEROBLOCKSIZE
	  : numleft;
	DWORD written;
	if( ! WriteFile ((HANDLE) _get_osfhandle (fileno (fp)),
	      __mingw_zeros, nzeros, &written, NULL)
	  )
	  { /* Best we can hope for, or at least DJ says so.
	     */
	    SetFilePointer( (HANDLE) _get_osfhandle (fileno (fp)),
		0, 0, FILE_BEGIN
	      );
	    return -1;
	  }
	if( written < nzeros )
	{
	  /* Likewise. */
	  SetFilePointer( (HANDLE) _get_osfhandle (fileno (fp)),
	      0, 0, FILE_BEGIN
	    );
	  return -1;
	}
	numleft -= written;
      }
      FlushFileBuffers ((HANDLE) _get_osfhandle (fileno (fp)));
    }
  }
  return (fwrite)(buffer, size, count, fp);
}

/* $RCSfile$: end of file */
