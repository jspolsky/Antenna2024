#pragma once

#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>

namespace Led
{
    void setup();
    void loop();
    void showSomeLeds(int cLeds);
}