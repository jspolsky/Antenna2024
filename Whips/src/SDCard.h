#pragma once

#include <SPI.h>
#include <SD.h>

namespace SDCard
{
    void setup();
    void loop();

    void printDirectory(File dir, int numTabs);
}