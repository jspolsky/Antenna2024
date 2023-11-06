#include <Arduino.h>
#include <PacketSerial.h>
#include <CRC32.h>

#include "pins.h"
#include "Util.h"
#include "Led.h"
#include "Commands.h"
#include "DipSwitch.h"

#if defined(SUB)
namespace Led
{

#define NUM_LEDS 110

    CRGB leds[NUM_LEDS];

    PacketSerial packetSerial;

    void setup()
    {
        Serial1.begin(2000000);
        packetSerial.setStream(&Serial1);
        packetSerial.setPacketHandler(&onPacketReceived);

        FastLED.addLeds<WS2812SERIAL, pinLEDStrip, BGR>(leds, NUM_LEDS);
    }

    void loop()
    {
        packetSerial.update();
    }

    void onPacketReceived(const uint8_t *buffer, size_t size)
    {
        if (size < sizeof(UNKNOWNCOMMAND))
        {
            // impossible packet doesn't even have room for checksum and command
            return;
        }

        UNKNOWNCOMMAND *punk = (UNKNOWNCOMMAND *)buffer;

        uint32_t checksum = punk->checksum;
        punk->checksum = 0; // when packet checksum was calculated, first 4 bytes were 0

        if (checksum != CRC32::calculate(buffer, size))
        {
            // packet garbled
            return;
        }

        if (punk->whip != DipSwitch::getWhipNumber() && punk->whip != 255)
        {
            // not a message for us
            return;
        }

        if (punk->chCommand == 'c')
        {
            SETWHIPCOLOR *pSetWhipColor = (SETWHIPCOLOR *)buffer;
            FastLED.showColor(pSetWhipColor->rgb);
        }
    }
}
#endif
