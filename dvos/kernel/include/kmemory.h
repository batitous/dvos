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
#ifndef DVOS_KERNEL_MEMORY_H
#define DVOS_KERNEL_MEMORY_H

/** @brief Memory link object */
typedef struct _kernel_link_memory_
{
    UInt16 prev;        /**< previous block of memory */
    UInt16 next;        /**< next block of memory */
} KMemory;


/** @brief
 * 
 * @param mem
 * @param sizeInByte            Maximum value: 131068 bytes (127Kbytes)
 * @return 
 */
extern KMemory * initKernelMemory(const UInt8 * mem, UInt32 sizeInByte);

extern UInt32 getMemoryAvailable(KMemory * mem);

extern void * allocMemory(KMemory * mem, UInt32 sizeInBytes);

extern void freeMemory(KMemory * mem, UInt8 * ptr);



/** @brief Default memory object. */
extern KMemory * defaultMemory;

/** @brief Malloc */
#define malloc(size)     allocMemory(defaultMemory,size)
/** @brief Free */
#define free(ptr)       freeMemory(defaultMemory,ptr)


#endif

