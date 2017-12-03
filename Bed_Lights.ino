//This project was created by Danica Fernandez

#include <avr/power.h>
#include "FastLED.h"

#define NUM_LEDS 50 //how many leds your strip has
#define DATA_PIN 0 //data line for your strip 
#define CLOCK_PIN 1 //clock line for your strip, is your strip dont have this comment it
#define SENSOR_PIN 1 //where the sensor is connected, on the adafruit trinket analog pin 1 equals to digital pin 2
#define TRIGGER 50 //the value below whe consider someone is stepping 

CRGB leds[NUM_LEDS];

int inicialization = 0;
int state = 0;

void setup()
{
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1); //whe want the trinket runnig at 16MHZ, pleaso also select it on the board menu

  // Uncomment/edit one of the following lines for your led strip that are you using
  // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  //FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  // FastLED.addLeds<APA104, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);

  // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<P9813, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<APA102, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<DOTSTAR, RGB>(leds, NUM_LEDS);

  // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS); //in my case this is my strip model
  // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);

  inicialization = 1;
  delay(500);
}

void loop()
{

  if (inicialization == 1) //turn off all leds in power on
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i].setRGB(0, 0, 0);
    }
    FastLED.show();
    inicialization = 0;
    FastLED.show();
  }

  if (analogRead(SENSOR_PIN) <= TRIGGER) //if someone is on the rug
  {
    if (state == 0) //is leds are off then do this animation for turning on
    {
      for (int i = 0; i < NUM_LEDS; i++)
      {
        leds[i].setRGB(0, 0, 20);
        FastLED.show();
        delay(100);
      }
      delay(200);

      for (int x = 20; x <= 125; x++)
      {
        for (int i = 0; i < NUM_LEDS; i++)
        {
          leds[i].setRGB(0, 0, x);
        }
        FastLED.show();
        delay(20);
      }
      while (analogRead(SENSOR_PIN) <= TRIGGER); //wait until the person steps away
      delay(2000);
      state = 1;
    }
    else //is leds are on then do this animation for turning off
    {
      for (int x = 125; x >= 20; x--)
      {
        for (int i = 0; i < NUM_LEDS; i++)
        {
          leds[i].setRGB(0, 0, x);
        }
        FastLED.show();
        delay(20);
      }
      delay(100);

      for (int i = 49; i >= 0; i--)
      {
        leds[i].setRGB(0, 0, 0);
        FastLED.show();
        delay(100);
      }
      while (analogRead(SENSOR_PIN) <= TRIGGER); //wait until the person steps away
      delay(2000);
      state = 0;
    }
  }
  delay(200);
}
