#include <Arduino.h>

#include "Util.h"
#include "Led.h"
#include "StatusLed.h"
#include "LedShow.h"

#ifdef DOM
#define szMode "Dom"
#endif
#ifdef SUB
#define szMode "Sub"
#endif

void setup()
{

  Util::setup();
  StatusLed::setup();
#ifdef SUB
  Led::setup();
#endif
#ifdef DOM
  LedShow::setup();
#endif

  dbgprintf("Whip Controller in " szMode " mode!\n");
}

void loop()
{

  StatusLed::loop();

#ifdef DOM
  LedShow::loop();
#endif

#ifdef SUB
  Led::loop();
#endif
}
