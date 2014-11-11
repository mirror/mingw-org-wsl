/*
 * dlfcn.c
 *
 * Core implementation for (approximately) POSIX conforming dlopen(),
 * dlsym(), dlclose(), and dlerror() API functions.
 *
 * $Id$
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 * Copyright (C) 2014, MinGW.org Project
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
 *
 * This source file implements the core functionality for each of the POSIX
 * dynamic loader API functions, dlopen(), dlsym(), dlclose(), and dlerror();
 * each is implemented such that it is conveniently accessed via a macro, or
 * an inline function representation, by way of a publicly visible table of
 * entry point vectors (i.e. function pointers).
 *
 */
#include <dlfcn.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

/* In addition to normal C runtime services, this implementation requires
 * the use of the MS-Windows API; the light-weight subset will suffice...
 */
#define WIN32_LEAN_AND_MEAN
/*
 * ...while accessing it throught its standard interface.
 */
#include <windows.h>

/* In addition to the POSIX constants which are defined in dlfcn.h,
 * we also define some private manifest constants, which POSIX does
 * not specify, but which facilitate our implementation:
 *
 *   RTLD_EXPLICIT, used to qualify RTLD_GLOBAL modules which have
 *   been explicitly loaded by dlopen(), so an RTLD_DEFAULT search
 *   need not consider them.
 */
# define RTLD_EXPLICIT     16
/*
 *   RTLD_ALL_GLOBAL, returned by dlopen() when the module name is
 *   given as a NULL pointer; this is a fake module handle, similar
 *   to RTLD_DEFAULT and RTLD_NEXT, representing the corpus of all
 *   RTLD_GLOBAL modules, both implicitly and explicitly loaded.
 */
# define RTLD_ALL_GLOBAL  (void *)(-5)

/* Before anything else, ensure that the dlerror() implementation
 * is in place, so that other components may access it freely.
 *
 * We provide TWO reference pointers for error message buffering, so
 * that we may continue to hold a reference to allocated memory, even
 * after dlerror() has discarded the pointer to a pending message;
 * initially, we mark both as unassigned.
 */
static char *dlfcn_error_pending = NULL;
static char *dlfcn_error_message = NULL;

static void dlfcn_store_error_message( const char *fmt, ... )
{
  /* This private function provides printf() style formatting for
   * dlfcn error messages, storing them into dynamically allocated
   * memory, and updating both reference pointers for subsequent
   * retrieval by the dlerror() accessor function.
   */
  int msglen;
  va_list argv;
  va_start( argv, fmt );
  msglen = 1 + vsnprintf( NULL, 0, fmt, argv );
  if( (dlfcn_error_pending = realloc( dlfcn_error_message, msglen )) != NULL )
    /*
     * Store message, only if a buffer was successfully allocated.
     */
    vsnprintf( dlfcn_error_pending, msglen, fmt, argv );
  dlfcn_error_message = dlfcn_error_pending;
  va_end( argv );
}

static char *dlfcn_strerror( int errcode )
{
  /* This private function emulates strerror(), but substitutes an
   * errcode obtained from GetLastError() for errno.
   */
  char *text;
  uint32_t description = FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER
      | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL,
      errcode, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), (char *)(&text),
      0, NULL
    );
  if( description )
  {
    /* We successfully obtained an error description; POSIX insists
     * that it must not be encoded with any terminating newline.
     */
    char *tmp = text + strlen( text );
    while( (*--tmp == '\n') || (*tmp == '\r') ) *tmp = '\0';

    /* Ensure that we consistently return the error description in
     * a buffer which may be released by the free() function, (since
     * we cannot be sure that LocalFree() is compatible).
     */
    text = strdup( tmp = text );
    LocalFree( tmp );
  }
  else
  { /* We were unable to find an error description; substitute a
     * formatted reference to the unknown error code.
     */
    char *fmt = "Unknown error %d";
    char tmp[1 + snprintf( NULL, 0, fmt, errcode )];
    snprintf( tmp, sizeof( tmp ), fmt, errcode );
    text = strdup( tmp );
  }
  /* However we derived it, the error description is now available
   * in a dynamically allocated text buffer which may be released
   * by calling free().
   */
  return text;
}

