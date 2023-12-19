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
    }

    // if ixCommand == 1, load next Gif
    void loop(int ixCommand)
    {
        static int ixGif = 1;
        if (ixCommand == 1)
        {
            ixGif++;
            if (ixGif > 12) // UNDONE - just do this if loading the gif fails
                ixGif = 1;
            dbgprintf("new gif number %d\n", ixGif);
        }

        // UNDONE
        // This is refreshing every 40 milliseconds
        // Different GIFs actually have different animation times
        // Need to load the gif ourselves to figure it out!

        EVERY_N_MILLIS(40)
        {
            static cmdShowGIFFrame p3(255, 0, 1);
            static uint32_t frame = 0;
            p3.frame = frame++;
            p3.iGifNumber = ixGif;
            SendPacket(&p3, packetSerial);
        }

        EVERY_N_MILLIS(100)
        {
            cmdSetBrightness p2(255, Potentiometers::brightness);
            SendPacket(&p2, packetSerial);
        }
    }

}
