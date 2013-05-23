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
#include "../include/libs-hardware.h"

// code comes from nxp application notes


#define FLASH_SECTOR_0_START      0x00000000
#define FLASH_SECTOR_1_START      0x00001000
#define FLASH_SECTOR_2_START      0x00002000
#define FLASH_SECTOR_3_START      0x00003000
#define FLASH_SECTOR_4_START      0x00004000
#define FLASH_SECTOR_5_START      0x00005000
#define FLASH_SECTOR_6_START      0x00006000
#define FLASH_SECTOR_7_START      0x00007000
#define FLASH_SECTOR_8_START      0x00008000
#define FLASH_SECTOR_9_START      0x00009000
#define FLASH_SECTOR_10_START     0x0000A000
#define FLASH_SECTOR_11_START     0x0000B000
#define FLASH_SECTOR_12_START     0x0000C000
#define FLASH_SECTOR_13_START     0x0000D000
#define FLASH_SECTOR_14_START     0x0000E000
#define FLASH_SECTOR_15_START     0x0000F000
#define FLASH_SECTOR_16_START     0x00010000
#define FLASH_SECTOR_17_START     0x00018000
#define FLASH_SECTOR_18_START     0x00020000
#define FLASH_SECTOR_19_START     0x00028000
#define FLASH_SECTOR_20_START     0x00030000
#define FLASH_SECTOR_21_START     0x00038000
#define FLASH_SECTOR_22_START     0x00040000
#define FLASH_SECTOR_23_START     0x00048000
#define FLASH_SECTOR_24_START     0x00050000
#define FLASH_SECTOR_25_START     0x00058000
#define FLASH_SECTOR_26_START     0x00060000
#define FLASH_SECTOR_27_START     0x00068000
#define FLASH_SECTOR_28_START     0x00070000
#define FLASH_SECTOR_29_START     0x00078000

/* Define end address of each Flash sector */
#define SECTOR_0_END        0x00000FFF
#define SECTOR_1_END        0x00001FFF
#define SECTOR_2_END        0x00002FFF
#define SECTOR_3_END        0x00003FFF
#define SECTOR_4_END        0x00004FFF
#define SECTOR_5_END        0x00005FFF
#define SECTOR_6_END        0x00006FFF
#define SECTOR_7_END        0x00007FFF
#define SECTOR_8_END        0x00008FFF
#define SECTOR_9_END        0x00009FFF
#define SECTOR_10_END       0x0000AFFF
#define SECTOR_11_END       0x0000BFFF
#define SECTOR_12_END       0x0000CFFF
#define SECTOR_13_END       0x0000DFFF
#define SECTOR_14_END       0x0000EFFF
#define SECTOR_15_END       0x0000FFFF
#define SECTOR_16_END       0x00017FFF
#define SECTOR_17_END       0x0001FFFF
#define SECTOR_18_END       0x00027FFF
#define SECTOR_19_END       0x0002FFFF
#define SECTOR_20_END       0x00037FFF
#define SECTOR_21_END       0x0003FFFF
#define SECTOR_22_END       0x00047FFF
#define SECTOR_23_END       0x0004FFFF
#define SECTOR_24_END       0x00057FFF
#define SECTOR_25_END       0x0005FFFF
#define SECTOR_26_END       0x00067FFF
#define SECTOR_27_END       0x0006FFFF
#define SECTOR_28_END       0x00077FFF
#define SECTOR_29_END       0x0007FFFF

// sector 0 to 15: 4K
// sector 16 to 29: 32K

// 512K of flash : 30 (SECTOR_29_END)
// 256K of flash : 22 (SECTOR_21_END)
// 128K of flash : 18 (SECTOR_17_END)


#define MAX_FLASH_SECTOR 30

