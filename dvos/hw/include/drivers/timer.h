
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

extern void SetTimer0Callback(TimerIrqCallback c);
extern void SetTimer1Callback(TimerIrqCallback c);


extern void InitTimer32(TIMER timerSelected, UInt32 waitInUs);
extern void SetTimer32(TIMER timerSelected, UInt32 waitInUs);
extern void EnableTimer32(TIMER timerSelected, Bool enable);

// only on lpc17xx
extern void WaitTimer32(TIMER timerSelected);


extern void WaitUsPrecise(UInt32 waitInUs);

// on lpc17xx, McuClock uses the RIT
// on lpc13xx : McuClock uses the 32 bits TIMER1 !
extern void InitMcuClock(void);
extern UInt32 GetMcuClock(void);


#ifdef __cplusplus
 }
#endif

#endif
