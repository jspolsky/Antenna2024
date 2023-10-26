#include <Arduino.h>

#include "Util.h"
#include "Led.h"

void setup()
{

  pinMode(LED_BUILTIN, OUTPUT);

  Util::setup();
  Led::setup();

  Serial1.begin(2000000);
}

void loop()
{

#ifdef DOM

  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(1000);                     // wait for a second
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  delay(1000);                     // wait for a second
  dbgprintf("Sending message at %d\n", millis());
  Serial1.println("Hello, Sub!");

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
