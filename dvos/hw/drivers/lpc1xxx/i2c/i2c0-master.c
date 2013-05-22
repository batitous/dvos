
#include "../include/libs-hardware.h"


#define I2C_I2CONSET    LPC_I2C0->I2CONSET
#define I2C_I2CONCLR    LPC_I2C0->I2CONCLR
#define I2C_I2STAT      LPC_I2C0->I2STAT
#define I2C_I2DAT       LPC_I2C0->I2DAT
#define I2C_I2SCLL      LPC_I2C0->I2SCLL
#define I2C_I2SCLH      LPC_I2C0->I2SCLH

UInt32 i2c0_write(UInt8 data);


#define I2C_CNT         65536

UInt32 private_i2c0_getStat(void)
{
    UInt32 cnt = I2C_CNT;
    while( (I2C_I2CONSET & 0x08) == 0)
    {
        cnt--;
        waitUs(1);
       if(cnt==0)
       {
           return I2C_TIMEOUT;
       }
    }
    return 0;
}

#define GET_I2C_STATUS()    if( private_i2c0_getStat()!=0){ return I2C_TIMEOUT;}\
                            status = I2C_I2STAT


UInt32 private_i2c0_send(UInt8 data)
{
    UInt32 cnt = I2C_CNT;
    while( i2c0_write(data) == I2C_BUSY)
    {
        cnt--;
        waitUs(1);
        if(cnt==0)
        {
            return I2C_TIMEOUT;
        }
    }
    return 0;
}

#define SEND_AND_WAIT(data) if( private_i2c0_send(data)!=0) { return I2C_TIMEOUT;}\
            if( i2c0_wait_after_write() != I2C_OK) return I2C_ERROR_SEND



#define SEND_ACK()			I2C_I2CONSET |= 0x04; /*AA=1*/ I2C_I2CONCLR = 0x08 /*clear SI flag*/
#define SEND_NACK()			I2C_I2CONCLR = 0x04; I2C_I2CONCLR = 0x08   /*clear SI flag*/

UInt32 i2c0_start(void)
{
//    UInt32 cnt;
	UInt32 result;
	UInt8 status;

	//start
	I2C_I2CONSET |= 0x20;

	while(1)
	{
		GET_I2C_STATUS();

		//start transmitted
		if((status == 0x08) || (status == 0x10))
		{
			result = I2C_OK;
			break;
		}
		//error
		else if(status != 0xf8)
		{
			result = I2C_ERROR;
			break;
		}
		else
		{
			//clear SI flag
			I2C_I2CONCLR = 0x08;
		}

	}

	//clear start flag
	I2C_I2CONCLR = 0x20;

	return result;
}


void i2c0_stop(void)
{
    UInt32 cnt = I2C_CNT;

	I2C_I2CONSET |= 0x10;  //STO = 1, set stop flag
	I2C_I2CONCLR = 0x08;   //clear SI flag

	//wait for STOP detected (while STO = 1)
	while((I2C_I2CONSET & 0x10) == 0x10)
	{
	    cnt--;
            waitUs(1);
            if(cnt==0)
            {
                return;
            }
	}
}

UInt32 i2c0_write(UInt8 data)
{
	//check if I2C Data register can be accessed
	if((I2C_I2CONSET & 0x08) != 0)    //if SI = 1
	{
		/* send data */
		I2C_I2DAT    = data;
		I2C_I2CONCLR = 0x08;       //clear SI flag
		return I2C_OK;
	}
	else
	{
		//data register not ready
		return I2C_BUSY;
	}

}

UInt32 i2c0_wait_after_write(void)
{
	UInt8 status;

    //DebugPrintf("i2c0_wait_after_write\r\n");
	//wait until data transmitted
	while(1)
	{
		//get new status
		GET_I2C_STATUS();

		/*
		 * SLA+W transmitted, ACK received or
		 * data byte transmitted, ACK received
		 */
		if( (status == 0x18) || (status == 0x28) )
		{
			//data transmitted and ACK received
			return I2C_OK;
		}
		//no relevant status information
		else if(status != 0xf8 )
		{
		    //DebugPrintf("i2c0_wait_after_write status = %x\r\n", status);
			return I2C_ERROR;
		}
	}
}

