#include "HAL/HAL.h"
#include "App/Configs/Version.h"

void HAL::Init()
{
    Serial.println(VERSION_FIRMWARE_NAME);
    Serial.println("Version: " VERSION_SOFTWARE);
    Serial.println("Author: " VERSION_AUTHOR_NAME);

    HAL::BT_Init(); // ToDo: some of the process below will interrupt BLE connection, find it out
    HAL::Power_Init();
    HAL::Backlight_Init();
    HAL::Encoder_Init();
    HAL::Buzz_init();
    HAL::Audio_Init();
    HAL::SD_Init();
    // HAL::I2C_Init(true);
    HAL::IMU_Init();

    HAL::Audio_PlayMusic("Startup");
}

void HAL::Update()
{
    HAL::Power_Update();
    HAL::Encoder_Update();
    HAL::Audio_Update();
    HAL::IMU_Update();
    HAL::BT_Update();
    __IntervalExecute(HAL::SD_Update(), 500);
}
