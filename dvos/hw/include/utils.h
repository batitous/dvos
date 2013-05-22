
#ifndef LIBS_HW_UTILS_H
#define LIBS_HW_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif


// set value at specified position
#define BITS(position,value) 	((value)<<(position))

// set 1 at specified position
#define BIT(position) 		(1<<(position))

// set 1 into register at position
#define SETBIT(reg,position)    reg |= (1<<((UInt32)position))

// clear one bit of register at position
#define CLRBIT(reg,position)  reg &= ~(1<<((UInt32)position))

// clear multiple bits of register
#define CLRBITS(reg,mask)     reg &= ~(mask)
    

// software delay : this functions don't use any timer or kernel code
// DONT USE THIS FUNCTION FOR PRECISE DELAY !
extern void  waitUs(UInt32  delay);



typedef void (*DebugInterfaceCallback)(UInt8 data); 

extern void SetDebugInterface(DebugInterfaceCallback callback);


#ifdef FIRMWARE_USE_DEBUG

#      ifndef FIRMWARE_USE_DEBUG_LITE
extern void DebugPrintf(const char *format, ...);
#       else
#       define  DebugPrintf(...)
#endif

#else
#       define  DebugPrintf(...)
#endif




#ifdef __cplusplus
 }
#endif

#endif
