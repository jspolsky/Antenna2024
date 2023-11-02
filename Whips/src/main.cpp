#include <Arduino.h>

#include "Util.h"
#include "Led.h"
#include "StatusLed.h"
#include "LedShow.h"
#include "DipSwitch.h"

#if defined(DOM)
#define szMode "Dom"
#elif defined(SUB)
#define szMode "Sub"
#endif

void setup()
{

  Util::setup();
  StatusLed::setup();
#if defined(DOM)
  LedShow::setup();
#elif defined(SUB)
  DipSwitch::setup();
  Led::setup();
#endif

  dbgprintf("Whip Controller in " szMode " mode!\n");
}

void loop()
{

  StatusLed::loop();

#if defined(DOM)
  LedShow::loop();
#elif defined(SUB)
  DipSwitch::loop();
  Led::loop();
#endif
}
