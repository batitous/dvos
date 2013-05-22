
#ifndef LIB_HW_BYC_BOARD_H
#define LIB_HW_BYC_BOARD_H

#ifdef __cplusplus
extern "C" {
#endif
    
    
extern void SetMainPowerSupply(Bool enable);

// micro volts
extern UInt32 GetBatteryVoltage(void);

// mA
extern UInt32 GetCurrentConsumption(void);

#ifdef __cplusplus
 }
#endif

#endif

