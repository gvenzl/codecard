/*
 * File: print.cpp
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

#include "print.h"

#include <Arduino.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold18pt7b.h>  // Adafruit GFX graphics core library - https://github.com/adafruit/Adafruit-GFX-Library
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMono9pt7b.h>

#include "icons.h"

int16_t tbx, tby;
uint16_t tbw, tbh;

extern GxEPD2_BW<GxEPD2_270, GxEPD2_270::HEIGHT> display;

/********************************************************************************************/
/***************************************** NAME PRINT ***************************************/
/********************************************************************************************/

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

void printName()
{
  printNameTemplate("Gerald Venzl", "Master Product Manager", "Oracle Corporation");
}

/********************************************************************************************/
/************************************** SESSION PRINT ***************************************/
/********************************************************************************************/

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

void printSessionTemplate(String time, String room, String title, String titleLine2)
{
  printSessionTemplate(time, room, title, titleLine2, "");
}

void printSessionTemplate(String time, String room, String title)
{
  printSessionTemplate(time, room, title, "", "");
}

void printSession()
{
  printSessionTemplate("Monday June 24 - 11:00AM", "Room 620, Level 6", "Decrypting the", "Tech Hype", "for the Busy Coder");
}

/********************************************************************************************/
/************************************** CONTACT PRINT ***************************************/
/********************************************************************************************/

void printContact(String twitterHandle, String blogURL, String youtubeChannel)
{
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

/********************************************************************************************/
/************************************** HEADSHOT PRINT **************************************/
/********************************************************************************************/

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
