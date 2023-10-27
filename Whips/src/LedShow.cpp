#include <Arduino.h>
#include <PacketSerial.h>
#include "Util.h"
#include "LedShow.h"

#if defined(DOM)

namespace LedShow
{
    PacketSerial packetSerial;

    void setup()
    {
        Serial1.begin(2000000);
        packetSerial.setStream(&Serial1);
    }

    void loop()
    {
        EVERY_N_MILLIS(50)
        {
            static uint8_t hue = 0;
            setWhipColor(32, CHSV(hue, 255, 255));
            hue = (hue + 1) % 256;
            dbgprintf("time: %d\n", millis());
        }
    }

    // local utility functions

    void setWhipColor(uint8_t whip, CRGB rgb)
    {
        uint8_t packet[6];

        packet[0] = whip;
        packet[1] = 'c';
        packet[2] = rgb.red;
        packet[3] = rgb.green;
        packet[4] = rgb.blue;
        packet[5] = '\n';

        packetSerial.send(packet, 6);
    }
}

#endif
