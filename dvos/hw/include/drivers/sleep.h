
#ifndef LIB_HW_SLEEP_H
#define LIB_HW_SLEEP_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _sleep_mode
{
    SLEEP_DEFAULT       = 0x01,         /**< Default sleep, wakeup from any IRQ : nothing to do */
    SLEEP_DEEP          = 0x02,         /**< Deep sleep, you have to set your own wakeup source */
    SLEEP_DEEP_POWERDOWN= 0x04          /**< Deep power down sleep, wakeup very specific, don't use this... */
}SLEEPMODE;


/** @brief Put hardware into sleep
 * 
 * @param mode          Selected sleep (SLEEP_DEEP)
 */
extern void SetMcuToSleep(SLEEPMODE mode);

/** @brief Initialize the wakeup source for the hardware 
 * 
 * DONT CALL IT DIRECTLY
 * 
 */
extern void InitWakeUp(void);


// Macro for the idle kernel thread 
// Uses a macro for reduce footprint of kernel (avoid sleep.o linking)
#ifdef MCU_IS_LPC17XX
#       define SetMcuToDefaultSleep()  LPC_SC->PCON = 0; SCB->SCR = 0; __WFI();
#endif
       
#ifdef MCU_IS_LPC13XX
#       define SetMcuToDefaultSleep()    CLRBIT(LPC_PMU->PCON,1); SETBIT(LPC_PMU->PCON,11); CLRBIT(SCB->SCR,2); __WFI();
#endif

#ifdef __cplusplus
 }
#endif

#endif