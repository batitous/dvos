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

// MATH_PI = 3.141592653589793 * 256
#define MATH_PI         804


Int16 GetDegreeFromRadian(IntQ15 radian)
{
    Int32 tmp = radian * 180 * 32768;
    
    tmp = tmp / (MATH_PI * 256);
    
    return tmp;
}

IntQ15 GetRadianFromDegree(Int16 degree)
{
    Int32 tmp = degree * 32768 * MATH_PI;
    
    tmp = tmp / (180*256);
    
    return tmp;
}

RadianQ15 getRadianQ15FromDegree(Int16 degree)
{
    Int32 tmp = degree * 32768;
    return tmp / 360;
}
