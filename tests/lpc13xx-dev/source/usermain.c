

#include <libs-hardware.h>
#include <kernel-dvos.h>

#include "../include/Sensors.h"



void led(void)
{
    UInt32 led=0;
    
    //setGpioDirection(GPIO0_7,GPIO_OUT); //led
    
    waitMs(1000);
    
    dumpKernel();
    
    while(1)
    {
        
        
        if(led==0)
        {
            setGpioValue(GPIO0_7,0);
            led=1;
        }
        else
        {
            setGpioValue(GPIO0_7,1);
            led=0;
        }
        
        waitMs(50);
        
    }
}


int usermain(void)
{
    setGpioDirection(GPIO0_7,GPIO_OUT); //led
    
    
    // Initialize uart0 and set debugger interface
    initUART0();
    setDebugInterface(sendByteToUART0);
    
    debugPrintf("lpc13xx is running !\r\n");
    
    
    // Power down usb clock
    SETBIT(LPC_SYSCON->PDRUNCFG,10);
    SETBIT(LPC_SYSCON->PDRUNCFG,8);
    

    newThread(led,512,10,5);
//    newThread(PRS_I2CComm,512,10,4);

   
    
    return 0;
}

