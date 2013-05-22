
#ifndef DVOS_KERNEL_MUTEX_H
#define DVOS_KERNEL_MUTEX_H

/** @brief Mutex Object.
 */
typedef struct _kmutex_
{
    UInt32      lock;       /**< internal lock */
    KThread *   blocked;    /**< thread blocked on this mutex */
} KMutex;

/** @brief Create a new mutex object.
 *
 * @return A new KMutex object, or 0 if error.
 */
extern KMutex * newMutex(void);

/** @brief Lock a mutex.
 *
 * @param mutex     A pointer to a mutex object.
 */
extern void lockMutex(KMutex * mutex);

/** @brief Unlock a mutex.
 *
 * @param mutex     A pointer to a mutex object.
 */
extern void unlockMutex(KMutex * mutex);


#endif
