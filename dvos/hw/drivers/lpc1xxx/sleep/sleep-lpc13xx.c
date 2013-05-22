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



//-------------------------- public functions

void SetMcuToSleep(SLEEPMODE mode)
{
    if(SLEEP_DEFAULT==mode)
    {
        // Sleep mode:
        // PCON.DPDEN bit 1 = 0
        // SCR.SLEEDEEP bit 2 = 0
        // WFI
        // Sleep mode exit: any IRQ enabled
        
        CLRBIT(LPC_PMU->PCON,1); //PCON.DPDEN bit 1 = 0
        SETBIT(LPC_PMU->PCON,11); //Clear the Deep power-down flag
        CLRBIT(SCB->SCR,2);
        __WFI();
    }
    else if(SLEEP_DEEP==mode)
    {
        // Deep-sleep mode:
        // PCON.DPDEN bit 1 = 0
        // set MAINCLKSEL to IRC
        // set PDAWAKECFG for wakeup

        // external pins used: see start logic register and enable start logic IRQ
        // pin: PIO0_0 to PIO0_11, PIO1_0 to PIO1_11 and PIO2_0 to PIO2_7
        // Enable register pin : STARTERP0
        // 

        // disable all peripherals SYSAHBCLKCTRL
        // SCR.SLEEPDEEP bit 2 = 1
        // WFI

        // Deep-sleep mode exit: GPIO IRQ, RTC alarm, Watchdog timeout, USB
        
        // Use internal clock for the main clock
        LPC_SYSCON->MAINCLKSEL    = 0;

        // Update main clock selection
        LPC_SYSCON->MAINCLKUEN    = 1;
        LPC_SYSCON->MAINCLKUEN    = 0;
        LPC_SYSCON->MAINCLKUEN    = 1;

        // Wait main clock
        while ( !(LPC_SYSCON->MAINCLKUEN & BIT(0)) );

        
        // Clear deep sleep flag
//        SETBIT(LPC_PMU->PCON,8);
        
        // Clear the deep power down flag
        SETBIT(LPC_PMU->PCON,11);
        CLRBIT(LPC_PMU->PCON,1);
        
        // Turn off Watchdog and brown out detector (decrease consumption)
        LPC_SYSCON->PDSLEEPCFG |= 0x00000FFF;
        
        // Select the peripheral to be powered when wakeup
        LPC_SYSCON->PDAWAKECFG = LPC_SYSCON->PDRUNCFG;
        
        // Initialize the wakeup source
        InitWakeUp();
        
        // Set Deep Sleep mode
        SETBIT(SCB->SCR,2);
        
        __WFI();
    }
    else if(SLEEP_DEEP_POWERDOWN==mode)
    {
        // We can wakeup only on the Wakeup pin AD5 
        
        // bref j'ai pas vu de difference de consommation 
        // entre le slee deep et le sleep deep powerdown
        
        // todo trouver le machin qui consomme ?
        
        SETBIT(LPC_PMU->PCON,1);
      
        //setIOInLowPowerMode();
        
       // set IRCOUT_PD & IRC_PD bits to 0 (PDRUNCFG Register)  
       // Set bits in PDRUNCFG to power down all perihphics except Flash and BOD powered  
       LPC_SYSCON->PDRUNCFG=0xEDFC; 
       LPC_SYSCON->SYSAHBCLKCTRL = 0;
       
       CLRBIT(LPC_SYSCON->SYSAHBCLKCTRL,5);
       CLRBIT(LPC_SYSCON->SYSAHBCLKCTRL,6);
       CLRBIT(LPC_SYSCON->SYSAHBCLKCTRL,7);
       CLRBIT(LPC_SYSCON->SYSAHBCLKCTRL,11);
       CLRBIT(LPC_SYSCON->SYSAHBCLKCTRL,13);
       CLRBIT(LPC_SYSCON->SYSAHBCLKCTRL,14);
    
       //Write 1 to SLEEPDEEP bit SCR Register
        SETBIT(SCB->SCR,2);
        
        __WFI();
    }
    
    
}

