
#include "../include/libs-hardware.h"




//----------------------------- public functions

Bool iapWriteBuffer(UInt32 flash_address, UInt32 * buffer, UInt32 count)
{
    UInt32 iapParameter[5];
    UInt32 iapResult[5];

    //todo disable irq
    __disable_irq();
    
    iapParameter[0] = IAP_COPY_RAM_TO_FLASH;
    iapParameter[1] = flash_address;
    iapParameter[2] = (UInt32)buffer;
    iapParameter[3] = count;
    iapParameter[4] = IAP_CCLK;
    iapExecute(iapParameter,iapResult);

    //todo enable irq
    __enable_irq();
    
    if(iapResult[0] != IAP_SUCCESS)
    {
        return False;
    }
    return True;
}

Bool iapEraseSector(UInt32 start_sector,UInt32 end_sector)
{
    UInt32 iapParameter[5];
    UInt32 iapResult[5];
    
    iapParameter[0] = IAP_ERASE_SECTOR;
    iapParameter[1] = start_sector;
    iapParameter[2] = end_sector;
    iapParameter[3] = IAP_CCLK;
    iapExecute(iapParameter,iapResult);
    
    if(iapResult[0] != IAP_SUCCESS)
    {
        return False;
    }
    return True;
}

Bool iapPrepareSector(UInt32 start_sector,UInt32 end_sector)
{
    UInt32 iapParameter[5];
    UInt32 iapResult[5];
    
    iapParameter[0] = IAP_PREPARE_SECTOR_FOR_WRITE;
    iapParameter[1] = start_sector;
    iapParameter[2] = end_sector;
    iapParameter[3] = IAP_CCLK;
    iapExecute(iapParameter,iapResult);
    
    if(iapResult[0] != IAP_SUCCESS)
    {
        return False;
    }
    return True;
}


