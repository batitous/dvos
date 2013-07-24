/*
	Dvos - Copyright © 2013 Baptiste Burles, Christophe Casson, Sylvain Fay-Chatelard

    This file is part of Dvos.

    Dvos is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    Dvos is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "../include/libs-hardware.h"


//----------------------------- private functions


#ifdef MCU_IS_LPC1311
#       define ANA_CR           LPC_ADC->CR
#       define ANA_RESULT       LPC_ADC->GDR
#       define GET_RESULT(reg)  (reg>>6) & 0x03FF
#endif

#ifdef MCU_IS_LPC1315
#       define ANA_CR           LPC_ADC->CR
#       define ANA_RESULT       LPC_ADC->GDR
#       define GET_RESULT(reg)  (reg>>4) & 0x0FFF
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

ANALOG_CHANNEL getAnalogChannel(UInt8 channel)
{
    return analogChannelArray[channel];
}

UInt16 getMcuAnalog(ANALOG_CHANNEL channel)
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
