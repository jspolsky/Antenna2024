#pragma once

#include <PacketSerial.h>

//
// a bunch of data structures sent over the serial wire
// from DOM to SUB with instructions to do things to the lights
//

#pragma pack(push, 1)

// Every command includes this at the top:
struct cmdUnknown
{
    cmdUnknown(char chCommand, uint8_t whip) : checksum(0),
                                               chCommand(chCommand),
                                               whip(whip) {}

    uint16_t checksum; // CRC16 checksum
    char chCommand;    // command. Use 'c' for cmdSetWhipColor, for example
    uint8_t whip;      // which whip should respond. 0 - 23 or 255 for all whips
};

/* Set an entire whip to the same color */
/* set chCommand to 'c' */
struct cmdSetWhipColor : cmdUnknown
{
    cmdSetWhipColor(uint8_t whip, CRGB rgb) : cmdUnknown('c', whip),
                                              rgb(rgb)
    {
    }

    void send(PacketSerial &ps)
    {
        checksum = calcCRC16((uint8_t *)this, sizeof(cmdSetWhipColor));
        ps.send((uint8_t *)this, sizeof(cmdSetWhipColor));
    }

    CRGB rgb; // the color
};

/* Play a sound */
/* set chCommand to 's' */
struct cmdPlaySound : cmdUnknown
{
    cmdPlaySound(uint8_t whip, char chSoundName) : cmdUnknown('s', whip),
                                                   chSoundName(chSoundName)
    {
    }

    void send(PacketSerial &ps)
    {
        checksum = calcCRC16((uint8_t *)this, sizeof(cmdPlaySound));
        ps.send((uint8_t *)this, sizeof(cmdPlaySound));
    }

    char chSoundName; // A printable letter. The sound played will be fx%c.wav from the SD Card
};

/* Set volume */
/* set chCommand to 'v' */
struct cmdSetVolume : cmdUnknown
{
    cmdSetVolume(uint8_t whip, uint8_t volume) : cmdUnknown('v', whip),
                                                 volume(volume)
    {
    }

    void send(PacketSerial &ps)
    {
        checksum = calcCRC16((uint8_t *)this, sizeof(cmdSetVolume));
        ps.send((uint8_t *)this, sizeof(cmdSetVolume));
    }

    uint8_t volume; // 0 (off) to 255 (max)
};

#pragma pack(pop)