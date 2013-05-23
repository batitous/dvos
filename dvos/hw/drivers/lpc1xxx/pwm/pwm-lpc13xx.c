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


//-------------------------- private functions:


void setPwmPin(PWMTIMER timerType, TIMER timerSelected, PWM pwmSelected)
{
    // IOCON_R_PIO0_11 CT32B0_MAT3 warning : AD0 FUNC=0x3
    // IOCON_R_PIO1_0 CT32B1_CAP0 warning : AD1 FUNC=0x3
    // IOCON_PIO1_4 CT32B1_MAT3 warning: AD5 FUNC=0x2
    // IOCON_PIO1_5 CT32B0_CAP0 FUNC=0x2
    
    if(timerType == TIMER32)
    {
        if(timerSelected==TIMER0)
        {
            if( (pwmSelected&PWM0)==PWM0)
            {
                // not activated!

                // IOCON_PIO1_6 CT32B0_MAT0 warning: RXD FUNC=0x2
                //SETBIT(LPC_IOCON->PIO1_6,1);
            }

            if( (pwmSelected&PWM1)==PWM1)
            {
                // not activated!

                // IOCON_PIO1_7 CT32B0_MAT1 warning: TXD FUNC=0x2
                //SETBIT(LPC_IOCON->PIO1_7,1);
            }

            if( (pwmSelected&PWM2)==PWM2)
            {
                // IOCON_PIO0_1 CT32B0_MAT2 FUNC=0x2
                SETBIT(LPC_IOCON->PIO0_1,1);
            }
        }
        else
        {
            if( (pwmSelected&PWM0)==PWM0)
            {
                // IOCON_R_PIO1_1 CT32B1_MAT0 warning : AD2 FUNC=0x3
                SETBIT(LPC_IOCON->R_PIO1_1,0);
                SETBIT(LPC_IOCON->R_PIO1_1,1);
            }

            if( (pwmSelected&PWM1)==PWM1)
            {
                // IOCON_R_PIO1_2 CT32B1_MAT1 warning : AD3 FUNC=0x3
                SETBIT(LPC_IOCON->R_PIO1_2,0);
                SETBIT(LPC_IOCON->R_PIO1_2,1);
            }

            if( (pwmSelected&PWM2)==PWM2)
            {
                // IOCON_SWDIO_PIO1_3 CT32B1_MAT2 warning : AD4 FUNC=0x3
                SETBIT(LPC_IOCON->SWDIO_PIO1_3,0);
                SETBIT(LPC_IOCON->SWDIO_PIO1_3,1);
            }
        }
    }
    else if(timerType == TIMER16)
    {
        if(timerSelected==TIMER0)
        {
            if( (pwmSelected&PWM0)==PWM0)
            {
                // not activated!

                // IOCON_PIO1_6 CT32B0_MAT0 warning: RXD FUNC=0x2
                //SETBIT(LPC_IOCON->PIO1_6,1);
            }

            if( (pwmSelected&PWM1)==PWM1)
            {
                // IOCON_PIO0_9 CT16B0_MAT1
                SETBIT(LPC_IOCON->PIO0_9,1);
            }

            if( (pwmSelected&PWM2)==PWM2)
            {
                // IOCON_PIO0_10 CT16B0_MAT2
                SETBIT(LPC_IOCON->SWCLK_PIO0_10,0);
                SETBIT(LPC_IOCON->SWCLK_PIO0_10,1);
            }
        }
        else
        {
            if( (pwmSelected&PWM0)==PWM0)
            {
                // IOCON_R_PIO1_1 CT32B1_MAT0 warning : AD2 FUNC=0x3
                //SETBIT(LPC_IOCON->R_PIO1_1,0);
                //SETBIT(LPC_IOCON->R_PIO1_1,1);
            }

            if( (pwmSelected&PWM1)==PWM1)
            {
                // IOCON_PIO0_9 CT16B0_MAT1
                //SETBIT(LPC_IOCON->PIO0_9,1);
            }

            if( (pwmSelected&PWM2)==PWM2)
            {
                // IOCON_SWDIO_PIO1_3 CT32B1_MAT2 warning : AD4 FUNC=0x3
                //SETBIT(LPC_IOCON->SWDIO_PIO1_3,0);
                //SETBIT(LPC_IOCON->SWDIO_PIO1_3,1);
            }
        }

    }
    
}

void setPwmConfig(LPC_TMR_TypeDef * timer, PWM pwmSelected, UInt32 cycle)
{
    if( (pwmSelected&PWM0)==PWM0)
    {
        timer->MR0 = cycle;
        // state of MAT0 output, when start pwm, we set to HIGH
        SETBIT(timer->EMR,0);
        // toggle MAT0 pin output
        timer->EMR |= BITS(4,0x3);
        // EM0 is controlled by PWM
        SETBIT(timer->PWMC,0);
    }
    
    if( (pwmSelected&PWM1)==PWM1)
    {
        timer->MR1 = cycle;
        SETBIT(timer->EMR,1);
        timer->EMR |= BITS(6,0x3);
        SETBIT(timer->PWMC,1);
    }
    
    if( (pwmSelected&PWM2)==PWM2)
    {
        timer->MR2 = cycle;
        SETBIT(timer->EMR,2);
        timer->EMR |= BITS(8,0x3);
        SETBIT(timer->PWMC,2);
    }
}

