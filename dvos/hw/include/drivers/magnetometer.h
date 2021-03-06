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
#ifndef LIB_HW_MAGNETOMETER_H
#define LIB_HW_MAGNETOMETER_H

#ifdef __cplusplus
extern "C" {
#endif
    
    
typedef struct _magnetics_raw_values_
{
    Int16       x;
    Int16       y;
    Int16       z;
    //Int32       angleNorth;
} MagneticRawValue;


extern Bool initMagnetometer(void);

extern Bool getMagneticValue(MagneticRawValue * rawvalue, MagneticRawValue * value/*, UInt8* calibratestate*/);

extern UInt8 getTemperature(void);


extern void startMagnetometerCalibration(void);

extern void stopMagnetometerCalibration(void);

#ifdef __cplusplus
 }
#endif

#endif
