#include <Arduino.h>
#include <PacketSerial.h>
#include <CRC16.h>
#include <CRC.h>

#include "Util.h"
#include "LedShow.h"
#include "Commands.h"
#include "Potentiometers.h"

#if defined(DOM)

namespace LedShow
{
    PacketSerial packetSerial;

    void setup()
    {
        dbgprintf("In LedShow.Setup\n");
        Serial1.begin(2000000);
        packetSerial.setStream(&Serial1);
        dbgprintf("...done\n");
    }

    void loop()
    {
        EVERY_N_MILLIS(100)
        {
            static uint8_t hue = 0;

            cmdSetWhipColor packet(1, CHSV(hue, 255, 255));
            SendPacket(&packet, packetSerial);
            hue = (hue + 1) % 256;

            cmdSetBrightness p2(255, Potentiometers::brightness);
            SendPacket(&p2, packetSerial);
        }

        EVERY_N_SECONDS(5)
        {
            cmdPlaySound p1(1, 'A');
            SendPacket(&p1, packetSerial);

            cmdSetVolume pvol(1, Potentiometers::volume);
            SendPacket(&pvol, packetSerial);

            cmdSetWhipColor p2(1, CRGB::White);
            SendPacket(&p2, packetSerial);
        }
    }

}

#endif
