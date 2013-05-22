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
