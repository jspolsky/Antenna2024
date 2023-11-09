#pragma once

/*
 * volume and brightness pots on DOM
 */

#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>

#if defined(DOM)
namespace Potentiometers
{
    extern uint8_t brightness, volume;

    void setup();
    void loop();
}
#endif
