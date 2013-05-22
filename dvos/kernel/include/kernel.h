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
#ifndef DVOS_KERNEL_H
#define DVOS_KERNEL_H

/** @brief Initialize kernel object.
 */
extern void initKernel(void);

/** @brief Start the kernel.
 */
extern void startKernel(void);

/** @brief Get time of kernel.
 *
 * @return Number of tick from the beginning.
 */
extern UInt32 getCurrentTimeOfKernel(void);



#ifdef KERNEL_USE_DEBUG
        extern void dumpKernel(void);
#else
#       define dumpKernel()
#endif



#endif
