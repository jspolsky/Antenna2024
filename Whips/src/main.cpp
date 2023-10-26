#include <Arduino.h>


#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>

#include "Util.h"

#ifdef SUB
  #define NUM_LEDS 110
  #define DATA_PIN 8
  CRGB leds[NUM_LEDS];
#endif

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  Util::setup();

  Serial1.begin(2000000);

#ifdef SUB

  FastLED.addLeds<WS2812SERIAL, DATA_PIN, BGR>(leds, NUM_LEDS);

#endif 

}

void loop() {

#ifdef DOM

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  dbgprintf("Sending message at %d\n", millis());
  Serial1.println("Hello, Sub!");

#endif 

#ifdef SUB

  static int cLeds = 0;

  while (Serial1.available())
  {
    dbgprintf("%c", Serial1.read());

    for (int i = 0; i < NUM_LEDS; i++)
    {
      if (i < cLeds) leds[i] = CRGB::Red; else leds[i] = CRGB::Green;
    }

    cLeds = (cLeds + 1) % NUM_LEDS;
    FastLED.show();
  }

#endif


}
