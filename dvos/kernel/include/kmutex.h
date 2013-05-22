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
