#pragma once

//
// a bunch of data structures sent over the serial wire
// from DOM to SUB with instructions to do things to the lights
//

#pragma pack(push, 1)

// Every command includes this at the top:
struct cmdUnknown
{
    uint16_t checksum; // CRC16 checksum
    char chCommand;    // command. Use 'c' for cmdSetWhipColor, for example
    uint8_t whip;      // which whip should respond. 0 - 23 or 255 for all whips
};

/* Set an entire whip to the same color */
/* set chCommand to 'c' */
struct cmdSetWhipColor : cmdUnknown
{
    CRGB rgb; // the color
};

/* Play a sound */
/* set chCommand to 's' */
struct cmdPlaySound : cmdUnknown
{
    char chSoundName; // A printable letter. The sound played will be fx%c.wav from the SD Card
};

/* Set volume */
/* set chCommand to 'v' */
struct cmdSetVolume : cmdUnknown
{
    uint8_t volume; // 0 (off) to 255 (max)
};

#pragma pack(pop)