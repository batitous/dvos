
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
extern void InitUserFlash(UInt32 sectorStart, UInt32 sectorEnd);


extern UInt32 GetUserFlashSize(void);

/** @brief Get a pointer on the beginning of the user flash 
 *
 * Warning, you can't write to this pointer !
 * 
 * @return A pointer.
 */
extern UInt8 * GetUserFlashBuffer(void);


extern Bool EraseAllUserFlashSector(void);


/** @brief Erase a complete sector of flash.
 * @param flashAddr    Address of the flash sector
 * @return False if error.
 */
extern Bool EraseFlashSector(UInt32 flashAddr);

/** @brief Write a buffer into the flash.
 *
 * The buffer is written only if you send 256 bytes !
 * 
 * @param flashAddr     Address of the flash sector where write the buffer
 * @param src           Buffer to write
 * @param size          Size of buffer.
 * @param False if error.
 */
extern Bool WriteBufferToFlash(UInt32 * flashAddr, UInt8 * src, UInt32 size);



#ifdef __cplusplus
}
#endif

#endif