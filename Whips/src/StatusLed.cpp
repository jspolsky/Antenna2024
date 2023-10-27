#include <Arduino.h>
#include "Util.h"
#include "StatusLed.h"

#include <FastLED.h> /* herein used for macros like EVERY_N_MILLIS only */

namespace StatusLed
{
    const uint8_t pinStatus = LED_BUILTIN;

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
            digitalWrite(LED_BUILTIN, fStatusLED ? HIGH : LOW);
        }
    }
}
