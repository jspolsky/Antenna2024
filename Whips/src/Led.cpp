#include <Arduino.h>
#include "Util.h"
#include "Led.h"

#if defined(SUB)
namespace Led
{

#define NUM_LEDS 110
#define DATA_PIN 8
    CRGB leds[NUM_LEDS];

    void setup()
    {
        Serial1.begin(2000000);
        FastLED.addLeds<WS2812SERIAL, DATA_PIN, BGR>(leds, NUM_LEDS);
    }

    void loop()
    {
        static uint32_t cLeds = 0;

        while (Serial1.available())
        {
            dbgprintf("%c", Serial1.read());
            Led::showSomeLeds(cLeds);
            cLeds++;
        }
    }

    void showSomeLeds(int cLeds)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            if (i < cLeds % NUM_LEDS)
                leds[i] = CRGB::Red;
            else
                leds[i] = CRGB::Green;
        }
        FastLED.show();
    }
}
#endif
