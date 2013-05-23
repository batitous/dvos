/*
	Dvos - Copyright (C) 2013 Baptiste Burles, Christophe Casson, Sylvain Fay-Chatelard

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


//----------------------------- public functions

void initMcuAnalog(UInt32 analogChannel)
{
    //bit0 to bit2 : pin configuration  
    //bit7 : ADMODE set to 0
    
    
    if( (analogChannel & ANA0) == ANA0)
    {
        // AD0
        CLRBITS(LPC_IOCON->R_PIO0_11,0x1F);
        SETBIT(LPC_IOCON->R_PIO0_11,0);
        CLRBIT(LPC_IOCON->R_PIO0_11,7);
    }
    
    if( (analogChannel & ANA1) == ANA1)
    {
        //AD1 IOCON_R_PIO1_0
        CLRBITS(LPC_IOCON->R_PIO1_0,0x1F);
        SETBIT(LPC_IOCON->R_PIO1_0,1);
        CLRBIT(LPC_IOCON->R_PIO1_0,7);
    }
    
    if( (analogChannel & ANA2) == ANA2)
    {
       //AD2 IOCON_R_PIO1_1
       CLRBITS(LPC_IOCON->R_PIO1_1,0x1F);
       SETBIT(LPC_IOCON->R_PIO1_1,1);
       CLRBIT(LPC_IOCON->R_PIO1_1,7);
    }
    
    if( (analogChannel & ANA3) == ANA3)
    {
       //AD3 IOCON_R_PIO1_2
       CLRBITS(LPC_IOCON->R_PIO1_2,0x1F);
       SETBIT(LPC_IOCON->R_PIO1_2,1);
       CLRBIT(LPC_IOCON->R_PIO1_2,7);
    }
    
    if( (analogChannel & ANA4) == ANA4)
    {
       //AD4 IOCON_SWDIO_PIO1_3
       CLRBITS(LPC_IOCON->SWDIO_PIO1_3,0x1F);
       SETBIT(LPC_IOCON->SWDIO_PIO1_3,1);
       CLRBIT(LPC_IOCON->SWDIO_PIO1_3,7);
    }
    
    if( (analogChannel & ANA5) == ANA5)
    {
        //AD5 IOCON_PIO1_4
        CLRBITS(LPC_IOCON->PIO1_4,0x1F);
        SETBIT(LPC_IOCON->PIO1_4,0);
        CLRBIT(LPC_IOCON->PIO1_4,7);
    }
    
    if( (analogChannel & ANA6) == ANA6)
    {
        //AD6 IOCON_PIO1_10
        CLRBITS(LPC_IOCON->PIO1_10,0x1F);
        SETBIT(LPC_IOCON->PIO1_10,0);
        CLRBIT(LPC_IOCON->PIO1_10,7);
    }
    
    if( (analogChannel & ANA7) == ANA7)
    {
        //AD7 IOCON_PIO1_11
        CLRBITS(LPC_IOCON->PIO1_11,0x1F);
        SETBIT(LPC_IOCON->PIO1_11,0);
        CLRBIT(LPC_IOCON->PIO1_11,7);
    }
        
    // power on the analog peripheral
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,13);
    CLRBIT(LPC_SYSCON->PDRUNCFG,4);
        
    // set clkdiv less or egual to 4.5 MHz = 72MHz / 18
    LPC_ADC->CR |= BITS(8,17);
	
	
}

