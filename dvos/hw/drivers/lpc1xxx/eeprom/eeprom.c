
#include "../include/libs-hardware.h"

//--------------------- private functions:

static Bool executeEepromCommand(UInt32 command, UInt32 addr, UInt8 * buffer, UInt32 size)
{
    UInt32 param[5];
    UInt32 result[4];
    
    param[0] = command;
    param[1] = addr;
    param[2] = (UInt32)buffer;
    param[3] = size;
    param[4] = IAP_CCLK;
    iapExecute(param,result);
    
    if(result[0] != IAP_SUCCESS)
    {
        return False;
    }
    
    return True;
}

//--------------------- public functions:

Bool ReadByteFromEeprom(UInt32 addr, UInt8* data)
{
    return executeEepromCommand(IAP_READ_EEPROM,addr,data,1);
}

Bool ReadBufferFromEeprom(UInt32 addr, UInt8* buffer, UInt32 size)
{
    return executeEepromCommand(IAP_READ_EEPROM,addr,buffer,size);
}


Bool WriteByteToEeprom(UInt32 addr, UInt8 data)
{
    return executeEepromCommand(IAP_WRITE_EEPROM,addr,&data,1);
}

Bool WriteBufferToEeprom(UInt32 addr, UInt8* buffer, UInt32 size)
{
    return executeEepromCommand(IAP_WRITE_EEPROM,addr,buffer,size);
}

Bool EraseEeprom()
{
    return False;
}

