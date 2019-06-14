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

// Wake pin (keeps chip running)
#define WAKE_PIN 16

// Button pins
#define BUTTONA_PIN 10   // 10
#define BUTTONB_PIN 12   // 12
bool btnAOn = true;  // Set to true to print name first

// Baud speed
#define BAUD_SPEED 115200
#define PRINT_LANDSCAPE 3

int16_t tbx, tby;
uint16_t tbw, tbh;

GxEPD2_BW<GxEPD2_270, GxEPD2_270::HEIGHT> display(GxEPD2_270(/*CS=D8*/ 2, /*DC=D3*/ 0, /*RST=D4*/ 4, /*BUSY=D2*/ 5)); // 2.7" b/w 264x176
