
#include "../../kernel/include/kernel-dvos.h"
#include "../include/libs-hardware.h"

//----------------------------- private objects:



// Manage the input/output interrupt for the KEvent manager
void keventGpioIrqCallback(UInt32 event, UInt32 edge)
{
    PostEventFromIrq(KEVENT_GPIO_MASK | event, edge );
}
