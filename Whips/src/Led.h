#pragma once

/*
 * Led is the SUB-side code that receives commands from
 * DOM over serial and actually controls one whip's LEDs.
 */

#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>

#ifdef SUB
namespace Led
{
    void setup();
    void loop();
    void showSomeLeds(int cLeds);
}
#endif
