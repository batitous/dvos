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

#include "../../kernel/include/kernel-dvos.h"


//-------------------------- I2C Slave Transmitter status codes
#define I2C_STX_ADR_ACK            0xA8  // Own SLA+R has been received; ACK has been returned
#define I2C_STX_ADR_ACK_M_ARB_LOST 0xB0  // Arbitration lost in SLA+R/W as Master; own SLA+R has been received; ACK has been returned
#define I2C_STX_DATA_ACK           0xB8  // Data byte in TWDR has been transmitted; ACK has been received
#define I2C_STX_DATA_NACK          0xC0  // Data byte in TWDR has been transmitted; NOT ACK has been received
#define I2C_STX_DATA_ACK_LAST_BYTE 0xC8  // Last data byte in TWDR has been transmitted (TWEA = "0"); ACK has been received

//-------------------------- I2C Slave Receiver status codes
#define I2C_SRX_ADR_ACK            0x60  // Own SLA+W has been received ACK has been returned
#define I2C_SRX_ADR_ACK_M_ARB_LOST 0x68  // Arbitration lost in SLA+R/W as Master; own SLA+W has been received; ACK has been returned
#define I2C_SRX_GEN_ACK            0x70  // General call address has been received; ACK has been returned
#define I2C_SRX_GEN_ACK_M_ARB_LOST 0x78  // Arbitration lost in SLA+R/W as Master; General call address has been received; ACK has been returned
#define I2C_SRX_ADR_DATA_ACK       0x80  // Previously addressed with own SLA+W; data has been received; ACK has been returned
#define I2C_SRX_ADR_DATA_NACK      0x88  // Previously addressed with own SLA+W; data has been received; NOT ACK has been returned
#define I2C_SRX_GEN_DATA_ACK       0x90  // Previously addressed with general call; data has been received; ACK has been returned
#define I2C_SRX_GEN_DATA_NACK      0x98  // Previously addressed with general call; data has been received; NOT ACK has been returned
#define I2C_SRX_STOP_RESTART       0xA0  // A STOP condition or repeated START condition has been received while still addressed as Slave

//-------------------------- I2C Register defines
#define STA	0x20
#define SIC	0x08
#define SI	0x08
#define STO	0x10
#define STAC    0x20
#define AA	0x04


//-------------------------- private defines


#define I2C_STREAM_BUFFER_SIZE	64		/**< Buffer size of slave device */

//-------------------------- private variables

//volatile UInt8 i2cSlaveFlag;			/**< i2c interrupt flag */

static volatile KIOStream * i2cStream = 0;

//volatile UInt32 i2cWriteFlag = 0;

volatile UInt8 i2cWriteIndex;
volatile UInt8 i2cWriteBuffer[I2C_STREAM_BUFFER_SIZE];		/**< pointer to the write buffer */

//-------------------------- private functions

