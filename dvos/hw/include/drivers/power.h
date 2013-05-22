
#ifndef LIB_HW_POWER_H
#define LIB_HW_POWER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _power_driver_
{
    POWER_UART0 = 3,
    POWER_PWM   = 6,
    POWER_I2C0  = 7,
    POWER_SPI   = 8,
    POWER_RTC   = 9,
    POWER_SSP1  = 10,
    POWER_ADC   = 12,
    POWER_I2C1  = 19,
    POWER_SSP0  = 21,
    POWER_I2C2  = 26,
    POWER_USB   = 31
}POWERDRIVER;


extern void SetPowerSupply(POWERDRIVER driver, Bool enable);


#ifdef __cplusplus
 }
#endif

#endif

