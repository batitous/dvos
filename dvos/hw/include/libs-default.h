
#ifndef LIBS_HW_DEFAULT_H
#define LIBS_HW_DEFAULT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"
#include "core/bit-band.h"
    
#ifdef MCU_IS_LPC17XX
#include "mcu/lpc17xx.h"
#endif
    
#ifdef MCU_IS_LPC13XX
#include "mcu/lpc13xx.h"
#endif
    
    
#include "libc.h"
#include "math.h"
#include "utils.h"
#include "drivers/sleep.h"

#ifdef __cplusplus
 }
#endif

#endif
