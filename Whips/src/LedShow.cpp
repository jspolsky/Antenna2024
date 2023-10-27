#include <Arduino.h>
#include <PacketSerial.h>
#include <CRC32.h>

#include "Util.h"
#include "LedShow.h"
#include "Commands.h"

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
        EVERY_N_MILLIS(15)
        {
            static uint8_t hue = 0;
            setWhipColor(255, CHSV(hue, 255, 255));
            hue = (hue + 1) % 256;
        }
    }

    // local utility functions

    void setWhipColor(uint8_t whip, CRGB rgb)
    {
        SETWHIPCOLOR packet;
        memset(&packet, 0, sizeof(packet));
        packet.chCommand = 'c';
        packet.whip = whip;
        packet.rgb = rgb;
        packet.checksum = CRC32::calculate((uint8_t *)&packet, sizeof(packet));
        packetSerial.send((uint8_t *)&packet, sizeof(packet));
    }
}

#endif
