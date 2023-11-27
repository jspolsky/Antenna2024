#pragma once

/*
 * DIP Switch used to set the address of any SUB board
 */

#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>

namespace DipSwitch
{
    void setup();
    void loop();
    uint8_t getWhipNumber();

    void readWhipNumber();
}
