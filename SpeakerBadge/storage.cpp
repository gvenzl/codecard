/*
 * File: storage.cpp
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

#include "storage.h"

#include <Arduino.h>
#include <EEPROM.h>

#include "config.h"
#include "speaker.h"
#include "talks.h"

extern void debugPrintSpeaker(Speaker speaker);

Storage::Storage()
{
  EEPROM.begin(EEPROM_SIZE);
}

Storage::~Storage()
{
  EEPROM.end();
}

Speaker Storage::retrieveSpeaker()
{
  Serial.println(F("DEBUG: Retrieving speaker from EEPROM"));
  EEPROM.get(SPEAKER_EEPROM_ADDR, this->speaker);
  return this->speaker;
}

/*
 * 0 --> speaker stored
 * 1 --> speaker equal
 */
int Storage::updateSpeaker(Speaker speaker_new)
{
  Serial.println(F("Updating speaker information..."));
  this->speaker = retrieveSpeaker();
  Serial.println(F("Old stored speaker details:"));
  debugPrintSpeaker(this->speaker);
  
  // Only write speaker struct if it is different.
  if (!this->isEqualSpeakerStruct(speaker_new))
  {
    Serial.println(F("DEBUG: Writing speaker to EEPROM"));
    EEPROM.put(SPEAKER_EEPROM_ADDR, speaker_new);
    EEPROM.commit();
    return 0;
  }
  else
  {
    Serial.println(F("DEBUG: Speaker is identical, not persisting!"));
    return 1;
  }
}

bool Storage::isEqualSpeakerStruct(struct Speaker current)
{
  return ( current.name           == this->speaker.name &&
           current.title          == this->speaker.title &&
           current.company        == this->speaker.company &&
           current.twitterHandle  == this->speaker.twitterHandle &&
           current.blogUrl        == this->speaker.blogUrl &&
           current.youtubeChannel == this->speaker.youtubeChannel
         );
}

Talks::Talk *Storage::retrieveTalks()
{
  Talks::Talk talks[MAX_TALKS];
  return talks;
}

int Storage::updateTalks(Talks::Talk talks[])
{
  return 0;
}
