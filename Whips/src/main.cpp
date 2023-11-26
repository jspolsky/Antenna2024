#include <Arduino.h>

#include "pins.h"
#include "Util.h"
#include "Led.h"
#include "LedShow.h"
#include "DipSwitch.h"
#include "SdCard.h"
#include "Sound.h"
#include "Potentiometers.h"
#include "Gif.h"

#if defined(DOM)
#define szMode "Dom"
#elif defined(SUB)
#define szMode "Sub"
#endif

void setup()
{

  Util::setup();

  delay(2000);

  if (!(SD.begin(pinSDCardCS)))
  {
    dbgprintf("Unable to access sd card\n");
    return;
  }

  dbgprintf("Whip Controller in " szMode " mode!\n");

#if defined(DOM)
  LedShow::setup();
  Potentiometers::setup();
  Gif::setup();
#elif defined(SUB)
  DipSwitch::setup();
  Led::setup();
  Sound::setup();
#endif
}

void loop()
{
#if defined(DOM)
  LedShow::loop();
  Potentiometers::loop();
  Gif::loop();
#elif defined(SUB)
  DipSwitch::loop();
  Led::loop();
  Sound::loop();
#endif
}
