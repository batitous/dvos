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

#include "../include/kmemory.h"
#include "../include/klock.h"
#include "../include/klist.h"
#include "../include/kthread.h"
#include "../include/kmutex.h"

#include "../include/kernel-private.h"

KMutex * newMutex(void)
{
    KMutex * result = malloc( sizeof(KMutex));
    if(result==0)
    {
        return 0;
    }

    result->lock = 0;
    result->blocked = 0;

    return result;
}


void lockMutex(KMutex * mutex)
{
    if( trylock( &mutex->lock ) == False)
    {
        mutex->blocked = (KThread *)currentTask;
        setTaskAsBlocked();
    }
}


void unlockMutex(KMutex * mutex)
{
    unlock( &mutex->lock);
    KThread * tmp = mutex->blocked;
    if( tmp != 0)
    {
        mutex->blocked = 0;
        setTaskAsReady(tmp);
    }
}
