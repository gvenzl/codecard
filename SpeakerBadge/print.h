/*
 * File: print.h
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

#ifndef PRINT_H
#define PRINT_H

#include <Arduino.h>

#include "talks.h"

// Prints the name
void printName();

// Prints the session information
void printTalk(Talks::Talk &talk);

// Prints the contact information
void printContact();

// Prints an icon
void printIcon(const unsigned char *icon);

// Prints the headShot
void printHeadShot();

// Prints the penguin picture
void printPenguin();

// Prints the microphone picture
void printMicrophone();

#endif
