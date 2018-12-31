// **** INCLUDES *****
#include "LowPower.h"
#include <Wire.h>
#include "RTClib.h"
// Use pin 2 as wake up pin
const int wakeUpPin = 2;

#define PRINT

RTC_DS3231 rtc;

void wakeUp()
{
  // Just a handler for the pin interrupt.
}

void setup()
{

  Serial.begin(19200);

  delay(3000);
  rtc.begin();
#ifdef PRINT
  DateTime now = rtc.now();

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
#endif
  // Configure wake up pin as input.
  // This will consumes few uA of current.
  pinMode(wakeUpPin, INPUT);

  rtc.writeSqwPinMode(DS3231_SquareWave1Hz);
  //delay(1500);
}

void loop()
{
  // Allow wake up pin to trigger interrupt on low.
  //attachInterrupt(0, wakeUp, LOW);

  // Enter power down state with ADC and BOD module disabled.
  // Wake up when wake up pin is low.
  //LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

  // Disable external pin interrupt on wake up pin.
  //detachInterrupt(0);

  rtc.temperature(true);
  delay(500);
  uint8_t temp = rtc.temperature(false);
  delay(500);
  Serial.println(temp, DEC);

}
