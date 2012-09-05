/**
 * @file amaudio.h
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
#ifndef _AMAUDIO_H
#define _AMAUDIO_H
#pragma GCC system_header

#include <dsound.h>

#ifdef __cplusplus
extern "C" {
#endif

#define INTERFACE IAMDirectSound
DECLARE_INTERFACE_(IAMDirectSound, IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,LPVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetDirectSoundInterface)(THIS_ LPDIRECTSOUND*) PURE;
	STDMETHOD(GetPrimaryBufferInterface)(THIS_ LPDIRECTSOUNDBUFFER*) PURE;
	STDMETHOD(GetSecondaryBufferInterface)(THIS_ LPDIRECTSOUNDBUFFER*) PURE;
	STDMETHOD(GetFocusWindow)(THIS_ HWND*,BOOL*) PURE ;
	STDMETHOD(ReleaseDirectSoundInterface)(THIS_ LPDIRECTSOUND) PURE;
	STDMETHOD(ReleasePrimaryBufferInterface)(THIS_ LPDIRECTSOUNDBUFFER) PURE;
	STDMETHOD(ReleaseSecondaryBufferInterface)(THIS_ LPDIRECTSOUNDBUFFER) PURE;
	STDMETHOD(SetFocusWindow)(THIS_ HWND,BOOL) PURE ;
};
#undef INTERFACE

#ifdef __cplusplus
}
#endif
#endif
