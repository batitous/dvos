
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
