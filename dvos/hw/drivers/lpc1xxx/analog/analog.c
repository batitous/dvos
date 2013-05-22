
#include "../include/libs-hardware.h"


//----------------------------- private functions


#ifdef MCU_IS_LPC13XX
#       define ANA_CR           LPC_ADC->CR
#       define ANA_RESULT       LPC_ADC->GDR
#       define GET_RESULT(reg)  (reg>>6) & 0x03FF
#endif

#ifdef MCU_IS_LPC17XX
#       define ANA_CR           LPC_ADC->ADCR
#       define ANA_RESULT       LPC_ADC->ADGDR
#       define GET_RESULT(reg)  (reg>>4) & 0x0FFF
#endif


const ANALOG_CHANNEL analogChannelArray[]=
{
    ANA0, ANA1, ANA2, ANA3, ANA4, ANA5, ANA6, ANA7
};


//----------------------------- public functions

ANALOG_CHANNEL GetAnalogChannel(UInt8 channel)
{
    return analogChannelArray[channel];
}

UInt16 GetMcuAnalog(ANALOG_CHANNEL channel)
{
	UInt16 result;
	UInt32 temp;

	// clear previous channel
        CLRBITS(ANA_CR, 0xFF);
	// set channel
	ANA_CR |= channel;
	// start conversion
        SETBIT(ANA_CR,24);

        while( ((temp=ANA_RESULT) & BIT(31) ) == 0);
         
        CLRBIT(ANA_CR,24);

	result = GET_RESULT(temp);
        
	return result;
}
