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

//-------------------------- private functions

void TIMER_16_0_IRQn_Handler(void)
{

    
    
}

void TIMER_16_1_IRQn_Handler(void)
{

    
    
}

//-------------------------- public functions

Bool initTimer16(TIMER timerSelected, UInt32 waitInUs)
{
    LPC_TMR_TypeDef * timer;
    UInt32 waitInTick;
    
    
    // SYSAHBCLKCTRL bit7 1 = timer0 bit8 1 =timer1
    if( timerSelected == TIMER0)
    {
        timer = LPC_TMR16B0;
        SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,7);
    }
    else
    {
        timer = LPC_TMR16B1;
        SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,8);
    }
    
    //todo 100us = (KERNEL_CPU_FREQ/100)*10 -1
    //todo 10us  = (KERNEL_CPU_FREQ /100) -1
    //todo 1us   = (KERNEL_CPU_FREQ /1000) -1
    
    // maximum value : 910 us
    waitInTick = (KERNEL_CPU_FREQ / 1000) * waitInUs -1;
    if(waitInUs>0xFFFF)
    {
        return False;
    }
    
    timer->MR0 = waitInTick;
    
    // interrupt on MR0
    SETBIT(timer->MCR,0);
    // reset when MRO match
    SETBIT(timer->MCR,1);
    
    // enable IRQ
    if(timerSelected==TIMER0)
    {
        NVIC_EnableIRQ(TIMER_16_0_IRQn);
    }
    else
    {
        NVIC_EnableIRQ(TIMER_16_1_IRQn);
    }
    
    // enable timer
    SETBIT(timer->TCR,0);
    
    return True;
}

