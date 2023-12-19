#pragma once

#include <PacketSerial.h>

//
// a bunch of data structures sent over the serial wire
// from DOM to SUB with instructions to do things to the lights
//

// Here is a utility function that sends any command
// as a packet over the PacketSerial driver.
template <typename T>
void SendPacket(T *cmd, PacketSerial &packetSerial)
{
    cmd->checksum = 0;
    cmd->checksum = calcCRC16((uint8_t *)cmd, sizeof(T));
    packetSerial.send((uint8_t *)cmd, sizeof(T));
}

// minimize byte size to maximize the throughput
#pragma pack(push, 1)

// Every command has four bytes at the beginning:
struct cmdUnknown
{
    cmdUnknown(char chCommand, uint8_t whip) : checksum(0),
                                               chCommand(chCommand),
                                               whip(whip) {}

    uint16_t checksum; // CRC16 checksum - will be filled in by SendPacket right before sending
    char chCommand;    // command. Use 'c' for cmdSetWhipColor, for example
    uint8_t whip;      // which whip should respond. 0 - 23 or 255 for all whips
};

/* Set an entire whip to the same color */
struct cmdSetWhipColor : cmdUnknown
{
    cmdSetWhipColor(uint8_t whip, CRGB rgb) : cmdUnknown('c', whip),
                                              rgb(rgb)
    {
    }

    CRGB rgb; // the color
};

/* Load an animated GIF from a file into memory */
struct cmdLoadGIF : cmdUnknown
{
    cmdLoadGIF(uint8_t whip, uint16_t iGifNumber) : cmdUnknown('g', whip),
                                                    iGifNumber(iGifNumber)
    {
    }

    uint16_t iGifNumber; // We will look for a file named %03d.gif to display
};

/* Show a single frame from the loaded GIF */
struct cmdShowGIFFrame : cmdUnknown
{
    cmdShowGIFFrame(uint8_t whip, uint32_t frame) : cmdUnknown('j', whip),
                                                    frame(frame)
    {
    }

    uint32_t frame; // frame will be increasing forever because DOM doesn't know how many
                    // frames are in the animation. Sub mods it by the number of frames in the animation.
};

/* Set volume */
struct cmdSetVolume : cmdUnknown
{
    cmdSetVolume(uint8_t whip, uint8_t volume) : cmdUnknown('v', whip),
                                                 volume(volume)
    {
    }

    uint8_t volume; // 0 (off) to 255 (max)
};

/* Set Brightness */
struct cmdSetBrightness : cmdUnknown
{
    cmdSetBrightness(uint8_t whip, uint8_t brightness) : cmdUnknown('b', whip),
                                                         brightness(brightness)
    {
    }

    uint8_t brightness; // 0 (off) to 255 (blinding)
};

#pragma pack(pop)
