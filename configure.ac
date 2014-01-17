##
# @file configure.ac
# Copyright 2012-2014 MinGW.org project
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
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
##

#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([MinGW.org WSL], [4.0], [http://www.mingw.org/report_bugs], [mingw-org-wsl], [http://www.mingw.org])
AC_CONFIG_AUX_DIR([build-aux])
AC_PREFIX_DEFAULT([/mingw])
AC_CONFIG_SRCDIR([include/_mingw.h])
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

#When set to prod, meaning production release, the RELEASE_STATUS and
#RELEASE_REFERENCE are ignored.
AC_ARG_VAR([RELEASE_STATUS], [Release package status, prod, rc, alpha, etc])
AC_SUBST([RELEASE_STATUS], [${RELEASE_STATUS-"prod"}])
AC_ARG_VAR([RELEASE_REFERENCE], [Reference serial number for the release status])
AC_SUBST([RELEASE_REFERENCE], [${RELEASE_REFERENCE-"1"}])

AC_CONFIG_FILES([Makefile tests/Makefile])
AC_OUTPUT
