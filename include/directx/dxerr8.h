/**
 * @file dxerr8.h
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
#ifndef _DXERR8_H
#define _DXERR8_H
#pragma GCC system_header

#ifdef __cplusplus
extern "C" {
#endif

const char *WINAPI DXGetErrorString8A(HRESULT);
const WCHAR *WINAPI DXGetErrorString8W(HRESULT);
const char* WINAPI DXGetErrorDescription8A(HRESULT);
const WCHAR* WINAPI DXGetErrorDescription8W(HRESULT);
HRESULT WINAPI DXTraceA(const char*,DWORD,HRESULT,const char*,BOOL);
HRESULT WINAPI DXTraceW(const char*,DWORD,HRESULT,const WCHAR*,BOOL);

#ifdef UNICODE
#define DXGetErrorString8 DXGetErrorString8W
#define DXGetErrorDescription8 DXGetErrorDescription8W
#define DXTrace DXTraceW
#else
#define DXGetErrorString8 DXGetErrorString8A
#define DXGetErrorDescription8 DXGetErrorDescription8A
#define DXTrace DXTraceA
#endif 

#if defined(DEBUG) || defined(_DEBUG)
#define DXTRACE_MSG(str)	DXTrace(__FILE__,(DWORD)__LINE__,0,str,FALSE)
#define DXTRACE_ERR(str,hr)	DXTrace(__FILE__,(DWORD)__LINE__,hr,str,TRUE)
#define DXTRACE_ERR_NOMSGBOX(str,hr)	DXTrace(__FILE__,(DWORD)__LINE__,hr,str,FALSE)
#else
#define DXTRACE_MSG(str)	(0L)
#define DXTRACE_ERR(str,hr)	(hr)
#define DXTRACE_ERR_NOMSGBOX(str,hr)	(hr)
#endif

#ifdef __cplusplus
}
#endif
#endif
