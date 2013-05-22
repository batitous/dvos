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

//-------------------------- private variables

volatile UInt32 timer0IrqFired;

//-------------------------- private functions

void TIMER0_IRQHandler(void)
{
    //clear MR0 interrupt
    SETBIT(LPC_TIM0->IR,0);
    
    timer0IrqFired = True;
}

void TIMER1_IRQHandler(void)
{
    //clear MR0 interrupt
    SETBIT(LPC_TIM1->IR,0);
}

void TIMER2_IRQHandler(void)
{
    //clear MR0 interrupt
    SETBIT(LPC_TIM2->IR,0);
}

void TIMER3_IRQHandler(void)
{
    //clear MR0 interrupt
    SETBIT(LPC_TIM3->IR,0);
}

//-------------------------- public functions

Bool InitTimer32(TIMER timerSelected, UInt32 waitInUs)
{
    LPC_TIM_TypeDef * timer = 0;
    UInt32 waitInTick;
    
    switch(timerSelected)
    {
        case TIMER0:
            SETBIT(LPC_SC->PCONP,1);
            SETBIT(LPC_SC->PCLKSEL0,2);
            timer = LPC_TIM0;
            break;
        case TIMER1:
            SETBIT(LPC_SC->PCONP,2);
            SETBIT(LPC_SC->PCLKSEL0,4);
            timer = LPC_TIM1;
            break;
        case TIMER2:
            SETBIT(LPC_SC->PCONP,22);
            SETBIT(LPC_SC->PCLKSEL1,12);
            timer = LPC_TIM2;
            break;
        case TIMER3:
            SETBIT(LPC_SC->PCONP,23);
            SETBIT(LPC_SC->PCLKSEL1,14);
            timer = LPC_TIM3;
            break;
    }
    
    //todo 100us = (KERNEL_CPU_FREQ/100)*10 -1
    //todo 10us  = (KERNEL_CPU_FREQ /100) -1
    //todo 1us   = (KERNEL_CPU_FREQ /1000) -1
    
    waitInTick = (KERNEL_CPU_FREQ / 1000) * waitInUs -1;
    
    
    timer->MR0 = waitInTick;
    
    // interrupt on MR0
    SETBIT(timer->MCR,0);
    // reset when MRO match
    SETBIT(timer->MCR,1);
    
    
    // enable IRQ
    switch(timerSelected)
    {
        case TIMER0:
            timer0IrqFired = False;
            NVIC_EnableIRQ(TIMER0_IRQn);
            break;
        case TIMER1:
            NVIC_EnableIRQ(TIMER1_IRQn);
            break;
        case TIMER2:
            NVIC_EnableIRQ(TIMER2_IRQn);
            break;
        case TIMER3:
            NVIC_EnableIRQ(TIMER3_IRQn);
            break;
    }
    
    // enable timer
    SETBIT(timer->TCR,0);
    
    return True;
}

void WaitTimer32(TIMER timerSelected)
{
    while(timer0IrqFired==False);
    
    timer0IrqFired = False;
}

void WaitUsPrecise(UInt32 waitInUs)
{
    LPC_TIM_TypeDef * timer = LPC_TIM3;
    
    SETBIT(LPC_SC->PCONP,23);
    SETBIT(LPC_SC->PCLKSEL1,14);
    
    timer->MR3 = (KERNEL_CPU_FREQ / 1000) * waitInUs -1;
    
    SETBIT(timer->MCR,11);
    SETBIT(timer->TCR,0);
    
    while( (timer->TCR & 0x1) == 0x1);
}

void InitMcuClock(void)
{
    SETBIT(LPC_SC->PCONP,16);
//    SETBIT(LPC_SC->PCLKSEL1,26);

    //Set up default register values
    LPC_RIT->RICOMPVAL  = 0xFFFFFFFF;
    LPC_RIT->RIMASK	= 0x00000000;
    LPC_RIT->RICOUNTER	= 0x00000000;
}

UInt32 GetMcuClock(void)
{    
    return ((LPC_RIT->RICOUNTER+1)*1000)/KERNEL_CPU_FREQ;
}
