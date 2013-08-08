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

#ifdef MCU_IS_LPC13XX
#       define I2C_I2CONSET    LPC_I2C->CONSET
#       define I2C_I2CONCLR    LPC_I2C->CONCLR
#       define I2C_I2STAT      LPC_I2C->STAT
#       define I2C_I2DAT       LPC_I2C->DAT
#       define I2C_I2SCLL      LPC_I2C->SCLL
#       define I2C_I2SCLH      LPC_I2C->SCLH
#endif

#ifdef MCU_IS_LPC17XX
#       define I2C_I2CONSET    LPC_I2C0->I2CONSET
#       define I2C_I2CONCLR    LPC_I2C0->I2CONCLR
#       define I2C_I2STAT      LPC_I2C0->I2STAT
#       define I2C_I2DAT       LPC_I2C0->I2DAT
#       define I2C_I2SCLL      LPC_I2C0->I2SCLL
#       define I2C_I2SCLH      LPC_I2C0->I2SCLH
#endif
