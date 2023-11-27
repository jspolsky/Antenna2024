#include <Arduino.h>

#include "Util.h"
#include "DipSwitch.h"

uint8_t whip;

namespace DipSwitch
{
    void setup()
    {
        pinMode(2, INPUT_PULLUP);
        pinMode(3, INPUT_PULLUP);
        pinMode(4, INPUT_PULLUP);
        pinMode(5, INPUT_PULLUP);
        pinMode(6, INPUT_PULLUP);

        readWhipNumber();
    }

    void loop()
    {
        EVERY_N_MILLIS(1000)
        {
            readWhipNumber();
        }
    }

    uint8_t getWhipNumber()
    {
        return whip;
    }

    void readWhipNumber()
    {
        whip = (digitalReadFast(2) == HIGH ? 0 : 16) +
               (digitalReadFast(3) == HIGH ? 0 : 8) +
               (digitalReadFast(4) == HIGH ? 0 : 4) +
               (digitalReadFast(5) == HIGH ? 0 : 2) +
               (digitalReadFast(6) == HIGH ? 0 : 1);
    }
}
