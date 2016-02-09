# $Id$
#
# Configure script specification for compilation of cross-reference
# documentation for the symbols which are exported by various versions
# of MSVCRT.DLL and MSVCRxx.DLL
#
# Written by Keith Marshall <keithmarshall@users.sourceforge.net>
# Copyright (C) 2014, 2015, MinGW.org Project.
#
#
# This is free software.  Permission is granted to copy, modify and
# redistribute this software, under the provisions of the GNU General
# Public License, Version 3, (or, at your option, any later version),
# as published by the Free Software Foundation; see the file COPYING
# for licensing details.
#
# Note, in particular, that this software is provided "as is", in the
# hope that it may prove useful, but WITHOUT WARRANTY OF ANY KIND; not
# even an implied WARRANTY OF MERCHANTABILITY, nor of FITNESS FOR ANY
# PARTICULAR PURPOSE.  Under no circumstances will the author, or the
# MinGW.org Project, accept liability for any damages, however caused,
# arising from the use of this software.
#
AC_INIT
AC_CHECK_PROGS([CC],[gcc cc])

# To format the README file, for online display, we require nroff...
#
AC_CHECK_PROGS([NROFF],[nroff])
#
# ...while, to format the ultimate document provided by this package,
# we require the GNU implementation of troff, which we invoke with the
# formatting options specified in GROFF_FORMAT.
#
AC_CHECK_PROGS([GROFF],[groff])
AC_SUBST([GROFF_FORMAT],[${GROFF_FORMAT-"-d paper=a4 -P-pa4"}])
AC_ARG_VAR([GROFF_FORMAT], [formatting options for troff processing of
 the output document; defaults are "-d paper=a4 -P-pa4"
])

# The preferred document output format is as PDF; this requires that
# GhostScript is available to the formatter, in which case we invoke it
# with the associated set of flags...
#
AC_CHECK_PROGS([GS],[gswin32c gs])
AC_CHECK_PROGS([PDFROFF],[pdfroff])
AC_SUBST([GSFLAGS],[${GSFLAGS-"-dQUIET -dBATCH -dSAFER -dNOPAUSE"}])
AC_ARG_VAR([GSFLAGS], [invocation options for document post-processing
 with GhostScript; defaults are "-dQUIET -dBATCH -dSAFER -dNOPAUSE"
])
#
# ...but, in the event that it is unavailable, we simply fall back to
# document production in Postscript format.
#
AS_IF([test "x$GS" = "x"],[ac_val="ps"],[ac_val="pdf"])
AC_SUBST([OUTPUT_FORMAT],[${OUTPUT_FORMAT-"$ac_val"}])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

# $RCSfile$: end of file
