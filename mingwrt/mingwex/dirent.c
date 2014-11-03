/*
 * dirent.c
 *
 * This file has no copyright assigned and is placed in the Public Domain.
 *
 * This file is a part of the mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within the package.
 *
 * Derived from DIRLIB.C by Matt J. Weinstein
 * This note appears in the DIRLIB.H
 * DIRLIB.H by M. J. Weinstein   Released to public domain 1-Jan-89
 *
 * Updated by Jeremy Bettis <jeremy@hksys.com>
 * Significantly revised and rewinddir, seekdir and telldir added
 * by Colin Peters <colin@fu.is.saga-u.ac.jp>
 * Further significantly revised for improved memory utilisation,
 * efficiency in operation, and better POSIX standards compliance
 * by Keith Marshall <keithmarshall@users.sourceforge.net>
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>

#ifdef _UNICODE
  /* In a Unicode build, the path name within the _wdirent struct is
   * represented by a wchar_t string; we use the snwprintf() function
   * to simultaneously assign the d_name and d_namlen fields, copying
   * from a temporary WIN32_FIND_DATA struct on the stack...
   */
# include <wchar.h>
# define DIRENT_ASSIGN_NAME  snwprintf

#else
  /* ...while for a non-Unicode build, the corresponding data within
   * the dirent structure is represented by a normal char string, and
   * the assignments are made by the snprintf() function.
   */
# define DIRENT_ASSIGN_NAME  snprintf
#endif

/* This implementation applies a "__mingw_" pseudo-namespace prefix to
 * the standard POSIX function names, for each each function it defines;
 * the following pair of macros facilitates this.
 */
#define __mingw_impl__(__function__)  __mingw_token_prefix__(__function__)
#define __mingw_token_prefix__(__suffix__)  __mingw_##__suffix__

/* The following macros facilitate a conditional abort of any function,
 * while reporting a specified condition code via "errno".
 */
#define DIRENT_RETURN_NOTHING
#define DIRENT_REJECT( chk, err, rtn )	\
  do { if( chk ){ errno = (err); return rtn; }} while(0)

struct __dirstream_t
{
  /* Actual (private) declaration for opaque data type "DIR". */

  /* Encapsulated dirent struct to be returned.  (NOTE: this makes
   * this thread safe as long as only one thread uses a particular
   * DIR struct at any time)
   */
  struct dirent 	dd_dirent;

  /* Handle, for use when performing FindFirstFile()/FindNextFile()
   * file system searches.
   */
  void *		dd_handle;

  /* Index for next FindFirstFile()/FindNextFile() entry:
   *   0 = not started yet (next entry to read is first entry);
   *   positive value = 0 based index of next entry to be read;
   *   set to -1 when no more matching entries to be read.
   */
  int			dd_index;

  /* File name pattern to be matched in FindFirstFile() file system
   * search; note that the actual size will be adjusted at run time,
   * causing the DIR struct to grow to accommodate the pattern.
   */
  char			dd_name[1];
};

struct __wdirstream_t
{
  /* Actual (private) declaration for opaque data type "_WDIR". */

  /* Encapsulated dirent struct to be returned.  (NOTE: this makes
   * this thread safe as long as only one thread uses a particular
   * _WDIR struct at any time)
   */
  struct _wdirent	dd_dirent;

  /* Handle, for use when performing FindFirstFile()/FindNextFile()
   * file system searches.
   */
  void *		dd_handle;

  /* Index for next FindFirstFile()/FindNextFile() entry:
   *   0 = not started yet (next entry to read is first entry);
   *   positive value = 0 based index of next entry to be read;
   *   set to -1 when no more matching entries to be read.
   */
  int			dd_index;

  /* File name pattern to be matched in FindFirstFile() file system
   * search; note that the actual size will be adjusted at run time,
   * causing the DIR struct to grow to accommodate the pattern.
   */
  wchar_t		dd_name[1];
};

