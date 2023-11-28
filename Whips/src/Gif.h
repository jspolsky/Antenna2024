#pragma once
#include <AnimatedGIF.h>

#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>

/*
 * Animated GIF handling
 */

namespace Gif
{
    void setup();
    void LoadGif(uint16_t ixGifNumber);
    void GetFrame(uint32_t frame, CRGB *leds);

    void *GIFOpenFile(const char *fname, int32_t *pSize);
    void GIFCloseFile(void *pHandle);
    int32_t GIFReadFile(GIFFILE *pFile, uint8_t *pBuf, int32_t iLen);
    int32_t GIFSeekFile(GIFFILE *pFile, int32_t iPosition);
    void GIFDraw(GIFDRAW *pDraw);
    void *GIFAlloc(uint32_t u32Size);
    void GIFFree(void *p);
}
