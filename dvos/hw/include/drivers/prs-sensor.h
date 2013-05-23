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
#ifndef LIB_HW_PRS_SENSOR_H
#define LIB_HW_PRS_SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Sensor type enumeration.
 */
typedef enum _sensor_type_
{
    SENSOR_UNKNOWN              = 0,    /**< [0] Unknown or no device found */
    SENSOR_ANA_IN               = 1,    /**< [1] An analog input */
    SENSOR_ANA_DIG_IN           = 2,    /**< [2] An analog input and a digital input */
    SENSOR_DIG_IN               = 3,    /**< [3] A digital input */
    SENSOR_DIG_OUT              = 4,    /**< [4] A digital output */

    SENSOR_I2C                  = 10,   /**< [10] An Unknown I2C device */

    SENSOR_I2C_LINESENSOR_SHARP = 11,   /**< [11] Line Follower */
    SENSOR_I2C_RGBLED           = 12,   /**< [12] Red Green Blue Led device */
    SENSOR_I2C_24LED            = 13,   /**< [13] 24 LED Display */
    SENSOR_I2C_MOTORDRIVER      = 14,   /**< [14] Direct Current Motor */
    SENSOR_I2C_ULTRASONIC       = 15,   /**< [15] Ultrasonic sensor */
    SENSOR_I2C_TEMPSENSOR       = 16,   /**< [16] Temperature sensor */
    SENSOR_I2C_EEPROM           = 17,   /**< [17] Eeprom memory */
    SENSOR_I2C_ACCELEROMETER    = 18,   /**< [18] Accelerometer sensor */
    SENSOR_I2C_COMPASS          = 19,   /**< [19] Compass */
    SENSOR_I2C_IRBEACON         = 20,   /**< [20] IR Beacon */
    SENSOR_I2C_IRDA             = 21,   /**< [21] IRDA transceiver */
    SENSOR_I2C_PORTEXPANDER     = 22,   /**< [22] Port expander */
    SENSOR_I2C_CAMERA           = 23,   /**< [23] Camera */
    SENSOR_I2C_VEXPANDER        = 24,   /**< [24] VEX port expander */
    SENSOR_I2C_MINIVEX          = 25,   /**< [25] MiniVEX port expander */
    SENSOR_I2C_IRFOLLOWER       = 26,   /**< [26] IR Follower */
    SENSOR_I2C_COMPASSACCELEROMETER = 27, /**< [27] Compass-Accelerometer */
    SENSOR_I2C_7SEGMENT         = 28    /**< [28] 4 7Segment display module */
} SensorType;


/** @brief Initialize PRS Sensor Slave communication
 *
 * @param mtype         Type of slave sensor.
 * @param pin           Input pin of slave communication.
 * @return 0 if error, else i2c address of the PRS Sensor.
 */
extern UInt8 initSensorPRS(SensorType mtype, GPIO_PIN pin);

#ifdef __cplusplus
 }
#endif

#endif