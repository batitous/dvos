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
#include "../include/libs-hardware.h"


void setMcuToSleep(SLEEPMODE mode)
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
