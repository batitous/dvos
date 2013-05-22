
#include "../include/types.h"

// c'est pas fait pour faire des trucs précis, juste à placer delais !

#ifdef MCU_IS_LPC13XX
#       define LOOP_DELAY      2
#endif

#ifdef MCU_IS_LPC17XX
#       define LOOP_DELAY       4
#endif

void  waitUs(UInt32  delay)
{
    volatile  UInt32  i;

    for (i = 0; i < (LOOP_DELAY * delay); i++)
    {
        ;
    }
}