static char *dlerror_internal( void )
{
  /* This is the internal implementation of the public dlerror() API.
   * POSIX does not require this to be thread safe, so we take no care
   * to make it such.
   */
  if( (dlfcn_error_pending == NULL) && (dlfcn_error_message != NULL) )
  {
    /* There is no pending message, but a buffer remains allocated
     * to one which has already been retrieved; we may release it.
     */
    free( dlfcn_error_message );
    dlfcn_error_message = NULL;
  }
  /* Mark any pending error message as "retrieved"...
   */
  dlfcn_error_pending = NULL;
  /*
   * ...and return it.
   */
  return dlfcn_error_message;
}

typedef
/* A pointer type, representing a reference to a function for
 * retrieving exported symbol references from any loaded module.
 */
int WINAPI (*lookup_fn)( HANDLE, HMODULE *, uint32_t, uint32_t * );

/* POSIX requires that dlsym() be able to look up symbol references
 * for any dynamically loaded module within the address space of the
 * calling process, including those which have been implicitly loaded
 * at process start-up.  To facilitate this, we will use Microsoft's
 * PSAPI.DLL services, to enumerate such implicitly loaded modules,
 * before we explicitly load any using dlopen(), or we perform any
 * look-up using dlsym() itself.
 */
static struct
{ /* Structure providing a convenient encapsulation of the PSAPI.DLL
   * interface, which may itself need to be explicitly loaded.
   */
  HMODULE	 dll;
  const char	*dll_name;
  const char	*lookup_fn_name;
  lookup_fn	 lookup;
}
psapi = { NULL, "psapi.dll", "EnumProcessModules", NULL };

/* The two NULL fields, within the preceding structure, must be
 * initialized before use; the following pair of inline functions
 * facilitate this, with the first looking up the API entry...
 */
static __inline__ lookup_fn psapi_lookup_fn( HMODULE provider )
{ return (lookup_fn)(GetProcAddress( provider, psapi.lookup_fn_name )); }

/* ...when called from within the second, which both ensures that
 * PSAPI.DLL is loaded, and assigns the requisite field values.
 */
static __inline__ lookup_fn psapi_lookup_fn_init( void )
{ return psapi.lookup = ((psapi.dll = LoadLibrary( psapi.dll_name )) != NULL)
    ? psapi_lookup_fn( psapi.dll ) : NULL;
}

/* After the PSAPI.DLL interface has been initialized, by calling
 * the preceding function, we may call the following inline helper
 * to retrieve a list of module handles...
 */
static __inline__ unsigned int psapi_enum_modules( HMODULE **modules )
{
  /* ...focussing on modules which are currently loaded within
   * the address space of the current process.
   */
  HANDLE me = GetCurrentProcess();

  /* We will dynamically allocate memory to store the handles;
   * initially we request zero bytes of storage to receive them,
   * then we use a while loop, which should execute exactly twice,
   * to retrieve them; on the first pass, we determine the actual
   * memory requirement and allocate it; on the second, we store
   * the list of module handles into it...
   */
  uint32_t wanted, request = 0;
  while( psapi.lookup( me, *modules, request, &wanted ) && (wanted > request) )
    if( (*modules = realloc( *modules, request = wanted )) == NULL )
    {
      /* ...trying to record an appropriate diagnostic message on
       * failure, (but noting that failure is likely to result from
       * insufficient memory, so there may not be enough to record
       * the message either)...
       */
      char *reason = dlfcn_strerror( ERROR_OUTOFMEMORY );
      dlfcn_store_error_message( "dlfcn_init:enum_modules: %s", reason );
      free( reason );
    }
  /* ...before ultimately returning the number retrieved.
   */
  return wanted / sizeof( HMODULE );
}

typedef struct dltab
{
  /* Structure used to map module handle references, and associated
   * status, into the global modules list.
   */
  unsigned int   slots;
  unsigned char *flags;
  HMODULE	*modules;
} dltab;

/* The global modules list itself, initially empty, but suitable
 * for reallocation on the heap.
 */
static dltab rtld = { 0, NULL, NULL };

/* Microsoft's LoadLibrary() API is explicitly documented as being
 * unable to handle regular slashes as directory separators in module
 * path names, (in spite of their validity elsewhere), thus...
 */
