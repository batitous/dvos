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


//----------------------------- get/set/clear pin macro

#ifdef MCU_IS_LPC1311
#       define GPIODIR         gpio->DIR
#       define GPIOGET         gpio->DATA
#       define GPIOSET         SETBIT(gpio->DATA,thepin);
#       define GPIOCLR         CLRBIT(gpio->DATA,thepin);
#       define getGpioPortNumber(pin) 0
#endif

#ifdef MCU_IS_LPC1315
#       define GPIODIR         gpio->DIR[portNumber]
#       define GPIOGET         gpio->PIN[portNumber]
#       define GPIOSET         SETBIT(gpio->SET[portNumber],thepin);
#       define GPIOCLR         SETBIT(gpio->CLR[portNumber],thepin);

static UInt32 getGpioPortNumber(GPIO_PIN pin)
{
    if( (pin & 0xFFFF0000) == GPIO_PORT1)
    {
        return 1;
    }
    
    return 0;
}

#endif


#ifdef MCU_IS_LPC17XX
#       define GPIODIR         gpio->FIODIR
#       define GPIOGET         gpio->FIOPIN
#       define GPIOSET         SETBIT(gpio->FIOSET,thepin);
#       define GPIOCLR         SETBIT(gpio->FIOCLR,thepin);
#       define getGpioPortNumber(pin) 0
#endif

//----------------------------- private functions

LPC_GPIO_TypeDef * getGpioPort(GPIO_PIN pin)
{
    // select io port
    switch(pin & 0xFFFF0000)
    {
        case GPIO_PORT0:
            return LPC_GPIO0;
            break;
        case GPIO_PORT1:
            return LPC_GPIO1;
            break;
            
#ifdef MCU_IS_LPC1311
        case GPIO_PORT2:
            return LPC_GPIO2;
            break;
        case GPIO_PORT3:
            return LPC_GPIO3;
        break;
#endif
        
#ifdef MCU_IS_LPC17XX
        case GPIO_PORT4:
            return LPC_GPIO4;
            break;
#endif
        default:
            return 0;
    }
}

//----------------------------- public functions

void SetGpioDirection(GPIO_PIN pin, GPIO_DIR dir)
{
    LPC_GPIO_TypeDef * gpio = getGpioPort(pin);
    UInt32 portNumber = getGpioPortNumber(pin);
    
    UInt32 thepin = pin & 0xFFFF;
    
    if(gpio==0)
    {
        return;
    }
    
    if(dir==GPIO_OUT)
    {
        SETBIT(GPIODIR,thepin);
    }
    else
    {
        CLRBIT(GPIODIR,thepin);
    }
    
#ifdef MCU_IS_LPC1311
    //set the fucking FUNC to 1 in SWCLK pin
    if(pin == GPIO0_10)
    {
        SETBIT(LPC_IOCON->SWCLK_PIO0_10,0);
    }
    else if(pin == GPIO0_0)
    {
        SETBIT(LPC_IOCON->RESET_PIO0_0,0);
    }
    else if(pin == GPIO0_11)
    {
        SETBIT(LPC_IOCON->R_PIO0_11,0);
    }
    else if(pin == GPIO1_3)
    {
        SETBIT(LPC_IOCON->SWDIO_PIO1_3,0);
    }
    else if(pin == GPIO1_0)
    {
        SETBIT(LPC_IOCON->R_PIO1_0,0);
    }
    else if(pin == GPIO1_1)
    {
        SETBIT(LPC_IOCON->R_PIO1_1,0);
    }
    else if(pin == GPIO1_2)
    {
        SETBIT(LPC_IOCON->R_PIO1_2,0);
    }
#endif
    
#ifdef MCU_IS_LPC1315
    if(pin == GPIO0_10)
    {
        SETBIT(LPC_IOCON->SWCLK_PIO0_10,0);
    }
    else if(pin == GPIO0_11)
    {
        SETBIT(LPC_IOCON->TDI_PIO0_11,0);
    }
    else if(pin == GPIO0_15)
    {
        SETBIT(LPC_IOCON->SWDIO_PIO0_15,0);
    }
    else if(pin == GPIO0_12)
    {
        SETBIT(LPC_IOCON->TMS_PIO0_12,0);
    }
    else if(pin == GPIO0_13)
    {
        SETBIT(LPC_IOCON->TDO_PIO0_13,0);
    }
    else if(pin == GPIO0_14)
    {
        SETBIT(LPC_IOCON->TRST_PIO0_14,0);
    }
    
#endif
       
#ifdef MCU_IS_LPC17XX

#endif
}

void SetGpioValue(GPIO_PIN pin, UInt32 bit)
{
    LPC_GPIO_TypeDef * gpio = getGpioPort(pin);
    UInt32 portNumber = getGpioPortNumber(pin);
    
    UInt32 thepin = pin & 0xFFFF;
    
    if(gpio==0)
    {
        return;
    }
    
    if(bit!=0)
    {
        GPIOSET
    }
    else
    {
        GPIOCLR
    }
}

UInt32 GetGpioValue(GPIO_PIN pin)
{
    LPC_GPIO_TypeDef * gpio = getGpioPort(pin);
    UInt32 portNumber = getGpioPortNumber(pin);
    
    UInt32 thepin = pin & 0xFFFF;
    
    if(gpio==0)
    {
        return 0;
    }
    
    return (GPIOGET >> thepin) & 0x1;
}

