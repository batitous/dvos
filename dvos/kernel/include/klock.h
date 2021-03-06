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
