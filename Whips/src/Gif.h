#pragma once
#include <AnimatedGIF.h>

/*
 * Animated GIF handling
 */

namespace Gif
{
    void setup();
    void loop();

    void *GIFOpenFile(const char *fname, int32_t *pSize);
    void GIFCloseFile(void *pHandle);
    int32_t GIFReadFile(GIFFILE *pFile, uint8_t *pBuf, int32_t iLen);
    int32_t GIFSeekFile(GIFFILE *pFile, int32_t iPosition);
    void GIFDraw(GIFDRAW *pDraw);
}
