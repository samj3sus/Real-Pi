/*
; -------------------------------------------------------------------
; OSTaskStkInit - build up initial stack for a task
; This will be the first register window. Must set %pc, %psr and %sp.
; Values of other registers does not matter. 
; Put pointer to task name into the return value (%o0).
; -------------------------------------------------------------------
*/
#include "ucos/includes.h"

#define  ARM_SYS_MODE   (0x0000001FL)

OS_STK       *OSTaskStkInit(void (*task)(void *pd), void *pdata, OS_STK *ptos, INT16U opt)
{
    OS_STK *stk;

    opt      = opt;                         /* 'opt' is not used, prevent warning                      */
    stk      = ptos;                        /* Load stack pointer                                      */
    *(stk)   = (OS_STK)task;                /* Entry Point                                             */
    *(--stk) = (INT32U)0x14141414L;         /* R14 (LR)                                                */
    *(--stk) = (INT32U)0x12121212L;         /* R12                                                     */
    *(--stk) = (INT32U)0x11111111L;         /* R11                                                     */
    *(--stk) = (INT32U)0x10101010L;         /* R10                                                     */
    *(--stk) = (INT32U)0x09090909L;         /* R9                                                      */
    *(--stk) = (INT32U)0x08080808L;         /* R8                                                      */
    *(--stk) = (INT32U)0x07070707L;         /* R7                                                      */
    *(--stk) = (INT32U)0x06060606L;         /* R6                                                      */
    *(--stk) = (INT32U)0x05050505L;         /* R5                                                      */
    *(--stk) = (INT32U)0x04040404L;         /* R4                                                      */
    *(--stk) = (INT32U)0x03030303L;         /* R3                                                      */
    *(--stk) = (INT32U)0x02020202L;         /* R2                                                      */
    *(--stk) = (INT32U)0x01010101L;         /* R1                                                      */
    *(--stk) = (INT32U)pdata;               /* R0 : argument                                           */
    *(--stk) = (INT32U)ARM_SYS_MODE;        /* CPSR  (Enable both IRQ and FIQ interrupts)              */

    return (stk);
}

#if OS_CPU_HOOKS_EN
/*
; -------------------------------------------------------------------
; OSTaskCreateHook
;	A stub for now. Fill in if needed.
; -------------------------------------------------------------------
*/
void
OSTaskCreateHook (
OS_TCB *ptcb)
{
	ptcb = ptcb;
}

/*
; -------------------------------------------------------------------
; OSTaskDelHook
;	A stub for now. Fill in if needed.
; -------------------------------------------------------------------
*/
void
OSTaskDelHook (
OS_TCB *ptcb)
{
	ptcb = ptcb;
}

/*
; -------------------------------------------------------------------
; OSTaskSwHook
;	A stub for now. Fill in if needed.
; -------------------------------------------------------------------
*/
void
OSTaskSwHook (
void )
{

}

/*
; -------------------------------------------------------------------
; OSTaskStatHook
;	A stub for now. Fill in if needed.
; -------------------------------------------------------------------
*/
void
OSTaskStatHook (
void )
{

}

/*
; -------------------------------------------------------------------
; OSTimeTickHook
;	A stub for now. Fill in if needed.
; -------------------------------------------------------------------
*/
void
OSTimeTickHook (
void)
{
}

#endif //OS_CPU_HOOKS_EN

#if OS_CPU_HOOKS_EN > 0 && OS_VERSION > 203
void  OSInitHookBegin (void)
{
}
#endif

#if OS_CPU_HOOKS_EN > 0 && OS_VERSION > 203
void  OSInitHookEnd (void)
{
}
#endif


#if OS_CPU_HOOKS_EN > 0 && OS_VERSION >= 251
void  OSTaskIdleHook (void)
{

}
#endif

#if OS_CPU_HOOKS_EN > 0 && OS_VERSION > 203
void  OSTCBInitHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                                           /* Prevent Compiler warning                 */
}
#endif

//------------------------------------------------------------------------
//-------------------------------------------------------------------------
//
// Copyright (c) 2012 David Welch dwelch@dwelch.com
// Modification Copyright (c) 2013 Weng Kai
// Modification Copyright (c) 2018 Samuel Delaney delaney.samuel@gmail.com 
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