static __inline__ wchar_t *normalized_form( wchar_t *pathname )
{
  /* ...we provide this helper, to replace them with backslashes.
   */
  wchar_t *scan = pathname;
  do { if( *scan == L'/' ) *scan = L'\\'; } while( *scan++ != L'\0' );
  return pathname;
}

static void dlopen_store_error_message( const char *name, unsigned status )
{
  /* A convenience helper, to record diagnostic messages to explain
   * causes of failure encountered when calling dlopen().
   */
  char *reason = dlfcn_strerror( status );
  dlfcn_store_error_message( "dlopen:'%s': %s", name, reason );
  free( reason );
}

static void *dlopen_internal( const char *name, int mode )
{
  /* This is the formal implementation of the public dlopen() function;
   * note that this (currently) ignores the RTLD_LAZY loading option, and
   * processes each request as if specified as RTLD_NOW.
   */
  if( name == NULL )
    /* POSIX specifies this as a special case, requiring us to return
     * a handle, through which all symbols exported by all modules which
     * are currently loaded with the RTLD_GLOBAL attribute, (explicitly
     * or implicitly), would be accessible.
     */
    return RTLD_ALL_GLOBAL;

  /* We will use LoadLibrary() to obtain a handle for the dlopen()ed
   * module; Microsoft advise us that we should ensure that we always
   * use backslashes, and to avoid use of POSIX compatible slashes, in
   * any path name passed to this function.  To ensure this, the name
   * argument should be normalized, (working in the UTF-16LE domain,
   * to avoid inadvertent transformation of trail bytes within MBC
   * sequences), to transform slashes accordingly.
   */
  size_t buflen; wchar_t internal_name[buflen = 1 + strlen( name )];
  MultiByteToWideChar( CP_ACP, 0, name, -1, internal_name, buflen );

  /* Now, we may safely call LoadLibrary(), to obtain a module handle.
   */
  void *module = LoadLibraryW( normalized_form( internal_name ) );
  if( module == NULL )
  {
    /* The named module could not be opened; record an appropriate
     * error message for retrieval by dlerror().
     */
    dlopen_store_error_message( name, GetLastError() );
  }
  else
  { /* We got a handle for the requested module; we need to ensure
     * that it is allocated a slot in our global symbol table, but we
     * must first check that it isn't already present.
     */
    int index, insertion_point = rtld.slots;
    for( index = 0; index < rtld.slots; index++ )
    {
      /* As we scan the list of already loaded modules, check for any
       * existing slot which may be vacant...
       */
      if( rtld.flags[index] == 0 )
      {
	/* ...marking the first available, if any, as a candidate for
	 * possible insertion of a new entry.
	 */
	if( index < insertion_point )
	  insertion_point = index;
      }
      else if( module == rtld.modules[index] )
      {
	/* The requested module appears to be loaded already; calling
	 * LoadLibrary() will have increased its reference count, but
	 * our management strategy doesn't require this; reduce it...
	 */
	FreeLibrary( module );
	/*
	 * ...but promote its existing status to RTLD_GLOBAL, if that
	 * is indicated as required by the requested mode...
	 */
	rtld.flags[index] |= mode & RTLD_GLOBAL;
	/*
	 * ...and immediately return the module handle.
	 */
	return module;
      }
    }
    /* If we get to here, there is no entry for the requested module,
     * within the global modules list; we must add it now, either using
     * an existing vacant slot, if there is one...
     */
    if( insertion_point < rtld.slots )
    {
      /* ...but noting that we cannot simply insert a new reference
       * within it, since that would disrupt the order in which modules
       * are subsequently searched, and POSIX requires that this is to
       * preserve loading order, (strictly, symbol resolution order),
       * when searching RTLD_GLOBAL modules, (and since any module may
       * be promoted to RTLD_GLOBAL status, even after it was originally
       * loaded as RTLD_LOCAL, this means that we must preserve loading
       * order for ALL active modules).  Thus, we must pack the list of
       * active modules after the nominated insertion point...
       */
      index = insertion_point;

      /* ...after which, the first vacant slot will have been relocated
       * to follow all active slots, and we may adjust the nominated
       * insertion point accordingly.
       */
      do { /* First, we identify the first slot following the nominated
	    * insertion point, which is NOT vacant.
	    */
	   while( (index < rtld.slots) && (rtld.flags[index] == 0) )
	     ++index;

	   /* Now, we move that non-vacant slot, and any which follow
	    * it, upwards in the list, to fill vacant slots...
	    */
	   while( (index < rtld.slots) && (rtld.flags[index] != 0) )
	   {
	     /* ...by simply copying content from the non-vacant slots
	      * to overwrite content in the preceding slots...
	      */
	     rtld.modules[insertion_point] = rtld.modules[index];
	     rtld.flags[insertion_point++] = rtld.flags[index++];
	   }
	   /* ...repeating the entire procedure, until all vacant slots
	    * have been filled, and the nominated insertion point has
	    * been moved to follow the last relocated non-vacant entry.
	    */
	 } while( index < rtld.slots );

      /* After packing, any already allocated slots after and including
       * the relocated insertion point MUST be vacant; ensure that they
       * are marked accordingly.
       */
      for( index = insertion_point; index < rtld.slots; index++ )
	rtld.flags[index] = 0;
    }
    else
    { /* There is no vacant slot: we must expand the allocated memory
       * pool to create one; first increment the modules list size...
       */
      size_t slots = 1 + rtld.slots;
      HMODULE *modules = rtld.modules;
      if( (modules = realloc( modules, sizeof( HMODULE ) * slots )) != NULL )
      {
	/* ...and, having sucessfully increased the modules list memory
	 * allocation, do likewise for the associated flags...
	 */
	unsigned char *flags = rtld.flags;
	if( (flags = realloc( flags, slots )) != NULL )
	  /*
	   * ...initializing the new flags register, and incrementing
	   * the slots count, when that is also successful.
	   */
	  (rtld.flags = flags)[rtld.slots++] = 0;

	/* Regardless of the success, or otherwise, of the flags memory
	 * adjustment, the modules list was reallocated, so we need to
	 * adjust its reference pointer accordingly.
	 */
	rtld.modules = modules;
      }
      /* Before proceeding further, verify that the new slot has been
       * fully created, and is ready to store the module data...
       */
      if( insertion_point == rtld.slots )
      {
	/* ...but if allocation failed, the nominated insertion point
	 * will lie beyond the available space, so we MUST fail, after
	 * discarding the now unreferenced module handle, and trying to
	 * record an appropriate diagnostic message, (but we note that
	 * this may also fail, due to insufficient memory).
	 */
	FreeLibrary( module );
	dlopen_store_error_message( name, ERROR_OUTOFMEMORY );
	return NULL;
      }
    }
    /* When we get to here, we now have a suitable slot in which to add
     * the reference data for the newly dlopen()ed module, (either by
     * allocation of a new slot, or by relocation of an existing vacant
     * slot); we may safely store the appropriate reference data.
     */
    rtld.flags[insertion_point] = RTLD_EXPLICIT | mode;
    rtld.modules[insertion_point] = module;
  }
  /* Finally, we return whatever module handle we got from LoadLibrary(),
   * (which may be NULL, if this failed).
   */
  return module;
}

