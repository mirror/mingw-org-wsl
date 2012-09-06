/**
 * @file conio.h
 * @copy 2012 MinGW.org project
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
#ifndef	_CONIO_H_
#define	_CONIO_H_
#pragma GCC system_header

/*
 * Low level console I/O functions. Pretty please try to use the ANSI
 * standard ones if you are writing new code.
 */

/* All the headers include this file. */
#include <_mingw.h>

#ifndef RC_INVOKED

#ifdef	__cplusplus
extern "C" {
#endif

_CRTIMP char* __cdecl __MINGW_NOTHROW	_cgets (char*);
_CRTIMP int __cdecl __MINGW_NOTHROW	_cprintf (const char*, ...);
_CRTIMP int __cdecl __MINGW_NOTHROW	_cputs (const char*);
_CRTIMP int __cdecl __MINGW_NOTHROW	_cscanf (char*, ...);

_CRTIMP int __cdecl __MINGW_NOTHROW	_getch (void);
_CRTIMP int __cdecl __MINGW_NOTHROW	_getche (void);
_CRTIMP int __cdecl __MINGW_NOTHROW	_kbhit (void);
_CRTIMP int __cdecl __MINGW_NOTHROW	_putch (int);
_CRTIMP int __cdecl __MINGW_NOTHROW	_ungetch (int);


#ifndef	_NO_OLDNAMES

_CRTIMP int __cdecl __MINGW_NOTHROW	getch (void);
_CRTIMP int __cdecl __MINGW_NOTHROW	getche (void);
_CRTIMP int __cdecl __MINGW_NOTHROW	kbhit (void);
_CRTIMP int __cdecl __MINGW_NOTHROW	putch (int);
_CRTIMP int __cdecl __MINGW_NOTHROW	ungetch (int);

#endif	/* Not _NO_OLDNAMES */


#ifdef	__cplusplus
}
#endif

#endif	/* Not RC_INVOKED */

#endif	/* Not _CONIO_H_ */
