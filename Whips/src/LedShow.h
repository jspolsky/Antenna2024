#pragma once

/*
 * LedShow is the DOM-side code that drives a show or animation
 * or chase or something pretty on the whips
 */

#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>

#if defined(DOM)

namespace LedShow
{
    void setup();
    void loop();

    void setWhipColor(uint8_t whip, CRGB rgb);
}

#endif