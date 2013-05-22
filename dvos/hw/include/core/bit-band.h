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
#ifndef LIBS_HW_BIT_BAND_H
#define LIBS_HW_BIT_BAND_H

#ifdef __cplusplus
extern "C" {
#endif


//take from lpc datasheet: ARM appendix


#define GET_BITBAND( addr , bitnum )  (( (addr) & 0xF0000000 ) + 0x2000000+ (((addr) & 0xFFFFF) << 5) +(bitnum <<2) )


// convert an device address into a bit-band device address
// for an example, see driver/uart.c

// get bit value from an address
#define BITBAND( addr, bitnum )     *((volatile unsigned long *)(GET_BITBAND(addr,bitnum)))


#ifdef __cplusplus
 }
#endif

#endif