static void *dlsym_internal( void *module, const char *name )
{
  /* This is the formal implementation of the public dlsym() function.
   */
  static unsigned int index = 0;
  static const char *last_named_symbol = NULL;
  static unsigned char rtld_exclude = 0;
  void *rtn;

  if( module == RTLD_NEXT )
  {
    /* NOTE: We MUST identify this special case BEFORE any other!
     *
     * POSIX doesn't require this to be supported yet, but reserves it
     * for future use; it should cause dlsym() to repeat its search for
     * the named symbol, (provided it remains the same as last named in
     * a global search), continuing from the next module in the current
     * search order, following that in which the symbol was previously
     * found; (this permits us to locate symbols which may defined in
     * more than one loaded module).
     */
    index = (name == last_named_symbol) ? index + 1 : 0;
    module = RTLD_ALL_GLOBAL;
  }
  else if( module == RTLD_DEFAULT )
  {
    /* NOTE: We MUST keep this AFTER the check for RTLD_NEXT!
     *
     * Once again, POSIX doesn't require this to be supported yet, but
     * reserves it for future use to search for symbols which could have
     * been found within the process address space prior to any explicit
     * dlopen() call; this capability may be supported by searching all
     * modules in the address space, (i.e. equivalent to a search with
     * module == RTLD_ALL_GLOBAL), excluding those which have been
     * explicitly loaded since process start-up.
     */
    module = RTLD_ALL_GLOBAL;
    rtld_exclude = RTLD_EXPLICIT;
    index = 0;
  }
  else
    /* Neither RTLD_DEFAULT, nor RTLD_NEXT was specified; we must reset
     * the RTLD_GLOBAL search index, and cancel all search exclusions.
     */
    index = rtld_exclude = 0;

  if( module == RTLD_ALL_GLOBAL )
  {
    /* The RTLD_ALL_GLOBAL module reference represents a request to
     * perform an in-order traversal of all modules within the process
     * address space, either implicitly loaded, or explicitly loaded
     * with the RTLD_GLOBAL mode attribute, either until the named
     * symbol is found, or all such modules have been searched
     * without finding it.
     */ 
    for( rtn = NULL; (rtn == NULL) && (index < rtld.slots); index++ )
      if( ((rtld_exclude & rtld.flags[index]) == 0)
      &&  ((rtld.flags[index] & RTLD_GLOBAL) == RTLD_GLOBAL)  )
	rtn = GetProcAddress( rtld.modules[index], name );

    /* Note the symbol named in the current search, so that we may
     * check for consistency in the event that the next search is
     * invoked as an RTLD_NEXT request.
     */
    last_named_symbol = name;
  }
  else
  { /* When a specific module reference is specified, confine the
     * search to the specified module alone...
     */
    rtn = GetProcAddress( (HMODULE)(module), name );

    /* ...and inhibit any attempt to follow this search with one
     * specifying RTLD_NEXT; (this would not be valid, since there
     * is no concept of a "next" module to be searched, when not
     * searching through an ordered list of modules).
     */
    last_named_symbol = NULL;
  }

  if( rtn == NULL )
  {
    /* The named symbol was not found in any module which was searched;
     * record the appropriate error message for retrieval by dlerror().
     */
    char *reason = dlfcn_strerror( GetLastError() );
    dlfcn_store_error_message( "dlsym:'%s': %s", name, reason );
    free( reason );
  }

  /* Return the symbol address, as assigned to the return value;
   * (this will be NULL, if the named symbol was not found).
   */
  return rtn;
}

