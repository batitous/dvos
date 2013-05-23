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


// code taken from a linux driver:
//
// #define mma7660fc_get_realdata(x) if(((x)& (0x01<<5))){(x)=((x) |0xe0);}
// else{(x)=((x) & 0x1f); }

// use it after get x, y and z
// mma7660fc_get_realdata(x);
// mma7660fc_get_realdata(y);
// mma7660fc_get_realdata(z);

//f (Xbyte>31)
//{
//Xbyte = Xbyte-64;
//}
//
//if (Ybyte>31)
//{
//Ybyte = Ybyte -64;
//}
//
//if (Zbyte>31)
//{
//Zbyte = Zbyte -64;
//}

#define MMA7660FC_I2C_ADDR      0x98

/*
const Int16 angleXY[] =
{
  0, 269, 538, 808, 1081, 1355, 1633, 1916,
  2202, 2495, 2795, 3104, 3423, 3754, 4101,
  4468, 4859, 5283, 5754, 6295, 6964 
};

const Int16 angleZ[] = 
{
  9000, 8731, 8462, 8192, 7919, 7645, 7367, 7084,
  6798, 6505, 6205, 5896, 5577, 5246, 4899, 4532,
  4141, 3717, 3246, 2905, 2036, 1014
};*/

//-------------------------- private functions


static Int16 getGValue(UInt8 byte)
{
    Int16 g;
    
    g = (byte&0x1F);
    
    if( (byte & 0x20)!=0)
    {
        g = g | 0xFFE0 ;
    }
        
    return g;
}

/*static void setAccelerationAngle(AccelerationRawValue *raw, AccelerationAngle *angle)
{
    Int16 temp;
    
    temp = raw->x;
    if(temp<0)
        temp = - temp;
    if(temp>21)
        temp=20;
    angle->x = angleXY[temp];
    if(raw->x<0)
        angle->x = -angle->x;
    
    
    temp = raw->y;
    if(temp<0)
        temp = - temp;
    if(temp>21)
        temp=20;
    angle->y = angleXY[temp];
    if(raw->y<0)
        angle->y = -angle->y;
    
    temp = raw->z;
    if(temp<0)
        temp = - temp;
    if(temp>21)
        temp=20;
    angle->z = angleZ[temp];
    if(raw->z<0)
        angle->z = -angle->z;
}*/

//-------------------------- public functions


void initAccelerometer(AccelerometerConfig config, UInt8 tapCount, UInt8 tapSensibility)
{
    UInt8 buffer[2];
    
    // standby mode
    buffer[0] = 0x07;
    buffer[1] = 0x00;
    sendBufferToI2CSoft(MMA7660FC_I2C_ADDR,buffer,2);
    
    // set timing for update and tilt
    buffer[0] = 0x08;

    if( config == ACCELEROMETER_CONFIG_DEFAULT)
    {
        //for orientation:
        // 32 sample per seconds, 8 measures sample before update TILT
        //buffer[1] = 0xE2;
        
        //for orientation:
        // 8 sample per seconds
        //buffer[1] = 0xE4;
        
        //for orientation:
        // 16 sample per seconds
        buffer[1] = 0xE3;
    }
    else
    {
        //for tap:
        buffer[1] = 0x00;
    }
    sendBufferToI2CSoft(MMA7660FC_I2C_ADDR,buffer,2);
    
    if( config == ACCELEROMETER_CONFIG_DETECT_TAP)
    {
        buffer[0] = 0x09;
        buffer[1] = tapCount; //11 by default?
        sendBufferToI2CSoft(MMA7660FC_I2C_ADDR,buffer,2);
        
        buffer[0] = 0x0A;
        //buffer[1] = 0x5F;
        buffer[1] = tapSensibility; // 11 by default ?
        sendBufferToI2CSoft(MMA7660FC_I2C_ADDR,buffer,2);
    }
    
    // active mode
    buffer[0] = 0x07;
    buffer[1] = 0x01;
    sendBufferToI2CSoft(MMA7660FC_I2C_ADDR,buffer,2);
    
}

