// ESP and Arduino libraries
#include <Arduino.h>
#include <EEPROM.h>
// External libraries
#include <FastLED.h>
// My libraries
#include "my_ota.h"
#include "coms.h"
#include "led_lib.h"

// GPIO pins
#define LED_BUILDIN GPIO_NUM_2

// Global variables
#define EEPROM_SIZE 512
uint32_t millisCounter = 0;
uint32_t lastMillis = 0;

// Functions

void setup()
{
  // Setup for GPIO pins
  gpio_set_direction(LED_BUILDIN, GPIO_MODE_OUTPUT);

  // Setup EEPROM
  //! IMPORTANT init EEPROM before calling WiFi_setup
  EEPROM.begin(EEPROM_SIZE);

  // Setup for WiFi and !TODO BLE
  if (!WifiSetup())
  {
    delay(5000);
    ESP.restart();
  }

  // Setup FastLED
  setupFastLED();

  // Setup OTA
  setupOta();

  lastMillis = millis();
}

void loop()
{
  uint32_t currentMillis = millis();

  // OTA
  ArduinoOTA.handle();

  ///! @todo State machine
  // Update LED-strip pattern
  updateLEDs(millisCounter);
  //flashBang(); ///! @warning

  // ms counter
  if (currentMillis - lastMillis >= 1)
  {
    millisCounter++;
    lastMillis = currentMillis;
  }
}
