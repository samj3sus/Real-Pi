
#ifndef UART_H_
#define UART_H_

#define DISP_FGND_BLACK           0x00
#define DISP_FGND_RED             0x01
#define DISP_FGND_GREEN           0x02
#define DISP_FGND_BROWN           0x03
#define DISP_FGND_BLUE            0x04
#define DISP_FGND_PURPLE          0x05
#define DISP_FGND_CYAN            0x06
#define DISP_FGND_LIGHT_GRAY      0x07
#define DISP_FGND_DARK_GRAY       0x08
#define DISP_FGND_LIGHT_RED       0x09
#define DISP_FGND_LIGHT_GREEN     0x0A
#define DISP_FGND_YELLOW          0x0B
#define DISP_FGND_LIGHT_BLUE      0x0C
#define DISP_FGND_LIGHT_PURPLE    0x0D
#define DISP_FGND_LIGHT_CYAN      0x0E
#define DISP_FGND_WHITE           0x0F

#define DISP_BGND_BLACK           0x00
#define DISP_BGND_RED             0x10
#define DISP_BGND_GREEN           0x20
#define DISP_BGND_BROWN           0x30
#define DISP_BGND_BLUE            0x40
#define DISP_BGND_PURPLE          0x50
#define DISP_BGND_CYAN            0x60
#define DISP_BGND_LIGHT_GRAY      0x70

#define DISP_BLINK                0x80


unsigned int uart_lcr ( void );
unsigned int uart_recv ( void );
void uart_send ( unsigned int );
void uart_flush ( void );
void hexstrings ( unsigned int );
void hexstring ( unsigned int );
void uart_init ( void );
void uart_string(char *);
void    PC_DispClrScr(unsigned char bgnd_color);
void    PC_DispClrLine(unsigned char y, unsigned char bgnd_color);
void    PC_DispChar(unsigned char x ,unsigned char y, char c, unsigned char color);
void    PC_DispStr(unsigned char x,unsigned char y, unsigned char *s,unsigned char color);
void    setrc(unsigned char r, unsigned char c);
void    setatr(unsigned char color);
#endif /* UART_H_ */

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

