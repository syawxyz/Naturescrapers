#include "RTClib.h"
#include <FastLED.h>
#include <stdint.h>


#define LED_Pin 13
#define NUM_LEDS 10

CRGB leds [NUM_LEDS];

// #define Red 15
// #define Green 2
// #define Blue 4

uint8_t ledyellow [3] = {255, 222, 89};
uint8_t ledblue [3] = {182, 38, 177};
short int mode =0;

// int redcount;
// int greencount;
// int bluecount;

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = { "Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu" };


void setColour (uint8_t val_r, uint8_t val_g, uint8_t val_b)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds [i] = CRGB (val_r, val_g, val_b);
    FastLED.show();
    delay (1000);
  }
}

void setup() 
{
  Serial.begin(115200);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }
  // pinMode(Red, OUTPUT);
  // pinMode(Green, OUTPUT);
  // pinMode(Blue, OUTPUT);
}

void loop() 
{
  DateTime now = rtc.now();

  Serial.print("Current time: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  delay(1000);

  if (now.second() <= 30) 
    mode = 0;
  else 
    mode = 1;
  
  switch (mode)
  {
    case 1:
      setColour (ledyellow [0], ledyellow [1], ledyellow [2]);
      break;
    default:
      setColour(ledblue [0], ledblue [1], ledblue [2]);
  }
}
