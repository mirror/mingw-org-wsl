#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([MinGW.org WSL], [4.0], [http://www.mingw.org/report_bugs], [mingw.org-wsl], [http://www.mingw.org])
AC_CONFIG_AUX_DIR([build-aux])
AC_PREFIX_DEFAULT([/mingw])
AC_CONFIG_SRCDIR([include/_mingw.h])
AC_CONFIG_HEADERS([config.h])
AC_CANONICAL_SYSTEM

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MKDIR_P
AC_PROG_RANLIB
AC_CHECK_TOOL([AS], [as], [as])
AC_CHECK_TOOL([DLLTOOL], [dlltool], [dlltool])

AC_ARG_VAR([PACKAGE_RELEASE], [Release serial number for the current PACKAGE_VERSION])
AC_SUBST([PACKAGE_RELEASE], [${PACKAGE_RELEASE-"1"}])

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h fenv.h float.h inttypes.h limits.h locale.h malloc.h memory.h stddef.h stdint.h stdlib.h string.h strings.h sys/file.h sys/param.h sys/time.h sys/timeb.h unistd.h values.h wchar.h wctype.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_CHECK_MEMBERS([struct stat.st_rdev])
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MBRTOWC
AC_FUNC_MKTIME
AC_FUNC_REALLOC
AC_FUNC_STRCOLL
AC_FUNC_STRTOD
AC_CHECK_FUNCS([atexit btowc bzero dup2 fesetround floor ftime ftruncate getcwd gethostbyaddr gethostbyname gethostname gettimeofday inet_ntoa isascii iswprint localeconv mblen mbrlen memchr memmove memset mkdir modf pow putenv rint rmdir select setlocale socket sqrt strcasecmp strchr strcspn strdup strerror strncasecmp strpbrk strrchr strspn strstr strtol strtoul strtoull strtoumax tzset utime])

AC_CONFIG_FILES([Makefile tests/Makefile])
AC_OUTPUT
