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
#ifndef LIB_HW_FLASH_H
#define LIB_HW_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

    
    
    
// low level flash functions for baptiste
extern Bool iapPrepareSector(UInt32 start_sector,UInt32 end_sector);
extern Bool iapWriteBuffer(UInt32 flash_address, UInt32 * buffer, UInt32 count);
extern Bool iapEraseSector(UInt32 start_sector,UInt32 end_sector);


/** @brief Define the flash available for user for read/write.
 *
 * @param sectorStart   Start number
 * @param sectorEnd     End number
 */
extern void initUserFlash(UInt32 sectorStart, UInt32 sectorEnd);


extern UInt32 getUserFlashSize(void);

/** @brief Get a pointer on the beginning of the user flash 
 *
 * Warning, you can't write to this pointer !
 * 
 * @return A pointer.
 */
extern UInt8 * getUserFlashBuffer(void);


extern Bool eraseAllUserFlashSector(void);


/** @brief Erase a complete sector of flash.
 * @param flashAddr    Address of the flash sector
 * @return False if error.
 */
extern Bool eraseFlashSector(UInt32 flashAddr);

/** @brief Write a buffer into the flash.
 *
 * The buffer is written only if you send 256 bytes !
 * 
 * @param flashAddr     Address of the flash sector where write the buffer
 * @param src           Buffer to write
 * @param size          Size of buffer.
 * @param False if error.
 */
extern Bool writeBufferToFlash(UInt32 * flashAddr, UInt8 * src, UInt32 size);



#ifdef __cplusplus
}
#endif

#endif