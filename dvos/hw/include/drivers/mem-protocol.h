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
#ifndef LIB_HW_MEM_PROTOCOL_H
#define LIB_HW_MEM_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

    
typedef void (*MemProtocolSendCallback)(UInt16 address, UInt8 *ptr, UInt32 size);


typedef void (*MemProtocolUpdateCallback)(void);


typedef struct _mem_modules_
{
	UInt16                    id;     /**< Module identifier. */
	UInt16                    size;   /**< Size of memory. */
	UInt8 *                   ptr;	  /**< Pointer to memory. */
	MemProtocolUpdateCallback update; /**< Code for update memory. */
} MemoryModule;


/** @brief Initialize memory module
 *
 * @param number        Number of modules.
 * @param func          Pointer to a function.
 */
extern void InitMemoryModule(UInt32 number, MemProtocolSendCallback func);


/** @brief Add a module to the memory protocol.
 * 
 * @param virtualAddr   Virtual address of your object.
 * @param objectAddr    Address of your object.
 * @param objectSize    Size of your object.
 * @param update        Pointer to function for update your object.
 */
extern void AddMemoryModule(UInt16 virtualAddr, UInt8 * objectAddr, UInt32 objectSize, MemProtocolUpdateCallback update);


/** @brief Get a module from an address 
 *
 * @param address       Virtual address of the module
 * @return Pointer to a valid memory module or 0 if error.
 */
extern MemoryModule * GetMemoryModuleFromAddress(UInt16 address);


/** @brief Update the memory module.
 * 
 *  memory protocol:
 * 
 * buffer[0] low bits of address
 * buffer[1] high bits of address
 * 
 * if size > 2, then write order: buffer[3] to buffer[size-2] copyied to address
 * else, read order. 
 * 
 * @param buffer        Pointer to a buffer that contains memory data.
 * @param size          Size of buffer.
 */
extern void UpdateMemoryModule(UInt8 *buffer, UInt8 size);


    
#ifdef __cplusplus
 }
#endif

#endif
