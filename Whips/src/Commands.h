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

/* Play a sound */
struct cmdPlaySound : cmdUnknown
{
    cmdPlaySound(uint8_t whip, char chSoundName) : cmdUnknown('s', whip),
                                                   chSoundName(chSoundName)
    {
    }

    char chSoundName; // A printable letter. The sound played will be fx%c.wav from the SD Card
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

#pragma pack(pop)
