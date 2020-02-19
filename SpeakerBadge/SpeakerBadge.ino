/*
 * File: SpeakerBadge.ino
 * 
 * Copyright (c) 2019 Gerald Venzl
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ESP8266WiFi.h>               // ESP8266 Board support needed. Add https://arduino.esp8266.com/stable/package_esp8266com_index.json to Borad Manager Urls (Preferences)
#include <EEPROM.h>                    // EEPROM memory controller - https://www.arduino.cc/en/Reference/EEPROM
#include <GxEPD2_BW.h>                 // Arduino Display Library for SPI E-Paper Displays - https://github.com/ZinggJM/GxEPD2

#include "config.h"
#include "print.h"
#include "cli.h"
#include "speaker.h"
#include "talks.h"

GxEPD2_BW<GxEPD2_270, GxEPD2_270::HEIGHT> display(GxEPD2_270(/*CS=D8*/ 2, /*DC=D3*/ 0, /*RST=D4*/ 4, /*BUSY=D2*/ 5)); // 2.7" b/w 264x176
CLI cli = CLI();
Speaker speaker = Speaker();
Talks talks = Talks();
int btnAState = talks.getTalkCount(); // Print name first, then talks, hence set button state to last talk
int btnBState = 0;

void initDisplay()
{
  display.init(BAUD_SPEED);
  display.setRotation(PRINT_LANDSCAPE);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
}

void checkButtonA()
{
  if (digitalRead(BUTTONA_PIN) == HIGH)
  {
    Serial.println(F("State of Button A has changed!"));

    if (btnAState == talks.getTalkCount())
    {
      Serial.println(F("Printing name"));
      printName();
      btnAState=0;
    }
    else
    {
      Serial.println(F("Printing Session..."));
      Talks::Talk talk = talks.getNextTalk();
      printTalk(talk);
      btnAState++;
    }
  }
}

void checkButtonB()
{
  if (digitalRead(BUTTONB_PIN) == HIGH)
  {
    Serial.println(F("State of Button B has changed!"));

    switch (btnBState)
    {
      case 0:
      {
        Serial.println(F("Printing contact..."));
        printContact();
        btnBState++;
        break;
      }
      case 1:
      {
        Serial.println(F("Printing headshot..."));
        printHeadShot();
        btnBState = 0;
        break;
      }
      default:  
      {
        Serial.println(F("Default, this shouldn't happen, tell Gerald please!"));
        Serial.println(F("Printing headshot..."));
        printHeadShot();
        btnBState = 0;
        break;
      }
    }
  }
}

void setup()
{
  // Set the wake pin to HIGH to keep the chip enabled.
  // Otherwise any button press will call setup again.
  pinMode(WAKE_PIN, OUTPUT);
  digitalWrite(WAKE_PIN, HIGH);

  // Initialize Serial
  Serial.begin(BAUD_SPEED);
  Serial.println();
  Serial.println(F("Setup..."));
  
  // Initialize Display
  initDisplay();

  // Print headshot as setup / standby picture
  Serial.println(F("Printing headshot..."));
  printHeadShot();

  // The display class is setting pin 12 as output (theory).
  // The pinMode for input has to be set AFTER the display.init() has been called.
  // Specify both buttons as input --> PULLUP effectively inverts the behavior of the INPUT mode, where HIGH means the sensor is off, and LOW means the sensor is on.
  pinMode(BUTTONA_PIN, INPUT_PULLUP);
  pinMode(BUTTONB_PIN, INPUT_PULLUP);
  
  Serial.println(F("Setup done"));
  Serial.println();
  Serial.println(F("Welcome to Code Card - by Gerald Venzl"));
  
  cli.printHelp();
}

void loop()
{
  checkButtonA();
  checkButtonB();
  cli.read();
  // sleep for 100ms
  delay(100);
}
