
#ifndef LIB_HW_I2C_SOFT_H
#define LIB_HW_I2C_SOFT_H

#ifdef __cplusplus
extern "C" {
#endif
    
extern void InitI2CSoft(void);

extern UInt32 SendBufferToI2CSoft(UInt8 addr, UInt8 *buffer, UInt32 len);

extern UInt32 GetBufferFromI2CSoft(UInt8 addr, UInt8 *buffer, UInt32 len);

    
#ifdef __cplusplus
}
#endif

#endif
