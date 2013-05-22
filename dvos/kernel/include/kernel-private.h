
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
