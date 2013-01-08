/**
 * @file mthr.c
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

/* @FIXME - Is this used by current GCC? */

/*
 * Created by Mumit Khan  <khan@nanotech.wisc.edu>
 *
 * Implement Mingw thread-support DLL .
 *
 * This file is used iff the following conditions are met:
 *  - gcc uses -mthreads option 
 *  - user code uses C++ exceptions
 *
 * The sole job of the Mingw thread support DLL (MingwThr) is to catch 
 * all the dying threads and clean up the data allocated in the TLSs 
 * for exception contexts during C++ EH. Posix threads have key dtors, 
 * but win32 TLS keys do not, hence the magic. Without this, there's at 
 * least `6 * sizeof (void*)' bytes leaks for each catch/throw in each
 * thread. The only public interface is __mingwthr_key_dtor(). 
 */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#include <stdlib.h>

/* To protect the thread/key association data structure modifications. */
CRITICAL_SECTION __mingwthr_cs;

typedef struct __mingwthr_key __mingwthr_key_t;

/* The list of threads active with key/dtor pairs. */
struct __mingwthr_key {
  DWORD key;
  void (*dtor) (void *);
  __mingwthr_key_t *next;
};


static __mingwthr_key_t *key_dtor_list;

/*
 * __mingwthr_key_add:
 *
 * Add key/dtor association for this thread. If the thread entry does not
 * exist, create a new one and add to the head of the threads list; add
 * the new assoc at the head of the keys list. 
 *
 */

static int
___mingwthr_add_key_dtor ( DWORD key, void (*dtor) (void *))
{
  __mingwthr_key_t *new_key;

  new_key = (__mingwthr_key_t *) calloc (1, sizeof (__mingwthr_key_t));
  if (new_key == NULL)
    return -1;
  
  new_key->key = key;
  new_key->dtor = dtor;

  EnterCriticalSection (&__mingwthr_cs);

  new_key->next = key_dtor_list;
  key_dtor_list = new_key;

  LeaveCriticalSection (&__mingwthr_cs);

#ifdef DEBUG
  printf ("%s: allocating: (%ld, %x)\n", 
          __FUNCTION__, key, dtor);
#endif

  return 0;
}

static int
___mingwthr_remove_key_dtor ( DWORD key )
{
  __mingwthr_key_t *prev_key;
  __mingwthr_key_t *cur_key;

  EnterCriticalSection (&__mingwthr_cs);

  prev_key = NULL;
  cur_key = key_dtor_list;

  while( cur_key != NULL )
  {
     if( cur_key->key == key )
     {
// take key/dtor out of list
        if( prev_key == NULL )
        {
           key_dtor_list = cur_key->next;
        }
        else
        {
           prev_key->next = cur_key->next;
        }

#ifdef DEBUG
        printf ("%s: removing: (%ld)\n", 
                __FUNCTION__, key );
#endif

        free( cur_key );
        break;
     }

     prev_key = cur_key;
     cur_key = cur_key->next;
  }

  LeaveCriticalSection (&__mingwthr_cs);

  return 0;
}

/*
 * __mingwthr_run_key_dtors (void):
 *
 * Callback from DllMain when thread detaches to clean up the key
 * storage. 
 *
 * Note that this does not delete the key itself, but just runs
 * the dtor if the current value are both non-NULL. Note that the
 * keys with NULL dtors are not added by __mingwthr_key_dtor, the
 * only public interface, so we don't need to check. 
 *
 */

void
__mingwthr_run_key_dtors (void)
{
  __mingwthr_key_t *keyp;

#ifdef DEBUG
  printf ("%s: Entering Thread id %ld\n", __FUNCTION__, GetCurrentThreadId() );
#endif

  EnterCriticalSection (&__mingwthr_cs);

  for (keyp = key_dtor_list; keyp; )
  {
     LPVOID value = TlsGetValue (keyp->key);
     if (GetLastError () == ERROR_SUCCESS)
     {
#ifdef DEBUG
        printf ("   (%ld, %x)\n", keyp->key, keyp->dtor);
#endif
        if (value)
           (*keyp->dtor) (value);
     }
#ifdef DEBUG
     else
     {
        printf ("   TlsGetValue FAILED  (%ld, %x)\n", 
                keyp->key, keyp->dtor);
     }
#endif
     keyp = keyp->next;
  }
  
  LeaveCriticalSection (&__mingwthr_cs);

#ifdef DEBUG
  printf ("%s: Exiting Thread id %ld\n", __FUNCTION__, GetCurrentThreadId() );
#endif
}
  
/*
 * __mingwthr_register_key_dtor (DWORD key, void (*dtor) (void *))
 *
 * Public interface called by C++ exception handling mechanism in
 * libgcc (cf: __gthread_key_create).
 *
 */

__declspec(dllexport)
int
__mingwthr_key_dtor (DWORD key, void (*dtor) (void *))
{
  if (dtor)
    {
      return ___mingwthr_add_key_dtor (key, dtor);
    }

  return 0;
}

__declspec(dllexport)
int
__mingwthr_remove_key_dtor (DWORD key )
{
   return ___mingwthr_remove_key_dtor ( key );
}
