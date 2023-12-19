#include <Arduino.h>
#include <PacketSerial.h>
#include <CRC16.h>
#include <CRC.h>

#include "Util.h"
#include "LedShow.h"
#include "Commands.h"
#include "Potentiometers.h"

namespace LedShow
{
    PacketSerial packetSerial;

    void setup()
    {
        dbgprintf("In LedShow.Setup\n");
        Serial1.begin(2000000);
        packetSerial.setStream(&Serial1);
        dbgprintf("...done\n");

        // TESTING GIF ANIMATIONS
        cmdLoadGIF p1(255, 1);
        SendPacket(&p1, packetSerial);
    }

    void loop()
    {
        // UNDONE
        // This is refreshing every 40 milliseconds
        // Different GIFs actually have different animation times
        // Need to load the gif ourselves to figure it out!

        EVERY_N_MILLIS(40)
        {
            static cmdShowGIFFrame p3(255, 0);
            static uint32_t frame = 0;
            p3.frame = frame++;
            SendPacket(&p3, packetSerial);
        }

        EVERY_N_MILLIS(100)
        {
            cmdSetBrightness p2(255, Potentiometers::brightness);
            SendPacket(&p2, packetSerial);
        }
    }

}
