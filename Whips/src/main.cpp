#include <Arduino.h>

#include "Util.h"
#include "Led.h"
#include "StatusLed.h"
#include "LedShow.h"

#if defined(DOM)
#define szMode "Dom"
#elif defined(SUB)
#define szMode "Sub"
#endif

void setup()
{

  Util::setup();
  StatusLed::setup();
#if defined(SUB)
  Led::setup();
#elif defined(DOM)
  LedShow::setup();
#endif

  dbgprintf("Whip Controller in " szMode " mode!\n");
}

void loop()
{

  StatusLed::loop();

#if defined(DOM)
  LedShow::loop();
#elif defined(SUB)
  Led::loop();
#endif
}
