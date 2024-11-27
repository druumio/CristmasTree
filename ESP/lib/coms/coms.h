#ifndef COMS_H
#define COMS_H

#include <WiFi.h>
#include <EEPROM.h>

// wifi
extern const char*  ssid;
extern const char*  password;

bool WifiSetup(void);
void writeEEPROM(String,String);
void readEEPROM(void);

#endif // COMS_H