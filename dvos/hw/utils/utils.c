
#include "../../hw/include/libs-default.h"

/* datasheet arm r2p1 page 8-4
#define CPU_RESET_CYCLECOUNTER    do { SCB_DEMCR = SCB_DEMCR | 0x01000000;  \
                                       DWT_CYCCNT = 0;                      \
                                       DWT_CTRL = DWT_CTRL | 1 ; } while(0)

int offset, cycles;

CPU_RESET_CYCLECOUNTER;
__asm volatile("nop");
cycles = DWT_CYCCNT;
offset = cycles - 1;

// Display the results
printf("1x nop = %d Cycles\r\n", cycles);
printf("DWT Cycle Counter offset set to %d\r\n", offset);*/