static int dlclose_store_error_message( int status )
{
  /* A private helper function to record an appropriate dlerror()
   * message, on failure of dlclose().
   */
  char *reason = dlfcn_strerror( status = GetLastError() );
  dlfcn_store_error_message( "dlclose: %s", reason );
  free( reason );
  return status;
}

static __inline__ int dlclose_internal_check_for_error( int status )
{
  /* A private helper function to set the return status for dlclose(),
   * while also recording a dlerror() message, when status is "failed".
   */
  return (status == 0) ? dlclose_store_error_message( status ) : 0;
}

static int dlclose_internal( void *module )
{
  /* This is the formal implementation of the public dlclose() function;
   * it will call Microsoft's FreeLibrary() function passing the specified
   * module handle, provided this is listed in the global module table as
   * having been explicitly opened by our dlopen() function.
   */
  int index;
  for( index = 0; index < rtld.slots; index++ )
    if( module == rtld.modules[index] )
    {
      /* The specified module handle is present in the global modules list;
       * while we could simply call FreeLibrary() immediately, it may not be
       * prudent to do so in respect of implicitly loaded modules, but for
       * those which we have explicitly loaded...
       */
      if( ((rtld.flags[index] & RTLD_EXPLICIT) == RTLD_EXPLICIT)
      /*
       * ...and which can be successfully released by FreeLibrary()...
       */
      &&  (dlclose_internal_check_for_error( FreeLibrary( module )) == 0)  )
	/*
	 * ...we mark them as no longer available for dlsym() processing,
	 * and return immediately, indicating success...
	 */
	return rtld.flags[index] = 0;

      /* ...but when we didn't successfully release the module, we have
       * no need to continue the search for its handle in the global list
       * of modules, (because we've already found it); we may immediately
       * abandon the search.
       */
      break;
    }

  /* If we get to here, we either didn't find the specified module handle in
   * the global list of modules, or we found it but were unable to release
   * it; in either case, we force a module error condition.
   */
  return dlclose_store_error_message( FreeLibrary( NULL ) );
}

