#define pinLEDStrip 8

// Which SD Card are we using?
// BUILTIN_SDCARD - for Teensy 4.1
// 10 - when connected to external SD Card using SPI
//      Currently not using this because it is not fast enough
//      and causes audio to sound crap
#define pinSDCardCS BUILTIN_SDCARD
// #define pinSDCardCS 10

#define pinStatus LED_BUILTIN
#define pinBrightness A0
#define pinVolume A1
#define pinLEDRxIndicator 9
#define pinGndMeansDom 10