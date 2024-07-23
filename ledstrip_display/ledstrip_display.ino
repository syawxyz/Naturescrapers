#include <SoftwareSerial.h>
#include "RTClib.h"
#include <FastLED.h>
#include <stdint.h>


#define LED_Pin 13
#define NUM_LEDS 144

SoftwareSerial display (12,14);//rx,tx
RTC_DS3231 rtc;
CRGB leds [NUM_LEDS];


uint8_t ledyellow [3] = {255, 222, 89};
uint8_t ledblue [3] = {182, 38, 177};
short int mode = 0;
uint8_t brightness_calib = 0;

// char daysOfTheWeek[7][12] = { "Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu" };


void displayok ()
{
  display.write(0xff);
  display.write(0xff);
  display.write(0xff);
}

void setColour (uint8_t val_r, uint8_t val_g, uint8_t val_b)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds [i] = CRGB (val_r, val_g, val_b);
    FastLED.show();
    delay (1);
  }
}

void setup() 
{
  display.begin(115200);
  Serial.begin(115200);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }
  FastLED.addLeds<WS2812, LED_Pin, GRB>(leds, NUM_LEDS);
}

void loop() 
{
  DateTime now = rtc.now();

  display.print ("n0.val=");
  display.print (now.hour(), DEC);
  displayok();

  display.print ("n1.val=");
  display.print (now.minute(), DEC);
  displayok();

  display.print ("n3.val=");
  display.print (now.second(), DEC);
  displayok();

  delay (10);

  // Serial.print("Current time: ");
  // Serial.print(now.year(), DEC);
  // Serial.print('/');
  // Serial.print(now.month(), DEC);
  // Serial.print('/');
  // Serial.print(now.day(), DEC);
  // Serial.print(" (");
  // Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  // Serial.print(") ");
  // Serial.print(now.hour(), DEC);
  // Serial.print(':');
  // Serial.print(now.minute(), DEC);
  // Serial.print(':');
  // Serial.print(now.second(), DEC);
  // Serial.println();

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
  // if (brightness_calib == 0);
  // {
  //   for (int i = 0; i<=255; i++)
  // {
  //   FastLED.setBrightness(i);
  //   delay (250);
  // }
  // brightness_calib = 1;
  // }
}
