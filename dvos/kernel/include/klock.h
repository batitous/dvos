
#ifndef DVOS_KERNEL_LOCK_H
#define DVOS_KERNEL_LOCK_H



/** @brief Try to lock a ressource (and lock it if success).
 *
 * If True is returned, then you get the ressource and you MUST unlock after using it!
 *
 * @param ressources        Pointer to a ressource (integer).
 * @return False if try failed, else True.
 */
extern Bool trylock(UInt32 * ressource);


/** @brief Unlock a ressource.
 *
 * @param ressources        Pointer to a locked ressources.
 */
extern void unlock(UInt32 * ressource);


#endif
