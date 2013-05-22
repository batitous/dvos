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
#include "../../hw/include/libs-default.h"

#include "../include/kmemory.h"
#include "../include/klist.h"
#include "../include/kthread.h"
#include "../include/kernel.h"
#include "../include/kernel-private.h"
#include "../include/kevent.h"

//-------------------------- private menbers:

#define EVENT_MAX                       16      /**< if you have more than 16 events in less than 100 us, then increase */

#define EVENT_THREAD_CPU_TIME           10      /**< 1 ms is given to the event thread */
#define EVENT_THREAD_PRIORITY           100     /**< high priority */
#define EVENT_THREAD_STACK_SIZE         512     /**< size of event thread stack */

static UInt32 kEventRead;               /**< read index in kEvents */
static volatile UInt32 kEventWrite;     /**< write index in kEvents */

static KEvent kEvents[EVENT_MAX];       /**< stack of event */

static SList kEventRegisters ;          /**< list of event callback */
KThread * kEventThread;                 /**< event thread manager */


//-------------------------- private functions:

KEventRegister * getEventRegister(UInt32 id)
{
    KEventRegister * temp = (KEventRegister *)kEventRegisters.next;

    // todo ca pue ce truc pour le moment
    
    while(temp!=0)
    {
        if(temp->id==id)
        {
            return temp;
        }
        temp = temp->next;
    }
    
    return 0;
}

void kEventThreadManager(void)
{
    UInt32 size,i;
    KEventRegister * manager = kEventRegisters.next;
    KEvent * e;
    
    while(1)
    {
        size = kEventWrite;
        
        if(size!=kEventRead)
        {
            for( i = kEventRead ; i != size ; )
            {
                // retrieve the event object from the event posted
                // then, call the event callback
                
                e = kEvents + (i & (EVENT_MAX-1));
                
                if(manager->id!=e->id)
                {
                    manager = getEventRegister(e->id);
                }
                
                
                if(manager!=0)
                {
                    if(manager->callback!=0)
                    {
                        manager->callback(e);
                    }
                }
                
                i++;
            }
            kEventRead = i;
        }
        
        // if event has been posted during the for loop, then relaunch the loop
        if(kEventWrite==kEventRead)
        {
            setTaskAsBlocked();
        }
    }
}

void _postKEvent(UInt32 id, UInt32 message)
{
    UInt32 tmp = kEventWrite & (EVENT_MAX-1);
    
    kEvents[tmp].id = id;
    kEvents[tmp].message = message;
    kEvents[tmp].time = GetCurrentTimeOfKernel();
    
    kEventWrite++;
}

//--------------------------  public menbers:

void initEventManager(void)
{
    UInt32 i;
    
    kEventRead = 0;
    kEventWrite = 0;
    
    initSList(&kEventRegisters);
    
    for(i=0;i<EVENT_MAX;i++)
    {
        kEvents[i].time = 0;
        kEvents[i].id = 0;
        kEvents[i].message = 0;
    }
    
    // event manager thread is set with a high priority
    kEventThread = newThread(&kEventThreadManager,EVENT_THREAD_STACK_SIZE,EVENT_THREAD_CPU_TIME,EVENT_THREAD_PRIORITY);
       
}

Bool registerEvent(UInt32 id, KEventCallback user)
{
    KEventRegister * manager;
    
    
    manager = getEventRegister(id);
    if( manager != 0)
    {
        //todo add user callback in the event callback list
        
        
        // event already exist !
        return False;
    }
    
    manager = (KEventRegister *)malloc(sizeof(KEventRegister));
    if( manager == 0)
    {
        return False;
    }
    
    
    manager->id = id;
    manager->callback = user;
 
    insertSNodeToStart(&kEventRegisters,(KLink *)manager);

//    DebugPrintf("RegisterEvent 0x%x\r\n", id);
    
    return True;
}

void postEvent(UInt32 id, UInt32 message)
{
    _postKEvent(id,message);
    setTaskAsReady(kEventThread);
}

void postEventFromIrq(UInt32 id, UInt32 message)
{
    _postKEvent(id,message);
    irqSetTaskAsReady(kEventThread);
}