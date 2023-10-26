#include <Arduino.h>
#include "Util.h"
#include "Led.h"

namespace Led
{

#ifdef SUB
#define NUM_LEDS 110
#define DATA_PIN 8
    CRGB leds[NUM_LEDS];
#endif

    void setup()
    {
#ifdef SUB
        FastLED.addLeds<WS2812SERIAL, DATA_PIN, BGR>(leds, NUM_LEDS);
#endif
    }

    void loop()
    {
    }

    void showSomeLeds(int cLeds)
    {
#ifdef SUB
        for (int i = 0; i < NUM_LEDS; i++)
        {
            if (i < cLeds % NUM_LEDS)
                leds[i] = CRGB::Red;
            else
                leds[i] = CRGB::Green;
        }
        FastLED.show();
#endif
    }

}