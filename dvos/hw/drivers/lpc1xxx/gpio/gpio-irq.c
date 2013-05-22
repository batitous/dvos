
#include "../include/libs-hardware.h"


//----------------------------- private functions

extern void keventGpioIrqCallback(UInt32 event, UInt32 edge);

UInt32 getIRQNumber(UInt32 reg)
{
    UInt32 i;
    
    for(i=0;i<31;i++)
    {
        if( ((reg >> i)&0x1) != 0)
        {
            return i;
        }
    }
    return 0;
}

//----------------------------- public functions

void EnableEventOnGpio(GPIO_PIN pin, GPIO_EDGE edge, KEventCallback callback)
{
    // encode the event id with pin, edge and event mask
    if( RegisterEvent( KEVENT_GPIO_MASK | pin /*| edge*/, callback) == False )
    {
        return;
    }
    
    SetGpioIrqCallback(keventGpioIrqCallback);
        
    SetGpioDirection(pin,GPIO_IN);
    EnableGpioIrq(pin,edge);
    
}
