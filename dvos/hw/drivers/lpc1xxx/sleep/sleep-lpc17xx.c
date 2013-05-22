
#include "../include/libs-hardware.h"


void SetMcuToSleep(SLEEPMODE mode)
{
    // power down not implemented
    
    if(SLEEP_DEEP_POWERDOWN==mode)
    {
        // deep power down sleep
        
        SETBIT(SCB->SCR,2);
        
        // power down
        SETBIT(LPC_SC->PCON,0);
        // deep power down
        SETBIT(LPC_SC->PCON,1);
        
        //fully deactivate brown out
        SETBIT(LPC_SC->PCON,2);
        SETBIT(LPC_SC->PCON,3);
        
        __WFI();
    }
    else if (SLEEP_DEEP==mode)   
    {
        //deep sleep
        LPC_SC->PCON = 0x00;
        
       //fully deactivate brown out 
       SETBIT(LPC_SC->PCON,2);
       SETBIT(LPC_SC->PCON,3);
       
       //Enable sleepdeep 
       SETBIT(SCB->SCR,2);
        
      __WFI();
    }
    else
    {
        // default sleep
        LPC_SC->PCON = 0;
        SCB->SCR = 0;
        
       __WFI();
    }
}
