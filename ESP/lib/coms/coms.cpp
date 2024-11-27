#include "coms.h"

const char*  ssid;
const char*  password;

/**
 * @brief Tries to connect to the WiFi network stored in EEPROM.
 *
 * @details This function reads the WiFi network credentials from EEPROM and
 *          attempts to connect to the network. If the connection fails, it
 *          returns false. Otherwise it returns true.
 *
 * @returns true if the connection is successful, false otherwise.
 * 
 * @todo Add error handling
 *       return type -> int
 */
bool WifiSetup()
{
  readEEPROM();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    return false;
  }
  return true;
}

/**
 * @brief Writes the WiFi network credentials to EEPROM.
 *
 * @details This function writes the WiFi network credentials to EEPROM. The
 *          credentials are stored in the format "ssid\0password\0", where \0
 *          is the NULL character.
 *
 * @param newSsid The new ssid to write to EEPROM.
 * @param newPassword The new password to write to EEPROM.
 */
void writeEEPROM(String newSsid, String newPassword)
{
  for (int i = 0; i < newSsid.length(); ++i)
  {
    EEPROM.write(i, newSsid[i]);
  }

  // write the termination character
  // "i + 1"
  EEPROM.write(newSsid.length(), '\0');

  for (int i = 0; i < newPassword.length(); ++i)
  {
    EEPROM.write(i + 1 + newSsid.length(), newPassword[i]);
  }

  // write the termination character
  EEPROM.write(newSsid.length() + 1 + newPassword.length(), '\0');

  EEPROM.commit();
}

/**
 * @brief Reads the WiFi network credentials from EEPROM.
 *
 * @details This function reads the WiFi network credentials from EEPROM and
 *          stores them in the global variables ssid and password. The
 *          credentials are stored in the format "ssid\0password\0", where \0
 *          is the NULL character.
 */
void readEEPROM()
{
  char readChar;
  int i = 0;

  while (readChar != '\0')
  {
    readChar = EEPROM.read(i);
    i++;
    delay(10);

    if (readChar != '\0')
    {
      ssid += readChar;
    }
  }
  readChar = EEPROM.read(i);

  while (readChar != '\0')
  {
    readChar = EEPROM.read(i);
    i++;
    delay(10);

    if (readChar != '\0')
    {
      password += readChar;
    }
  }
}