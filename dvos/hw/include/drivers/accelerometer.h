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
#ifndef LIB_HW_ACCELEROMETER_H
#define LIB_HW_ACCELEROMETER_H

#ifdef __cplusplus
extern "C" {
#endif
    
/** @brief Orientation of the devices where accelerometer is connected. */
typedef enum _accel_orientation_
{
    ORIENTATION_UNKNOWN = 0x00, /**< ? */
    ORIENTATION_LEFT    = 0x01,
    ORIENTATION_RIGHT   = 0x02,
    ORIENTATION_DOWN    = 0x04,
    ORIENTATION_UP      = 0x80,
    ORIENTATION_FRONT   = 0x10,
    ORIENTATION_BACK    = 0x20
} AccelOrientation;
    

// il faut voir ce truc comme un cube
// et les infos nous donne l'orientation du cube

/** @brief Acceleration information */
typedef struct _accel_info_
{
    AccelOrientation orientation;
    AccelOrientation backOrFront;
    Bool shake; /**< Shake detected or not ? Shake is defined as an acceleration on any axis that is greater than +/- 1.3g */
    Bool tap;   /**< tap detected or not ? */
} AccelerationInfo;


/** @brief Accelerometer values in milli g. */
typedef struct _accel_raw_
{
    Int16 x;
    Int16 y;
    Int16 z;
} AccelerationRawValue;

/** @brief Angle of  the devices */
/*typedef struct _accel_angle_
{
    Int16 x;
    Int16 y;
    Int16 z;
} AccelerationAngle;
*/

/** @brief Accelerometer configuration */
typedef enum _accel_detect_
{
    ACCELEROMETER_CONFIG_DEFAULT        = 0,    /**< Default configuration */
    ACCELEROMETER_CONFIG_DETECT_TAP     = 1,    /**< Set accelerometer to detect tap */        
} AccelerometerConfig;

/** initialize the accelerometer.
 * 
 * Accelerometer can have 2 configurations: the default and the tap detection configuration.
 * 
 * @param config                Accelerometer configuration.
 * @param tapCount              Number of tap to detect.
 * @param tapSensibility        Sensibility of tap detection.
 */
extern void InitAccelerometer(AccelerometerConfig config, UInt8 tapCount, UInt8 tapSensibility);

/** Get accelerometer values.
 * 
 * @param info          Information about acceleration
 * @param value         Raw values in milli g of acceleration
 * @param gBound        True to set g value between -1g and +1g
 * @return False if no new values available.
 */
extern Bool GetAccelerometer(AccelerationInfo * info, AccelerationRawValue * value, Bool gBound);

    
#ifdef __cplusplus
 }
#endif

#endif
