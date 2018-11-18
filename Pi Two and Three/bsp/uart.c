#include "regs.h"
#include "ucos/includes.h"

extern void PUT32 ( unsigned int, unsigned int );
extern void PUT16 ( unsigned int, unsigned int );
extern void PUT8 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void BRANCHTO ( unsigned int );
extern void dummy ( unsigned int );

static unsigned char     sioerror;
 OS_EVENT  *DosSem;
static unsigned char     s_init[]={27,91,0x30,0x6d,0};        /*  esc [0m  */
static unsigned char     s_cls[] ={27,91,0x32,0x4a,0};        /*  esc[2J   */
static unsigned char   s_cln[] ={27,91,0x32,0x4b,0};        /*  esc[2K   */
static unsigned char     s_newl[]={27,0x45,0};                /*  escE     */
static unsigned char     s_rc[]  ={27,91,0x30,0x30,0x3b,0x30,0x30,0x48,0};
static unsigned char     s_atr[] ={27,91,0x30,59,0x32,59,0x33,0x37,59,0x34,0x30,59,0x32,0x6d,0};
static unsigned char     s_col[] = {27,91,0x30,0x30, 0x43,0};

unsigned int uart_lcr ( void )
{
    return(GET32(AUX_MU_LSR_REG));
}

unsigned int uart_recv ( void )
{
    while(1)
    {
        if(GET32(AUX_MU_LSR_REG)&0x01) break;
    }
    return(GET32(AUX_MU_IO_REG)&0xFF);
}
//------------------------------------------------------------------------
unsigned int uart_check ( void )
{
    if(GET32(AUX_MU_LSR_REG)&0x01) return(1);
    return(0);
}
//------------------------------------------------------------------------
void uart_send ( unsigned int c )
{
	int i;
    while(1)
    {
        if(GET32(AUX_MU_LSR_REG)&0x20) break;
    }
    //for(i=0;i<0x7FF;i++);
    PUT32(AUX_MU_IO_REG,c);
}

void uart_flush ( void )
{
    while(1)
    {
        if((GET32(AUX_MU_LSR_REG)&0x100)==0) break;
    }
}

void hexstrings ( unsigned int d )
{
    //unsigned int ra;
    unsigned int rb;
    unsigned int rc;

    rb=32;
    while(1)
    {
        rb-=4;
        rc=(d>>rb)&0xF;
        if(rc>9) rc+=0x37; else rc+=0x30;
        uart_send(rc);
        if(rb==0) break;
    }
    uart_send(0x20);
}

void hexstring ( unsigned int d )
{
    hexstrings(d);
    uart_send(0x0D);
    uart_send(0x0A);
}

void uart_init ( void )
{
    unsigned int ra;

    PUT32(AUX_ENABLES,1);
    PUT32(AUX_MU_IER_REG,0);
    PUT32(AUX_MU_CNTL_REG,0);
    PUT32(AUX_MU_LCR_REG,3);
    PUT32(AUX_MU_MCR_REG,0);
    PUT32(AUX_MU_IER_REG,0);
    PUT32(AUX_MU_IIR_REG,0xC6);
    PUT32(AUX_MU_BAUD_REG,270);
    ra=GET32(GPFSEL1);
    ra&=~(7<<12); //gpio14
    ra|=2<<12;    //alt5
    ra&=~(7<<15); //gpio15
    ra|=2<<15;    //alt5
    PUT32(GPFSEL1,ra);
    PUT32(GPPUD,0);
    for(ra=0;ra<150;ra++) dummy(ra);
    PUT32(GPPUDCLK0,(1<<14)|(1<<15));
    for(ra=0;ra<150;ra++) dummy(ra);
    PUT32(GPPUDCLK0,0);
    PUT32(AUX_MU_CNTL_REG,3);
}

void uart_string (char* s)
{
	while(*s!=0)
    {
    	uart_send((unsigned int)*s);
    	s++;
    }
//uart_send(0x0D);
//	uart_send(0x0A);
}

void setrc(unsigned char r, unsigned char c)
 {
  s_rc[3] = ((r % 10) + 0x30);
  if ((r /= 10) > 0) s_rc[2] = ((r % 10) + 0x30);
        else s_rc[2] = 0x30;
  s_rc[6] = ((c % 10) + 0x30);
  if ((c /= 10) > 0) s_rc[5] = ((c % 10) + 0x30);
        else s_rc[5] = 0x30;
 }

void setatr(unsigned char color)
 {
  unsigned char ctemp;
  ctemp = (color & 0x0f);
  if (ctemp < 8) s_atr[4] = 0x32;
        else {s_atr[4] = 0x31; ctemp = ctemp - 8;}
  s_atr[7] = (0x30 | ctemp);
  ctemp = ((color & 0x70) >> 4);
  s_atr[10] = (0x30 | ctemp);
  if (color & 0x80) s_atr[12] = 0x35;
        else s_atr[12] = s_atr[4];
 }

void PC_DispClrScr (unsigned char color)
{
  OSSemPend(DosSem, 0, &sioerror);
  setatr(color);
  uart_string(s_atr);
  uart_string(s_cls);
  OSSemPost(DosSem);
}

void PC_DispClrLine (unsigned char y, unsigned char color)
{
  OSSemPend(DosSem, 0, &sioerror);
  y++;
  setrc(y,0);
  uart_string(s_rc);
  setatr(color);
  uart_string(s_atr);
  uart_string(s_cln);
  OSSemPost(DosSem);
}

void PC_DispChar (unsigned char x, unsigned char y, char c, unsigned char color)
{
  OSSemPend(DosSem, 0, &sioerror);
  y++;
  x++;
  setrc(y, x);
  uart_string(s_rc);
  setatr(color);
  uart_string(s_atr);
  uart_send(c);
  OSSemPost(DosSem);
}

void PC_DispStr (unsigned char x, unsigned char y, unsigned char *s, unsigned char color)
{
  OSSemPend(DosSem, 0, &sioerror);
  y++;
  x++;
  setrc(y, x);
  uart_string(s_rc);
  setatr(color);
  uart_string(s_atr);
  uart_string(s);
  OSSemPost(DosSem);
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
//-------------------------------------------------------------------------
