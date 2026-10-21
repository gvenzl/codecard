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

// Global vars
GxEPD2_BW<GxEPD2_270, GxEPD2_270::HEIGHT> display(GxEPD2_270(/*CS=D8*/ 2, /*DC=D3*/ 0, /*RST=D4*/ 4, /*BUSY=D2*/ 5)); // 2.7" b/w 264x176
CLI cli = CLI();

Speaker speaker = Speaker();
Talks talks = Talks();
int btnAState   = 0;
int btnBState   = 0;
int currentTalk = 0;

void initDisplay()
{
  display.init(BAUD_SPEED);
  display.setRotation(PRINT_LANDSCAPE);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
}

void initSpeaker()
{
  speaker.setName("Gerald Venzl");
  speaker.setTitle("VP, Dev & AI Initiatives");
  speaker.setCompany("Oracle AI Database");
  speaker.setBlogUrl("GeraldOnIT.com");
  speaker.setLinkedInHandle("GeraldVenzl");
  speaker.setBlueSkyHandle("gvenzl");
  speaker.setTwitterHandle("@GeraldVenzl");
  speaker.setYoutubeChannel("GeraldOnIT");
}

void initTalks()
{
  Talks::Talk talk;

  talk = Talks::Talk("Oracle User Groups", "Leader Reception", "", "Oct 25 - 19:00-21:00", "Buddy V's Ristorante");
  talks.addTalk(talk);

  talk = Talks::Talk("Oracle ACE", "Souvenir Exchange", "", "Oct 26 - 16:00-17:00", "ACE Hub");
  talks.addTalk(talk);

  talk = Talks::Talk("Oracle ACE", "Reception", "", "Oct 27 - 18:00-21:00", "Mercato Della Pescheria");
  talks.addTalk(talk);

  talk = Talks::Talk("Global Leaders", "Customer Event", "", "Oct 28 - 13:00-20:00", "Ghostbar");
  talks.addTalk(talk);

  talk = Talks::Talk("Oracle ACE", "Adventure", "", "Oct 29 - 07:45-14:00", "Hoover Dam");
  talks.addTalk(talk);
}

void checkButtonA()
{
  if (digitalRead(BUTTONA_PIN) == HIGH)
  {
    Serial.println(F("State of Button A has changed!"));

    // Change button B back to 0
    btnBState = 0;

    switch (btnAState)
    {
      case 0:
      {
        Serial.println(F("Printing name..."));
        printName();
        btnAState++;
        break;
      }

      case 1:
      {
        Serial.println(F("Printing LinkedIn QR code..."));
        printLinkedInQRCode();
        btnAState++;
        break;
      }

      case 2:
      {
        Serial.println(F("Printing Headshot..."));
        printHeadShot();
        btnAState++;
        break;
      }

      case 3:
      {
        Serial.println(F("Printing next talk..."));
        Serial.println("DEBUG: TalkCount: " + String(talks.getTalkCount()));
        Serial.println("DEBUG: currentTalk: " + String(currentTalk));
        Serial.println("DEBUG: nextTalkIndex: " + String(talks.getNextTalkIndex()));

        if (talks.getTalkCount() > 0 && (currentTalk < (talks.getNextTalkIndex()+1)) )
        {
          Serial.println(F("Printing next talk..."));
          Talks::Talk talk = talks.getNextTalk();
          printTalk(talk);
          currentTalk++;
          // No bntAState increase, we are still in the Talk printing
        }
        else
        {
          Serial.println(F("No talk found, printing name and skipping case 0"));
          printName();
          currentTalk=0;
          btnAState = 1;
        }
        break;
      }

      default:
      {
        Serial.println(F("Default, this shouldn't happen, tell Gerald please!"));
        Serial.println(F("Printing headshot..."));
        printHeadShot();
        btnAState = 0;
        currentTalk=0;
        break;
      }
    }
  }
}

void checkButtonB()
{
  if (digitalRead(BUTTONB_PIN) == HIGH)
  {
    Serial.println(F("State of Button B has changed!"));

    // Change button A and current talks back to 0
    btnAState = 0;
    currentTalk=0;

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
        Serial.println(F("Printing ACE Logo..."));
        printACELogo();
        btnBState++;
        break;
      }

      case 2:
      {
        Serial.println(F("Printing ace.oracle.com..."));
        printText("ace.oracle.com", 12);
        btnBState++;
        break;
      }

      case 3:
      {
        Serial.println(F("Printing OUG website..."));
        printText("oracle.com/user-groups");
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

  // Initalize speaker data
  initSpeaker();

  // Initialize Talks
  initTalks();

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
