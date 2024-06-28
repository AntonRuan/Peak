#include <Arduino.h>
#include <M5Stack.h>
#include "HAL/HAL.h"
#include "Port/Display.h"
#include "App/App.h"

void setup()
{
    M5.begin(true, false);
    M5.Power.begin();

    HAL::Init();
    Port_Init();
    App_Init();
}

void loop()
{
    HAL::Update();

    delay(20);
}