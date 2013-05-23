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
#ifndef LIB_HW_TIMER_H
#define LIB_HW_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif


typedef enum _timer_
{
    TIMER0 = 0,
    TIMER1 = 1,
    TIMER2 = 2,
    TIMER3 = 3
} TIMER;


typedef void (*TimerIrqCallback)(void);

extern void setTimer0Callback(TimerIrqCallback c);
extern void setTimer1Callback(TimerIrqCallback c);


extern void initTimer32(TIMER timerSelected, UInt32 waitInUs);
extern void setTimer32(TIMER timerSelected, UInt32 waitInUs);
extern void enableTimer32(TIMER timerSelected, Bool enable);

// only on lpc17xx
extern void waitTimer32(TIMER timerSelected);


extern void waitUsPrecise(UInt32 waitInUs);

// on lpc17xx, McuClock uses the RIT
// on lpc13xx : McuClock uses the 32 bits TIMER1 !
extern void initMcuClock(void);
extern UInt32 getMcuClock(void);


#ifdef __cplusplus
 }
#endif

#endif