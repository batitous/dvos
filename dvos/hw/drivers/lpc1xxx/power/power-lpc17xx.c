
#include "../include/libs-hardware.h"


void SetPowerSupply(POWERDRIVER driver, Bool enable)
{
    if(enable==True)
    {
        SETBIT(LPC_SC->PCONP,driver);
    }
    else
    {
        CLRBIT(LPC_SC->PCONP,driver);
    }
    
}


