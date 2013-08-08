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
#include "../include/libs-hardware.h"

#define EEPROM_SIZE		    65536
#define PAGE_SIZE		    128

#define E2P_I2C_ADDR        0xA0

extern void i2c_soft_start(void);
extern void i2c_soft_stop(void);
extern UInt8 i2c_soft_send_byte(UInt8 data);

Bool private_e2p_writebyte(UInt32 addr, UInt8 dat, UInt32 size)
{
    UInt8 buffer[3];

    if(addr >= size)
    {
        return False;
    }

    buffer[0] = addr>>8;
    buffer[1] = addr;
    buffer[2] = dat;
    sendBufferToI2CSoft(E2P_I2C_ADDR,buffer,3);

    return True;
}

Bool writeByteToEeprom(UInt32 addr, UInt8 dat)
{
    return private_e2p_writebyte(addr,dat,EEPROM_SIZE);
}


Bool private_e2p_readbyte(UInt32 addr, UInt8 *dat, UInt32 size)
{
    UInt8 buffer[2];

    if(addr >= size)
    {

        return False;
    }

    buffer[0] = addr>>8;
    buffer[1] = addr;
    sendBufferToI2CSoft(E2P_I2C_ADDR,buffer,2);

    getBufferFromI2CSoft(E2P_I2C_ADDR,dat,1);

    return True;
}

Bool readByteFromEeprom(UInt32 addr, UInt8* dat)
{
    return private_e2p_readbyte(addr,dat,EEPROM_SIZE);
}


Bool private_e2p_readbuffer(Int32 addr, Int32 size, UInt8 *buffer, Int32 totalSize)
{
    if((addr+size) >= totalSize)
    {
        return False;
    }

    buffer[0] = addr>>8;
    buffer[1] = addr;
    sendBufferToI2CSoft(E2P_I2C_ADDR,buffer,2);

    getBufferFromI2CSoft(E2P_I2C_ADDR,buffer,size);

    return True;
}

Bool readBufferFromEeprom(UInt32 addr, UInt8* buffer, UInt32 size)
{
    return private_e2p_readbuffer(addr,size,buffer,EEPROM_SIZE);
}


Bool private_e2p_writebuffer(UInt32 addr, UInt32 size, UInt8 *buffer, UInt32 totalSize)
{
    UInt32 j=0;
    Int32 remain = size;
    UInt32 r = 0;
    Int32 count = 0;


    if((addr+size) >= totalSize)
    {
        return False;
    }


    while( remain > 0 )
    {
        i2c_soft_start();
        i2c_soft_send_byte(E2P_I2C_ADDR);
        i2c_soft_send_byte(addr>>8);
        i2c_soft_send_byte(addr);


        if(remain >= PAGE_SIZE)
        {
            for(j=0;j<PAGE_SIZE;j++)
            {
                i2c_soft_send_byte(buffer[count]);
                count++;
                remain--;
            }
        }
        else
        {
            r = remain;
            for(j=0;j<r;j++)
            {
                i2c_soft_send_byte(buffer[count]);
                count++;
                remain--;
            }
        }

        i2c_soft_stop();

        waitUs(5000);

        addr+=PAGE_SIZE;
    }

    return True;
}

Bool writeBufferToEeprom(UInt32 addr, UInt8* buffer, UInt32 size)
{
    return private_e2p_writebuffer(addr,size,buffer,EEPROM_SIZE);
}


Bool private_e2p_erase( UInt32 addr, UInt32 totalSize)
{
    UInt32 i=0, j=0;

    for(i=0;i<totalSize;i++)
    {
        i2c_soft_start();
        i2c_soft_send_byte(E2P_I2C_ADDR);
        i2c_soft_send_byte(addr>>8);
        i2c_soft_send_byte(addr);
        for(j=0;j<PAGE_SIZE;j++)
        {
                i2c_soft_send_byte(0x00);
        }
        i2c_soft_stop();
        addr+=PAGE_SIZE;
    }

	return True;
}

Bool eraseEeprom()
{
    return private_e2p_erase(0,(EEPROM_SIZE/PAGE_SIZE));
}


