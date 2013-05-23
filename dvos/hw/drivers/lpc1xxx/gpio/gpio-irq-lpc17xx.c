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
#include "../../kernel/include/kernel-dvos.h"
#include "../include/libs-hardware.h"

extern UInt32 getIRQNumber(UInt32 reg);

//----------------------------- private object

void defaultIrqCallback();

static GpioIrqCallback gpioIrqCallback = defaultIrqCallback;


//----------------------------- private functions

void defaultIrqCallback(UInt32 gpioIrqEvent, UInt32 gpioIrqEdge)
{
    gpioIrqEvent = 0;
    gpioIrqEdge = 0;
}

UInt32 getEventFromGpio(UInt32 * edge)
{
    UInt32 event;
    UInt32 thepin;
    
    if( (LPC_GPIOINT->IntStatus & 0x1)!=0)
    {
        //port0 irq
        event = GPIO_PORT0;
        
        if( LPC_GPIOINT->IO0IntStatR != 0)
        {
            // rising
            *edge = GPIO_RISING_EDGE;
            thepin = getIRQNumber(LPC_GPIOINT->IO0IntStatR);
        }
        else
        {
            // falling
            *edge = GPIO_FALLING_EDGE;
            thepin = getIRQNumber(LPC_GPIOINT->IO0IntStatF);
        }
        
        //clear irq pin
        SETBIT(LPC_GPIOINT->IO0IntClr,thepin);
    }
    else
    {
        //port2 irq
        event = GPIO_PORT2;
        
        if(LPC_GPIOINT->IO2IntStatR != 0)
        {
            //rising
            *edge = GPIO_RISING_EDGE;
            thepin = getIRQNumber(LPC_GPIOINT->IO2IntStatR);
        }
        else
        {
            // falling
            *edge = GPIO_FALLING_EDGE;
            thepin = getIRQNumber(LPC_GPIOINT->IO2IntStatF);
        }
        
        //clear irq pin
        SETBIT(LPC_GPIOINT->IO2IntClr,thepin);
    }
    
    event |= thepin;
 
    return event;
}

//----------------------------- irq routine

void EINT3_IRQHandler(void)
{
    UInt32 edge;
    UInt32 event = getEventFromGpio(&edge);
    
    // event stores the irq state as a mask with:
    // GPIO_PORT
    // GPIO_EDGE
    // GPIO_PIN
    
    gpioIrqCallback(event,edge);    
}




//----------------------------- public functions


void setGpioIrqCallback(GpioIrqCallback callback)
{
    gpioIrqCallback = callback;
}


void enableGpioIrq(GPIO_PIN pin, GPIO_EDGE edge)
{
    UInt32 thepin = pin & 0xFFFF;
    UInt32 port = pin & 0xFFFF0000;
    
    if(port==GPIO_PORT0)
    {
        if(edge==GPIO_FALLING_EDGE)
        {
            //falling edge
            SETBIT(LPC_GPIOINT->IO0IntEnF,thepin);
        }
        else //if(edge==GPIO_RISING_EDGE)
        {
            //rising edge
            SETBIT(LPC_GPIOINT->IO0IntEnR,thepin);
        }
    }
    else if(port==GPIO_PORT2)
    {
        if(edge==GPIO_FALLING_EDGE)
        {
            //falling edge
            SETBIT(LPC_GPIOINT->IO2IntEnF,thepin);
        }
        else //if(edge==GPIO_RISING_EDGE)
        {
            //rising edge
            SETBIT(LPC_GPIOINT->IO2IntEnR,thepin);
        }
    }
    else
    {
        return;
    }
    
    NVIC_SetPriority(EINT3_IRQn, 0x01);
    NVIC_EnableIRQ(EINT3_IRQn);
}

void disableGpioIrq(GPIO_PIN pin, GPIO_EDGE edge)
{
    UInt32 thepin = pin & 0xFFFF;
    UInt32 port = pin & 0xFFFF0000;
    
    if(port==GPIO_PORT0)
    {
        if(edge==GPIO_FALLING_EDGE)
        {
            //falling edge
            CLRBIT(LPC_GPIOINT->IO0IntEnF,thepin);
        }
        else //if(edge==GPIO_RISING_EDGE)
        {
            //rising edge
            CLRBIT(LPC_GPIOINT->IO0IntEnR,thepin);
        }
    }
    else if(port==GPIO_PORT2)
    {
        if(edge==GPIO_FALLING_EDGE)
        {
            //falling edge
            CLRBIT(LPC_GPIOINT->IO2IntEnF,thepin);
        }
        else //if(edge==GPIO_RISING_EDGE)
        {
            //rising edge
            CLRBIT(LPC_GPIOINT->IO2IntEnR,thepin);
        }
    }
}
