
//
// a bunch of data structures sent over the serial wire
// from DOM to SUB with instructions to do things to the lights
//

/* Set an entire whip to the same color */

// Every command includes this at the top:
typedef struct
{
    uint32_t checksum; // CRC32 checksum
    char chCommand;    // must be 'c' for setWhipColor
    uint8_t whip;      // which whip should respond. 0 - 23 or 255 for all whips
} UNKNOWNCOMMAND;

typedef struct
{

    uint32_t checksum; // CRC32 checksum
    char chCommand;    // must be 'c' for setWhipColor
    uint8_t whip;      // which whip should respond. 0 - 23 or 255 for all whips
    CRGB rgb;          // the color

} SETWHIPCOLOR;
