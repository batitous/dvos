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
#ifndef DVOS_KERNEL_THREAD_H
#define DVOS_KERNEL_THREAD_H

#define THREAD_CPU_MINIMUM     1        /**< lowest cpu request (don't use it...) */
#define THREAD_CPU_MAXIMUM     255      /**< highest cpu request */

#define THREAD_PRIORITY_MIN     1       /**< lowest scheduler priority (don't use it...) */
#define THREAD_PRIORITY_MAX     255     /**< highest scheduler priority */


/** @brief Kernel thread object
 *
 */
typedef struct _kernel_thread_
{
    KLink *     next;       /**< pointer to the next thread */
    KLink *     prev;       /**< pointer to the previous thread */
    UInt32 *    stack;      /**< thread stack */
//    UInt32      signal;     /**< signal pattern */
    UInt32      waiting;    /**< remaining time to wait for this thread */
    UInt8       quantum;    /**< current quantum of task's scheduler */
    UInt8       cpuRequest; /**< cpu time */
    UInt8       priority;   /**< priority */
    UInt8       isReady;    /**< is this thread in the ready task list ? */
    
#ifdef KERNEL_USE_DEBUG
    UInt32      cpuUsage;   /**< cpu used by the thread */
    UInt32 *    stackBegin; /**< address of stack */
    UInt32      stackUsage; /**< stack used by thread */
#endif
    
} KThread;


/** @brief Create a new thread.
 *
 * @param userCode      Pointer to a function.
 * @param stackSize     Size of stack for this thread.
 * @param cpuTime       Cpu time requested.
 * @param priority      Thread priority.
 * @return A new KThread pointer or 0 if system is out of memory.
 */
extern KThread * newThread( void (*userCode)(void) , UInt32 stackSize , UInt8 cpuTime, UInt8 priority);


#endif
