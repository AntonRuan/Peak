#include "HAL/HAL.h"
#include "SPI.h"
#include "SD.h"

static bool g_sd_ready = false;
static uint64_t g_cardSize = 0;

bool HAL::SD_Init()
{
    // pinMode(CONFIG_SD_DET_PIN, INPUT);

    SPIClass* sd_spi = new SPIClass(VSPI); // another SPI
    if (!SD.begin(4, *sd_spi)) // SD-Card SS pin is 15
    {
        Serial.println("Card Mount Failed");
        return false;
    }
    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE)
    {
        Serial.println("No SD card attached");
        return false;
    }

    Serial.print("SD Card Type: ");
    if (cardType == CARD_MMC)
    {
        Serial.println("MMC");
    } else if (cardType == CARD_SD)
    {
        Serial.println("SDSC");
    } else if (cardType == CARD_SDHC)
    {
        Serial.println("SDHC");
    } else
    {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);

    g_sd_ready = true;
    g_cardSize = cardSize;
    return true;
}

bool HAL::SD_GetReady()
{
    return g_sd_ready;//!digitalRead(CONFIG_SD_DET_PIN);
}

float HAL::SD_GetCardSizeMB()
{
    return g_cardSize;
}

static void SD_Check(bool isInsert)
{

}

void HAL::SD_SetEventCallback(SD_CallbackFunction_t callback)
{

}

void HAL::SD_Update()
{

}