void i2c0_write_wait(UInt8 data)
{
    UInt32 cnt = I2C_CNT;
    while( i2c0_write(data) == I2C_BUSY)
    {
        cnt--;
         waitUs(1);
        if(cnt==0)
        {
            //DebugPrintf("i2c0_write_wait timeout\r\n");
            return;
        }
    }

    i2c0_wait_after_write();
}

UInt32 i2c0_read(UInt8 *data)
{
	//check if I2C Data register can be accessed
    if((I2C_I2CONSET & 0x08) != 0)    //SI = 1
    {
		//read data
		*data = I2C_I2DAT;
		return I2C_OK;
    }
    else
    {
		//No data available
		return I2C_EMPTY;
    }
}


void InitI2C0(I2C_SPEED speed)
{
	UInt32 reg;

	I2C_I2CONCLR = 0xFF;

	//  set pinouts as scl and sda
        LPC_PINCON->PINSEL1 |= BIT(22);
        LPC_PINCON->PINSEL1 |= BIT(24);
        
        // how to compute i2c clock bus = PCLKI2C / (I2C_SCLL + I2C_SCLH)
        
        // i2c frequency set to 100 MHz
        LPC_SC->PCLKSEL0 |= BITS(14,1);
        
	switch(speed)
	{
	case I2C_400_KHZ:
		reg = 125;
		break;
	case I2C_100_KHZ:
        default:
		reg = 500;
		break;
	}

	I2C_I2SCLL=reg;
	I2C_I2SCLH=reg;

        // active master mode on i2c bus
	I2C_I2CONSET = 0x40;
}

UInt32 SendBufferToI2C0(UInt8 addr, UInt8 *buffer, UInt32 len)
{
	UInt32 i;
	//send start condition
	if(i2c0_start()!=I2C_OK)
	{
	    //i2c0_stop();
	    //DebugPrintf("SendBufferToI2C0.i2c0_start\r\n");
		return I2C_ERROR_START;
	}

	//send address
	SEND_AND_WAIT(addr);

	for(i=0;i<len;i++)
	{
		SEND_AND_WAIT(buffer[i]);
	}

	i2c0_stop();

    //DebugPrintf("SendBufferToI2C0 I2C_OK\r\n");
	return I2C_OK;
}

UInt32 GetBufferFromI2C0(UInt8 addr, UInt8 *buffer, UInt32 len)
{
	UInt32 i;
	UInt8 status;
    UInt8 *ptr;

    ptr = buffer;
	if( i2c0_start()!=I2C_OK)
	{
	    //DebugPrintf("GetBufferFromI2C0.i2c0_start I2C_ERROR\r\n");
	    //i2c0_stop();
		return I2C_ERROR;
	}

    addr = addr|1;
	while( i2c0_write(addr) == I2C_BUSY);

	for(i=0;i<len;i++)
	{
		while(1)
		{
			GET_I2C_STATUS();

			/*
			 * SLA+R transmitted, ACK received or
			 * SLA+R transmitted, ACK not received
			 * data byte received in master mode, ACK transmitted
			 */
			if((status == 0x40 ) || (status == 0x48 ) || (status == 0x50 ))
			{
				if(i==len-1)
				{
					SEND_NACK();
				}
				else
				{
					SEND_ACK();
				}

				while(i2c0_read(ptr)==I2C_EMPTY);

				ptr++;
				break;

			}
			else if(status != 0xf8 )
			{
				i2c0_stop();
                //DebugPrintf("GetBufferFromI2C0 I2C_ERROR\r\n");
				return I2C_ERROR;
			}

		}//while(0)
	}//for

	i2c0_stop();

	return I2C_OK;
}
