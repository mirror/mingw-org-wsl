/**
 * @file tlsthrd.c
 * Copyright 2012, 2013 MinGW.org project
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
 * This file is used by if gcc is built with --enable-threads=win32.
 *
 * Written by Kai Tietz  <kai.tietz@onevision.com>
 * Based on version created by Mumit Khan  <khan@nanotech.wisc.edu>
 */

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <stdlib.h>

WINBOOL __mingw_TLScallback (HANDLE hDllHandle, DWORD reason, LPVOID reserved);
int ___w64_mingwthr_remove_key_dtor (DWORD key);
int ___w64_mingwthr_add_key_dtor (DWORD key, void (*dtor)(void *));

/* To protect the thread/key association data structure modifications. */
static CRITICAL_SECTION __mingwthr_cs;
static volatile int __mingwthr_cs_init = 0;

typedef struct __mingwthr_key __mingwthr_key_t;

/* The list of threads active with key/dtor pairs. */
struct __mingwthr_key {
  DWORD key;
  void (*dtor)(void *);
  __mingwthr_key_t volatile *next;
};


static __mingwthr_key_t volatile *key_dtor_list;

int
___w64_mingwthr_add_key_dtor (DWORD key, void (*dtor)(void *))
{
  __mingwthr_key_t *new_key;

  if (__mingwthr_cs_init == 0)
    return 0;
  new_key = (__mingwthr_key_t *) calloc (1, sizeof (__mingwthr_key_t));
  if (new_key == NULL)
    return -1;

  new_key->key = key;
  new_key->dtor = dtor;

  EnterCriticalSection (&__mingwthr_cs);

  new_key->next = key_dtor_list;
  key_dtor_list = new_key;

  LeaveCriticalSection (&__mingwthr_cs);
  return 0;
}

int
___w64_mingwthr_remove_key_dtor (DWORD key)
{
  __mingwthr_key_t volatile *prev_key;
  __mingwthr_key_t volatile *cur_key;

  if (__mingwthr_cs_init == 0)
    return 0;

  EnterCriticalSection (&__mingwthr_cs);

  prev_key = NULL;
  cur_key = key_dtor_list;

  while (cur_key != NULL)
    {
      if ( cur_key->key == key)
        {
          if (prev_key == NULL)
            key_dtor_list = cur_key->next;
          else
            prev_key->next = cur_key->next;

          free ((void*)cur_key);
          break;
        }
      prev_key = cur_key;
      cur_key = cur_key->next;
    }

  LeaveCriticalSection (&__mingwthr_cs);
  return 0;
}

static void
__mingwthr_run_key_dtors (void)
{
  __mingwthr_key_t volatile *keyp;

  if (__mingwthr_cs_init == 0)
    return;
  EnterCriticalSection (&__mingwthr_cs);

  for (keyp = key_dtor_list; keyp; )
    {
      LPVOID value = TlsGetValue (keyp->key);
      if (GetLastError () == ERROR_SUCCESS)
        {
          if (value)
            (*keyp->dtor) (value);
        }
      keyp = keyp->next;
    }

  LeaveCriticalSection (&__mingwthr_cs);
}

WINBOOL
__mingw_TLScallback (HANDLE hDllHandle __attribute__ ((__unused__)),
		     DWORD reason,
		     LPVOID reserved __attribute__ ((__unused__)))
{
  switch (reason)
    {
    case DLL_PROCESS_ATTACH:
      if (__mingwthr_cs_init == 0)
        InitializeCriticalSection (&__mingwthr_cs);
      __mingwthr_cs_init = 1;
      break;
    case DLL_PROCESS_DETACH:
      __mingwthr_run_key_dtors();
      if (__mingwthr_cs_init == 1)
        {
          __mingwthr_cs_init = 0;
          DeleteCriticalSection (&__mingwthr_cs);
        }
      break;
    case DLL_THREAD_ATTACH:
      break;
    case DLL_THREAD_DETACH:
      __mingwthr_run_key_dtors();
      break;
    }
  return TRUE;
}
