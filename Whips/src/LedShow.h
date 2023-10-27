#pragma once

/*
 * LedShow is the DOM-side code that drives a show or animation
 * or chase or something pretty on the whips
 */

#if defined(DOM)

#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>

namespace LedShow
{
    void setup();
    void loop();
}

#endif