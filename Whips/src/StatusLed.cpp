#include <Arduino.h>

#include "pins.h"
#include "Util.h"
#include "StatusLed.h"

#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h> /* herein used for macros like EVERY_N_MILLIS only */

namespace StatusLed
{
    void setup()
    {
        pinMode(pinStatus, OUTPUT);
    }

    void loop()
    {
        static bool fStatusLED = false;

        EVERY_N_MILLIS(250)
        {
            fStatusLED = !fStatusLED;
            digitalWrite(pinStatus, fStatusLED ? HIGH : LOW);
        }
    }
}
