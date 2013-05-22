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
#ifndef LIBS_HW_DEFAULT_H
#define LIBS_HW_DEFAULT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"
#include "core/bit-band.h"
    
#ifdef MCU_IS_LPC17XX
#include "mcu/lpc17xx.h"
#endif
    
#ifdef MCU_IS_LPC13XX
#include "mcu/lpc13xx.h"
#endif
    
    
#include "libc.h"
#include "math.h"
#include "utils.h"
#include "drivers/sleep.h"

#ifdef __cplusplus
 }
#endif

#endif
