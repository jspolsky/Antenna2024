#include <Arduino.h>
#include <PacketSerial.h>
#include <CRC16.h>
#include <CRC.h>

#include "pins.h"
#include "Util.h"
#include "Led.h"
#include "Commands.h"
#include "DipSwitch.h"
#include "Gif.h"

namespace Led
{

    CRGB leds[NUM_LEDS];

    PacketSerial packetSerial;

    void setup()
    {
        Serial1.begin(2000000);
        packetSerial.setStream(&Serial1);
        packetSerial.setPacketHandler(&onPacketReceived);

        FastLED.addLeds<WS2812SERIAL, pinLEDStrip, BGR>(leds, NUM_LEDS);
        FastLED.setBrightness(64);

        pinMode(pinLEDRxIndicator, OUTPUT);
    }

    void loop()
    {
        packetSerial.update();

        EVERY_N_MILLIS(1000)
        {
            digitalWriteFast(pinLEDRxIndicator, LOW);
        }
    }

    void onPacketReceived(const uint8_t *buffer, size_t size)
    {
        if (size < sizeof(cmdUnknown))
        {
            // impossible packet doesn't even have room for checksum and command
            return;
        }

        cmdUnknown *punk = (cmdUnknown *)buffer;

        uint16_t checksum = punk->checksum;
        punk->checksum = 0; // when packet checksum was calculated, these 2 bytes were 0

        if (checksum != calcCRC16(buffer, size))
        {
            // packet garbled
            dbgprintf("garbled packet. Size was %d\n", size);
            return;
        }

        digitalWriteFast(pinLEDRxIndicator, HIGH);

        if (punk->whip != DipSwitch::getWhipNumber() && punk->whip != 255)
        {
            // not a message for us
            return;
        }

        switch (punk->chCommand)
        {
        case 'c':
        {
            cmdSetWhipColor *pSetWhipColor = (cmdSetWhipColor *)buffer;
            FastLED.showColor(pSetWhipColor->rgb);
        }
        break;

        case 'b':
        {

            cmdSetBrightness *pSetBrightness = (cmdSetBrightness *)buffer;
            FastLED.setBrightness(pSetBrightness->brightness);
        }
        break;

        case 'g':
        {
            static uint16_t iGifLoaded = 0;

            cmdShowGIFFrame *pShowGIFFrame = (cmdShowGIFFrame *)buffer;

            if (iGifLoaded != pShowGIFFrame->iGifNumber)
            {
                Gif::LoadGif(iGifLoaded = pShowGIFFrame->iGifNumber);
                dbgprintf("Loading gif number %d\n", pShowGIFFrame->iGifNumber);
            }
            Gif::GetFrame(pShowGIFFrame->frame, leds);
            FastLED.show();
            break;
        }
        }
    }
}
