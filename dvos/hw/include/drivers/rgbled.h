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
#ifndef LIB_HW_RGB_LED_H
#define LIB_HW_RGB_LED_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _rgb_led_color_
{
	UInt8   red;
	UInt8   green;
	UInt8   blue;
} RgbLedColor;

typedef enum _rgb_fixed_color_
{
    COLOR_BLACK = 0,
    COLOR_WHITE = 1,
    COLOR_COLDWHITE = 2,
    COLOR_RED = 3,
    COLOR_GREEN = 4,
    COLOR_BLUE = 5,
    COLOR_YELLOW = 6,
    COLOR_FUCHSIA = 7,
    COLOR_CYAN = 8,
    COLOR_ORANGE = 9,
    COLOR_LIME = 10,
    COLOR_PINK = 11,
    COLOR_PURPLE = 12,
    COLOR_TURQUOISE = 13,
    COLOR_AQUA = 14,
    COLOR_GOLD = 15
} RgbLedFixedColor;



extern void initRgbLed(void);


extern void setColorToRgbLed(UInt8 red, UInt8 green, UInt8 blue);


extern void setPredefinedColorToRgbLed(RgbLedFixedColor c);


extern void setRgbLedSequence(UInt32 sequenceNumber, RgbLedFixedColor c, UInt32 time);


extern void startRgbLedSequence(UInt32 number, Bool loop);



#ifdef __cplusplus
 }
#endif

#endif
