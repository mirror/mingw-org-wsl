# configure.ac -*- Autoconf -*- vim: filetype=config
#
# Process this file with autoconf, to create a configure script for
# the MinGW.org 32-bit MS-Windows API package.
#
# $Id$
#
# Written by Keith Marshall <keithmarshall@users.sourceforge.net>
# Copyright (C) 2015, 2016, MinGW.org Project
#
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice (including the next
# paragraph) shall be included in all copies or substantial portions of the
# Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR THE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#
  AC_PREREQ([2.64])
  AC_INIT([MinGW Win32 API],[3.18.2],[http://mingw.org/Reporting_Bugs],[w32api])

  AC_PREFIX_DEFAULT([/mingw])
  AC_CONFIG_SRCDIR([include/w32api.h.in])
  MINGW_AC_CONFIG_EXTRA_SRCDIR([mingwrt],[include/_mingw.h.in])

  MINGW_AC_PROG_CC_COMPILE_ONLY

  AC_CHECK_TOOL([AS],[as],[as])
  AC_CHECK_TOOL([DLLTOOL],[dlltool],[dlltool])
  AC_CHECK_TOOL([STRIP],[strip],[strip])

  AC_CHECK_TOOL([AR],[ar],[ar])
  AC_ARG_VAR([ARFLAGS],[ar mode flags for creation of archive libraries [rcs]])
  AC_SUBST([ARFLAGS],[${ARFLAGS-"rcs"}])
  AC_PROG_RANLIB

  AC_PROG_INSTALL
  AC_PROG_MKDIR_P

  AC_CONFIG_FILES([Makefile])
  AC_OUTPUT
#
# $RCSfile$: end of file
