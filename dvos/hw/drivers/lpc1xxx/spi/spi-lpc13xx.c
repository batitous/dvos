/*
	Dvos - Copyright © 2013 Baptiste Burles, Christophe Casson, Sylvain Fay-Chatelard

    This file is part of Dvos.

    Dvos is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    Dvos is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "../include/libs-hardware.h"


#define CPHA    7
#define CPOL    6

#define SSE     1

void initSPI(void)
{        
    // de assert reset spi line
    SETBIT(LPC_SYSCON->PRESETCTRL,0);
  
    // enable spi0
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,11);
    
        
    // MOSI GPIO0_9
    SETBIT(LPC_IOCON->PIO0_9,0);
    
    // MISO GPIO0_8
    SETBIT(LPC_IOCON->PIO0_8,0);
    
    // SCK GPIO1_29
    SETBIT(LPC_IOCON->PIO1_29,0);
    
    
    LPC_SYSCON->SSP0CLKDIV = 1;
    
    LPC_SSP0->CR0 = 0x7;
    
    CLRBIT(LPC_SSP0->CR0,CPOL);
    CLRBIT(LPC_SSP0->CR0,CPHA);

    // clock : PCLK / CPSR = 72MHz / 12MHz
    LPC_SSP0->CPSR = 6;
    
    
    // enable ssp0
    SETBIT(LPC_SSP0->CR1,SSE); 
}



UInt8 sendByteToSPI(UInt8 outgoing)
{
    UInt8 incoming;
    
    while ((LPC_SSP0->SR & (0x2 | 0x10)) != 0x2);
    LPC_SSP0->DR = outgoing;

    while ( (LPC_SSP0->SR & (0x10|0x4)) != 0x4 );
    incoming = LPC_SSP0->DR;
    
    return incoming;
}


void sendBufferToSPI(UInt8 * buffer, UInt32 length)
{
    UInt32 i;
    for(i=0; i<length; i++)
    {
        sendByteToSPI(buffer[i]);
    }
}


UInt8 getByteFromSPI(void)
{
    return sendByteToSPI(0x00);
}

void getBufferFromSPI(UInt8 * buffer, UInt32 size)
{
    UInt32 i;
    for (i=0; i<size; i++)
    {
        buffer[i] = getByteFromSPI();
    }
}

