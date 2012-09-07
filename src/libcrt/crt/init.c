/**
 * @file init.c
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

/*
 * Code to initialize standard file handles and command line arguments.
 * This file is #included in both crt1.c and dllcrt1.c.
 */

/*
 * Access to a standard 'main'-like argument count and list. Also included
 * is a table of environment variables.
 */
int _argc = 0;
char **_argv = 0;

/* NOTE: Thanks to Pedro A. Aranda Gutiirrez <paag@tid.es> for pointing
 * this out to me. GetMainArgs (used below) takes a fourth argument
 * which is an int that controls the globbing of the command line. If
 * _CRT_glob is non-zero the command line will be globbed (e.g. *.*
 * expanded to be all files in the startup directory). In the mingw32
 * library a _CRT_glob variable is defined as being -1, enabling
 * this command line globbing by default. To turn it off and do all
 * command line processing yourself (and possibly escape bogons in
 * MS's globbing code) include a line in one of your source modules
 * defining _CRT_glob and setting it to zero, like this:
 *  int _CRT_glob = 0;
 */
extern int _CRT_glob;

typedef struct {
  int newmode;
} _startupinfo;
extern void __getmainargs (int *, char ***, char ***, int, _startupinfo *);

/*
 * Initialize the _argc, _argv and environ variables.
 */
static void
_mingw32_init_mainargs ()
{
  /* The environ variable is provided directly in stdlib.h through
   * a dll function call. */
  char **dummy_environ;
  _startupinfo start_info;
  start_info.newmode = 0;

  /*
   * Microsoft's runtime provides a function for doing just that.
   */
  (void) __getmainargs (&_argc, &_argv, &dummy_environ, _CRT_glob, 
                        &start_info);
}

