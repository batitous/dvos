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


#define PWMREDLED       PWM4
#define PWMGREENLED     PWM2
#define PWMBLUELED      PWM5

#define RGB_LED_SEQUENCE_MAX    16

typedef enum _rgb_led_state_
{
        RGB_LED_STOP = 0,
        RGB_LED_PLAY = 1,
        RGB_LED_PLAY_SEQUENCE = 2
} RgbLedState;

typedef struct _RGBLed_
{
   UInt32 red;
   UInt32 green;
   UInt32 blue;
} RgbLed;

typedef struct __rgb_led_sequence_
{
    RgbLedColor color;
    UInt32      time;
} RGBLedSequence;

const RgbLedColor colors[16] =
{
    { 0,    0,    0   },  //BLACK
    { 100,  100,  100 },  //WHITE
    { 45,  100,  100 },  //COLDWHITE
    { 100,  0,    0   },  //RED
    { 0,    100,  0   },  //GREEN
    { 0,    0,    100 },  //BLUE
    { 100,  100,  0   },  //YELLOW
    { 100,  0,    100 },  //FUCHSIA
    { 0,    100,  100 },  //CYAN
    { 100,  15,   0   },  //ORANGE
    { 15,   100,  0   },  //LIME
    { 100,  0,    15  },  //PINK
    { 15,   0,    100 },  //PURPLE
    { 0,    100,  15  },  //TURQUOISE
    { 0,    15,   100 },  //AQUA
    { 80,  100,  3  }   //GOLD
};

//-------------------------- private variables:

static RgbLed led;
static RgbLedState ledState;

static UInt32 currentSequence;
static UInt32 numberOfSequence;
static Bool loopSequence;
static RGBLedSequence  sequences[RGB_LED_SEQUENCE_MAX];


//-------------------------- private functions:

void setRgbLed(void)
{
    setPwmDutyCycle(PWMREDLED, led.red);
    setPwmDutyCycle(PWMGREENLED, led.green);
    setPwmDutyCycle(PWMBLUELED, led.blue);
}

void threadRgbLed(void)
{
    while(1)
    {
        switch(ledState)
        {
        //--- stop rgb led driver
        case RGB_LED_STOP:
            //todo stop pwm
            
            //just for not consumme cpu
            waitMs(10);
            break;
        case RGB_LED_PLAY:
            
            setRgbLed();
            
            ledState = RGB_LED_STOP;
           break;
        //--- play a rgb led sequence
        case RGB_LED_PLAY_SEQUENCE:
            led.red = sequences[currentSequence].color.red;
            led.green = sequences[currentSequence].color.green;
            led.blue = sequences[currentSequence].color.blue;
                    
            setRgbLed();

            waitMs(sequences[currentSequence].time);

            currentSequence++;
            if( currentSequence == numberOfSequence)
            {
                if(loopSequence==True)
                {
                    currentSequence = 0;
                }
                else
                {
                    ledState = RGB_LED_STOP;
                }
            }
            break;
        }//switch
    }//while
    
}

//-------------------------- public functions:


void initRgbLed(void)
{
    UInt32 i;
   
    initPwm(PWMREDLED|PWMGREENLED|PWMBLUELED, 10000, 0);
    enablePwm(True);
    
    led.red = 0;
    led.green = 0;
    led.blue = 0;
    
    ledState = RGB_LED_STOP;
    loopSequence = False;
    currentSequence = 0;
    numberOfSequence = RGB_LED_SEQUENCE_MAX;
    for(i=0; i < RGB_LED_SEQUENCE_MAX; i++)
    {
        sequences[i].color.blue = colors[i].blue;
        sequences[i].color.red = colors[i].red;
        sequences[i].color.green = colors[i].green;
        
        sequences[i].time = 1000; 
    }
    
    newThread(&threadRgbLed,256,2,2);
}

void setColorToRgbLed(UInt8 red, UInt8 green, UInt8 blue)
{
    led.red = red;
    led.green = green;
    led.blue = blue;
    
    ledState = RGB_LED_PLAY;

    // just for debug !
    setRgbLed();
}

void setPredefinedColorToRgbLed(RgbLedFixedColor c)
{
    RgbLedColor color = colors[c];
    
    led.red = color.red;
    led.green = color.green;
    led.blue = color.blue;
    
    ledState = RGB_LED_PLAY;
    
    // just for debug !
    setRgbLed();
}

void setRgbLedSequence(UInt32 sequenceNumber, RgbLedFixedColor c, UInt32 time)
{
    RgbLedColor color = colors[c];
    
    sequences[sequenceNumber].color = color;
    sequences[sequenceNumber].time = time;
}

void startRgbLedSequence(UInt32 number, Bool loop)
{
    currentSequence = 0;
    numberOfSequence = number;
    loopSequence = loop;
    ledState = RGB_LED_PLAY_SEQUENCE;
}
