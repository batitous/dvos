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
#include <kernel-dvos.h>
#include <libs-hardware.h>

#define SST25_CHIP_SELECT       GPIO0_21
#define SST25_RESET             GPIO0_22

#define HalSST25Select()        setGpioValue(SST25_CHIP_SELECT,0)
#define HalSST25Unselect()      setGpioValue(SST25_CHIP_SELECT,1)

#define HalSST25SendByte(b)     sendByteToSPI(b)
#define HalSST25RcvByte()       sendByteToSPI(0)



void SST25Init(void)
{
    // set reset gpio
    setGpioDirection(SST25_RESET,GPIO_OUT);
    
    // set chip select gpio
    setGpioDirection(SST25_CHIP_SELECT,GPIO_OUT);
    
    
    // flash reset : enable device
    setGpioValue(SST25_RESET,1);
    
    // deselect flash chip
    HalSST25Unselect();
}

void SST25Erase(void)
{						
    HalSST25Select();
    HalSST25SendByte(0x60);
    HalSST25Unselect();
}

UInt8 SST25ReadStatus(void)
{
    unsigned char byte = 0;
    
    HalSST25Select();
    HalSST25SendByte(0x05);
    byte = HalSST25RcvByte();
    HalSST25Unselect();
    
    return byte;
}

Bool SST25IsBusy(void)
{
    if ( (SST25ReadStatus() & 0x1)==0 )
    {
        return False;
    }
    
    return True;
}

void SST25DisableWriteProtection(void)
{
    HalSST25Select();
    HalSST25SendByte(0x50);
    HalSST25Unselect();

    HalSST25Select();
    HalSST25SendByte(0x01);
    HalSST25SendByte(0x00);
    HalSST25Unselect();
}

void SST25EnableWrite(void)
{
    HalSST25Select();
    // WREN command
    HalSST25SendByte(0x06);
    HalSST25Unselect();
}

void SST25DisableWrite()
{
    HalSST25Select();
    // WRDI command
    HalSST25SendByte(0x04);
    HalSST25Unselect();
}

UInt8 SST25ReadByte(UInt32 address) 
{
    unsigned char byte = 0;	

    HalSST25Select();
    
    HalSST25SendByte(0x03);
    HalSST25SendByte(((address & 0xFFFFFF) >> 16));
    HalSST25SendByte(((address & 0xFFFF) >> 8));
    HalSST25SendByte(address & 0xFF);
    byte = HalSST25RcvByte();
    
    HalSST25Unselect();

    return byte;
}

// max read : 128 bytes
void SST25ReadBuffer(UInt32 address, UInt8 * buffer, UInt32 size)
{
    UInt32 i;
    
    HalSST25Select();
    
    HalSST25SendByte(0x03);
    HalSST25SendByte(((address & 0xFFFFFF) >> 16));
    HalSST25SendByte(((address & 0xFFFF) >> 8));
    HalSST25SendByte(address & 0xFF);
    
    for (i=0; i<size; i++)
    {
            buffer[i] = HalSST25RcvByte();
    }

    HalSST25Unselect();
}

// erase sector of 4K
// erase sequence : enable write / erase / check busy / disable write
void SST25EraseSector(UInt32 address)
{
    HalSST25Select();
    
    HalSST25SendByte(0x20);
    HalSST25SendByte(((address & 0xFFFFFF) >> 16));
    HalSST25SendByte(((address & 0xFFFF) >> 8));
    HalSST25SendByte(address & 0xFF);
    
    HalSST25Unselect();
}

// max write : 256 bytes
// write sequence : enable write / write / check busy / disable write
void SST25WriteBuffer(UInt32 address, UInt8 * buffer, UInt32 size)
{
    UInt32 i;

    HalSST25Select();

    HalSST25SendByte(0x02);
    HalSST25SendByte(((address & 0xFFFFFF) >> 16));
    HalSST25SendByte(((address & 0xFFFF) >> 8));
    HalSST25SendByte(address & 0xFF);

    for (i=0; i<size; i++)
    {
	HalSST25SendByte(buffer[i]);
    }
    
    HalSST25Unselect();
}



// ID_addr = 0 = Manufacturer ID 
// ID_addr = 1 = Device ID
UInt32 SST25GetID(UInt8 ID_addr)
{
    unsigned long byte = 0;

    HalSST25Select();

    HalSST25SendByte(0x90);
    HalSST25SendByte(0x00);
    HalSST25SendByte(0x00);
    HalSST25SendByte(ID_addr);

    byte = HalSST25RcvByte()<<8;
    byte = byte | HalSST25RcvByte();

    HalSST25Unselect();

    return byte;
}
