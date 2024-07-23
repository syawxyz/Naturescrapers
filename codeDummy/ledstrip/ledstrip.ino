// #include <SoftwareSerial.h>
#include <DS3231.h>
#include <Wire.h>
#include <FastLED.h>
#include <stdint.h>


#define LED_Pin 13
#define NUM_LEDS 144

// SoftwareSerial display (12,14);//rx,tx
RTClib RTC;
DS3231 rtc;
CRGB leds [NUM_LEDS];


uint8_t ledyellow [3] [3] = {{255, 187, 0}, {255, 83, 0}, {255, 187, 0}};
uint8_t ledblue [3] [3] = {{0, 137, 255}, {35, 0, 255}, {0, 137, 255}};
short int mode = 0;
uint8_t brightness_calib = 0;
bool century = 0;
bool h12flag;
bool pmflag; 

void setColour (uint8_t val_r1, uint8_t val_g1, uint8_t val_b1, uint8_t val_r2, uint8_t val_g2, uint8_t val_b2, uint8_t val_r3, uint8_t val_g3, uint8_t val_b3)
{
  const uint8_t num_section1 = 48;
  const uint8_t num_section2 = 96;
  const uint8_t num_section3 = 144;
  for (int i = 0; i < NUM_LEDS; i++)
  {
    // if (i >= 0 && i < (num_section1/2)){
    if (i>=0 && i<num_section1)
    {  
      leds [i] = CRGB (val_r1, val_g1, val_b1);
      FastLED.setBrightness(100);
      FastLED.show();;
      delay (1);
    }
    // else if (i >= (num_section1/2) && i < num_section1)
    // {
    //   leds [i] = CRGB (val_r1, (val_g1-50), val_b1);
    //   FastLED.setBrightness(100);
    //   FastLED.show();;
    //   delay (1);
    // }
    else if (i>=num_section1 && i< num_section2)
    {
      leds [i] = CRGB (val_r2, val_g2, val_b2);
      FastLED.setBrightness(100);
      FastLED.show();;
      delay (1);
    }
    // else if (i>= num_section2 && i < (num_section3 - 24))
    // {
    //   leds [i] = CRGB (val_r3, (val_g3-50), val_b3);
    //   FastLED.setBrightness(100);
    //   FastLED.show();;
    //   delay (1);
    // }
    else 
    {
      leds [i] = CRGB (val_r3, val_g3, val_b3);
      FastLED.setBrightness(100);
      FastLED.show();;
      delay (1);
    }
  }
}

void setup() 
{
  // display.begin(115200);
  Wire.begin();
  Serial.begin(115200);
  FastLED.addLeds<WS2812, LED_Pin, GRB>(leds, NUM_LEDS);
  rtc.setYear(rtc.getYear());
  rtc.setMonth(rtc.getMonth(century));
  rtc.setDate(rtc.getDate());
  rtc.setDoW(rtc.getDoW());
  rtc.setHour(rtc.getHour(h12flag, pmflag));
  rtc.setMinute(rtc.getMinute());
  rtc.setSecond(rtc.getSecond());
  delay(500);
}

void loop() 
{
  delay (1000);
  DateTime now = RTC.now();

  if (now.second() >= 0 && now.second() <= 30)
  {
    mode = 1;
  }
  else if (now.second() > 30 && now.second() <= 60)
  {
    mode = 2;
  }
  else
  {
    mode = 0;
  }
  
  switch (mode)
  {
    case 0:
      Serial.print ("Error");
      break;
    case 1:
      setColour (ledyellow [0] [0], ledyellow [0] [1], ledyellow [0] [2], ledyellow [1] [0], ledyellow [1] [1], ledyellow [1] [2], ledyellow [2] [0], ledyellow [2] [1], ledyellow [2] [2]);
      break;
    case 2:
      setColour(ledblue [0] [0], ledblue [0] [1], ledblue [0] [2], ledblue [1] [0], ledblue [1] [1], ledblue [1] [2], ledblue [2] [0], ledblue [2] [1], ledblue [2] [2] );
      break;
  }

  if (mode != 0)
  {
    Serial.print("Waktu: ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  }

}
