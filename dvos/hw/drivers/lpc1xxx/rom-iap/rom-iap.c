
#include "../include/libs-hardware.h"


void iapExecute(UInt32 *param_tab,UInt32 *result_tab)
{
    void (*iap)(unsigned [],unsigned []);

    iap = (void (*)(unsigned [],unsigned []))IAP_ADDRESS;
    iap(param_tab,result_tab);
}


