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
#include "i2c-master-common.h"

void initI2C0(I2C_SPEED speed)
{
    UInt32 reg;

    I2C_I2CONCLR = 0xFF;

    // how to compute i2c clock bus :
    // i2c frequency = PCLKI2C / (I2C_SCLL + I2C_SCLH)
    
    //  set pinouts as scl and sda
    LPC_PINCON->PINSEL1 |= BIT(22);
    LPC_PINCON->PINSEL1 |= BIT(24);

    // i2c frequency set to 100 MHz
    LPC_SC->PCLKSEL0 |= BITS(14,1);

    switch(speed)
    {
    case I2C_400_KHZ:
            reg = 125;
            break;
    case I2C_100_KHZ:
    default:
            reg = 500;
            break;
    }
    
    I2C_I2SCLL=reg;
    I2C_I2SCLH=reg;

    // active master mode on i2c bus
    I2C_I2CONSET = 0x40;
}