const UInt32 sector_start_map[MAX_FLASH_SECTOR] = {FLASH_SECTOR_0_START,             \
FLASH_SECTOR_1_START,FLASH_SECTOR_2_START,FLASH_SECTOR_3_START,FLASH_SECTOR_4_START,FLASH_SECTOR_5_START,      \
FLASH_SECTOR_6_START,FLASH_SECTOR_7_START,FLASH_SECTOR_8_START,FLASH_SECTOR_9_START,FLASH_SECTOR_10_START,     \
FLASH_SECTOR_11_START,FLASH_SECTOR_12_START,FLASH_SECTOR_13_START,FLASH_SECTOR_14_START,FLASH_SECTOR_15_START, \
FLASH_SECTOR_16_START,FLASH_SECTOR_17_START,FLASH_SECTOR_18_START,FLASH_SECTOR_19_START,FLASH_SECTOR_20_START, \
FLASH_SECTOR_21_START,FLASH_SECTOR_22_START,FLASH_SECTOR_23_START,FLASH_SECTOR_24_START,FLASH_SECTOR_25_START, \
FLASH_SECTOR_26_START,FLASH_SECTOR_27_START,FLASH_SECTOR_28_START,FLASH_SECTOR_29_START	};

const UInt32 sector_end_map[MAX_FLASH_SECTOR] = {SECTOR_0_END,SECTOR_1_END,    \
SECTOR_2_END,SECTOR_3_END,SECTOR_4_END,SECTOR_5_END,SECTOR_6_END,SECTOR_7_END,   \
SECTOR_8_END,SECTOR_9_END,SECTOR_10_END,SECTOR_11_END,SECTOR_12_END,             \
SECTOR_13_END,SECTOR_14_END,SECTOR_15_END,SECTOR_16_END,SECTOR_17_END,           \
SECTOR_18_END,SECTOR_19_END,SECTOR_20_END,SECTOR_21_END,SECTOR_22_END,           \
SECTOR_23_END,SECTOR_24_END,SECTOR_25_END,SECTOR_26_END,                         \
SECTOR_27_END,SECTOR_28_END,SECTOR_29_END };



#define FLASH_BUFFER_SIZE       256


UInt8 userFlashBuffer[FLASH_BUFFER_SIZE];

UInt32 * userFlashAddress;
UInt32 userFlashCounter;
UInt16 userFlashSector[2];


void initUserFlash(UInt32 sectorStart, UInt32 sectorEnd)
{
    userFlashAddress = 0;
    userFlashCounter = 0;
    
    userFlashSector[0] = sectorStart;
    userFlashSector[1] = sectorEnd;
}


UInt32 getUserFlashSize(void)
{
    return (sector_end_map[userFlashSector[1]] - sector_start_map[userFlashSector[0]])  +1;
}

UInt8 * getUserFlashBuffer(void)
{
    return sector_start_map[userFlashSector[0]];
}

Bool eraseAllUserFlashSector(void)
{
    if(iapPrepareSector(userFlashSector[0],userFlashSector[1])==False)
        return False;
    
    if(iapEraseSector(userFlashSector[0],userFlashSector[1])==False)
        return False;
    
    return True;
}

Bool eraseFlashSector(UInt32 flashAddr)
{
    UInt32 i;
 

    //todo disable irq
    __disable_irq();

    for(i=userFlashSector[0];i<=userFlashSector[1];i++)
    {
        if(flashAddr < sector_end_map[i])
        {
            if( flashAddr == sector_start_map[i])
            {
                // if we begins at the first address of this sector, the erase it !
                if(iapPrepareSector(i,i)==False)
                    return False;
                
                if(iapEraseSector(i,i)==False)
                    return False;
            }
            
            if(iapPrepareSector(i,i)==False)
                return False;
            
            return True;
        }
    }

    //todo enable irq
    __enable_irq();
    
    return False;
}

Bool writeBufferToFlash(UInt32 * flashAddrDestination, UInt8 * src, UInt32 size)
{
    UInt32 i;
    
    if(userFlashAddress==0)
    {
        userFlashAddress= flashAddrDestination;
    }
    
    for( i=0 ; i<size ; i++ )
    {
        userFlashBuffer[(userFlashCounter+i)] = *(src+i);
    }
    
    userFlashCounter += size;

    if( userFlashCounter == FLASH_BUFFER_SIZE)
    {
        // We have accumulated enough bytes to trigger a flash write
        if(eraseFlashSector((UInt32)userFlashAddress)==False)
        {
            return False;
        }
        
        if(iapWriteBuffer( (UInt32)userFlashAddress, (UInt32 *)userFlashBuffer, FLASH_BUFFER_SIZE)==False)
        {
            return False;
        }
    
        // Reset byte counter and flash address
        userFlashCounter = 0;
        userFlashAddress = 0;
    }

    return True;
}
