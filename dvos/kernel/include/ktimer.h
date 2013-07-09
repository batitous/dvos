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
extern KAlarm * enableEventOnAlarm(UInt32 delay, KEventCallback callback, UInt32 dataForCallback);

#endif
