

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
        
        waitMs(4);
        
    }
}


void PRS_I2CComm(void)
{
    UInt8 data;
    UInt8 buffer[16];
    
    data = 0;
    
    initSensorPRS(SENSOR_I2C_7SEGMENT, GPIO3_0);
        
    while(1)
    {
        data = getBufferFromMasterI2C0(buffer, 16);
        
        if( data != 0)
        {
                updateMemoryModule(buffer,data);
        }
    }
}

UInt8 array[16];

void func(void)
{
    //DebugPrintf("%c", array[0]);
}


void memCallback(UInt16 address, UInt8 *ptr, UInt32 size)
{
    setBufferToMasterI2C0(ptr,size);
}

int usermain(void)
{
    setGpioDirection(GPIO0_7,GPIO_OUT); //led
    
    /*
    SetGpioValue(GPIO0_7,1);
    waitUs(100000);
    SetGpioValue(GPIO0_7,0);
    waitUs(100000);
    SetGpioValue(GPIO0_7,1);
     */ 
    waitUs(100000);
    setGpioValue(GPIO0_7,0);
    waitUs(100000);
    setGpioValue(GPIO0_7,1);
    
    
    // Initialize uart0 and set debugger interface
    initUART0();
    setDebugInterface(sendByteToUART0);
    
    debugPrintf("lpc13xx is running !\r\n");
    
    
    
    initMemoryModule(6, memCallback);
    
    addMemoryModule(    0x1000,      (UInt8 *)&array,  16,   &func       );
    addMemoryModule(    0x2000,      (UInt8 *)&array,  16,   &func       );
    addMemoryModule(    0x3000,      (UInt8 *)&array,  16,   &func       );
    addMemoryModule(    0x4000,      (UInt8 *)&array,  16,   &func       );
    addMemoryModule(    0x5000,      (UInt8 *)&array,  16,   &func       );
    addMemoryModule(    0x6000,      (UInt8 *)&array,  16,   &func       );
    
    

    newThread(led,512,10,5);
    newThread(PRS_I2CComm,512,10,4);

   
    
    return 0;
}

