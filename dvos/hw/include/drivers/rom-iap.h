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
#ifndef LIB_HW_ROM_IAP_H
#define LIB_HW_ROM_IAP_H

#ifdef __cplusplus
extern "C" {
#endif

    
// Function to execute the ROM IAP code of NXP to access flash and eeprom
    

#define IAP_CCLK        KERNEL_CPU_FREQ


typedef enum _iapCommandCode_
{
        IAP_PREPARE_SECTOR_FOR_WRITE	=50,
        IAP_COPY_RAM_TO_FLASH		=51,
        IAP_ERASE_SECTOR		=52,
        IAP_BLANK_CHECK_SECTOR		=53,
        IAP_READ_PART_ID		=54,
        IAP_READ_BOOT_VER		=55,
        IAP_COMPARE			=56,
        IAP_REINVOKE_ISP		=57,
        IAP_WRITE_EEPROM                =61,
        IAP_READ_EEPROM                 =62
} iapCommandCode;


#define IAP_SUCCESS 0
#define IAP_ADDRESS 0x1FFF1FF1


extern void iapExecute(UInt32 *param_tab,UInt32 *result_tab);


// low level flash functions for baptiste
extern Bool iapPrepareSector(UInt32 start_sector,UInt32 end_sector);
extern Bool iapWriteBuffer(UInt32 flash_address, UInt32 * buffer, UInt32 count);
extern Bool iapEraseSector(UInt32 start_sector,UInt32 end_sector);
extern void iapReinvokeBootloader(void);


#ifdef __cplusplus
 }
#endif

#endif
