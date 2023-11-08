#include <Arduino.h>
#include <PacketSerial.h>
#include <CRC16.h>
#include <CRC.h>

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
            setWhipColor(1, CHSV(hue, 255, 255));
            hue = (hue + 1) % 256;
        }

        EVERY_N_SECONDS(10)
        {
            static uint8_t static_volume = 32;
            cmdSetVolume pvol;
            memset(&pvol, 0, sizeof(pvol));
            pvol.chCommand = 'v';
            pvol.whip = 1;
            pvol.volume = static_volume;
            pvol.checksum = calcCRC16((uint8_t *)&pvol, sizeof(pvol));
            packetSerial.send((uint8_t *)&pvol, sizeof(pvol));
            static_volume = (static_volume + 32) % 256;

            cmdPlaySound packet;
            memset(&packet, 0, sizeof(packet));
            packet.chCommand = 's';
            packet.whip = 1;
            packet.chSoundName = 'A';
            packet.checksum = calcCRC16((uint8_t *)&packet, sizeof(packet));
            packetSerial.send((uint8_t *)&packet, sizeof(packet));
        }
    }

    // local utility functions

    void setWhipColor(uint8_t whip, CRGB rgb)
    {
        cmdSetWhipColor packet;
        memset(&packet, 0, sizeof(packet));
        packet.chCommand = 'c';
        packet.whip = whip;
        packet.rgb = rgb;
        packet.checksum = calcCRC16((uint8_t *)&packet, sizeof(packet));
        packetSerial.send((uint8_t *)&packet, sizeof(packet));
    }
}

#endif
