#include <Arduino.h>

#include "Util.h"
#include "pins.h"
#include "Potentiometers.h"

#if defined(DOM)

namespace Potentiometers
{
    uint8_t brightness, volume;

    void setup()
    {
        pinMode(pinBrightness, INPUT);
        pinMode(pinVolume, INPUT);
    }

    void loop()
    {
        EVERY_N_MILLIS(100)
        {
            brightness = max(0, min(255, analogRead(pinBrightness) / 4));
            volume = max(0, min(255, analogRead(pinVolume) / 4));
        }
    }

}
#endif