/* We map the BSD d_type field in the returned dirent structure
 * from the Microsoft WIN32_FIND_DATA.dwFileAttribute bits, which we
 * mask to retrieve these _finddata_t equivalents:
 *
 *   _A_NORMAL	(0x0000)	normal file: best fit for DT_REG
 *   _A_RDONLY	(0x0001)	read-only: no BSD d_type equivalent
 *   _A_HIDDEN	(0x0002)	hidden entity: no BSD equivalent
 *   _A_SYSTEM	(0x0004)	system entity: no BSD equivalent
 *   _A_VOLID	(0x0008)	volume label: no BSD equivalent
 *   _A_SUBDIR	(0x0010)	directory: best fit for DT_DIR
 *   _A_ARCH	(0x0020)	"dirty": no BSD equivalent
 *
 * Of these, _A_RDONLY, _A_HIDDEN, _A_SYSTEM, and _A_ARCH are
 * modifier bits, rather than true entity type specifiers; we
 * will ignore them in the mapping, by applying this mask:
 */
#define DT_IGNORED	(_A_RDONLY | _A_HIDDEN | _A_SYSTEM | _A_ARCH)

/* Microsoft have regally screwed up their _findfirst() and _findnext()
 * implementation, making its ABI arbitrarily dependent on the state of the
 * insane _USE_32BIT_TIME_T macro; thus, we can no longer depend on it to
 * return data in any deterministically structured manner.  Furthermore, the
 * first deterministic alternative, _findfirst64() and _findnext64(), which
 * they have provided, is not available in all versions of Windows which we
 * would like to support; thus, we must furnish our own implementation,
 * based on the more primitive FindFirstFile()/FindNextFile() API.
 *
 * Weirdly, when we use the FindFirstFile()/FindNextFile() API, (as
 * our dirent_findfirst()/dirent_findnext() functions do), _A_NORMAL
 * is represented by the value 0x0080; we need to suppress this:
 */
#define DT_VALID_BITS	~(DT_IGNORED | 0x0080)

static
void dirent_update( struct _tdirent *dd, WIN32_FIND_DATA *fd )
{
  /* Helper function, used by dirent_findfirst() and dirent_findnext(),
   * to transfer all relevant data from their respective WIN32_FIND_DATA
   * buffers to the specified dirent structure.
   */
  dd->d_namlen = DIRENT_ASSIGN_NAME( dd->d_name, FILENAME_MAX,
      _T("%s"), fd->cFileName
    );
  if( (dd->d_type = fd->dwFileAttributes & DT_VALID_BITS) > DT_DIR )
    dd->d_type = DT_UNKNOWN;
}

static
void *dirent_findfirst( const _TCHAR *lookup, struct _tdirent *dd )
{
  /* Replacement for Microsoft's _findfirst() function; it temporarily
   * captures the result of a FindFirstFile() call in a local buffer,
   * whence it updates the specified dirent structure, before returning
   * an opaque handle for subsequent use by FindNextFile().
   */
  void *fd;
  WIN32_FIND_DATA buf;
  if( (fd = FindFirstFile( lookup, &buf )) == INVALID_HANDLE_VALUE )
  {
    /* The look-up failed: set errno accordingly; (note that this
     * requires mapping of some system error codes to the equivalent
     * errno values prescribed by POSIX).
     */
    if( (errno = GetLastError()) == ERROR_PATH_NOT_FOUND )
      errno = ENOENT;

    else if( errno == ERROR_DIRECTORY )
      errno = ENOTDIR;

    else if( errno != ENOENT )
      errno = EINVAL;
  }
  else
    /* The look-up was successful: update the dirent structure.
     */
    dirent_update( dd, &buf );

  /* Ultimately, return the (possibly invalid) search handle
   * which FindFirstFile() has given us.
   */
  return fd;
}

