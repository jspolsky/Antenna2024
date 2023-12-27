#include <Arduino.h>
#include <PacketSerial.h>
#include <CRC16.h>
#include <CRC.h>

#include "Util.h"
#include "IR.h"
#include "LedShow.h"
#include "Commands.h"
#include "Potentiometers.h"

namespace LedShow
{
    PacketSerial packetSerial;

    enum Mode
    {
        gif,
        solid,
        selfID
    };

    void setup()
    {
        dbgprintf("In LedShow.Setup\n");
        Serial1.begin(2000000);
        packetSerial.setStream(&Serial1);
        dbgprintf("...done\n");
    }

    void loop(IR::Op op)
    {
        static int ixGif = 1;
        static Mode modeCurrent = gif;
        static CRGB rgbSolid = CRGB::Black;

        if (op != IR::noop)
            dbgprintf("LedShow::op is %d\n", op);

        switch (op)
        {
        case IR::nextImage:
            modeCurrent = gif;
            ixGif++;
            if (ixGif > 12) // UNDONE - just do this if loading the gif fails
                ixGif = 1;
            dbgprintf("new gif number %d\n", ixGif);
            break;

        case IR::red:
            rgbSolid = CRGB::Red;
            modeCurrent = solid;
            break;

        case IR::green:
            rgbSolid = CRGB::Green;
            modeCurrent = solid;
            break;

        case IR::blue:
            rgbSolid = CRGB::Blue;
            modeCurrent = solid;
            break;

        case IR::white:
            rgbSolid = CRGB::White;
            modeCurrent = solid;
            break;

        case IR::flash:
            modeCurrent = selfID;
            break;

        default:
            break;
        }

        // UNDONE
        // This is refreshing every 40 milliseconds
        // Different GIFs actually have different animation times
        // Need to load the gif ourselves to figure it out!

        switch (modeCurrent)
        {
        case gif:
            EVERY_N_MILLIS(40)
            {
                static cmdShowGIFFrame p3(255, 0, 1);
                static uint32_t frame = 0;
                p3.frame = frame++;
                p3.iGifNumber = ixGif;
                SendPacket(&p3, packetSerial);
            }
            break;

        case solid:
            EVERY_N_MILLIS(40)
            {
                cmdSetWhipColor p4(255, rgbSolid);
                SendPacket(&p4, packetSerial);
            }
            break;

        case selfID:
            EVERY_N_MILLIS(40)
            {
                cmdSelfIdentify p5;
                SendPacket(&p5, packetSerial);
            }
        }

        EVERY_N_MILLIS(100)
        {
            cmdSetBrightness p2(255, Potentiometers::brightness);
            SendPacket(&p2, packetSerial);
        }
    }

}
