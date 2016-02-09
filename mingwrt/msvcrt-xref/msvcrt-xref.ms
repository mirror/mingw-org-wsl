.nr HY  0
.nr PO  1.5c
.nr FM  1.7c
.nr LT 18.0c
.nr LL 18.0c
.ds TITLE Symbols Exported by the Microsoft C Runtime Dynamic Link Library
.nr PSINCR 1.5p
.nr GROWPS 2
.
.mso pdfmark.tmac
.pdfview /PageMode /UseOutlines
.
.if duplex \{\
.   rn pg@top pg@top-orig
.   de pg@top nr
.      ie e .nr PO 1.5c
.      el   .nr PO 2.0c
.      pg@top-orig
.   nr LT 17.5c
.   nr LL 17.5c
.\}
.
.TL
.sp |3.0c
.pdfhref O 1 "Front Matter"
\*[TITLE]
.AU
Copyright \(co 2014, 2015, 2016, Keith Marshall
.QP
.nr midway \n(.p+\n(nl/2-3c
.sp |\n[midway]u
Permission is granted to copy, distribute and/or modify this document
under the terms of the GNU Free Documentation License, Version 1.3
or any later version published by the Free Software Foundation,
with no Invariant Sections, no \%Front-Cover Texts, and no \%Back-Cover Texts.
A copy of the license is included in the appendix entitled \(lqGNU
Free Documentation License\(rq.
.de EJ EJ
.   if o \{\
.      ie duplex \{\
.         EH ''''
.         bp
.         EH '\*(LH'\*(CH'\*(RH'
.         rs
.      \}
.      el .pn +2
.   \}
.EJ
.OH ''''
.bp
.de SS SS
.   ie '\\$1'C' \{\
.      shift
.      SH \\$1
.      ce 1
.      \}
.   el .SH \\$1
.   pdfhref O \\$@
.   shift
.   nop \\$*
.SS 1 "\*[TITLE]"
.OH '\*(LH'\*(CH'\*(RH'
.LP
The following pages tabulate the symbols\**, with \(oqextern "C"\(cq binding,
which have been exported by various versions of the Microsoft\(tm C runtime library.
.FS
Symbol names have been identified by running the \fCpexports\fP tool,
from \fCMinGW.org\fP, on original copies of the respective versions of
the dynamic link libraries, ignoring symbols which exhibit mangled names
indicative of C++ binding, together with a few others, (viz.\& \fC$I10_OUTPUT\fP,
exported by all analysed DLL versions, and the three symbols, \fC@_calloc_crt@8\fP,
\fC@_malloc_crt@4\fP, and \fC@_realloc_crt@8\fP, each of which is visible exclusively
in \fCmsvcr80.dll\fP), which do not represent valid symbol names in the C programming
language.
.FE
The tables
.ie \n(.p>22c \{ are presented in two groups: the first of these, designated as 
.pdfhref L -D "table-1" -A , -- "table\|1"
enumerates the symbols exported by those
.\}
.el \{ cover non\(hyfree variants of the library ranging from \fCmsvcr70.dll\fP
to \fCmsvcr120.dll\fP, in addition to several
.\}
versions of the freely available\** \fCmsvcrt.dll\fP, as distributed with the
following versions of the Microsoft Windows\(tm operating system:\(em
.FS
While it may not be strictly \(lqfree software\(rq, in the sense espoused by
the Free Software Foundation, \fCmsvcrt.dll\fP is freely available \fBfor use\fP
by those who run lawfully licensed copies of Microsoft Windows\(tm \(em and
indeed by those, whose actions we cannot condone, who may have acquired
an \fIunlawful\fP copy of the operating system.
.FE
.TS
tab(:);
l l s l s
l l s l s
l l r l r.
:MS\(hyWindows Version:Characterized by \fCmsvcrt.dll\fP Version
:\_:\_
:Windows-NT4 SP-6a:(4.0.1381):4.20.0.6201:(1996-10-14)
:Windows-98:(4.10.1998):5.0.7128.0:(1998-05-11)
:Windows-98 Second Edition:(4.10.2222):6.0.8397.0:(2000-06-26)
:Windows-2000 SP-4:(5.0.2195):6.1.9844.0:(2003-06-20)
:Windows-XP Professional SP-2:(5.1.2600):7.0.2600.2180:(2004-08-04)
:Windows-Vista Professional:(6.0.6002):7.0.6002.18005:(2009-04-11)
:Windows-7 Home Premium:(6.1.7601):7.0.7601.17744:(2011-11-06)
.TE
.LP
In the tables which follow, the leftmost column lists all \(oqextern "C"\(cq
symbols which have been identified, in all versions of the runtime libraries
which have been considered; however, each individual version of the library
may be expected to export only a subset of these symbols.
Each column to the right of this is specific to just one version of the
library; it indicates, by means of a yes/no (Y/N) mark against each symbol,
whether or not the associated version of the library exports the symbol.
.
.SS 2 "Table 1. Symbols Exported by Platform Specific MSVCRT.DLL Versions"
.ie duplex .nr PS 8.3p
.el .nr PS 8.5p
.LP
.TS H
expand,allbox,tab(%);
r2 c  s  s  s  s  s  s
a2 ce ce ce ce ce ce ce.
LIBRARY:%MSVCRT.DLL as of Windows Version
\^%WinNT4%Win98%Win98-SE%Win2K%WinXP%Vista%Win7
.TH
.so msvcrt-xref.platform.tbl
.TE
.EJ
.bp
.nr PS 10p
.pdfhref M -N "table-2a"
.SS 2 "Table 2a. Symbols Exported by Non-Free MSVC Runtime DLLs"
.LP
This table identifies the symbols which are exported by various versions of
the non-free runtime DLL libraries distributed with MSVC. For presentational
convenience, this table is subdivided into two sections; the first of these,
enumerated in table\|2a, covers library versions from \fCmsvcr70.dll\fP to
\fCmsvcr90.dll\fP inclusive, while versions from \fCmsvcr100.dll\fP to
\fCmsvcr120.dll\fP are covered by
.pdfhref L -D "table-2b" -A . -- "table\|2b"
.nr PS 8.5p
.LP
.TS H
expand,allbox,tab(%);
r2 ce ce ce ce ce s s s
a2 c  c  c  c  c  s s s.
LIBRARY:%msvcr70.dll%msvcr71.dll%msvcr80.dll%msvcr90.dll
.TH
.so msvcrt-xref.nonfree-1.tbl
.TE
.EJ
.bp
.nr PS 10p
.pdfhref M -N "table-2b"
.SS 2 "Table 2b. Symbols Exported by Non-Free MSVC Runtime DLLs"
.LP
This table identifies the symbols which are exported by versions of the
non-free runtime DLL libraries distributed with MSVC, from \fCmsvcr100.dll\fP
to \fCmsvcr120.dll\fP inclusive; for symbols exported by earlier versions,
from \fCmsvcr70.dll\fP to \fCmsvcr90.dll\fP inclusive, please refer to
.pdfhref L -D "table-2a" -A . -- "table\|2a"
.nr PS 8.5p
.LP
.TS H
expand,allbox,tab(%);
r2 ce ce ce ce se s s s
a2 c  c  c  c  s  s s s.
LIBRARY:%msvcr100.dll%msvcr110.dll%msvcr120.dll
.TH
.so msvcrt-xref.nonfree-2.tbl
.TE
.am EJ EJ
.   OH ''''
.EJ
.ig
.nr LT 18.0c
.nr LL 18.0c
.nr FM  2.5c
..
.bp
.nr PS 10.0p
.SH 1
.ce 1
.pdfhref O 1 "Appendix 1: GNU Free Documentation License"
Appendix 1
.OH '\*(LH'\*(CH'\*(RH'
.so fdl-1.3.ms
.EJ
.bp
.SH 1
.ce 1
.pdfhref O 1 "Appendix 2: Acknowledgements"
Appendix 2
.SH 1
.ce 1
Acknowledgements
.sp 2.0c
.LP
I have compiled this reference document because I was unable to find
any other documentation which, in my opinion, adequately identified the
availability of exported symbols, within the evolving versions of the
standard C runtime library, \fCmsvcrt.dll\fP, as distributed with various
versions of MS-Windows\(tm, as Windows itself has evolved.
.LP
The document content has been compiled on the basis of symbol listings,
generated directly from original copies of the C runtime DLL libraries
in question, using the \(oqpexports\(cq tool, which was originally
written by Anders Norlander, with subsequent maintenance updates by
Paul Sokolovsky, Tor Lillqvist, and myself.
Thanks are also due to Mark Bourne, Raffaello Di Napoli, and Jan Ringo\(vs,
who provided symbol listings from various versions of \fCmsvcrt.dll\fP, as it
was distributed with various historical MS-Windows\(tm versions.
.LP
The finished document has been typeset, for electronic publication in
Adobe\(tm Portable Document Format, using my own \(oqpdfroff\(cq
tool, and its accompanying \(oqpdfmark\(cq macro set, which I have
contributed to the GNU \(oqtroff\(cq project.
I would like to thank James Clark, for originally creating GNU \(oqtroff\(cq,
Werner Lemberg, who, for many years, has led its continuing development,
and the many other contributors to the GNU \(oqtroff\(cq project; without
their considerable undertaking, my own \(oqpdfroff\(cq tool, and
\(oqpdfmark\(cq macros would not exist.
.pdfsync
