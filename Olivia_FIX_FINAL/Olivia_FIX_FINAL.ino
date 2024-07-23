#include <DS3231.h>
#include <Wire.h>
#include <FastLED.h>
#include <stdint.h>

#define LED_Pin 13
#define NUM_LEDS 144

RTClib RTC;
DS3231 rtc;
CRGB leds [NUM_LEDS];

short int mode = 0;
short int submode = 0;
bool century = 0;
bool h12flag;
bool pmflag; 

void setColour (uint8_t par_led_r, uint8_t par_led_g, uint8_t par_led_b, uint8_t par_bright)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds [i] = CRGB (par_led_r, par_led_g, par_led_b);
    FastLED.setBrightness(par_bright);//178
    FastLED.show();;
    delay (1);
  }
}

void setup() {
  Wire.begin();
  Serial.begin(115200);

  // rtc.setYear(24);
  // rtc.setMonth(7);
  // rtc.setDate(19);
  // rtc.setDoW(6);
  // rtc.setHour(7);
  // rtc.setMinute(17);
  // rtc.setSecond(0);
  rtc.setYear(rtc.getYear());
  rtc.setMonth(rtc.getMonth(century));
  rtc.setDate(rtc.getDate());
  rtc.setDoW(rtc.getDoW());
  rtc.setHour(rtc.getHour(h12flag, pmflag));
  rtc.setMinute(rtc.getMinute());
  rtc.setSecond(rtc.getSecond());
  FastLED.addLeds<WS2812, LED_Pin, GRB>(leds, NUM_LEDS);
  delay (500);
}

void loop() {
  delay (500);
  DateTime now = RTC.now();
  //simulasi
  
  if (now.hour() >= 17 && now.hour() <= 18)
  {
    submode = 1;
  }

  else if (now.hour() > 18 && now.hour() <= 20)
  {
    submode = 2;
  }

  else if (now.hour () >= 3 && now.hour () <=5)
  {
    submode = 3;
  }

  else if (now.hour () >5 && now.hour() <=6)
  {
    submode = 1;
  }
  
  else
  {
    submode = 0;
  } 
        if (submode ==1)
          setColour (255, 57, 0,255);//635 orange
        else if (submode ==2)
        {
          setColour (0, 40, 255, 255);//445 biru gelap
        }
        else if (submode ==3)
        {
          setColour (0, 40, 255, 78);//445 biru gelap
        }
        else
        {
          Serial.println ("Error");
        }

  if (submode != 0)
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
    Serial.println(now.second(), DEC);
    Serial.println(mode);
    Serial.println(submode);
  }
}
