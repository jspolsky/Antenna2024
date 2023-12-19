#include <Arduino.h>

#include "pins.h"
#include "Util.h"
#include "Led.h"
#include "LedShow.h"
#include "DipSwitch.h"
#include "SdCard.h"
#include "Potentiometers.h"
#include "Gif.h"
#include "IR.h"

static bool domMode;

void setup()
{

  pinMode(pinGndMeansDom, INPUT_PULLUP);

  Util::setup();
  delay(1000);

  if (!(SD.begin(pinSDCardCS)))
  {
    dbgprintf("Unable to access sd card\n");
    return;
  }

  domMode = (digitalReadFast(pinGndMeansDom) == LOW);
  dbgprintf("Whip controller in %s mode\n", domMode ? "DOM" : "SUB");

  if (domMode)
  {
    LedShow::setup();
    Potentiometers::setup();
    IR::setup();
  }
  else
  {
    DipSwitch::setup();
    Led::setup();
  }
  Gif::setup();
}

void loop()
{
  if (domMode)
  {
    LedShow::loop();
    Potentiometers::loop();
    IR::loop();
  }
  else
  {
    DipSwitch::loop();
    Led::loop();
  }
}
