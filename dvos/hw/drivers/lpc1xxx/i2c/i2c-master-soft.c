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


//-------------------------- configuration macro

#ifdef HARDWARE_IS_LPC13_DEV
/* hardware is the lpc13 development board */
#       define GPIO_PORT       LPC_GPIO2
#       define SCL_PIN         0
#       define SDA_PIN         2
#       define initI2CIO()      /* remove pull-up:*/ \
                                CLRBITS(LPC_IOCON->PIO2_2,0x18);\
                                CLRBITS(LPC_IOCON->PIO2_0,0x18);
#endif


#ifdef HARDWARE_IS_LPC13XX_SENSOR
/* hardware is the lpc1311 sensor */
#       ifdef MCU_IS_LPC1311
#              define GPIO_PORT       LPC_GPIO1
#              define SCL_PIN         3
#              define SDA_PIN         4
#              define initI2CIO()     /* remove pull-up:*/ \
                                      CLRBITS(LPC_IOCON->PIO1_4,0x18);\
                                      CLRBITS(LPC_IOCON->SWDIO_PIO1_3,0x18);\
                                      /* set SWDIO_PIO1_3 to GPIO mode */ \
                                      SETBIT(LPC_IOCON->SWDIO_PIO1_3,0);
#       else
/* hardware is the lpc1315 sensor */
#              define GPIO_PORT       LPC_GPIO
#              define SCL_PIN         15
#              define SDA_PIN         16
#              define initI2CIO()     /* remove pull up */\
                                      CLRBITS(LPC_IOCON->SWDIO_PIO0_15,0x18);\
                                      CLRBITS(LPC_IOCON->PIO0_16,0x18);\
                                      /* set SWDIO_PIO0_15 to GPIO mode */\
                                      SETBIT(LPC_IOCON->SWDIO_PIO0_15,0);
#       endif
#endif

#ifdef HARDWARE_IS_BYC_V1
/* hardware is the byc board */
#       define GPIO_PORT       LPC_GPIO1
#       define SCL_PIN         22 //compass20
#       define SDA_PIN         20 //compass22
#       define initI2CIO()     /* remove pull-up */ \
                               SETBIT(LPC_PINCON->PINMODE1,9);\
                               SETBIT(LPC_PINCON->PINMODE1,13);
#endif


#ifdef MCU_IS_LPC1311
#       define I2C_DIR         GPIO_PORT->DIR     
#       define I2C_SET(pin)    SETBIT(GPIO_PORT->DATA,pin);
#       define I2C_CLR(pin)    CLRBIT(GPIO_PORT->DATA,pin);
#       define I2C_GET         GPIO_PORT->DATA
#endif

#ifdef MCU_IS_LPC1315
#       define I2C_DIR         GPIO_PORT->DIR[0]     
#       define I2C_SET(pin)    SETBIT(GPIO_PORT->SET[0],pin);
#       define I2C_CLR(pin)    SETBIT(GPIO_PORT->CLR[0],pin);
#       define I2C_GET         GPIO_PORT->PIN[0]
#endif

#ifdef MCU_IS_LPC17XX
#       define I2C_DIR         GPIO_PORT->FIODIR
#       define I2C_SET(pin)    SETBIT(GPIO_PORT->FIOSET,pin);
#       define I2C_CLR(pin)    SETBIT(GPIO_PORT->FIOCLR,pin);
#       define I2C_GET         GPIO_PORT->FIOPIN
#endif


#define SCL_INPUT()     CLRBIT(I2C_DIR,SCL_PIN)
#define SCL_OUTPUT()    SETBIT(I2C_DIR,SCL_PIN)

#define SCL0()          SCL_OUTPUT(); I2C_CLR(SCL_PIN)
#define SCL1()          SCL_INPUT()

#define SDA_INPUT()     CLRBIT(I2C_DIR,SDA_PIN)
#define SDA_OUTPUT()    SETBIT(I2C_DIR,SDA_PIN)

#define SDA(bit)        if(bit==0){ SDA_OUTPUT(); I2C_CLR(SDA_PIN); }\
                        else { SDA_INPUT(); }

