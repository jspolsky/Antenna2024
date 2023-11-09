#include <Arduino.h>

#include "pins.h"
#include "Util.h"
#include "Led.h"
#include "LedShow.h"
#include "DipSwitch.h"
#include "SdCard.h"
#include "Sound.h"
#include "Potentiometers.h"

#if defined(DOM)
#define szMode "Dom"
#elif defined(SUB)
#define szMode "Sub"
#endif

void setup()
{

  Util::setup();
#if defined(DOM)
  LedShow::setup();
  Potentiometers::setup();
#elif defined(SUB)
  DipSwitch::setup();
  Led::setup();
  Sound::setup();
#endif

  dbgprintf("Whip Controller in " szMode " mode!\n");
}

void loop()
{
#if defined(DOM)
  LedShow::loop();
  Potentiometers::loop();
#elif defined(SUB)
  DipSwitch::loop();
  Led::loop();
  Sound::loop();
#endif
}