void setPwmCycle(LPC_TMR_TypeDef * timer, PWM pwmSelected, UInt32 cycle)
{
    if( (pwmSelected&PWM0)==PWM0)
    {
        timer->MR0 = cycle;
    }
    
    if( (pwmSelected&PWM1)==PWM1)
    {
        timer->MR1 = cycle;
    }
    
    if( (pwmSelected&PWM2)==PWM2)
    {
        timer->MR2 = cycle;
    }
}




//-------------------------- public functions:


void initPwm(PWMTIMER timerType, TIMER timerSelected, PWM pwmSelected, UInt32 widthInUs, UInt32 widthDivider, UInt32 percentage)
{
    LPC_TMR_TypeDef * timer = 0;
    UInt32 widthPwm, cycle;
    
    // power on timer module
    
    
    if(timerType == TIMER32)
    {
        // SYSAHBCLKCTRL bit9 1 = timer0 bit10 1 =timer1 (32 bits)
        if( timerSelected == TIMER0)
        {
            timer = LPC_TMR32B0;
            SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,9);
        }
        else
        {
            timer = LPC_TMR32B1;
            SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,10);
        }
    }
    else if(timerType == TIMER16)
    {
        // SYSAHBCLKCTRL bit7 1 = timer0 bit8 1 =timer1 (16 bits)
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
    }
    
    // select output pwm pin 
    setPwmPin(timerType,timerSelected,pwmSelected);
    
    
    // For 16 bits timer, when prescaler set to 0, pwm is between 1.1 kHz and 1 MHz

    widthPwm = (KERNEL_CPU_FREQ / 1000) * widthInUs -1;
    
    // Set the width divider
    if (widthDivider!=0)
    {
        timer->PR = widthDivider -1;
    }
    
    //#ifdef PWM_UNIT_100NS
    //    widthPwm = (KERNEL_CPU_FREQ / 1000) * widthInUs -1;
    //#else
    //    widthPwm = (KERNEL_CPU_FREQ / 10000) * widthInUs -1;
    //#endif
    
    
    // MR3 store the pwm period
    timer->MR3 = widthPwm;

    // MRx store the pwm duty cycle: time the MATx pin is high
    cycle = (widthPwm * (100 - percentage)) / 100;
    
       
    // reset when MR3 match the timer counter
    SETBIT(timer->MCR,10);
    
    
    setPwmConfig(timer,pwmSelected,cycle);
    
    // enable pwm0 and pwm3:
    // 1- when a match occurs in MR0, then MAT0 goes HIGH
    // 2- and timer get the MR3 value
    // 3- when timer reach 0, then MAT0 goes LOW and reloaded with MR0
    SETBIT(timer->PWMC,3);
    
}

void enablePwm(PWMTIMER timerType, TIMER timerSelected, Bool start)
{
    LPC_TMR_TypeDef * timer = 0;
    
    if(timerType == TIMER32)
    {
        if( timerSelected == TIMER0)
        {
            timer = LPC_TMR32B0;
        }
        else
        {
            timer = LPC_TMR32B1;
        }
    }
    else if(timerType == TIMER16)
    {
        if( timerSelected == TIMER0)
        {
            timer = LPC_TMR16B0;
        }
        else
        {
            timer = LPC_TMR16B1;
        }
    }
    
    if( start==False)
    {
        // disable timer
        CLRBIT(timer->TCR,0);
        SETBIT(timer->TCR,1);
    }
    else
    {
        // enable timer
        SETBIT(timer->TCR,0);
        CLRBIT(timer->TCR,1);
    }
}

void setPwmDutyCycle(PWMTIMER timerType, TIMER timerSelected, PWM pwmSelected, UInt32 percentage)
{
    LPC_TMR_TypeDef * timer = 0;
    UInt32 widthPwm;
    UInt32 cycle;
    
    if(timerType == TIMER32)
    {
        if( timerSelected == TIMER0)
        {
            timer = LPC_TMR32B0;
        }
        else
        {
            timer = LPC_TMR32B1;
        }
    }
    else if(timerType == TIMER16)
    {
        if( timerSelected == TIMER0)
        {
            timer = LPC_TMR16B0;
        }
        else
        {
            timer = LPC_TMR16B1;
        }
    }
    
    widthPwm = timer->MR3;

    // MRx store the pwm duty cycle: time the MATx pin is high
    cycle = (widthPwm * (100 - percentage)) / 100;
    
    setPwmCycle(timer, pwmSelected,cycle);
}


void setPwmWidth(PWMTIMER timerType, TIMER timerSelected, UInt32 widthInUs)
{
    LPC_TMR_TypeDef * timer = 0;
    UInt32 widthPwm;
    
    // power on timer module
    
    if(timerType == TIMER32)
    {
        // SYSAHBCLKCTRL bit9 1 = timer0 bit10 1 =timer1 (32 bits)
        if( timerSelected == TIMER0)
        {
            timer = LPC_TMR32B0;
        }
        else
        {
            timer = LPC_TMR32B1;
        }
    }
    else if(timerType == TIMER16)
    {
        // SYSAHBCLKCTRL bit7 1 = timer0 bit8 1 =timer1 (16 bits)
        if( timerSelected == TIMER0)
        {
            timer = LPC_TMR16B0;
        }
        else
        {
            timer = LPC_TMR16B1;
        }
    }
   
    //todo 100us = (KERNEL_CPU_FREQ/100)*10 -1
    //todo 10us  = (KERNEL_CPU_FREQ /100) -1
    //todo 1us   = (KERNEL_CPU_FREQ /1000) -1
    
    widthPwm = (KERNEL_CPU_FREQ / 1000) * widthInUs -1;
   
    
    timer->TC = 0;
    
    // MR3 store the pwm period
    timer->MR3 = widthPwm;
}