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
#ifndef DVOS_KERNEL_EVENT_H
#define DVOS_KERNEL_EVENT_H


/** @brief An event */
typedef struct _k_event_
{
    UInt32          time;       /**< time when event posted */
    UInt32          id;         /**< identifier of event */
    UInt32          message;    /**< message (optionnal) */
} KEvent;


/** @brief Event callback */
typedef void (*KEventCallback)(KEvent * node);


/** @brief Event register object */
typedef struct _k_event_register_
{
    KLink *             next;   /**< next event registered */
    UInt32              id;     /**< id of event */
    KEventCallback      callback; /**< user callback code */
    UInt32              data;   /**< specific data for user callback */
    //todo add auto register or remove when first event ?
} KEventRegister;


// don't use id event with bit > 0x10000, it's system reserved !


#define KEVENT_GPIO_MASK        0x80000000      /**< gpio interrupt event */
#define KEVENT_ALARM_MASK       0x40000000      /**< alarm event */


/** @brief Initialize the event manager 
 */
extern void initEventManager(void);

/** @brief Register a event
 * @param id
 * @param user
 * @param userData
 * @return True if success
 */
extern Bool registerEvent(UInt32 id, KEventCallback user, UInt32 userData);

/** @brief Post an event
 * 
 * @param id
 * @param message
 */
extern void postEvent(UInt32 id, UInt32 message);

/** @brief Post event from an IRQ routine 
 * @param id
 * @param message
 */
extern void postEventFromIrq(UInt32 id, UInt32 message);

#endif
