#pragma once

/*
 * IR receiver, used only on DOM for misc. controls
 */

#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>

namespace IR
{
    void setup();
    void loop();
}
