#include <Arduino.h>

#include "Util.h"
#include "Led.h"
#include "StatusLed.h"

#ifdef DOM
#define szMode "Dom"
#endif
#ifdef SUB
#define szMode "Sub"
#endif

void setup()
{

  Util::setup();
  Led::setup();
  StatusLed::setup();
  Serial1.begin(2000000);

  dbgprintf("Whip Controller in " szMode " mode!\n");
}

void loop()
{

  StatusLed::loop();

#ifdef DOM

  EVERY_N_MILLIS(1000)
  {
    Serial1.println("Hello, Sub!");
    dbgprintf("time: %d\n", millis());
  }

#endif

#ifdef SUB

  static uint32_t cLeds = 0;

  while (Serial1.available())
  {
    dbgprintf("%c", Serial1.read());
    Led::showSomeLeds(cLeds);
    cLeds++;
  }

#endif
}
