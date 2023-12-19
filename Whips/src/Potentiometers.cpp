#include <Arduino.h>

#include "Util.h"
#include "pins.h"
#include "Potentiometers.h"

namespace Potentiometers
{
    uint8_t brightness, volume;

    void setup()
    {
        dbgprintf("Potentiometers.setup\n");
        pinMode(pinBrightness, INPUT);
    }

    void loop()
    {
        EVERY_N_MILLIS(100)
        {
            brightness = max(0, min(255, analogRead(pinBrightness) / 4));
        }
    }

}
