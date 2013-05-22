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
#ifndef LIB_HW_I2C_H
#define LIB_HW_I2C_H

#ifdef __cplusplus
extern "C" {
#endif


typedef enum _i2c_speed
{
    I2C_100_KHZ=0,		/**< I2C speed frequency 100 KHz */
    I2C_400_KHZ=1		/**< I2C speed frequency 400 KHz */
} I2C_SPEED;


#define I2C_OK          0   /**< Last operation on i2c bus is OK. */
#define I2C_ERROR       1   /**< Error on i2c bus. */
#define I2C_ERROR_START 2   /**< Error when send START bit on i2c bus. */
#define I2C_ERROR_SEND  3   /**< Error when send data on i2c bus. */
#define I2C_BUSY        4   /**< i2c bus is busy. */
#define I2C_EMPTY       5   /**< i2c buffer is empty. */
#define I2C_TIMEOUT     6   /**< Operation timeout on i2c bus */


extern void InitI2C0(I2C_SPEED speed);

extern UInt32 SendBufferToI2C0(UInt8 addr, UInt8 *buffer, UInt32 len);

extern UInt32 GetBufferFromI2C0(UInt8 addr, UInt8 *buffer, UInt32 len);

extern void InitI2C1(I2C_SPEED speed);

extern UInt32 SendBufferToI2C1(UInt8 addr, UInt8 *buffer, UInt32 len);

extern UInt32 GetBufferFromI2C1(UInt8 addr, UInt8 *buffer, UInt32 len);

extern void InitSlaveI2C0(UInt8 address, I2C_SPEED speed);

extern void ReInitSlaveI2C0(UInt8 address, I2C_SPEED speed);

extern UInt32 GetBufferFromMasterI2C0(UInt8 *buffer, UInt32 len);

extern void SetBufferToMasterI2C0(UInt8 *buffer, UInt8 size);

extern void HaltSlaveI2C0(void);

#ifdef __cplusplus
}
#endif

#endif