#define GET_SDA()       ((I2C_GET >> SDA_PIN) & 0x1)
#define GET_SCL()       ((I2C_GET >> SCL_PIN) & 0x1)

//-------------------------- private functions

void i2c_soft_start(void)
{
    SDA(0);
    SCL0();
    waitUs(1);
}

void i2c_soft_send_bit(UInt8 bit)
{
    // set bit on SDA
    // NOP
    // SCL = 1
    // wait SCL low
    // then SCL = 0

    SDA((bit&0x1));
    waitUs(1);
    SCL1();
    waitUs(2);
    
    SCL0();
    waitUs(1);
}

static UInt8 i2c_soft_receive_bit(void)
{
    // SDA = 1
    // SCL = 1
    // wait SCL low
    // bit = SDA
    // SCL = 0
    
    UInt8 bit;
    
    SDA(1);
    waitUs(1);
    
    SCL1();
    waitUs(1);
    while( GET_SCL() == 0);
    
    bit = GET_SDA();
    
    SCL0();
    SDA_OUTPUT();
    waitUs(1);
    
    return bit;
}


 void i2c_soft_stop(void)
{
    SCL1();
    waitUs(2);
    SDA(1);
    waitUs(1);
}

 UInt8 i2c_soft_send_byte(UInt8 byte)
{    
    // send byte :
    i2c_soft_send_bit(byte>>7);
    i2c_soft_send_bit(byte>>6);
    i2c_soft_send_bit(byte>>5);
    i2c_soft_send_bit(byte>>4);
    i2c_soft_send_bit(byte>>3);
    i2c_soft_send_bit(byte>>2);
    i2c_soft_send_bit(byte>>1);
    i2c_soft_send_bit(byte>>0);
    
    // receive ack:
    return i2c_soft_receive_bit();
}

 UInt8 i2c_soft_receive_byte(UInt8 ack)
{
    UInt8 bit;
    UInt8 byte;
    
    bit = i2c_soft_receive_bit();
    byte = bit << 7;
    
    bit = i2c_soft_receive_bit();
    byte |= bit << 6;
    
    bit = i2c_soft_receive_bit();
    byte |= bit << 5;
    
    bit = i2c_soft_receive_bit();
    byte |= bit << 4;
    
    bit = i2c_soft_receive_bit();
    byte |= bit << 3;
    
    bit = i2c_soft_receive_bit();
    byte |= bit << 2;
    
    bit = i2c_soft_receive_bit();
    byte |= bit << 1;
    
    bit = i2c_soft_receive_bit();
    byte |= bit;
    
    
    // send ack
    i2c_soft_send_bit(ack);
    
    return byte;
}

//-------------------------- public functions

void initI2CSoft(void)
{
    initI2CIO();
    
    
    // select i/o function
    //CLRBITS(LPC_IOCON->PIO0_4,0x3);
    // standard I/O
    //SETBIT(LPC_IOCON->PIO0_4,8);
    
    // select i/o function
    //CLRBITS(LPC_IOCON->PIO0_5,0x3);
    // standard I/O
    //SETBIT(LPC_IOCON->PIO0_5,8);
    
    
    
}

UInt32 sendBufferToI2CSoft(UInt8 addr, UInt8 *buffer, UInt32 len)
{
    UInt32 i;
    
    i2c_soft_start();
    
    i2c_soft_send_byte(addr);    
    
    for(i=0;i<len;i++)
    {
        i2c_soft_send_byte(buffer[i]);
    }
 
    i2c_soft_stop();
    
    return 0;
}

UInt32 getBufferFromI2CSoft(UInt8 addr, UInt8 *buffer, UInt32 len)
{
    UInt32 i;
    
    i2c_soft_start();
    
    i2c_soft_send_byte(addr|1);
    
    for(i=0;i<len-1;i++)
    {
        buffer[i]=i2c_soft_receive_byte(0);
    }
    buffer[i]=i2c_soft_receive_byte(1);
    
    i2c_soft_stop();
    
    return 0;
}

