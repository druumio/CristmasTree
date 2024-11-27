#ifndef LED_LIB_H
#define LED_LIB_H

#include <Arduino.h>
#include <FastLED.h>

#define LED_STRIP GPIO_NUM_15
#define LED_POWER GPIO_NUM_4
#define NUM_LEDS uint8_t(100)
#define LED_TYPE WS2812B

extern CRGB leds[];
extern uint8_t brightness;
extern uint16_t speed;

void setupFastLED(void);
int random255(void);
void resetLED(void);
int turnLedOff(uint8_t);
void updateLEDs(uint32_t);

void loop5leds(void);
void scrollHue(void);
void scrollHue2(void);
void flashRandomRGB(void);
void flashRandomHSV(void);

void flashBang(void);

#endif // LED_LIB_H