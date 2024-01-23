#include <Arduino.h>
#include <PacketSerial.h>
#include <CRC16.h>
#include <CRC.h>

#include "Util.h"
#include "IR.h"
#include "LedShow.h"
#include "Commands.h"
#include "Gif.h"

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
        static Mode modeCurrent = gif;
        static int ixGif = 1;
        static CRGB rgbSolid = CRGB::Black;
        static int gifDelay = 40;
        static uint8_t brightness = 128;

        if (op != IR::noop)
            dbgprintf("LedShow::op is %d\n", op);

        switch (op)
        {
        case IR::nextImage:

            modeCurrent = gif;
            {
                bool bDone = false;
                while (!bDone)
                {
                    ixGif++;

                    // try to load that GIF to see if it exists and to get its frame rate
                    if (Gif::GetGifInfo(ixGif, gifDelay))
                    {
                        dbgprintf("new gif number %d\n", ixGif);
                        bDone = true;
                    }
                    else
                    {
                        ixGif = 0;
                    }
                }
            }

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

        case IR::brighter:
            if (brightness < 255)
                brightness++;
            dbgprintf("brightness %d\n", brightness);
            break;

        case IR::dimmer:
            if (brightness > 0)
                brightness--;
            dbgprintf("brightness %d\n", brightness);
            break;

        default:
            break;
        }

        switch (modeCurrent)
        {
        case gif:
            EVERY_N_MILLIS_I(timerName, 400)
            {
                timerName.setPeriod(gifDelay);

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
            cmdSetBrightness p2(255, brightness);
            SendPacket(&p2, packetSerial);
        }
    }

}
