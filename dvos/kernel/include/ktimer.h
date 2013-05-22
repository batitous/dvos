
#ifndef DVOS_KERNEL_TIMER_H
#define DVOS_KERNEL_TIMER_H

/** @brief Alarm object
 */
typedef struct _kalarm_
{
    KLink *     next;       /**< pointer to the next alarm */
    KLink *     prev;       /**< pointer to the previous alarm*/
    KThread *   thread;     /**< thread that receive this alarm */
    UInt32      remaining;  /**< time remaining before alarm */
    UInt32      reload;     /**< time to be reloaded */
    UInt16      id;         /**< alarm's id for event post/get, 0 if it's not an event */
} KAlarm;


/** @brief Create a new alarm object.
 *
 * @param delay     in ms
 * @param A new alarm object.
 */
extern KAlarm * newAlarm(UInt32 delay);

/** @brief Start the alarm.
 *
 * @param alarm     The alarm to start.
 */
extern void startAlarm(KAlarm * alarm);

/** @brief Wait the alarm.
 *
 * @param alarm     The alarm.
 */
extern void waitAlarm(KAlarm * alarm);


/** @brief Wait some delays...
 *
 * @param delay     Delay to wait in ms, between 1 and 6500.
 */
extern void waitMs(UInt32 delay);

extern void wait100Us(UInt32 delay);

extern void setDelayOfAlarm(KAlarm * alarm, UInt32 delay);

//WARNING Alarm is not started !
extern KAlarm * enableEventOnAlarm(UInt32 delay, KEventCallback callback);

#endif
