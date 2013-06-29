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
#include "../include/mcu/lpc13xx.h"
#include "../include/types.h"
#include "../include/utils.h"

//
// lpc13xx mcu boot processor code
//



//this code is called at cpu reset: don't call it directly!
void initLowLevelCpu(void)
{
    UInt32 i;

    // Power on I/O
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,16);
        
    //====== CONFIGURE CLOCK & OSCILLATOR ====//

    // Power up system oscillator
    CLRBIT(LPC_SYSCON->PDRUNCFG,5); //system oscillator power on
    
    // Use an external oscillator between 1-20 MHz
//    SETBIT(LPC_SYSCON->SYSOSCCTRL,0);

    // use internal osc ?
    CLRBIT(LPC_SYSCON->SYSOSCCTRL,0);
  
    for (i = 0; i < 200; i++)
    {
        __NOP();
    }
    
    // Use system oscillator
    LPC_SYSCON->SYSPLLCLKSEL = 0 ;
        
#ifdef MCU_IS_LPC1311
    // Update system oscillator
    LPC_SYSCON->SYSPLLCLKUEN  = 1;
    LPC_SYSCON->SYSPLLCLKUEN  = 0;
    LPC_SYSCON->SYSPLLCLKUEN  = 1;

    // Wait oscillator update
    while ( !(LPC_SYSCON->SYSPLLCLKUEN & BIT(0)) );
#endif
    
    
    // Compute M :
    //
    // M = CPU / OSC
    // M = 72MHz / 12MHz
    
    // Compute P :
    //
    // FCC0 = 2 x P x 72MHz AND 156MHz < FCC0 < 320MHz
    //
    // P = 2
    // FCC0 = 2 x 2 x 72MHz = 288MHz
    //
    // MUST SET M-1 AND P-1
    
    // Set system pll clock value
    LPC_SYSCON->SYSPLLCTRL = BITS(0,5) | BITS(5,1);
      
    // Power up system pll
    CLRBIT(LPC_SYSCON->PDRUNCFG,7);
    
    while (!(LPC_SYSCON->SYSPLLSTAT & BIT(0)) );
    
    // Use system pll clock out for the main clock
    LPC_SYSCON->MAINCLKSEL    = 3;
    
    // Update main clock selection
#ifdef MCU_IS_LPC13xx
    LPC_SYSCON->MAINCLKUEN    = 1;
    LPC_SYSCON->MAINCLKUEN    = 0;
    LPC_SYSCON->MAINCLKUEN    = 1;

    // Wait main clock
    while ( !(LPC_SYSCON->MAINCLKUEN & BIT(0)) );
#endif
    
    //====== USB Clock ====//
    // USB avalaible only on LPC1343
    
    // Power down usb clock
    
   // SETBIT(LPC_SYSCON->PDRUNCFG,10);
   // SETBIT(LPC_SYSCON->PDRUNCFG,8);
      

    //====== Peripheral clock ====//
    
    // System clock divider : 
    // divide the main clock for the core, memory and peripheral
    LPC_SYSCON->SYSAHBCLKDIV  = 1;
    
    // Voir le datasheet page 26 pour les clocks des peripheriques
    
    // Disable USB clock
  //  CLRBIT(LPC_SYSCON->SYSAHBCLKCTRL,14);
     
    //====== Flash access clock ====//
    // bon pour le moment on s'en fout si cpu = 72MHz
    //    CLRBITS(LPC_SYSCON->FLASHCFG, 3);
//    LPC_SYSCON->FLASHCFG |= BIT(1);
    
    // Interrupt vectors are in flash memory
    //LPC_SYSCON->SYSMEMREMAP = 0x2;
    
    
   
}
