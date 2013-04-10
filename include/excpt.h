/**
 * @file excpt.h
 * Copyright 2012, 2013 MinGW.org project
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
#ifndef	_EXCPT_H_
#define	_EXCPT_H_
#pragma GCC system_header
#include <_mingw.h>

__PSHPACK8

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum _EXCEPTION_DISPOSITION {
  ExceptionContinueExecution,
  ExceptionContinueSearch,
  ExceptionNestedException,
  ExceptionCollidedUnwind
} EXCEPTION_DISPOSITION;

#ifdef _M_IX86
struct _EXCEPTION_RECORD;
struct _CONTEXT;

EXCEPTION_DISPOSITION __cdecl _except_handler (
  struct _EXCEPTION_RECORD *,
  void *,
  struct _CONTEXT *,
  void *
);

#elif defined(_M_X64) || defined (_M_ARM)
struct _CONTEXT;
struct _DISPATCHER_CONTEXT;
struct _EXCEPTION_RECORD;
#ifndef _M_CEE_PURE
_CRTIMP EXCEPTION_DISPOSITION __C_specific_handler(
  struct _EXCEPTION_RECORD *,
  void *,
  struct _CONTEXT *,
  struct _DISPATCHER_CONTEXT *
);
#endif /* ndef _M_CEE_PURE */
#endif /* _M_IX86 */

#define GetExceptionCode _exception_code
#define exception_code _exception_code
#define GetExceptionInformation (struct _EXCEPTION_POINTERS *)_exception_info
#define exception_info GetExceptionInformation
#define AbnormalTermination _abnormal_termination
#define abnormal_termination _abnormal_termination

unsigned long __cdecl _exception_code(void);
void * __cdecl _exception_info(void);
int __cdecl _abnormal_termination(void);

#define EXCEPTION_EXECUTE_HANDLER 1
#define EXCEPTION_CONTINUE_SEARCH 0
#define EXCEPTION_CONTINUE_EXECUTION -1

/* FIXME:
   Why are these here?  We probably need to move these to a _mingw-except.h
   file.
*/
/* ?????????? Compiler related? */
/*
 * The type of function that is expected as an exception handler to be
 * installed with __try1.
 */
typedef EXCEPTION_DISPOSITION (*PEXCEPTION_HANDLER)
		(struct _EXCEPTION_RECORD*, void*, struct _CONTEXT*, void*);

/* FIXME: See above */
/* ?????????? Compiler related? */
/*
 * This is not entirely necessary, but it is the structure installed by
 * the __try1 primitive below.
 */
typedef struct _EXCEPTION_REGISTRATION
{
	struct _EXCEPTION_REGISTRATION*	prev;
	PEXCEPTION_HANDLER		handler;
} EXCEPTION_REGISTRATION, *PEXCEPTION_REGISTRATION;

/* FIXME: See above */
typedef EXCEPTION_REGISTRATION EXCEPTION_REGISTRATION_RECORD;
typedef PEXCEPTION_REGISTRATION PEXCEPTION_REGISTRATION_RECORD;

/* FIXME: See above */
/*
 * A macro which installs the supplied exception handler.
 * Push the pointer to the new handler onto the stack,
 * then push the pointer to the old registration structure (at fs:0)
 * onto the stack, then put a pointer to the new registration
 * structure (i.e. the current stack pointer) at fs:0.
 */
#ifdef _WIN64
# define __try1(pHandler) \
	__asm__ __volatile__ ("pushq %0;pushq %%gs:0;movq %%rsp,%%gs:0;" : : \
	"g" (pHandler));
#else
# define __try1(pHandler) \
	__asm__ __volatile__ ("pushl %0;pushl %%fs:0;movl %%esp,%%fs:0;" : : \
	"g" (pHandler));
#endif

/* FIXME: See above */
/*
 * A macro which (despite its name) *removes* an installed
 * exception handler. Should be used only in conjunction with the above
 * install routine __try1.
 * Move the pointer to the old reg. struct (at the current stack
 * position) to fs:0, replacing the pointer we installed above,
 * then add 8 to the stack pointer to get rid of the space we
 * used when we pushed on our new reg. struct above. Notice that
 * the stack must be in the exact state at this point that it was
 * after we did __try1 or this will smash things.
 */
#ifdef _WIN64
# define	__except1	\
	__asm__ __volatile__ ("movq (%%rsp),%%rax;movq %%rax,%%gs:0;addq \
	$16,%%rsp;" : : : "%rax");
#else
# define __except1	\
	__asm__ __volatile__ ("movl (%%esp),%%eax;movl %%eax,%%fs:0;addl \
	$8,%%esp;" : : : "%eax");
#endif

#ifdef	__cplusplus
}
#endif

__POPPACK8
#endif	/* _EXCPT_H_ not defined */
