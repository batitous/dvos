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

#include "../include/klist.h"
#include "../include/kthread.h"
#include "../include/kernel.h"

extern volatile KThread * currentTask;

void dumpFaultHandler(UInt32 * stack)
{
    UInt32 r0,r1,r2,r3,r12,lr,pc,psr;
    
    UInt8 string[8];
    UInt32 i;
    
    r0 = stack[0];
    r1 = stack[1];
    r2 = stack[2];
    r3 = stack[3];
    r12 = stack[4];
    lr = stack[5];
    pc = stack[6];
    psr = stack[7];
    

    // print PC LR STACK KERNELTIME
    
    SendByteToUART0('P');
    SendByteToUART0('C');
    SendByteToUART0(':');
    
    PutHexa(string,0,8,0,pc);
    
    for(i=0;i<8;i++)
        SendByteToUART0(string[i]);
    
    
    SendByteToUART0(' ');
    SendByteToUART0('L');
    SendByteToUART0('R');
    SendByteToUART0(':');
    
    PutHexa(string,0,8,0,lr);
    
    for(i=0;i<8;i++)
        SendByteToUART0(string[i]);

    SendByteToUART0(' ');
    SendByteToUART0('S');
    SendByteToUART0('T');
    SendByteToUART0(':');
    
    PutHexa(string,0,8,0,stack);
    
    for(i=0;i<8;i++)
        SendByteToUART0(string[i]);
    
    SendByteToUART0(' ');
    SendByteToUART0('T');
    SendByteToUART0('h');
    SendByteToUART0(':');
    
    PutHexa(string,0,8,0,currentTask);
    
    for(i=0;i<8;i++)
        SendByteToUART0(string[i]);
    
    while(1);
}
