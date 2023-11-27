#include <Arduino.h>
#include "SPI.h"
#include <SD.h>

#include "Util.h"
#include "Gif.h"

namespace Gif
{
    AnimatedGIF gif;
    File f;

    void setup()
    {
        dbgprintf("in GIF.setup\n");
        // for now, just experimenting with AnimatedGif library
        gif.begin(LITTLE_ENDIAN_PIXELS);

        dbgprintf("gif.begin called\n");

        if (gif.open("/test.gif", GIFOpenFile, GIFCloseFile, GIFReadFile, GIFSeekFile, GIFDraw))
        {
            GIFINFO gi;
            dbgprintf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());

            // The getInfo() method can be slow since it walks through the entire GIF file to count the frames
            // and gather info about total play time. Comment out this section if you don't need this info
            if (gif.getInfo(&gi))
            {
                dbgprintf("frame count: %d\n", gi.iFrameCount);
                dbgprintf("duration: %d ms\n", gi.iDuration);
                dbgprintf("max delay: %d ms\n", gi.iMaxDelay);
                dbgprintf("min delay: %d ms\n", gi.iMinDelay);
            }

            if (gif.allocFrameBuf(GIFAlloc) == GIF_SUCCESS)
            {
                int32_t iFrame = 0;

                while (iFrame < gi.iFrameCount && gif.playFrame(false, NULL))
                {
                    iFrame++;
                }
                gif.freeFrameBuf(GIFFree);
            }
            else
            {
                dbgprintf("Insufficient memory\n");
            }

            gif.close();
        }
        else
        {
            dbgprintf("Error opening file = %d\n", gif.getLastError());
        }
    }

    void loop()
    {
    }

    void *GIFOpenFile(const char *fname, int32_t *pSize)
    {
        f = SD.open(fname);
        if (f)
        {
            *pSize = f.size();
            return (void *)&f;
        }
        return NULL;
    }

    void GIFCloseFile(void *pHandle)
    {
        File *f = static_cast<File *>(pHandle);
        if (f != NULL)
            f->close();
    }

    int32_t GIFReadFile(GIFFILE *pFile, uint8_t *pBuf, int32_t iLen)
    {
        int32_t iBytesRead;
        iBytesRead = iLen;
        File *f = static_cast<File *>(pFile->fHandle);
        // Note: If you read a file all the way to the last byte, seek() stops working
        if ((pFile->iSize - pFile->iPos) < iLen)
            iBytesRead = pFile->iSize - pFile->iPos - 1; // <-- ugly work-around
        if (iBytesRead <= 0)
            return 0;
        iBytesRead = (int32_t)f->read(pBuf, iBytesRead);
        pFile->iPos = f->position();
        return iBytesRead;
    }

    int32_t GIFSeekFile(GIFFILE *pFile, int32_t iPosition)
    {
        File *f = static_cast<File *>(pFile->fHandle);
        f->seek(iPosition);
        pFile->iPos = (int32_t)f->position();
        return pFile->iPos;
    }

    void GIFDraw(GIFDRAW *pDraw)
    {
    }

    void *GIFAlloc(uint32_t u32Size)
    {
        dbgprintf("Allocating %d for a frame\n", u32Size);
        return malloc(u32Size);
    }
    void GIFFree(void *p)
    {
        dbgprintf("Free\n");
        free(p);
    }

}
