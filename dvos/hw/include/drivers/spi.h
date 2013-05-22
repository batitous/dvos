
#ifndef LIB_HW_SPI_H
#define LIB_HW_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

void	InitSPI(void);

UInt8	SendByteToSPI(UInt8 outgoing);
void	SendBufferToSPI(UInt8 *buffer, UInt32 size);
UInt8   GetByteFromSPI(void);
void	GetBufferFromSPI(UInt8 *buffer, UInt32 size);

#ifdef __cplusplus
}
#endif

#endif