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
#ifndef LIB_HW_GPIO_H
#define LIB_HW_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "gpio-pins.h"
    
/** @brief GPIO Port */
typedef enum _GPIO_PORT_
{
        GPIO_PORT0=0x00000,     /**< gpio port 0 */
        GPIO_PORT1=0x10000,     /**< gpio port 1 */
        GPIO_PORT2=0x20000,     /**< gpio port 2 */
        GPIO_PORT3=0x40000,     /**< gpio port 3 */
#ifdef MCU_IS_LPC17XX
        GPIO_PORT4=0x80000      /**< gpio port 4 */
#endif
} GPIO_PORT;

/** @brief GPIO Edge sense */
typedef enum _GPIO_EDGE_
{
    GPIO_NO_EDGE        = 0x000000,
    GPIO_FALLING_EDGE   = 0x100000,     /**< fall */
    GPIO_RISING_EDGE    = 0x200000,     /**< rise */
#ifdef MCU_IS_LPC13XX
    GPIO_BOTH_EDGE      = 0x400000      /**< fall and rise */
#endif
} GPIO_EDGE;

/** @brief Mask on GPIO Pin and Port */
#define GPIO_MASK       0x0FFFFF

/** @brief Mask on GPIO Edge */
#define GPIO_EDGE_MASK  0xF00000


/** @brief GPIO direction */
typedef enum _GPIO_DIR_
{
    GPIO_IN  = 0,        /**< Digital pin is an Input */
    GPIO_OUT = 1         /**< Digital pin is an Output */
} GPIO_DIR ;

    
/** @brief Set GPIO direction
 * 
 * @param pin   GPIO to set
 * @param dir   Direction of the pin
 */
extern void SetGpioDirection(GPIO_PIN pin, GPIO_DIR dir);

/** @brief Set value of GPIO (0 or 1)
 *
 * @param pin   GPIO to set
 * @param bit   value
 */
extern void SetGpioValue(GPIO_PIN pin, UInt32 bit);

/** @brief Get value of a GPIO
 *
 * @param pin   GPIO to get
 * @return Value of the pin (0 or 1)
 */
extern UInt32 GetGpioValue(GPIO_PIN pin);


// TODO works only for lpc13xx
extern void EnableGpioHysteresis(GPIO_PIN pin);

/** @brief Enable an Kernel event on a GPIO pin
 *
 * @param pin           Pin
 * @param edge          Falling or Rising edge (only lpc13xx can have both on the same event!)
 * @param callback      event callback
 * @return
 */
extern void EnableEventOnGpio(GPIO_PIN pin, GPIO_EDGE edge, KEventCallback callback);


/** @brief IRQ callback type */
typedef void (*GpioIrqCallback)(UInt32 gpioEvent, UInt32 gpioEdge);


// set the gpio irq callback
extern void SetGpioIrqCallback(GpioIrqCallback callback);


// enable irq "by the hand"
// Use this in 2 cases:
// - you have previously disable irq
// - you want manage your own irq without event, you have to set your own gpio irq callback !
extern void EnableGpioIrq(GPIO_PIN pin, GPIO_EDGE edge);


// disable only the irq, the event object is not deactivated !

#ifdef MCU_IS_LPC13XX
extern void DisableGpioIrq(GPIO_PIN pin);
#endif

#ifdef MCU_IS_LPC17XX
extern void DisableGpioIrq(GPIO_PIN pin, GPIO_EDGE edge);
#endif 

#ifdef __cplusplus
 }
#endif

#endif
