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
#include "../../hw/include/libs-default.h"

/* datasheet arm r2p1 page 8-4
#define CPU_RESET_CYCLECOUNTER    do { SCB_DEMCR = SCB_DEMCR | 0x01000000;  \
                                       DWT_CYCCNT = 0;                      \
                                       DWT_CTRL = DWT_CTRL | 1 ; } while(0)

int offset, cycles;
 
 http://www.microbuilder.eu/Projects/LPC1343ReferenceDesign/DWTBenchmarking.aspx

CPU_RESET_CYCLECOUNTER;
__asm volatile("nop");
cycles = DWT_CYCCNT;
offset = cycles - 1;

// Display the results
printf("1x nop = %d Cycles\r\n", cycles);
printf("DWT Cycle Counter offset set to %d\r\n", offset);*/