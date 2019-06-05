/*
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
#include <Fonts/FreeMonoBold18pt7b.h>  // Adafruit GFX graphics core library - https://github.com/adafruit/Adafruit-GFX-Library
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMono9pt7b.h>

#define WAKE_PIN 16
#define BAUD_SPEED 115200
#define PRINT_LANDSCAPE 3

// Button pins
#define BUTTONA_PIN 10   // 10
#define BUTTONB_PIN 12   // 12

bool btnAOn = false;
bool btnBOn = false;

GxEPD2_BW<GxEPD2_270, GxEPD2_270::HEIGHT> display(GxEPD2_270(/*CS=D8*/ 2, /*DC=D3*/ 0, /*RST=D4*/ 4, /*BUSY=D2*/ 5)); // 2.7" b/w 264x176

void printName()
{
  Serial.println("Printing name");
  printNameTemplate("Gerald Venzl", "Master Product Manager", "Oracle Corporation");
}

void printSession()
{
  Serial.println("Printing Session...");
  printSessionTemplate("Monday June 24 - 11:00AM", "Room 620, Level 6", "Decrypting the", "Tech Hype", "for the Busy Coder");
}

void printContact()
{
  
}

void initDisplay()
{
  display.init(BAUD_SPEED);
  display.setRotation(PRINT_LANDSCAPE);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
}

void printNameTemplate(String name, String title, String company)
{  
  int16_t tbx, tby; uint16_t tbw, tbh;
  
  display.firstPage();
  do
  {
    display.setFont(&FreeMonoBold18pt7b);
    display.getTextBounds(name, 0, 0, &tbx, &tby, &tbw, &tbh);
    // X, Y = 0, 0 is the top left corner (given that the display has been already rotated.
    // X is set to 1 (beginning pixles of the text, Y is set to the height of the text as the pixels are printed from the bottom up, not top down)
    // 20 + is done to gain some more padding from the top
    display.setCursor(tbx, 20 + tbh);
    display.println(name);
    display.println();
    display.setFont(&FreeMonoBold9pt7b);
    display.println(title);
    display.println();
    display.println(company);
    
  }
  while (display.nextPage());

  display.powerOff();
}

void printSessionTemplate(String time, String room, String title)
{
  printSessionTemplate(time, room, title, "", "");
}

void printSessionTemplate(String time, String room, String title, String titleLine2)
{
  printSessionTemplate(time, room, title, titleLine2, "");
}

void printSessionTemplate(String time, String room, String title, String titleLine2, String titleLine3)
{
  int16_t tbx, tby; uint16_t tbw, tbh;
  
  display.firstPage();
  do
  {
    display.setFont(&FreeMonoBold12pt7b);
    display.getTextBounds(title, 0, 0, &tbx, &tby, &tbw, &tbh);
    /* X, Y = 0, 0 is the top left corner (given that the display has been already rotated.
     * X is set to 1 (beginning pixles of the text, Y is set to the height of the text as the pixels are printed from the bottom up, not top down)
     * 20 + is done to gain some more padding from the top
    */
    display.setCursor(tbx, tbh);
    display.println(title);
    if (titleLine2 != "") { display.println(titleLine2); }
    if (titleLine3 != "") { display.println(titleLine3); }
    display.println();
    display.setFont(&FreeMono9pt7b);
    display.println(time);
    display.println();
    display.println(room);
    
  }
  while (display.nextPage());

  display.powerOff();
}

void checkSerialInput()
{
  if (Serial.available() > 0) {
      String input = Serial.readString();
      input.trim();
      Serial.println("Received: " + input);
      // TODO implement
    }
}

void checkButtonA()
{
  if (digitalRead(BUTTONA_PIN) == HIGH)
  {
    Serial.println("State of Button A has changed!");
    // Button A has been switched on, print session details.
    if (!btnAOn)
    {
      printSession();
      btnAOn = true;
    }
    // Button has been switched off, print name.
    else
    {
      printName();
      btnAOn = false;
    }
  }
}

void checkButtonB()
{
  if (digitalRead(BUTTONB_PIN) == HIGH)
  {
    Serial.println("State of Button B has changed!");
    // Button B has been switched on, print contact details
    if (!btnBOn)
    {
      printContact();
      btnBOn = true;
    }
    // Button has been switched off, print name.
    else
    {
      printName();
      btnBOn = false;
    }
  }
}

void setup()
{
  pinMode(WAKE_PIN, OUTPUT);
  digitalWrite(WAKE_PIN, HIGH); //immediately set wake pin to HIGH to keep the chip enabled

  // Specify both buttons as input --> PULLUP effectively inverts the behavior of the INPUT mode, where HIGH means the sensor is off, and LOW means the sensor is on.
  pinMode(BUTTONA_PIN, INPUT_PULLUP);
  pinMode(BUTTONB_PIN, INPUT_PULLUP);
  delay(100);
  
  Serial.begin(BAUD_SPEED);
  Serial.println();
  Serial.println("Setup...");
  delay(100);
  initDisplay();

  printName();
  
  Serial.println("Setup done");
}

void loop()
{
    checkSerialInput();
    checkButtonA();
    checkButtonB();
    // sleep for 100ms
    delay(100);
}
