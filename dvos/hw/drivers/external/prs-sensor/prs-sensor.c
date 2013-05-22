/*
	Dvos - Copyright (C) 2013 Baptiste Burles, Christophe Casson, Sylvain Fay-Chatelard

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

//-------------------------- defines

/* Packet structure:

Offset	Name		Description
----------------------------------------
0		Header		Magic Number
1		Addr    	Address to set in module
1		Checksum	Checksum of Data (~data)
...


 */
#define DEFAULT_ADDR    0x20
#define PK_HEADER	0xF5
#define I2C_ACK_HEADER  0x5F


#define PRS_SENSOR_USE_DEBUG 1

#ifdef PRS_SENSOR_USE_DEBUG
#   define TRACE_PRS(str)	DebugPrintf str
#else
#   define TRACE_PRS(str)
#endif


//-------------------------- public functions:


UInt8 InitSensorPRS(SensorType mtype, GPIO_PIN pin)
{
    //UInt8 * i2caddrbuffer;
    UInt8 i2caddrbuffer[3];
    UInt8 replybuffer[3];
    //UInt8 * checkbuffer;
    UInt8 checkbuffer[8];
    UInt8 repcheckbuffer[8];
    UInt32 i = 0;
    UInt32 i2cdatalength;
    UInt8 i2caddr = DEFAULT_ADDR;

    replybuffer[0] = I2C_ACK_HEADER;
    replybuffer[1] = mtype;
    replybuffer[2] = mtype;

    SetGpioDirection(pin,GPIO_IN);

    TRACE_PRS(("InitSensorPRS: waiting for high pin state\r\n"));    
    while(GetGpioValue(pin)==0);

    TRACE_PRS(("InitSensorPRS: waiting for low pin state\r\n"));
    while(GetGpioValue(pin)==1);

    TRACE_PRS(("InitSensorPRS: Init i2c slave to %x\r\n", DEFAULT_ADDR));
    InitSlaveI2C0(DEFAULT_ADDR, I2C_400_KHZ);

    
    TRACE_PRS(("InitSensorPRS: waiting for addr packet\r\n"));
   
    i2cdatalength=GetBufferFromMasterI2C0(i2caddrbuffer, 3);
    
    TRACE_PRS(("InitSensorPRS: i2cdatalength = %x\r\n", i2cdatalength));
    
    if(i2cdatalength == 3)
    {
        //DebugPrintf("i2caddrbuffer[1] = %x\r\n", i2caddrbuffer[1]);
        if(i2caddrbuffer[0] == PK_HEADER)
        {
            //DebugPrintf("[0] = PK_HEADER\r\n");
            if(i2caddrbuffer[1] == i2caddrbuffer[2] )
            {
                //DebugPrintf("[1] = [2]\r\n");
                i2caddr = i2caddrbuffer[1];
                TRACE_PRS(("new addr = 0x%x\r\n", i2caddr));
                
                InitSlaveI2C0(i2caddr, I2C_400_KHZ);
                
                //DebugPrintf("sending ack packet\r\n");
                SetBufferToMasterI2C0(replybuffer, 3);

                i2cdatalength = GetBufferFromMasterI2C0(checkbuffer, 8);
                
                if(i2cdatalength == 8)
                {
                    //DebugPrintf("return 8 test bytes to master\r\n");
                    for(i=0;i<8;i++)
                    {
                        repcheckbuffer[i] = checkbuffer[i];
                    }
                    SetBufferToMasterI2C0(repcheckbuffer, 8);
                    
                    TRACE_PRS(("[END] - new addr is 0x%x\r\n", i2caddr));
                    
                    return i2caddr;
                }//if(i2cdatalength == 8)
            }//if(i2caddrbuffer[1] == i2caddrbuffer[2] )
        }//if(i2caddrbuffer[0] == PK_HEADER)
    }//if(i2cdatalength == 3)


    TRACE_PRS(("InitSensorPRS failed !\r\n"));
    
    //if error, halt i2c
    HaltSlaveI2C0();
    
    return 0;

}

