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


void initTimerClock(void)
{
    TIMER timerSelected;
    LPC_TMR_TypeDef * timer;
    UInt32 waitInTick;
    UInt32 waitInUs;
    
    timerSelected = TIMER1;
    
    if ( timerSelected==TIMER0)
    {
        timer = LPC_TMR32B0;
        SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,9);
    }
    else
    {
        timer = LPC_TMR32B1;
        SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,10);
    }
    
    // the timer will reset in 71 minutes
    waitInUs = 1;
    waitInTick = (KERNEL_CPU_FREQ / 1000) * waitInUs -1;
    
    timer->TCR = 0;
    timer->TC = 0;
    timer->PC = 0;
    timer->PR = waitInTick;
    
    // enable timer
    SETBIT(timer->TCR,0);
}

UInt32 getTimerClock(void)
{
    LPC_TMR_TypeDef * timer = LPC_TMR32B1;

//    TIMER timerSelected = TIMER1;  
//    if ( timerSelected==TIMER0)
//    {
//        timer = LPC_TMR32B0;
//    }
//    else
//    {
//        timer = LPC_TMR32B1;
//    }
    
    return timer->TC;
}
