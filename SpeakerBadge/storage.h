/*
 * File: storage.h
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

#ifndef STORAGE_H
#define STORAGE_H

#include "speaker.h"
#include "talks.h"

#define SPEAKER_EEPROM_ADDR 0
#define TALKS_EEPROM_ADDR sizeof(struct Speaker)

int updateSpeaker(Speaker speaker);
Speaker retrieveSpeaker();
bool isEqualSpeakerStruct(struct Speaker current, struct Speaker stored);
void printSpeaker(struct Speaker speaker);

int updateTalks(Talks::Talk talks[]);
Talks::Talk *retrieveTalks();

#endif
