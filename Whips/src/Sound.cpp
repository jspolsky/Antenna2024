#include <Arduino.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "pins.h"
#include "Util.h"
#include "Sound.h"

#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h> /* herein used for macros like EVERY_N_MILLIS only */

namespace Sound
{

    // GUItool: begin automatically generated code
    AudioPlaySdWav playSdWav1; // xy=280,232
    AudioOutputI2S i2s1;       // xy=559,259
    AudioConnection patchCord1(playSdWav1, 0, i2s1, 0);
    AudioConnection patchCord2(playSdWav1, 1, i2s1, 1);
    // GUItool: end automatically generated code

    void setup()
    {
        delay(2500);
        AudioMemory(8);
        if (!(SD.begin(BUILTIN_SDCARD)))
        {
            dbgprintf("Unable to access sd card\n");
            return;
        }

        dbgprintf("before play\n");
        playSdWav1.play("fxA.wav");
        delay(100);
        while (playSdWav1.isPlaying())
            ;
        dbgprintf("after play\n");
        dbgprintf("AudioMemoryUsageMax(); returns %d\n", AudioMemoryUsageMax());
        dbgprintf("AudioProcessorUsageMax(); returns %d\n", AudioProcessorUsageMax());
    }

    void loop()
    {
    }

}
