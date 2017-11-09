# configure.ac -*- Autoconf -*- vim: filetype=config
#
# Process this file with "autoreconf -I ..", to create configure scripts
# for the composite MinGW.org Runtime Library and Win-API packages.
#
# $Id$
#
# Written by Keith Marshall <keithmarshall@users.sourceforge.net>
# Copyright (C) 2016, MinGW.org Project
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
  AC_INIT([MinGW System Libraries],[__VERSION__],[__BUG_REPORT_URL__],[wsl])
  AC_PREFIX_DEFAULT([/mingw])

  AC_PROG_MKDIR_P
  AC_PATH_PROG([LN],[ln],[ln])

  AC_CONFIG_SUBDIRS([mingwrt wslapi])
  AC_CONFIG_FILES([Makefile])
  AC_OUTPUT
#
# $RCSfile$: end of file