Bool getAccelerometer(AccelerationInfo * info, AccelerationRawValue * value, Bool gBound)
{
    UInt8 backfront, pola;
    UInt8 buffer[4];
    
    // request accelerometer value
    buffer[0] = 0x00;
    sendBufferToI2CSoft(MMA7660FC_I2C_ADDR,buffer,1);
    getBufferFromI2CSoft(MMA7660FC_I2C_ADDR,buffer,4);
        
    if( (buffer[0] & 0x40)!=0 ||
        (buffer[1] & 0x40)!=0 ||
        (buffer[2] & 0x40)!=0 ||
        (buffer[3] & 0x40)!=0 )
    {
        return False;
    }
    
    // get milli g values
    value->x = getGValue(buffer[0]);
    value->y = getGValue(buffer[1]);
    value->z = getGValue(buffer[2]);
    
    // get angle
//    setAccelerationAngle(value,angle);
    
    //zero-g dead zone
    if(value->x <= 3 && value->x >=-3)  value->x = 0;
    if(value->y <= 3 && value->y >=-3)  value->y = 0;
    if(value->z <= 3 && value->z >=-3)  value->z = 0;
    
    value->x *= 47;
    value->y *= 47;
    value->z *= 47;
    
    //accelerometer boundaries
    if(gBound==True)
    {
        if(value->x > 984) value->x = 984;
        if(value->x < -984) value->x = -984;

        if(value->y > 984) value->y = 984;
        if(value->y < -984) value->y = -984;

        if(value->z > 984) value->z = 984;
        if(value->z < -984) value->z = -984;
    }
    
    
    // get informations about accelerometer
    info->shake = (buffer[3]&0x80)>>7;
        
    info->orientation = ORIENTATION_UNKNOWN;
    info->backOrFront = ORIENTATION_UNKNOWN;

    backfront = buffer[3]&0x3;
    switch(backfront)
    {
        case 1:
            //DebugPrintf("FRONT ");
            info->backOrFront = ORIENTATION_FRONT;
            break;
        case 2:
            //DebugPrintf("BACK ");
            info->backOrFront = ORIENTATION_BACK;
            break;
    }

    pola = (buffer[3]&0x1C)>>2;
    switch(pola)
    {
        case 1:
            //DebugPrintf("LEFT ");
            info->orientation = ORIENTATION_LEFT;
            break;
        case 2:
            //DebugPrintf("RIGHT ");
            info->orientation = ORIENTATION_RIGHT;
            break;
        case 5:
            //DebugPrintf("DOWN ");
            info->orientation = ORIENTATION_DOWN;
            break;
        case 6:
            //DebugPrintf("UP ");
            info->orientation = ORIENTATION_UP;
            break;
    }


    info->tap = (buffer[3]&0x20) >> 5;
    
    
    // baptiste: les secousses sur x, y z sont pas detecté ?
/*
    if( info->shake == True)
    {
        DebugPrintf("SHAKE ");
        
        buffer[0] = 0x06;
        SendBufferToI2CSoft(MMA7660FC_I2C_ADDR,buffer,1);
        GetBufferFromI2CSoft(MMA7660FC_I2C_ADDR,buffer,1);
        
        // shake on x axis
        if( (buffer[0]&0x80)!=0)
        {
            DebugPrintf("X ");
            info->shakeX = True;
        }
        else
        {
            info->shakeX = False;
        }
        
        // shake on y axis
        if( (buffer[0]&0x40)!=0)
        {
            DebugPrintf("Y ");
            info->shakeY = True;
        }
        else
        {
            info->shakeY = False;
        }
        
        // shake on z axis
        if( (buffer[0]&0x20)!=0)
        {
            DebugPrintf("Z ");
            info->shakeZ = True;
        }
        else
        {
            info->shakeZ = False;
        }
    }
*/
    

    //DebugPrintf("\r\n");

    return True;
}
