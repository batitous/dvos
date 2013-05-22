
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



extern void InitRgbLed(void);


extern void SetColorToRgbLed(UInt8 red, UInt8 green, UInt8 blue);


extern void SetPredefinedColorToRgbLed(RgbLedFixedColor c);


extern void SetRgbLedSequence(UInt32 sequenceNumber, RgbLedFixedColor c, UInt32 time);


extern void StartRgbLedSequence(UInt32 number, Bool loop);



#ifdef __cplusplus
 }
#endif

#endif
