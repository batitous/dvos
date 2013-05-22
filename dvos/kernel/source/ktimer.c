
#include "../../hw/include/libs-default.h"

#include "../include/kmemory.h"
#include "../include/klist.h"
#include "../include/kthread.h"
#include "../include/kernel.h"
#include "../include/kernel-private.h"
#include "../include/kevent.h"
#include "../include/ktimer.h"


/* private definitions */

extern void _postKEvent(UInt32 id, UInt32 message);

/* private menbers */

KList alarms;


/* private functions */

void initKAlarm(void)
{
    initKList(&alarms);
}


void manageKTimer(void)
{
    //warning this code is executed in kernel mode !
    KThread * th = (KThread *)(tasksWaiting.next);
    KAlarm * alarm = (KAlarm *)(alarms.next);

    KThread * next;


    // manage wait
    while( th != (KThread *)&tasksWaiting)
    {
        next = th->next;
        if(th->waiting!=0)
        {
            th->waiting = th->waiting -1;

            if(th->waiting == 0)
            {
                kernelSetTaskAsReady(th);
            }
        }

        th = next;
    }

    // manage alarm
    while( alarm!= (KAlarm *)&alarms)
    {
        if(alarm->remaining != 0)
        {
            alarm->remaining = alarm->remaining -1;

            if(alarm->remaining==0)
            {
#ifdef KERNEL_USE_KEVENT
                if(alarm->id!=0)
                {
                    // instead of wakeup a thread, post an event
                    alarm->remaining = alarm->reload;
                    

                    // we can't use the "postEvent" here :-(
                    _postKEvent(KEVENT_ALARM_MASK | alarm->id ,0);

                    extern KThread * kEventThread;
                    kernelSetTaskAsReady(kEventThread);
                }
                else
#endif //KERNEL_USE_KEVENT
                {    
                    if(alarm->thread!=0)
                    {
                        kernelSetTaskAsReady(alarm->thread);
                    }
                }    
            }
        }

        alarm = alarm->next;
    }
}

/* public functions */

void wait100Us(UInt32 delay)
{
    currentTask->waiting = delay;
    setTaskAsWaiting();
}

void waitMs(UInt32 delay)
{
    Wait100Us(delay*10);
}

KAlarm * newAlarm(UInt32 delay)
{
    KAlarm * alarm = malloc( sizeof(KAlarm));
    if(alarm==0)
    {
        return 0;
    }

    alarm->remaining = 0;
    alarm->reload = delay * 10;
    alarm->thread = (KThread *)currentTask;
    alarm->id = 0;
    
    insertKNodeToEnd(&alarms,(KNode *)alarm);

    return alarm;
}

void setDelayOfAlarm(KAlarm * alarm, UInt32 delay)
{
    alarm->reload = delay * 10;
}

void startAlarm(KAlarm * alarm)
{
    alarm->remaining = alarm->reload;
}

void waitAlarm(KAlarm * alarm)
{
    alarm->thread = (KThread *)currentTask;

    setTaskAsWaiting();

    alarm->remaining = alarm->reload;
}

#ifdef KERNEL_USE_KEVENT

static UInt16 kEventLastAlarmId = 1;

KAlarm * enableEventOnAlarm(UInt32 delay, KEventCallback callback)
{
    KAlarm * alarm = newAlarm(delay);
    
    alarm->id = kEventLastAlarmId;
    kEventLastAlarmId++;
        
    registerEvent( KEVENT_ALARM_MASK | alarm->id , callback);
    
    return alarm;
}
#endif
