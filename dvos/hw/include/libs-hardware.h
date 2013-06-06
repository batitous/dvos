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
#ifndef LIBS_HW_H
#define LIBS_HW_H

#ifdef __cplusplus
extern "C" {
#endif


#include "libs-default.h"


#include "../../kernel/include/kernel-dvos.h"

#include "drivers/uart.h"
#include "drivers/rom-iap.h"
#include "drivers/flash.h"
#include "drivers/i2c.h"
#include "drivers/i2c-soft.h"
#include "drivers/analog.h"
#include "drivers/gpio.h"
#include "drivers/spi.h"
#include "drivers/timer.h"
#include "drivers/pwm.h"
#include "drivers/sleep.h"
#include "drivers/power.h"
#include "drivers/prs-sensor.h"
#include "drivers/compass.h"
#include "drivers/accelerometer.h"
#include "drivers/magnetometer.h"
#include "drivers/mem-protocol.h"
#include "drivers/rgbled.h"
#include "drivers/byc-board.h"
#include "drivers/eeprom.h"
#include "device.h"
    

#ifdef __cplusplus
 }
#endif

#endif
