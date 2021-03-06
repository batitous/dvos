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

//----------------------------- private menbers

TimerIrqCallback timer0IrqCallback;
TimerIrqCallback timer1IrqCallback;

//----------------------------- private functions


void FakeUserIRQRoutine()
{
}




void TIMER_32_0_IRQn_Handler(void)
{
    // clear IRQ Match 0
    SETBIT(LPC_TMR32B0->IR,0);
    
    timer0IrqCallback();
    
}


void TIMER_32_1_IRQn_Handler(void)
{
    // clear IRQ Match 0
    SETBIT(LPC_TMR32B1->IR,0);
    
    timer1IrqCallback();
    
}

//----------------------------- public functions

Bool initTimer32(TIMER timerSelected, UInt32 waitInUs)
{
    LPC_TMR_TypeDef * timer;
    UInt32 waitInTick;
    
    // IOCON_PIO0_1 CT32B0_MAT2 FUNC=0x2
    // IOCON_R_PIO0_11 CT32B0_MAT3 warning : AD0 FUNC=0x3
    // IOCON_R_PIO1_0 CT32B1_CAP0 warning : AD1 FUNC=0x3
    // IOCON_R_PIO1_1 CT32B1_MAT0 warning : AD2 FUNC=0x3
    // IOCON_R_PIO1_2 CT32B1_MAT1 warning : AD3 FUNC=0x3
    // IOCON_SWDIO_PIO1_3 CT32B1_MAT2 warning : AD4 FUNC=0x3
    // IOCON_PIO1_4 CT32B1_MAT3 warning: AD5 FUNC=0x2
    // IOCON_PIO1_5 CT32B0_CAP0 FUNC=0x2
    // IOCON_PIO1_6 CT32B0_MAT0 warning: RXD FUNC=0x2
    // IOCON_PIO1_7 CT32B0_MAT1 warning: TXD FUNC=0x2
    
    
    
    // SYSAHBCLKCTRL bit9 1 = timer0 bit10 1 =timer1
    if ( timerSelected==TIMER0)
    {
        timer0IrqCallback = &FakeUserIRQRoutine;
        timer = LPC_TMR32B0;
        SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,9);
    }
    else
    {
        timer1IrqCallback = &FakeUserIRQRoutine;
        timer = LPC_TMR32B1;
        SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,10);
    }
        
    //todo 100us = (KERNEL_CPU_FREQ/100)*10 -1
    //todo 10us  = (KERNEL_CPU_FREQ /100) -1
    //todo 1us   = (KERNEL_CPU_FREQ /1000) -1
    waitInTick = (KERNEL_CPU_FREQ / 1000) * waitInUs -1;
    
    timer->MR0 = waitInTick;
    timer->TC = 0;
    
    // interrupt on MR0
    SETBIT(timer->MCR,0);
    // reset when MRO match
    SETBIT(timer->MCR,1);
    
    // enable IRQ
    if (timerSelected==TIMER0)
    {
        NVIC_SetPriority(TIMER_32_0_IRQn, 0x02);
        NVIC_EnableIRQ(TIMER_32_0_IRQn);
    }
    else
    {
        NVIC_SetPriority(TIMER_32_1_IRQn, 0x03);
        NVIC_EnableIRQ(TIMER_32_1_IRQn);
    }
    
    // enable timer
    //SETBIT(timer->TCR,0);
 
    return True;
}

void setTimer32(TIMER timerSelected, UInt32 waitInUs)
{
    UInt32 waitInTick;
    LPC_TMR_TypeDef * timer;
    
    if ( timerSelected==TIMER0)
    {
        timer = LPC_TMR32B0;
    }
    else
    {
        timer = LPC_TMR32B1;
    }
    
    CLRBIT(timer->TCR,0);
    
    waitInTick = (KERNEL_CPU_FREQ / 1000) * waitInUs -1;
    
    timer->MR0 = waitInTick;
    timer->TC = 0;
}

void enableTimer32(TIMER timerSelected, Bool enable)
{
    LPC_TMR_TypeDef * timer;
    
    if ( timerSelected==TIMER0)
    {
        timer = LPC_TMR32B0;
    }
    else
    {
        timer = LPC_TMR32B1;
    }
    
    if(enable==False)
    {
        CLRBIT(timer->TCR,0);
    }
    else
    {
        SETBIT(timer->TCR,0);
    }
}

void setTimer0Callback(TimerIrqCallback c)
{
    timer0IrqCallback = c;
}

void setTimer1Callback(TimerIrqCallback c)
{
    timer1IrqCallback = c;
}


// fonction a été testé, c'est ok !
void waitUsPrecise(UInt32 waitInUs)
{
    LPC_TMR_TypeDef * timer = LPC_TMR32B1;
    
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,10);
    
    timer->TCR = 0;
    timer->MR3 = (KERNEL_CPU_FREQ / 1000) * waitInUs -1;
    
    timer->TC = 0;
    
    SETBIT(timer->MCR,11);
    SETBIT(timer->TCR,0);
    
    while( (timer->TCR & 0x1) != 0);
}
