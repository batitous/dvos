
#ifndef LIBS_HW_BIT_BAND_H
#define LIBS_HW_BIT_BAND_H

#ifdef __cplusplus
extern "C" {
#endif


//take from lpc datasheet: ARM appendix


#define GET_BITBAND( addr , bitnum )  (( (addr) & 0xF0000000 ) + 0x2000000+ (((addr) & 0xFFFFF) << 5) +(bitnum <<2) )


// convert an device address into a bit-band device address
// for an example, see driver/uart.c

// get bit value from an address
#define BITBAND( addr, bitnum )     *((volatile unsigned long *)(GET_BITBAND(addr,bitnum)))


#ifdef __cplusplus
 }
#endif

#endif