#define DIRENT_OPEN(D)	\
    ((D)->dd_handle = dirent_findfirst((D)->dd_name, &((D)->dd_dirent)))

static
int dirent_findnext( void *fd, struct _tdirent *dd )
{
  /* Replacement for Microsoft's _findnext() function; it temporarily
   * captures the result of calling FindNextFile() in a local buffer,
   * whence it updates the specified dirent structure, before returning
   * an appropriate status value.
   */
  int status;
  WIN32_FIND_DATA buf;
  if( (status = FindNextFile( fd, &buf )) != 0 )
  {
    /* The look-up was successful; update the dirent structure, and
     * immediately return the (non-zero) status.
     */
    dirent_update( dd, &buf );
    return status;
  }

  /* If we get to here, the look-up was unsuccessful.  This may be
   * simply because there are no more files to find...
   */
  else if( (status = GetLastError()) != ERROR_NO_MORE_FILES )
    /*
     * ...but in any other case, we must update errno to reflect
     * an invalid position within the directory stream; (POSIX
     * prescribes ENOENT, for this error condition).
     */
    errno = ENOENT;

  /* In any case, for an unsuccessful look-up we always return
   * an effective status code of zero.
   */
  return 0;
}

#define DIRENT_UPDATE(D)  \
    dirent_findnext( (D)->dd_handle, &((D)->dd_dirent) )

/* For consistency, we also provide this simple wrapper for Microsoft's
 * FindClose() function, to clean up residual context from our replaced
 * _findfirst() and _findnext() functions.
 */
static __inline__ __attribute__((__always_inline__))
int dirent_findclose( void *fd ){ return FindClose( fd ); }


/*****
 *
 * opendir()
 *
 * Returns a pointer to a DIR structure appropriately filled in
 * to begin searching a directory.
 *
 */
