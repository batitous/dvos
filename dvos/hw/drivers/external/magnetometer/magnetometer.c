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

// MAG3110 driver

typedef struct _magnetic_field_MinMax_
{
    Int32 max;
    Int32 min;
} MagneticMinMax;


#define DEFAULT_VALUE           30000
#define MAG3110_I2C_ADDR        0x1C
#define AXIS_NUMBER             3


MagneticMinMax magnetics[AXIS_NUMBER];



//-------------------------- private functions


static Bool getRawMagneticFieldValue(MagneticRawValue * rawvalue)
{
    UInt8 buffer[6];
    Int16 x = 0;
    Int16 y = 0;
    Int16 z = 0;
    
    
    do
    {

        do
        {
            // check if we have new value in x, y and z axis
            buffer[0] = 0x00;
            SendBufferToI2CSoft(MAG3110_I2C_ADDR,buffer,1);
            GetBufferFromI2CSoft(MAG3110_I2C_ADDR,buffer,1);
            WaitMs(10);

        }while( (buffer[0]&0x08) == 0);


        buffer[0] = 0x01;
        SendBufferToI2CSoft(MAG3110_I2C_ADDR,buffer,1);
        GetBufferFromI2CSoft(MAG3110_I2C_ADDR,buffer,6);

        x = buffer[0]<<8;
        x |= buffer[1];

        y = buffer[2]<<8;
        y |= buffer[3];

        z = buffer[4]<<8;
        z |= buffer[5];
    
    }while(x == y || x == z || y == z);
    
    
    rawvalue->x = x;
    rawvalue->y = y;
    rawvalue->z = z;
    
    
    //DebugPrintf("x:%d y:%d z:%d\r\n",rawvalue->x, rawvalue->y, rawvalue->z);
    
    
    return True;
}


//-------------------------- public functions

Bool InitMagnetometer(void)
{
    UInt8 buffer[4];
    
    
    //standby mode
    buffer[0] = 0x10;
    buffer[1] = 0x00;
    SendBufferToI2CSoft(MAG3110_I2C_ADDR,buffer,2);
    
    
    WaitMs(100);
    
    // auto-reset CTRL_REG2 = 0x80
    buffer[0] = 0x11;
    //buffer[1] = 0x80; // not RAW
    buffer[1] = 0xB0; // RAW - reset
    //buffer[1] = 0x20; // RAW
//    buffer[1] = 0xB0; // reset mag
//    buffer[1] = 0x00;
    SendBufferToI2CSoft(MAG3110_I2C_ADDR,buffer,2);
    
    
    // active mode 80 Hz CTRL_REG1 = 0x01 :
    buffer[0] = 0x10;
    //buffer[1] = 0x01;
    buffer[1] = 0x19;
    SendBufferToI2CSoft(MAG3110_I2C_ADDR,buffer,2);
    
    
    // get id :
    buffer[0] = 0x07;
    SendBufferToI2CSoft(MAG3110_I2C_ADDR,buffer,1);
    GetBufferFromI2CSoft(MAG3110_I2C_ADDR,buffer,1);
    
    WaitMs(100);
    
    if( 0xC4 != buffer[0])
    {
        return False;
    }
    
    return True;
}


#define	M3110_MAX	 10000  //TODO set in calibration struct


#define NO_CALIB        0
#define INIT_CALIB      1
#define CALIBRATE       2
#define END_CALIB       3


UInt8 calibratestate = NO_CALIB;
Bool init = True;


void StartMagnetometerCalibration(void)
{
    calibratestate = INIT_CALIB;
}

void StopMagnetometerCalibration(void)
{
    calibratestate = END_CALIB;
}


Bool GetMagneticValue(MagneticRawValue * rawvalue, MagneticRawValue * value)
{    
    Int32 hix = 0, hiy = 0, hiz = 0;
    
    if(init == True)
    {
        //DebugPrintf("Init mag\r\n");

        InitMagnetometer();
        
        //load eeprom min-max values
        ReadBufferFromEeprom(0, (UInt8*)magnetics, sizeof(MagneticMinMax)*AXIS_NUMBER);
        
        init = False;
    }
     
    getRawMagneticFieldValue(rawvalue);
    
    
    switch(calibratestate)
    {
        case NO_CALIB: //no calibration
        {
            break;
        }
        
        case INIT_CALIB: //calibration init
        {
            getRawMagneticFieldValue(rawvalue);
            
            magnetics[0].min = rawvalue->x;
            magnetics[1].min = rawvalue->y;
            magnetics[2].min = rawvalue->z;
            magnetics[0].max = rawvalue->x;
            magnetics[1].max = rawvalue->y;
            magnetics[2].max = rawvalue->z;
            
            calibratestate = CALIBRATE; // go to calibration state
            
            break;
        }
        
        case CALIBRATE: //calibration
        {
            if( rawvalue->x > magnetics[0].max)
            {
                        magnetics[0].max = rawvalue->x;
                        //DebugPrintf("\tmax X: %d\r\n", magnetics[0].max);
            }

            if( rawvalue->y > magnetics[1].max)
            {
                        magnetics[1].max = rawvalue->y;
                        //DebugPrintf("\t\t\tmax Y: %d\r\n", magnetics[1].max);
            }

            if( rawvalue->z > magnetics[2].max)
            {
                        magnetics[2].max = rawvalue->z;
                        //DebugPrintf("\t\t\t\t\tmax Z: %d\r\n", magnetics[2].max);
            }

            if( rawvalue->x < magnetics[0].min)
            {
                        magnetics[0].min = rawvalue->x;
                        //DebugPrintf("min X: %d\r\n", magnetics[0].min);
            }

            if( rawvalue->y < magnetics[1].min)
            {
                        magnetics[1].min = rawvalue->y;
                        //DebugPrintf("\t\tmin Y: %d\r\n", magnetics[1].min);
            }

            if( rawvalue->z < magnetics[2].min)
            {
                        magnetics[2].min = rawvalue->z;
                        //DebugPrintf("\t\t\t\tmin Z: %d\r\n", magnetics[2].min);
            }
            
            //DebugPrintf("minX: %d\tmaxX: %d\t minY:%d\tmaxY: %d\r\n", magnetics[0].min, magnetics[0].max, magnetics[1].min, magnetics[1].max);
            
            break;
        }
        
        case END_CALIB: //calibration end -> saving data
        {
            WriteBufferToEeprom(0, (UInt8*)magnetics, sizeof(MagneticMinMax)*AXIS_NUMBER);
            
            calibratestate = NO_CALIB; // go to no calibration
            break;
        }
    }
    
   // if( rawvalue->x > M3110_MAX || rawvalue->x < -M3110_MAX || 
   //     rawvalue->y > M3110_MAX || rawvalue->y < -M3110_MAX ||
   //     rawvalue->z > M3110_MAX || rawvalue->z < -M3110_MAX)
   // {
   //     init = True;
   //     return False;
   // }
   // else
   // {
        hix = ((magnetics[0].max + magnetics[0].min) >> 1);
        hiy = ((magnetics[1].max + magnetics[1].min) >> 1);
        hiz = ((magnetics[2].max + magnetics[2].min) >> 1);

        value->x = rawvalue->x - hix;
        value->y = rawvalue->y - hiy;
        value->z = rawvalue->z - hiz;
        
        return True;
   // }
}
