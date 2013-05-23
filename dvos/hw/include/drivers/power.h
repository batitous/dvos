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
#ifndef LIB_HW_POWER_H
#define LIB_HW_POWER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _power_driver_
{
    POWER_UART0 = 3,
    POWER_PWM   = 6,
    POWER_I2C0  = 7,
    POWER_SPI   = 8,
    POWER_RTC   = 9,
    POWER_SSP1  = 10,
    POWER_ADC   = 12,
    POWER_I2C1  = 19,
    POWER_SSP0  = 21,
    POWER_I2C2  = 26,
    POWER_USB   = 31
}POWERDRIVER;


extern void setPowerSupply(POWERDRIVER driver, Bool enable);


#ifdef __cplusplus
 }
#endif

#endif

