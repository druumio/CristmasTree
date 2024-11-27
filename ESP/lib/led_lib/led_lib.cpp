#include "led_lib.h"

CRGB leds[NUM_LEDS];
uint8_t brightness = 150;
uint16_t speed = 250;

/**
 * @brief Initialize the FastLED library.
 *
 * @details This function sets up the GPIO outputs for the LED strip and
 *          the LED power pin. It also initializes the FastLED library
 *          with the correct LED type and count.
 */
void setupFastLED(void)
{
    // Setup for GPIO pins
    gpio_set_direction(LED_STRIP, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_POWER, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_POWER, HIGH);

    // Setup FastLED
    FastLED.addLeds<LED_TYPE, LED_STRIP>(leds, NUM_LEDS);

    resetLED();
}

/**
 * @brief Returns a random number between 0 and 255.
 *
 * @details This function uses the standard library's `rand()` function to
 *          generate a random number. The result is then truncated to the
 *          range 0 to 255 with the modulo operator.
 *
 * @returns A random number between 0 and 255.
 */
int random255(void)
{
    return rand() % 256;
}

/**
 * @brief Resets the LED strip to a blank state.
 * 
 * @details This function sets the LED strip brightness to the default value
 *          and turns all LEDs off.
 */
void resetLED(void)
{
    FastLED.setBrightness(brightness);
    FastLED.clear();
    FastLED.show();
    delay(25);
}

/**
 * @brief Returns the index of the LED that should be turned off.
 * 
 * @param led The index of the LED that should be turned on.
 * 
 * @returns The index of the LED that should be turned off.
 */
int turnLedOff(uint8_t led)
{
    if (led - 5 < 0)
    {
        return NUM_LEDS + (led - 5);
    }
    else
    {
        return led - 5;
    }
}

/**
 * @brief Updates the LED strip to a new state.
 * 
 * @details This function updates the LED strip to a new state at a rate
 *          determined by the speed global variable. The state of the LED
 *          strip is determined by the currently selected pattern.
 * 
 * @param millisCounter The current time in milliseconds.
 * 
 * @todo Swich/case
 *          - button
 *          - BLE
 *       global speed to variable speed
 *          - external pot
 *          - BLE
 */
void updateLEDs(uint32_t millisCounter)
{
    if (millisCounter % speed == 0)
    {
        scrollHue2();
        // loop5leds();
        // flashRandomRGB();
        FastLED.show();
    }
}

/**
 * @brief Updates the LED strip with a looping pattern of 5 LEDs.
 * 
 * @details This function updates the LED strip with a pattern of 5 LEDs
 *          that move around the strip. Each LED is set to scroll trough
 *          the rainbow colors. The first LED is set to a random hue
 *          and the last LED is set to black. The position of the
 *          current LED is stored in a static variable and updated each
 *          time the function is called.
 */
void loop5leds(void)
{
    static uint8_t current_led = 0;
    static uint8_t usrHue = random255();

    leds[current_led].setHue(usrHue);
    leds[turnLedOff(current_led)] = CRGB::Black;
    current_led = (current_led + 1) % NUM_LEDS;
    usrHue = (usrHue + 1) % 256;
}

/**
 * @brief Flashes all LEDs in the strip with a random RGB color.
 *
 * @details This function iterates over each LED in the strip and sets
 *          it to a random RGB color.
 */
void flashRandomRGB(void)
{
    for (uint8_t led = 0; led < NUM_LEDS; led++)
    {
        uint8_t r = random255();
        uint8_t g = random255();
        uint8_t b = random255();
        leds[led].setRGB(r, g, b);
    }
}

/**
 * @brief Flashes all LEDs in the strip with a random HSV color.
 *
 * @details This function iterates over each LED in the strip and sets
 *          it to a random HSV color. The hue is a random number between
 *          0 and 255, the saturation is a random number between 0 and
 *          255, and the value is a random number between 150 and 255.
 */

void flashRandomHSV(void)
{
    for (int led = 0; led < NUM_LEDS; led++)
    {
        uint8_t h = random255();
        uint8_t s = random255();
        uint8_t v = random(150, 256);
        leds[led].setHSV(h, s, v);
    }
}

/**
 * @brief Scrolls the hue of the LED strip.
 * 
 * @details This function updates the LED strip with a scrolling pattern
 *          of the hue. Each LED is set to the same hue and the hue
 *          is incremented each time the function is called.
 */
void scrollHue(void)
{
    static uint8_t usrHue = random255();

    for (uint8_t led = 0; led < NUM_LEDS; led++)
    {
        leds[led].setHue(usrHue);
    }

    usrHue = (usrHue + 1) % 256;
}

 
/**
 * @brief Scrolls through hues across the LED strip.
 * 
 * @details This function updates each LED with a hue that shifts along
 *          the strip, creating a gradient effect. The starting hue is 
 *          incremented each time the function is called, causing the 
 *          gradient to scroll over time down the christmas tree.
 * 
 *          Personal favourite pattern.
 */
void scrollHue2(void)
{
    static uint8_t usrHue = 0;
    uint8_t RunningHue;

    RunningHue = usrHue;

    for (uint8_t led = 0; led < NUM_LEDS; led++)
    {
        leds[led].setHue(RunningHue);
        RunningHue = (usrHue + led) % 256;
    }

    usrHue = (usrHue + 1) % 256;
}

/**
 * @brief Flashes all LEDs in the strip with white color.
 * 
 * @details This function iterates over each LED in the strip and sets
 *          it to white color.
 * 
 * @warning This is demonstrative code that I made to show underclassman why calculating 
 *          power consumption is important.
 *          In current setup first few leds are not lit white and later leds slowly fade to 
 *          yellow. While whole led strip stutters on and off.
 */
void flashBang(void)
{
    static bool once = false;

    if (!once)
    {
        FastLED.setBrightness(255);
        for (uint8_t led = 0; led < NUM_LEDS; led++)
        {
            leds[led].setRGB(255, 255, 255);
        }
        once = true;
        FastLED.show();
    }
    delay(1000);
}