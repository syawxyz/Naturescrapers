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
  // rtc.setHour(9);
  // rtc.setMinute(8);
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
  submode = now.minute() %2;
  //if (now.hour() >= 15 && (now.hour() <= 16 && now.minute < 1))
  // if (now.hour() >= 16 && now.hour() <= 18)
  // {
  //   submode = 1;
  // }
  // //else if ((now.hour() >= 16 && now.minute >= 1) && (now.hour() <= 17 && now.minute < 1))
  // else if (now.hour() > 18 && now.second() <= 20)
  // {
  //   submode = 2;
  // }
  // else if (now.hour() > 20 && now.hour() <= 23)
  // // else if (now.second() > 30 && now.second() <= 45)
  // {
  //   submode = 3;
  // }
  // //else if ((now.hour() >= 18 && now.minute >= 1) && (now.hour() <= 19 && now.minute < 1))
  // else if (now.second() > 45 && now.second() <= 60)
  // {
  //   submode = 4;
  // }
  // // else if (now.hour() >= 19 && now.minute >= 1) && (now.hour() <= 23 && now.minute < 59))
  // // {
  // //   submode = 5;
  // // }
  // //else if (now.hour() >= 3 && (now.hour() <= 4 && now.minute < 1))
  // // {
  // //   submode = 6;
  // // }
  // //else if ((now.hour() >= 4 && now.minute >= 1) && (now.hour() <= 5 && now.minute < 1))
  // // {
  // //   submode = 7;
  // // }
  // //else if ((now.hour() >= 5 && now.minute >= 1) && (now.hour() <= 6 && now.minute < 30))
  // // {
  // //   submode = 8;
  // // }
  
  // else
  // {
  //   submode = 0;
  // }
  //   switch (mode)
    // {
    //   case 0: 
        if (submode ==0)
          setColour (255, 57, 0,255);//635 orange
        else if (submode ==1)
        {
          if (now.second() >=30)
          {
            setColour (0, 40, 255, 100);//445 biru gelap
          }
          else
          {
            setColour (0, 40, 255, 255);//445 biru gelap
          }
        }
        else
        {
          Serial.println ("error");
        }
        
//         else if (submode ==4)
//           setColour (255,255,0);//580 kuning
//           break;
// //simulasi
//       case 1:
//         if (submode == 0)
//           Serial.print ("Error");
//         else if (submode ==1)
//         // else if (submode ==5)
//          setColour (255, 190, 0);//600 kuning ke oren
//         else if (submode ==2)
//         // else if (submode ==6)
//           setColour (255, 119, 0);//620 orange
//         else if (submode ==3)
//         // else if (submode ==7)
//           setColour (130, 0, 200);//405 ungu
//         else if (submode ==4)
//         // else if (submode ==8)
//           setColour (255, 119, 0);//620 orange
//           break;
//     }

  // if (mode != 0)
  // {
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
  // }
}
