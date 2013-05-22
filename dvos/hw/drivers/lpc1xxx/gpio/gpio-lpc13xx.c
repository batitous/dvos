
#include "../include/libs-hardware.h"


void EnableGpioHysteresis(GPIO_PIN pin)
{
    
    // to add your own GPIO Hysteresis, go to LPC13XX datasheet at chapter "I/O Configuration"
    
    switch(pin)
    {
        case GPIO3_3:
            SETBIT(LPC_IOCON->PIO3_3,5);
            break;
            
        case GPIO1_0:
            SETBIT(LPC_IOCON->R_PIO1_0,5);
            break;
    }
}
