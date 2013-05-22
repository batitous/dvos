
#ifndef LIB_HW_EEPROM_H
#define LIB_HW_EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif

/** /!\ WARNING top 64 bytes of LPC1315's eeprom are reserved !
 * 
 * 
 */

extern Bool WriteByteToEeprom(UInt32 addr, UInt8 dat);


extern Bool WriteBufferToEeprom(UInt32 addr, UInt8* buffer, UInt32 size);


extern Bool ReadByteFromEeprom(UInt32 addr, UInt8* dat);


extern Bool ReadBufferFromEeprom(UInt32 addr, UInt8* buffer, UInt32 size);


extern Bool EraseEeprom(void);



#ifdef __cplusplus
 }
#endif

#endif
