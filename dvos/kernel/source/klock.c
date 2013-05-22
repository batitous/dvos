/*
	Dvos - Copyright © 2013 Baptiste Burles, Christophe Casson, Sylvain Fay-Chatelard

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