_TDIR *
__mingw_impl__(_topendir)( const _TCHAR *path_name )
{
  _TDIR *nd;
  _TCHAR abs_path[MAX_PATH];

  /* Reject any request which passes a NULL or an empty path name;
   * note that POSIX doesn't specify the handling for the NULL case,
   * and some implementations may simply fail with a segmentation
   * fault.  We will fail more gracefully.  Previous versions used
   * EFAULT here, but EINVAL seems more appropriate; however, POSIX
   * specifies neither of these for any opendir() failure.
   */
  DIRENT_REJECT( (path_name == NULL), EINVAL, (_TDIR *)(NULL) );
  /*
   * Conversely, POSIX *does* specify ENOENT for the empty path
   * name case, where we previously had ENOTDIR; here, we correct
   * this previous anomaly.
   */
  DIRENT_REJECT( (*path_name == _T('\0')), ENOENT, (_TDIR *)(NULL) );

  /* Identify the absolute path name corresponding to the (maybe
   * relative) path name we are to process; (this ensures that we
   * may always refer back to this same path name, e.g. to rewind
   * the "directory stream", even after an intervening change of
   * current working directory).
   */
  _tfullpath( abs_path, path_name, MAX_PATH );

  /* Ensure that the generated absolute path name ends with a
   * directory separator (backslash) character, so that we may
   * correctly append a wild-card matching pattern which will
   * cause dirent_findfirst() and dirent_findnext() to return
   * every entry in the specified directory; (note that, for now
   * we may simply assume that abs_path refers to a directory;
   * we will verify that when we call dirent_findfirst() on it).
   */
  if( *abs_path != _T('\0') )
    {
      size_t offset = _tcslen( abs_path ) - 1;
      if( (abs_path[offset] != _T('/')) && (abs_path[offset] != _T('\\')) )
	_tcscat( abs_path, _T("\\") );
    }

  /* Now append the "match everything" wild-card pattern.
   */
  _tcscat( abs_path, _T("*") );

  /* Allocate space to store DIR structure.  The size MUST be
   * adjusted to accommodate the complete absolute path name for
   * the specified directory, extended to include the wild-card
   * matching pattern, as above; (note that we DO NOT need any
   * special provision for the terminating NUL on the path name,
   * since the base size of the DIR structure includes it).
   */
  nd = (_TDIR *)(malloc(
	 sizeof( _TDIR ) + (_tcslen( abs_path ) * sizeof( _TCHAR ))
       ));

  /* Bail out, if insufficient memory.
   */
  DIRENT_REJECT( (nd == NULL), ENOMEM, (_TDIR *)(NULL) );

  /* Copy the extended absolute path name string into place
   * within the allocated space for the DIR structure.
   */
  _tcscpy( nd->dd_name, abs_path );

  /* Initialize the "directory stream", by calling dirent_findfirst()
   * on it; this leaves the data for the first directory entry in the
   * internal dirent buffer, ready to be retrieved by readdir().
   */
  if( DIRENT_OPEN( nd ) == INVALID_HANDLE_VALUE )
    {
      /* The dirent_findfirst() call, (implied by DIRENT_OPEN), failed;
       * this will already have set errno appropriately, and we should
       * now prepare to return a NULL "directory stream" pointer; since
       * this implies that we will lose our reference pointer to the
       * block of memory we allocated for the stream, we must free
       * that before we bail out.
       */
      free( nd );
      return (_TDIR *)(NULL);
    }

  /* Initialize the status, (i.e. the location index), so that readdir()
   * will simply return the first directory entry, which has already been
   * fetched by dirent_findfirst(), without performing an intervening
   * dirent_findnext() call.
   */
  nd->dd_index = 0;

  /* The d_ino field has no relevance in MS-Windows; initialize it
   * to zero, as a one-time assignment for this DIR instance, and
   * henceforth forget them; (users should simply ignore it).
   */
  nd->dd_dirent.d_ino = 0;

  /* The d_reclen field represents the size, in bytes, of the dirent
   * struct within this DIR instance; (this may be useful for storage
   * of packed arrays of dirent structs, with truncated d_name fields,
   * but here, we need to keep the full size).  Initialize accordingly,
   * and henceforth forget it; we will never change it; users should
   * regard it as read-only, but we don't care if they do change it,
   * because we don't ever use it.
   */
  nd->dd_dirent.d_reclen = sizeof( struct _tdirent );

  /* We've now completely initialized an instance of a DIR structure,
   * representing the requested "directory stream"; return a pointer
   * via which the caller may access it.
   */
  return nd;
}


/*****
 *
 * readdir()
 *
 * Return a pointer to a dirent structure filled in with information
 * on the next available entry, (if any), in the "directory stream".
 */
struct _tdirent *
__mingw_impl__(_treaddir)( _TDIR *dirp )
{
  /* Check for a valid DIR stream reference; (we can't really
   * be certain until we try to read from it, except in the case
   * of a NULL pointer reference).  Where we lack a valid reference,
   * POSIX mandates reporting EBADF; we previously had EFAULT, so
   * this version corrects the former anomaly.
   */
  DIRENT_REJECT( (dirp == NULL), EBADF, (struct _tdirent *)(NULL) );

  /* Okay to proceed.  Unless this is the first readdir() request
   * following an opendir(), or a rewinddir(), (in which case the
   * current location index will be zero, and the requisite return
   * information will have been established already), we need to
   * update the DIR stream data, retrieving the data for the next
   * directory entry...
   */
  if( (dirp->dd_index++ > 0) && (DIRENT_UPDATE( dirp ) == 0) )
    /*
     * ...bailing out, if no such data is retrievable...
     */
    return (struct _tdirent *)(NULL);

  /* ...otherwise, returning the requisite data pointer.
   */
  return &dirp->dd_dirent;
}


/*****
 *
 * closedir()
 *
 * Frees up resources allocated by opendir().
 *
 */
