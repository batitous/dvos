
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
