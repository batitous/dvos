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
#ifndef DVOS_KERNEL_PRIVATE_H
#define DVOS_KERNEL_PRIVATE_H

/** this files include all the private functions and objects of the kernel.
*/


/** @brief Set task as ready and run this task.
 * must be use inside the kernel !
 */
extern void kernelSetTaskAsReady(KThread * thread );

/** @brief Same as previous, but inside an interrupt.
 */
extern void irqSetTaskAsReady(KThread * thread);

/** @brief Set task as ready and execute immediately this task.
 *
 * @warning the thread must be in the wait list !
 *
 * @warning don't use inside the kernel or an interrupt !
 *
 * @param thread        A thread.
 */
extern void setTaskAsReady(KThread * thread);

/** @brief Set the current task as waiting and schedule a new task immediately.
 */
extern void setTaskAsWaiting(void);

/** @brief Set the current task as blocked and schedule a new task immediately.
 */
extern void setTaskAsBlocked(void);

extern void initKAlarm(void);
extern void manageKTimer(void);


extern KList tasksWaiting;
extern KList tasksBlocked;
extern volatile KThread * currentTask;


#endif
