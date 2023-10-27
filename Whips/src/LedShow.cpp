#ifdef DOM

#include <Arduino.h>
#include "Util.h"
#include "LedShow.h"

namespace LedShow
{
    void setup()
    {
        Serial1.begin(2000000);
    }

    void loop()
    {
        EVERY_N_MILLIS(1000)
        {
            Serial1.println("showit!");
            dbgprintf("time: %d\n", millis());
        }
    }
}

#endif
