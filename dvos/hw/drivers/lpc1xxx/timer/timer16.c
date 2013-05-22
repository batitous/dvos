
#include "../include/libs-hardware.h"

//-------------------------- private functions

void TIMER_16_0_IRQn_Handler(void)
{

    
    
}

void TIMER_16_1_IRQn_Handler(void)
{

    
    
}

//-------------------------- public functions

Bool InitTimer16(TIMER timerSelected, UInt32 waitInUs)
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

