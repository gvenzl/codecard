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
#include "speaker.h"
#include "talks.h"

int16_t tbx, tby;
uint16_t tbw, tbh;

extern GxEPD2_BW<GxEPD2_270, GxEPD2_270::HEIGHT> display;
extern Speaker speaker;

/********************************************************************************************/
/***************************************** NAME PRINT ***************************************/
/********************************************************************************************/

void printName()
{ 
  display.firstPage();
  do
  {
    display.setFont(&FreeMonoBold18pt7b);
    display.getTextBounds(speaker.getName(), 0, 0, &tbx, &tby, &tbw, &tbh);
    // X, Y = 0, 0 is the top left corner (given that the display has been already rotated).
    // X is set to 0 (beginning pixles of the text), Y is set to the height of the text as the pixels are printed from the bottom up, not top down
    // 20 + is done to gain some more padding from the top
    display.setCursor(tbx, 20 + tbh);
    display.println(speaker.getName());
    display.println();
    display.setFont(&FreeMonoBold9pt7b);
    display.println(speaker.getTitle());
    display.println();
    display.println(speaker.getCompany());
    
  }
  while (display.nextPage());

  display.powerOff();
}

/********************************************************************************************/
/************************************** SESSION PRINT ***************************************/
/********************************************************************************************/

void printTalk(Talks::Talk &talk)
{
  int16_t tbx, tby; uint16_t tbw, tbh;
  
  display.firstPage();
  do
  {
    display.setFont(&FreeMonoBold12pt7b);
    display.getTextBounds(talk.getTitle(), 0, 0, &tbx, &tby, &tbw, &tbh);
    // X, Y = 0, 0 is the top left corner (given that the display has been already rotated.
    display.setCursor(tbx, tbh);
    display.println(talk.getTitle());
    if (talk.getTitleLine2() != "") { display.println(talk.getTitleLine2()); }
    if (talk.getTitleLine3() != "") { display.println(talk.getTitleLine3()); }
    display.println();
    display.setFont(&FreeMono9pt7b);
    display.println(talk.getTime());
    display.println();
    display.println(talk.getLocation());
    
  }
  while (display.nextPage());

  display.powerOff();
}


/********************************************************************************************/
/***************************************** CONTACT ******************************************/
/********************************************************************************************/

void printContact()
{
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);

    if (speaker.getLinkedInHandle() != "") {
      // Print Twitter icon
      display.drawInvertedBitmap(0, 0, linkedInIcon, 50, 50, GxEPD_BLACK);

      // Put handle next to icon
      display.setFont(&FreeMonoBold12pt7b);
      display.getTextBounds(speaker.getLinkedInHandle(), 65, 48, &tbx, &tby, &tbw, &tbh);
      // X, Y = 50, 50 is where the LinkedIn handle has been printed
      // X is set to + 15 = 65 (beginning pixles of the text, Y is set to the height of the text as the pixels are printed from the bottom up, not top down)
      // Y is set to + 5 = 55
      display.setCursor(tbx, tby);
      display.println(speaker.getLinkedInHandle());
    }

    if (speaker.getBlogUrl() != "") {
      // Print Blog icon
      display.drawInvertedBitmap(0, 55, blogIcon, 60, 60, GxEPD_BLACK);

      // Put blog URL next to icon
      display.setFont(&FreeMonoBold12pt7b);
      display.getTextBounds(speaker.getBlogUrl(), 65, 110, &tbx, &tby, &tbw, &tbh);
      // X, Y = 65, 110 is where the text should be printen (110 = 50 from the twitter icon and 60 from the blog icon)
      // X is set to 1 (beginning pixles of the text, Y is set to the height of the text as the pixels are printed from the bottom up, not top down)
      display.setCursor(tbx, tby);
      display.println(speaker.getBlogUrl());
    }

    if (speaker.getYoutubeChannel() != "") {
      // Print Youtube icon icon
      display.drawInvertedBitmap(0, 120, youtubeIcon, 64, 64, GxEPD_BLACK);

      // Put youtube URL next to icon
      display.setFont(&FreeMonoBold12pt7b);
      display.getTextBounds(speaker.getYoutubeChannel(), 70, 172, &tbx, &tby, &tbw, &tbh);
      // X, Y = 70, 172 is where the text should be printen (110 = 50 from the twitter icon and 60 from the blog icon)
      // X is set to 1 (beginning pixles of the text, Y is set to the height of the text as the pixels are printed from the bottom up, not top down)
      display.setCursor(tbx, tby);
      display.println(speaker.getYoutubeChannel());
    }
  }
  while (display.nextPage());

  display.powerOff();
}

/********************************************************************************************/
/*************************************** Print text *****************************************/
/********************************************************************************************/

void printText(String text, int fontSize)
{
  display.firstPage();
  do
  {
    if (fontSize == 9)
    {
      display.setFont(&FreeMonoBold9pt7b);
    }
    else if (fontSize == 12)
    {
      display.setFont(&FreeMonoBold12pt7b);
    }
    else if (fontSize == 18)
    {
      display.setFont(&FreeMonoBold18pt7b);
    }
    else
    {
      display.setFont(&FreeMonoBold12pt7b);
    }
    display.getTextBounds(text, 10, 100, &tbx, &tby, &tbw, &tbh);
    // X, Y = 10, 100 is the middle of the page with 10px to the right for padding
    display.setCursor(tbx, tby);
    display.println(text);
  }
  while (display.nextPage());

  display.powerOff();
}

/********************************************************************************************/
/******************************************* ICON *******************************************/
/********************************************************************************************/

void printIcon(const unsigned char *icon)
{
  display.firstPage();
  
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.drawInvertedBitmap(0, 0, icon, display.width(), display.height(), GxEPD_BLACK);
  }
  while (display.nextPage());
  
  display.powerOff();
}


/********************************************************************************************/
/***************************************** HEADSHOT *****************************************/
/********************************************************************************************/

void printHeadShot()
{
  printIcon(headShotIcon);
}

/********************************************************************************************/
/**************************************** ACE LOGO ******************************************/
/********************************************************************************************/

void printACELogo()
{
  printIcon(aceLogo);
}

/********************************************************************************************/
/************************************ LINKED IN QR CODE *************************************/
/********************************************************************************************/

void printLinkedInQRCode()
{
  printIcon(linkedInQRCode);
}

/********************************************************************************************/
/************************************** PENGUIN *********************************************/
/********************************************************************************************/

void printPenguin()
{
  printIcon(penguinIcon);
}

/********************************************************************************************/
/************************************* MICROPHONE *******************************************/
/********************************************************************************************/

void printMicrophone()
{
  printIcon(microphoneIcon);
}
