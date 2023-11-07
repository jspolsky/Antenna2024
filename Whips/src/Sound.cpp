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
    AudioAmplifier amp1;       // xy=448,299
    AudioOutputI2S i2s1;       // xy=649,296
    AudioConnection patchCord1(playSdWav1, 0, amp1, 0);
    AudioConnection patchCord2(amp1, 0, i2s1, 0);
    // GUItool: end automatically generated code

    void setup()
    {
        AudioMemory(8);
        if (!(SD.begin(pinSDCardCS)))
        {
            dbgprintf("Unable to access sd card\n");
            return;
        }
        amp1.gain(0.2);
    }

    void loop()
    {
    }

    void playSound(char chSoundName)
    {
        char rgchFileName[] = "fx*.wav";
        rgchFileName[2] = chSoundName;

        playSdWav1.play(rgchFileName);
    }

    void setVolume(uint8_t volume)
    {
        amp1.gain((float)volume / 255.0);
    }

}
