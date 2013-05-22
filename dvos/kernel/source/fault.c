
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
