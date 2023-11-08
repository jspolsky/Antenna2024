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

            cmdSetWhipColor packet(1, CHSV(hue, 255, 255));
            SendPacket(&packet, packetSerial);
            hue = (hue + 1) % 256;
        }

        EVERY_N_SECONDS(10)
        {
            static uint8_t static_volume = 32;
            cmdSetVolume pvol(1, static_volume);
            SendPacket(&pvol, packetSerial);
            static_volume = (static_volume + 32) % 256;

            cmdPlaySound packet(1, 'A');
            SendPacket(&packet, packetSerial);
        }
    }

}

#endif
