#include <Arduino.h>

#include "pins.h"
#include "Util.h"
#include "SDCard.h"

#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h> /* herein used for macros like EVERY_N_MILLIS only */

namespace SDCard
{
    File root;

    void setup()
    {
        // testing SD Card
        delay(5000);
        dbgprintf("Initializing SD card...\n");
        pinMode(pinSDCardCS, OUTPUT);

        if (!SD.begin(pinSDCardCS))
        {
            dbgprintf("initialization failed!\n");
            return;
        }
        dbgprintf("initialization done.\n");

        root = SD.open("/");

        printDirectory(root, 0);
    }

    void loop()
    {
    }

    void printDirectory(File dir, int numTabs)
    {
        while (true)
        {
            File entry = dir.openNextFile();
            if (!entry)
            {
                // no more files
                break;
            }
            for (uint8_t i = 0; i < numTabs; i++)
            {
                Serial.print('\t'); // prints a tab for each level of depth
            }
            if (entry.isDirectory())
            {
                // Serial.println("/");
                // printDirectory(entry, numTabs + 1);
            }
            else
            {
                // files have sizes, directories do not
                Serial.print(entry.name());
                Serial.print("\t\t");
                Serial.println(entry.size(), DEC);
            }
            entry.close();
        }
    }
}