int
__mingw_impl__(_tclosedir)( _TDIR * dirp )
{
  /* Attempting to reference a directory stream via a NULL pointer
   * would cause a segmentation fault; evade this.  Since NULL can
   * never represent an open directory stream, set the EBADF errno
   * status, as mandated by POSIX, once again correcting previous
   * anomalous use of EFAULT in this context.
   */
  DIRENT_REJECT(
      ((dirp == NULL) || (dirent_findclose( dirp->dd_handle ) == 0)),
	EBADF, -1
    );

  /* If we didn't bail out above, we have a valid DIR structure
   * with which we have finished; release the memory allocated
   * to it, before returning "success".
   */
  free( dirp );
  return 0;
}


/*****
 *
 * rewinddir()
 *
 * Return to the beginning of the directory "stream".  We simply call
 * dirent_findclose(), to clear prior context, then dirent_findfirst()
 * to restart the directory search, resetting the location index as it
 * would have been left by opendir().
 *
 */
void
__mingw_impl__(_trewinddir)( _TDIR * dirp )
{
  /* This is an XSI extension to POSIX, which specifies no formal
   * error conditions; we will continue to check for and evade the
   * potential segmentation fault which would result from passing a
   * NULL reference pointer.  For consistency with the core functions
   * implemented above, we will again report this as EBADF, rather
   * than the EFAULT of previous versions.
   */
  DIRENT_REJECT(
      ((dirp == NULL) || (dirent_findclose( dirp->dd_handle ) == 0)),
	EBADF, DIRENT_RETURN_NOTHING
    );

  /* We successfully closed the prior search context; reopen...
   */
  if( DIRENT_OPEN( dirp ) != INVALID_HANDLE_VALUE )
    /*
     * ...and, on success, reset the location index.
     */
    dirp->dd_index = 0;
}


/*****
 *
 * telldir()
 *
 * Returns the "position" in the "directory stream" which can then
 * be passed to seekdir(), to return back to a previous entry.  We
 * simply return the current location index.
 *
 */
long
__mingw_impl__(_ttelldir)( _TDIR * dirp )
{
  /* This too is a POSIX-XSI extension, with no mandatory error
   * conditions.  Once again, evade a potential segmentation fault
   * on passing a NULL reference pointer, again reporting it as
   * EBADF in preference to the EFAULT of previous versions.
   */
  DIRENT_REJECT( (dirp == NULL), EBADF, -1 );

  /* We didn't bail out; just assume dirp is valid, and return
   * the current location index.
   */
  return dirp->dd_index;
}


/*****
 *
 * seekdir()
 *
 * Seek to an entry previously returned by telldir().  We rewind
 * the "directory stream", then repeatedly call dirent_findnext()
 * while incrementing its internal location index until it matches
 * the position requested, or we reach the end of the stream.  This
 * is not perfect, in that the directory may have changed while we
 * weren't looking, but it is the best we can achieve, and may
 * likely reproduce the behaviour of other implementations.
 *
 */
void
__mingw_impl__(_tseekdir)( _TDIR * dirp, long loc )
{
  /* Another POSIX-XSI extension, with no specified mandatory
   * error conditions; we require a seek location of zero or
   * greater, and will reject less than zero as EINVAL...
   */
  DIRENT_REJECT( (loc < 0L), EINVAL, DIRENT_RETURN_NOTHING );

  /* Other than this, we simply accept any error condition
   * which arises as we "rewind" the "directory stream"...
   */
  __mingw_impl__(_trewinddir)( dirp );

  /* ...and, if this is successful...
   */
  if( (loc > 0) && (dirp->dd_handle != INVALID_HANDLE_VALUE) )
    /*
     * ...seek forward until the location index within
     * the DIR structure matches the requested location.
     */
    while( (++dirp->dd_index < loc)
      &&   (DIRENT_UPDATE( dirp ) != 0)  )
      ;
}

/* $RCSfile$: end of file */
