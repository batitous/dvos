
#ifndef LIB_HW_UART_H
#define LIB_HW_UART_H

#ifdef __cplusplus
extern "C" {
#endif

extern void InitUART0(void/*UInt32 baudrate*/);

extern void SendByteToUART0(UInt8 byte);

extern void SendBufferToUART0(UInt8 * Buffer,UInt32 Count);

extern Bool GetBufferFromUART0(UInt8 * buffer, UInt32 len);

//extern UInt32 GetAllBufferFromUART0(UInt8 *buffer, UInt32 len);

extern Bool GetByteFromUART0(UInt8 *Data);


extern void WaitDataFromUART0(void);

extern void PowerOnUART0(void);

extern void PowerOffUART0(void);


extern void InitUART1(UInt32 baudrate);

extern void InitUART1Intr(UInt32 baudrate);

extern void SendByteToUART1(UInt8 byte);

extern void SendBufferToUART1(UInt8 * Buffer,UInt32 Count);

extern UInt8 GetByteFromUART1(void);

extern UInt8 GetByteFromUART1Intr(UInt8 *Data);

extern UInt8 GetByteFromUART1NoWait(UInt8 *Data);

extern void GetBufferFromUART1(UInt8 *Buffer,UInt32 Count);


#ifdef __cplusplus
}
#endif

#endif