void I2C_IRQn_Handler(void)
{
    
    switch(LPC_I2C->STAT)
    {
	// Own SLA+R has been received; ACK has been returned.
	case I2C_STX_ADR_ACK:
	// Data byte in I2C0_I2DAT has been transmitted; ACK has been received.
	case I2C_STX_DATA_ACK:
		// Read the data from i2c master.

            //i2cWriteFlag = 1;
            
                if(i2cWriteIndex<I2C_STREAM_BUFFER_SIZE)
                {
                        LPC_I2C->DAT = i2cWriteBuffer[i2cWriteIndex];
                        i2cWriteIndex++;
                }

		// Data byte will be transmitted and ACK should be received.
		LPC_I2C->CONSET |= AA;
		LPC_I2C->CONCLR = SIC;
	break;
	// Data byte in I2C0_I2DAT has been transmitted; NOT ACK has been received.
	case I2C_STX_DATA_NACK:
	// Last data byte in I2C0_I2DAT has been transmitted (TWEA = "0"); ACK has been received.
	case I2C_STX_DATA_ACK_LAST_BYTE:

		// Switched to the not addressed slave mode; own SLA will be recognized.
		LPC_I2C->CONSET |= AA;
		LPC_I2C->CONCLR = SIC;
		break;
	// Own SLA+W has been received; ACK has been returned.
	case I2C_SRX_ADR_ACK:

                // master prepare a write operation

		// Data byte will be received and ACK will be returned.
		LPC_I2C->CONSET |= AA;
		LPC_I2C->CONCLR = SIC;
	break;
	// Previously addressed with own SLA+W; data has been received; ACK has been returned.
	case I2C_SRX_ADR_DATA_ACK:
		// Write the data to slave device.

		//Write master data in the i2c slave buffer
                setByteToStream(i2cStream,LPC_I2C->DAT);
                
		

		// Next data byte will be received and ACK will be returned.
		LPC_I2C->CONSET |= AA;
		LPC_I2C->CONCLR = SIC;
	break;
	// Previously addressed with own SLA+W; data has been received; NOT ACK has been returned.
	case I2C_SRX_ADR_DATA_NACK:
		// Switch to the not addressed slave mode; own SLA will be recognized.
		LPC_I2C->CONSET |= AA;
		LPC_I2C->CONCLR = SIC;
	break;
	// A STOP condition or repeated START condition has been received while still addressed as Slave.
	case I2C_SRX_STOP_RESTART:

                irqWakeUpTaskFromStream(i2cStream);
                
		i2cWriteIndex = 0;

		// Switch to the not addressed slave mode; own SLA will be recognized.
		LPC_I2C->CONSET |= AA;
		LPC_I2C->CONCLR = SIC;
	break;
	}


}

//-------------------------- public functions

void reInitSlaveI2C0(UInt8 address, I2C_SPEED speed)
{
    UInt32 reg;
    
    LPC_I2C->CONCLR = 0xFF;

    // i2c frequency = 72 000 / (L + H)

    switch(speed)
    {
    case I2C_100_KHZ:
            reg = 360;
            break;
    case I2C_400_KHZ:
            reg = 90;
            break;
    default:
            reg = 360;
            break;
    }

    LPC_I2C->SCLL=reg;
    LPC_I2C->SCLH=reg;

    LPC_I2C->ADR0 = address&0xFE; //set slave address


    NVIC_SetPriority(I2C_IRQn, 0x01);
    NVIC_EnableIRQ(I2C_IRQn);

    // activate slave mode and i2c bus
    LPC_I2C->CONSET = 0x44;
    
}

void initSlaveI2C0(UInt8 address, I2C_SPEED speed)
{
	
        SETBIT(LPC_IOCON->PIO0_4,0);
        SETBIT(LPC_IOCON->PIO0_5,0);
                
        SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,5);
        SETBIT(LPC_SYSCON->PRESETCTRL,1);
                
	reInitSlaveI2C0(address,speed);
        
        //i2cWriteIndex = 0;
        if(i2cStream == 0)
        {
                i2cStream = newInputOutputStream(I2C_STREAM_BUFFER_SIZE);
        }
}


void haltSlaveI2C0(void)
{
    LPC_I2C->CONCLR = 0x40;
    
    //todo deinitialize irq
}


UInt32 getBufferFromMasterI2C0(UInt8 *buffer, UInt32 len)
{
    waitDataFromStream(i2cStream);

    return getAllBufferFromStream(i2cStream,buffer, len);
}


void setBufferToMasterI2C0(UInt8 *buffer, UInt8 size)
{

    UInt8 i;
    i2cWriteIndex = 0;
    
    for( i=0 ; i < size && i < I2C_STREAM_BUFFER_SIZE ; i++ )
    {
        i2cWriteBuffer[i] = buffer[i];
    }
/*
    UInt32 i;
    
    for (i=0 ; i < size ; i++)
    {
        while(i2cWriteFlag==0);
        i2cWriteFlag = 0;
        
        LPC_I2C->DAT = buffer[i];
        LPC_I2C->CONSET |= AA;
        LPC_I2C->CONCLR = SIC;
    }
*/
}
