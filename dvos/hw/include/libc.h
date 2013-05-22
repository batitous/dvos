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
#ifndef LIBS_HW_LIBC_H
#define LIBS_HW_LIBC_H

#ifdef __cplusplus
extern "C" {
#endif

// libc function


extern void * memcpy(void *pDestination, const void *pSource, UInt32 size);

extern void * memset(void *pBuffer, int value, UInt32 size);

extern Int32 memcmp(const void *pBuffer1, const void *pBuffer2, UInt32 size);

extern UInt32 strlen(const Int8 *string);


/* Return 0 if equals
 *  Return >0 if 1st string > 2nd string
 *  Return <0 if 1st string < 2nd string
 */
extern Int32 strncmp(const Int8 *pString1, const Int8 *pString2, UInt32 count);

extern Int32 strcmp(const Int8 *pString1, const Int8 *pString2);


/* 
 * Copy 'count' byte of pSource into pDestination
 */
extern Int8 * strncpy(Int8 *pDestination, const Int8 *pSource, UInt32 count);

extern Int8 * strcpy(Int8 *pDestination, const Int8 *pSource);


extern signed int sprintf(char *pStr, const char *pFormat, ...);


#ifdef __cplusplus
 }
#endif

#endif