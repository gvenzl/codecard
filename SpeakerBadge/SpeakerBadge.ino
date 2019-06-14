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

#include "config.h"
#include "icons.h"

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

void printContact(String twitterHandle, String blogURL, String youtubeChannel)
{
  Serial.println("Printing contact...");

  display.firstPage();
  
  do
  {
    display.fillScreen(GxEPD_WHITE);

    if (twitterHandle != "") {
      // Print Twitter icon
      display.drawInvertedBitmap(0, 0, twitter, 61, 50, GxEPD_BLACK);

      // Put handle next to icon
      display.setFont(&FreeMonoBold12pt7b);
      display.getTextBounds(twitterHandle, 65, 50, &tbx, &tby, &tbw, &tbh);
      // X, Y = 61, 50 is where the twitter handle has been printed
      // X is set to 1 (beginning pixles of the text, Y is set to the height of the text as the pixels are printed from the bottom up, not top down)
      // 10 + is done to gain some more padding from the top
      display.setCursor(tbx, tby);
      display.println(twitterHandle);
    }

    if (blogURL != "") {
      // Print Blog icon
      display.drawInvertedBitmap(0, 55, blog, 60, 60, GxEPD_BLACK);

      // Put blog URL next to icon
      display.setFont(&FreeMonoBold12pt7b);
      display.getTextBounds(blogURL, 65, 110, &tbx, &tby, &tbw, &tbh);
      // X, Y = 60, 110 is where the text should be printen (110 = 50 from the twitter icon and 60 from the blog icon)
      // X is set to 1 (beginning pixles of the text, Y is set to the height of the text as the pixels are printed from the bottom up, not top down)
      // 20 + is done to gain some more padding from the top
      display.setCursor(tbx, tby);
      display.println(blogURL);
    }

    if (youtubeChannel != "") {
      // Print Youtube icon icon
      display.drawInvertedBitmap(0, 120, youtube, 64, 64, GxEPD_BLACK);

      // Put youtube URL next to icon
      display.setFont(&FreeMonoBold12pt7b);
      display.getTextBounds(youtubeChannel, 65, 174, &tbx, &tby, &tbw, &tbh);
      // X, Y = 60, 110 is where the text should be printen (110 = 50 from the twitter icon and 60 from the blog icon)
      // X is set to 1 (beginning pixles of the text, Y is set to the height of the text as the pixels are printed from the bottom up, not top down)
      // 20 + is done to gain some more padding from the top
      display.setCursor(tbx, tby);
      display.println(youtubeChannel);
    }
  }
  while (display.nextPage());

  display.powerOff();
}

void printHeadShot()
{
  display.firstPage();
  
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.drawInvertedBitmap(0, 0, headShot, display.width(), display.height(), GxEPD_BLACK);
  }
  while (display.nextPage());
  
  display.powerOff();
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
  display.firstPage();
  do
  {
    display.setFont(&FreeMonoBold18pt7b);
    display.getTextBounds(name, 0, 0, &tbx, &tby, &tbw, &tbh);
    // X, Y = 0, 0 is the top left corner (given that the display has been already rotated).
    // X is set to 1 (beginning pixles of the text), Y is set to the height of the text as the pixels are printed from the bottom up, not top down
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
    printContact("@GeraldVenzl", "geraldonit.com", "OracleDevs");
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
  Serial.println("Setup...");
  
  // Initialize Display
  initDisplay();

  // Print headshot as setup / standby picture
  printHeadShot();

  // The display class is setting pin 12 as output (theory).
  // The pinMode for input has to be set AFTER the display.init() has been called.
  // Specify both buttons as input --> PULLUP effectively inverts the behavior of the INPUT mode, where HIGH means the sensor is off, and LOW means the sensor is on.
  pinMode(BUTTONA_PIN, INPUT_PULLUP);
  pinMode(BUTTONB_PIN, INPUT_PULLUP);
  
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
