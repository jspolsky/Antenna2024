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
    Gif::setup();
  }
  else
  {
    DipSwitch::setup();
    Led::setup();
    Sound::setup();
  }
}

void loop()
{
  if (domMode)
  {
    LedShow::loop();
    Potentiometers::loop();
    Gif::loop();
  }
  else
  {
    DipSwitch::loop();
    Led::loop();
    Sound::loop();
  }
}
