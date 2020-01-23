/*
 * File: config.h
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

#ifndef CONFIG_H
#define CONFIG_H

// Wake pin (keeps chip running)
#define WAKE_PIN 16

// Button pins
#define BUTTONA_PIN 10   // 10
#define BUTTONB_PIN 12   // 12

// Baud speed
#define BAUD_SPEED 115200

// Display orientation
#define PRINT_LANDSCAPE 3

// How many talks to support
#define MAX_TALKS 6

#endif
