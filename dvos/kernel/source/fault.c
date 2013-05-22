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
#include "../../hw/include/libs-default.h"

#include "../include/kernel.h"



/* try to manage processor fault */

#ifdef FIRMWARE_USE_DEBUG

extern void dumpFaultHandler(UInt32 * stack);

#endif


// Bus Faults Exception
void BusFault_Handler(void)
{
    // access to invalid memory
    DebugPrintf("BUS FAULTS EXCEPTION\r\n");
}

// Memory Management Exception
void MemManage_Handler(void)
{
    // write to a read only memory, access to a undefined mpu region
    DebugPrintf("MEMORY MANAGEMENT EXCEPTION\r\n");
}

// Usage Faults Exception
void UsageFault_Handler(void)
{
    DebugPrintf("USAGE FAULTS EXCEPTION\r\n");
}


// Hard Faults Exception
//naked : no backup, no restore, no return : we need to do all this things
void HardFault_Handler(void) __attribute__( ( naked ) );
void HardFault_Handler(void)
{
#ifdef FIRMWARE_USE_DEBUG
    // this exception has the highest priority (whitout the reset and nmi) :
    // in most fault case, we are in this exception
    UInt32 reg;
    UInt32 * r;

    // get correct stack : process stack or main stack
    __asm __volatile__ (
        "tst    LR,#4\r\n"
        "ite    eq\r\n"
        "mrseq  %[result],MSP\r\n"
        "mrsne  %[result],PSP"
        : [result]"=r" (reg)
        );

    // function is naked: save LR register !
    __asm__ ("push {lr}");

    
    // dump stack :
    r = (UInt32 *)reg;
    dumpFaultHandler(r);
    

    // function is naked: exit irq by a pop !
    __asm__ ("pop {pc}");
#endif
}
