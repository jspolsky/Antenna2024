#include <Arduino.h>
#include <PacketSerial.h>
#include "Util.h"
#include "Led.h"

#if defined(SUB)
namespace Led
{

#define NUM_LEDS 110
#define DATA_PIN 8
    CRGB leds[NUM_LEDS];

    PacketSerial packetSerial;

    void setup()
    {
        Serial1.begin(2000000);
        packetSerial.setStream(&Serial1);
        packetSerial.setPacketHandler(&onPacketReceived);

        FastLED.addLeds<WS2812SERIAL, DATA_PIN, BGR>(leds, NUM_LEDS);
    }

    void loop()
    {
        packetSerial.update();
    }

    void onPacketReceived(const uint8_t *buffer, size_t size)
    {
        dbgprintf("Packet received size %d\n", size);
        if (size == 6 && buffer[0] == 32 && buffer[1] == 'c')
        {
            // CRGB rgb(buffer[2], buffer[3], buffer[4]);
            // for (int i = 0; i < NUM_LEDS; i++)
            //     leds[i] = rgb;

            for (int i = 0; i < NUM_LEDS; i++)
            {
                if (i < buffer[2])
                    leds[i] = CRGB::Red;
                else
                    leds[i] = CRGB::Blue;
            }
            FastLED.show();
        }
    }
}
#endif
