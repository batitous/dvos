
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
