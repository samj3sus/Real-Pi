#include "regs.h"
#include "interrupts.h"
#include "ucos/includes.h"

extern INTERRUPT_VECTOR g_VectorTable[BCM2835_INTC_TOTAL_IRQ];

static void tickISR()
{
	OSTimeTick();

	timerRegs->CLI = 0;
}

void timer_init( void )
{

	DisableInterrupt(64);

	g_VectorTable[64].pfnHandler=tickISR;

	timerRegs->CTL = 0x003E0000;
	timerRegs->LOD = 1000000 - 1;
	timerRegs->RLD = 1000000 - 1;
	timerRegs->DIV = 0xF9;
	timerRegs->CLI = 0;
	timerRegs->CTL = 0x003E02A2;

	EnableInterrupt(64);
}

unsigned int timer_tick ( void )
{
    return(GET32(timerRegs->CNT));
}

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