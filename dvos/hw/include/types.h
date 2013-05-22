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
#ifndef LIBS_HW_TYPES_H
#define LIBS_HW_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*@{*/
typedef enum _Bool_
{
    False = 0,
    True = 1
} Bool;

typedef unsigned char   UInt8 ;
typedef unsigned short  UInt16 ;
typedef unsigned int    UInt32 ;

typedef char            Int8 ;
typedef short           Int16 ;
typedef int             Int32 ;
/*@}*/


#ifdef __cplusplus
 }
#endif

#endif
