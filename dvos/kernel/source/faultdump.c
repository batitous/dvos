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
#include "../../hw/include/libs-default.h"

#include "../include/kernel.h"

#define BFAR    (*(volatile UInt32 *)(0xE000ED38))
#define MMAR    (*(volatile UInt32 *)(0xE000ED34))
#define MMSR    (*(volatile UInt32 *)(0xE000ED28))

void dumpFaultHandler(UInt32 * stack)
{
    UInt32 r0,r1,r2,r3,r12,lr,pc,psr;
    
    r0 = stack[0];
    r1 = stack[1];
    r2 = stack[2];
    r3 = stack[3];
    r12 = stack[4];
    lr = stack[5];
    pc = stack[6];
    psr = stack[7];

    DebugPrintf("HARDFAULT EXCEPTION\r\n");
    DebugPrintf("[ Dump stack and fault register from base 0x%x]\r\n", stack );
    DebugPrintf("R0  = 0x%x\r\n", r0);
    DebugPrintf("R1  = 0x%x\r\n", r1);
    DebugPrintf("R2  = 0x%x\r\n", r2);
    DebugPrintf("R3  = 0x%x\r\n", r3);
    DebugPrintf("R12 = 0x%x\r\n", r12);
    DebugPrintf("LR  = 0x%x\r\n", lr);
    DebugPrintf("PC  = 0x%x\r\n", pc);
    DebugPrintf("psr = 0x%x\r\n", psr);
    DebugPrintf("PSP = 0x%x\r\n", __get_PSP() );

    // Bus fault address 
    DebugPrintf("BFAR = %x\r\n", BFAR );
    // MemManage Fault address 
    DebugPrintf("MMAR = %x\r\n", MMAR );
    // MemManage Fault Status
    DebugPrintf("MMSR = %x\r\n", MMSR  );
    // Hard Fault Status
    DebugPrintf("HSFR = %x\r\n", (*(volatile UInt32 *)(0xE000ED2C)) );
    // Debug Fault Status
    DebugPrintf("DFSR = %x\r\n", (*(volatile UInt32 *)(0xE000ED30)) );
    // Auxiliary Fault Status
    DebugPrintf("AFSR = %x\r\n", (*(volatile UInt32 *)(0xE000ED3C)) );
    
    //MMSR = 0; //cradok de chez cradok
    
    // test virtual memory
//    if( BFAR > 0x80000 && BFAR < 0x10000000)
//    {
//        DebugPrintf("read/write to virtual address\r\n");
//        stack[6] = stack[6] +2; //arm +4
//    }
//    else
//    {
        dumpKernel();
        while(1);
//    }
            
}
