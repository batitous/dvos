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


#define SPI_SCK_PIN		15
#define SPI_MISO_PIN		17
#define SPI_MOSI_PIN		18

#define CPHA    3
#define CPOL    4
#define MSTR    5
#define SPIE	7
#define SPIF	7

void initSPI(void)
{
    // Turn on the power
    SETBIT(LPC_SC->PCONP, 8);

    //clock
    CLRBIT(LPC_SC->PCLKSEL0, 17);
    SETBIT(LPC_SC->PCLKSEL0, 16);

    // setup GPIO
    SETBIT(LPC_GPIO0->FIODIR, SPI_SCK_PIN);
    SETBIT(LPC_GPIO0->FIODIR, SPI_MOSI_PIN);
    CLRBIT(LPC_GPIO0->FIODIR, SPI_MISO_PIN);

    //SCK
    SETBIT(LPC_PINCON->PINSEL0, 30);
    SETBIT(LPC_PINCON->PINSEL0, 31);

    // MISO
    SETBIT(LPC_PINCON->PINSEL1, 2);
    SETBIT(LPC_PINCON->PINSEL1, 3);

    // MOSI
    SETBIT(LPC_PINCON->PINSEL1, 4);
    SETBIT(LPC_PINCON->PINSEL1, 5);

    //set speed
    // sck = PCLK_SPI / value
    // 8 is low speed: ~12,5Mhz
    // 4 = 25 MHz
    LPC_SPIF->SPCCR = 4;


    SETBIT(LPC_SPIF->SPCR, MSTR);   // 0=slave, 1=master 

    CLRBIT(LPC_SPIF->SPCR, CPHA);   // 0=first clock edge, 1=second clock edge

    CLRBIT(LPC_SPIF->SPCR, CPOL);   // 0=sck active high, 1=sck active low

    CLRBIT(LPC_SPIF->SPCR, SPIE);   // 0=no interrupt, 1=interrupt

        
}



UInt8 sendByteToSPI(UInt8 outgoing)
{
    UInt8 incoming;
    
    LPC_SPIF->SPDR = outgoing;
    
    while (!(LPC_SPIF->SPSR & BIT(SPIF)));
    
    incoming = LPC_SPIF->SPDR;

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
