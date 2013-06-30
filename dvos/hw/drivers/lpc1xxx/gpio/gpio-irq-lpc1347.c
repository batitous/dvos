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

extern LPC_GPIO_TypeDef * getGpioPort(GPIO_PIN pin);
extern UInt32 getGpioPortNumber(GPIO_PIN pin);

//----------------------------- private object

#define PIN_IRQ_MAX     8

void defaultIrqCallback();

static GpioIrqCallback gpioIrqCallback = defaultIrqCallback;
static UInt32 pinIrqFree = 0;
static GPIO_PIN pinIrq[PIN_IRQ_MAX];


//----------------------------- private functions

static UInt32 getIndexFromGpio(GPIO_PIN pin)
{
    UInt32 i;
    
    for (i=0;i<PIN_IRQ_MAX;i++)
    {
        if (pinIrq[i]==pin)
        {
            return i;
        }
    }
    
    // this function never fail...
    return 0;
}

void defaultIrqCallback(UInt32 gpioIrqEvent, UInt32 gpioIrqEdge)
{
    gpioIrqEvent = 0;
    gpioIrqEdge = 0;
}

void PIN_IRQ_Handler(UInt32 irqSlot)
{
    UInt32 edge = 0;
    GPIO_PIN pin = pinIrq[irqSlot];
    
    if ( ((LPC_GPIO_PIN_INT->RISE>>irqSlot) & 0x1)!=0 )
    {
        edge = GPIO_RISING_EDGE;
    }
    else if ( ((LPC_GPIO_PIN_INT->FALL>>irqSlot) & 0x1)!=0 )
    {
        edge = GPIO_FALLING_EDGE;
    }
    
    gpioIrqCallback(pin,edge);
    
    
    // clear falling/rising detection for this pin
    SETBIT(LPC_GPIO_PIN_INT->IST,irqSlot);
}

void PIN_INT0_IRQHandler(void)
{
    PIN_IRQ_Handler(0);
}

void PIN_INT1_IRQHandler(void)
{
    PIN_IRQ_Handler(1);
}

void PIN_INT2_IRQHandler(void)
{
    PIN_IRQ_Handler(2);
}

void PIN_INT3_IRQHandler(void)
{
    PIN_IRQ_Handler(3);
}

void PIN_INT4_IRQHandler(void)
{
    PIN_IRQ_Handler(4);
}

void PIN_INT5_IRQHandler(void)
{
    PIN_IRQ_Handler(5);
}

void PIN_INT6_IRQHandler(void)
{
    PIN_IRQ_Handler(6);
}

void PIN_INT7_IRQHandler(void)
{
    PIN_IRQ_Handler(7);
}


//----------------------------- public functions

void setGpioIrqCallback(GpioIrqCallback callback)
{
    gpioIrqCallback = callback;
}


void enableGpioIrq(GPIO_PIN pin, GPIO_EDGE edge)
{
    UInt32 thepin = pin & 0xFFFF;
    UInt32 portNumber = getGpioPortNumber(pin);
    
    if (pinIrqFree>=PIN_IRQ_MAX)
    {
        return;
    }
    
    if (portNumber==1)
    {
        // datasheet dit de mettre +24, mais l'exemple du datasheet ne donne pas ca... wtf ???
        thepin = 24 + thepin;
    }
    
    // set port number and pin number in the pin interrupt selector
    LPC_SYSCON->PINTSEL[pinIrqFree] = BITS(5,portNumber) | thepin;
    
    
    // select gpio irq as edge sensitive
    CLRBIT(LPC_GPIO_PIN_INT->ISEL,pinIrqFree);
    
    if (edge==GPIO_BOTH_EDGE)
    {
        // todo dont work ?
        // test : can't see the falling/rising edge in irq
        SETBIT(LPC_GPIO_PIN_INT->IENR,pinIrqFree);
        SETBIT(LPC_GPIO_PIN_INT->IENF,pinIrqFree);
    }
    else
    {
        if (edge==GPIO_FALLING_EDGE)
        {
            SETBIT(LPC_GPIO_PIN_INT->IENF,pinIrqFree);
        }
        else
        {
            SETBIT(LPC_GPIO_PIN_INT->IENR,pinIrqFree);
        }
    }
    
    // save the user gpio pin
    pinIrq[pinIrqFree] = pin;
    
    // enable interrupt
    switch (pinIrqFree)
    {
        case 0:
            NVIC_EnableIRQ(FLEX_INT0_IRQn);
            break;
        case 1:
            NVIC_EnableIRQ(FLEX_INT1_IRQn);
            break;
        case 2:
            NVIC_EnableIRQ(FLEX_INT2_IRQn);
            break;
        case 3:
            NVIC_EnableIRQ(FLEX_INT3_IRQn);
            break;
        case 4:
            NVIC_EnableIRQ(FLEX_INT4_IRQn);
            break;
        case 5:
            NVIC_EnableIRQ(FLEX_INT5_IRQn);
            break;
        case 6:
            NVIC_EnableIRQ(FLEX_INT6_IRQn);
            break;
        case 7:
            NVIC_EnableIRQ(FLEX_INT7_IRQn);
            break;
    }
    
    pinIrqFree++;
}

void disableGpioIrq(GPIO_PIN pin)
{
    UInt32 irqIndex = getIndexFromGpio(pin);
    
    SETBIT(LPC_GPIO_PIN_INT->CIENF, irqIndex);
    SETBIT(LPC_GPIO_PIN_INT->CIENR, irqIndex);
    
}