static void dlfcn_init( void )
{
  /* This private initialization function must be called, as a
   * prerequisite to the first use of either dlopen() or dlsym()
   * in any process; it uses Microsoft's PSAPI.DLL interface to
   * enumerate the implicitly loaded process modules, so that
   * they may be searched implicitly by dlsym().
   */
  if( psapi_lookup_fn_init() == NULL )
  {
    /* Initialization of the PSAPI.DLL interface failed.  Record
     * this for possible retrieval by dlerror(); we can do no more,
     * so the list of implicitly loaded mudules will remain empty.
     */
    char *reason = dlfcn_strerror( GetLastError() );
    dlfcn_store_error_message( "dlfcn_init:%s: %s", psapi.dll_name, reason );
    free( reason );
  }
  else
  { /* We've acquired a reference for the PSAPI EnumProcessModules()
     * service; invoke it, to obtain a list of all modules which are
     * currently accessible, within the address space of the current
     * process, (which we assume to represent all modules which were
     * loaded implicitly, at process start-up)...
     */
    rtld.slots = psapi_enum_modules( &(rtld.modules) );
    /*
     * ...but, noting that we explicitly added a refererence for the
     * PSAPI.DLL services interface, which we needed to acquire this
     * list, we may now discard that reference.
     */
    FreeLibrary( psapi.dll );

    /* Provided we've obtained a non-empty list of modules...
     */
    if(  (rtld.modules != NULL)
    /*
     * ...and we can successfully allocate storage for an associated
     * collection of flags registers, (one per module)...
     */
    &&  ((rtld.flags = realloc( rtld.flags, rtld.slots )) != NULL)  )
    {
      /* ...examine each reference in the modules list, and for each
       * which is not NULL...
       */
      unsigned int index;
      for( index = 0; index < rtld.slots; index++ )
	if( (rtld.modules[index] != NULL)
	/*
	 * ...and which is not the PSAPI.DLL reference we've already
	 * released...
	 */
	&&  ((rtld.modules[index] != psapi.dll)
	/*
	 * ...unless it continues to provide a valid reference to the
	 * PSAPI EnumProcessModules() service, (which indicates that
	 * the associated DLL had been implicitly loaded, BEFORE we
	 * explicitly requested it)...
	 */
	||  (psapi_lookup_fn( psapi.dll ) == psapi.lookup))  )
	  /*
	   * ...then we set the associated flags to indicate that the
	   * module was implicitly loaded and globally accessible...
	   */
	  rtld.flags[index] = RTLD_GLOBAL;
	else
	  /* ...otherwise, we mark it as if dlclose() has already been
	   * implicitly called, to discard it.
	   */
	  rtld.flags[index] = 0;

      /* Having thus populated the global modules list, on first call
       * to either dlopen() or dlsym(), we don't need to (and indeed we
       * shouldn't) do this again; redirect each of these two calls to
       * their respective internal handlers.
       */
      __mingw_dlfcn.dlopen = dlopen_internal;
      __mingw_dlfcn.dlsym = dlsym_internal;
    }
  }
}

/* The global symbol table needs to be initialized, before we process
 * the first call to either dlopen() or dlsym(); the following pair of
 * initializer functions take care of this requirement, before passing
 * the first-time request to the appropriate internal handler.
 */
static void *dlopen_init( const char *name, int mode )
{ dlfcn_init(); return dlopen_internal( name, mode ); }

static void *dlsym_init( void *module, const char *name )
{ dlfcn_init(); return dlsym_internal( module, name ); }

/* Finally, we may define the __mingw_dlfcn structure, and set up its
 * initial function pointers, referring to the four API functions...
 */
struct __dlfcn__ __mingw_dlfcn =
{ dlopen_init,		/* dlopen() implementation, with initialization. */
  dlsym_init,		/* dlsym() implementation, with initialization.  */
  dlerror_internal,	/* dlerror() implementation; (direct reference). */
  dlclose_internal	/* dlclose() implementation; (direct reference). */
};

/* $RCSfile$: end of file */
