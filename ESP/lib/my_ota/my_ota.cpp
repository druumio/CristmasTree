#include "my_ota.h"

/**
 * @brief Set up Over-The-Air (OTA) updates.
 *
 * @details This function sets up the OTA library to handle OTA updates
 *          of the device. The update process is handled asynchronously
 *          and the function returns immediately after setup is complete.
 *
 * @returns 0 on success, 23 on error (not implemented yet).
 */
int setupOta()
{
    ArduinoOTA
        .onStart([]()
                {
                String type;
                if (ArduinoOTA.getCommand() == U_FLASH)
                    type = "sketch";
                else // U_SPIFFS
                    type = "filesystem";
                })
        .onEnd([](){ ; })
        .onProgress([](unsigned int progress, unsigned int total){ ; })
        .onError([](ota_error_t error){ return 23; });
    ArduinoOTA.begin();
    return 0;
}
