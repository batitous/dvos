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
#ifndef LIB_HW_PWM_H
#define LIB_HW_PWM_H

#ifdef __cplusplus
extern "C" {
#endif


typedef enum _pwm_
{
#ifdef MCU_IS_LPC13XX
        PWM0 = 0x01,        /**< PWM output 0 */
        PWM1 = 0x02,        /**< PWM output 1 */
        PWM2 = 0x04         /**< PWM output 2 */
#endif

#ifdef MCU_IS_LPC17XX
        PWM1 = 0x01,
        PWM2 = 0x02,
        PWM3 = 0x04,
        PWM4 = 0x08,
        PWM5 = 0x10,
        PWM6 = 0x20
#endif
} PWM;


typedef enum _timertype_
{
    TIMER32 = 0,
    TIMER16 = 1
} PWMTIMER;

/** Warning on lpc13xx only !
 * 
 * TIMER0 PWM0 is on uart0
 * TIMER0 PWM1 is on uart0
 *   
 * TIMER1 PWM0 is on analog2
 * TIMER1 PWM1 is on analog3
 * TIMER1 PWM2 is on analog4
 * 
 */


#ifdef MCU_IS_LPC13XX
/** @brief Init PWM driver.
 * 
 * @param timerSelelected       Select a timer for the PWM.
 * @param pwmSelected           Select an PWM output (or multiple PWM output).
 * @param widthInUs             PWM period in us.
 * @param widthDivider          Constant to divide your period (to lower PWM frequency)
 * @param percentage            Duty cycle.
 */
extern void initPwm(PWMTIMER timerType, TIMER timerSelected, PWM pwmSelected, UInt32 widthInUs, UInt32 widthDivider, UInt32 percentage);
        
/** @brief Set PWM duty cycle.
 * 
 * @param timerSelected         Select the timer to be used for the PWM.
 * @param pwmSelected           Select the PWM you want set the duty cycle.
 * @param percentage            Set duty cycle.
 */
extern void setPwmDutyCycle(PWMTIMER timerType, TIMER timerSelected, PWM pwmSelected, UInt32 percentage);

extern void setPwmWidth(PWMTIMER timerType, TIMER timerSelected, UInt32 widthInUs);


/** @brief Enable or Disable PWM.
 * 
 * @param timerSelected
 * @param start         True to enalbe, False to disable.
 */
extern void enablePwm(PWMTIMER timerType, TIMER timerSelected, Bool start);

#endif

#ifdef MCU_IS_LPC17XX

extern void initPwm(PWM pwmSelected, UInt32 widthInUs, UInt32 percentage);
      
extern void enablePwm(Bool start);

extern void setPwmDutyCycle(PWM pwmSelected, UInt32 percentage);

extern void setPwmWidth(UInt32 widthInUs);

#endif
        



#ifdef __cplusplus
 }
#endif

#endif