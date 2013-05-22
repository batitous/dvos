
// a simple test...

#include "../../hw/include/libs-default.h"

#include "../include/kernel-dvos.h"


extern void usermain(void);

int main(void)
{
    
    initKernel();
    
    usermain();

    startKernel();

    return 0;
}





