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

void InitMcuAnalog(UInt32 analogChannel)
{
    // power on analog
    SETBIT(LPC_SC->PCONP,12);
        
    // ADC on
    SETBIT(LPC_ADC->ADCR,21);
    
    // analog clock set to cclk 100 MHz
    SETBIT(LPC_SC->PCLKSEL0,24);
    
    // set clkdiv less or egual to 13 MHz = 100 MHz / (7+1)
    LPC_ADC->ADCR |= BITS(8,7);
       
    
    // warning, not available on lpc17xx 80 pins !
    if( (analogChannel & ANA0) == ANA0)
    {
        SETBIT(LPC_PINCON->PINSEL1,14);
    }
    // warning, not available on lpc17xx 80 pins !
    if( (analogChannel & ANA1) == ANA1)
    {
        SETBIT(LPC_PINCON->PINSEL1,16);
    }
    
    if( (analogChannel & ANA2) == ANA2)
    {
        SETBIT(LPC_PINCON->PINSEL1,18);
    }
    
    if( (analogChannel & ANA3) == ANA3)
    {
        SETBIT(LPC_PINCON->PINSEL1,20);
    }
    
    if( (analogChannel & ANA4) == ANA4)
    {
        SETBIT(LPC_PINCON->PINSEL3,28);
        SETBIT(LPC_PINCON->PINSEL3,29);
    }
    
    if( (analogChannel & ANA5) == ANA5)
    {
        SETBIT(LPC_PINCON->PINSEL3,30);
        SETBIT(LPC_PINCON->PINSEL3,31);
    }
    
    if( (analogChannel & ANA6) == ANA6)
    {
        // warning, UART0 !
        SETBIT(LPC_PINCON->PINSEL0,7);
    }
    
    if( (analogChannel & ANA7) == ANA7)
    {
        // warning, UART0 !
        SETBIT(LPC_PINCON->PINSEL0,5);
    }
        	
}

