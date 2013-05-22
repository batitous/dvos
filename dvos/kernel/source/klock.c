
#include "../../hw/include/libs-default.h"

#include "../include/klock.h"

Bool trylock(UInt32 * ressources)
{
    if( __LDREXW((uint32_t *)ressources) == 0)
    {
        if(__STREXW( 1, (uint32_t *)ressources) != 0)
        {
            return False;
        }
        else
        {
            // ressources is not used by another thread, we can use them !
            return True;
        }
    }
    else
    {
        return False;
    }
}

void unlock(UInt32 * ressources)
{
    // clear the ressources for other thread
    //__STREXW( 0, ressources);

    *ressources = 0;
}


