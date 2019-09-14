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

void printSpeaker(Speaker speaker)
{
  Serial.println(F("**************** SPEAKER *****************"));
  Serial.println("Name: " + speaker.name);
  Serial.println("Title: " + speaker.title);
  Serial.println("Company: " + speaker.company);
  Serial.println("Twitter: " + speaker.twitterHandle);
  Serial.println("Blog: " + speaker.blogUrl);
  Serial.println("Youtube: " + speaker.youtubeChannel);
  Serial.println(F("******************************************"));
}

Speaker retrieveSpeaker()
{
  Speaker speaker;
  Serial.println(F("DEBUG: Retrieving speaker from EEPROM"));
  EEPROM.get(SPEAKER_EEPROM_ADDR, speaker);
  return speaker;
}

/*
 * 0 --> speaker stored
 * 1 --> speaker equal
 */
int updateSpeaker(Speaker speaker)
{
  Serial.println(F("Updating speaker information..."));
  Speaker speakerStored = retrieveSpeaker();
  Serial.println(F("Old stored speaker details:"));
  printSpeaker(speakerStored);
  
  // Only write speaker struct if it is different.
  if (!isEqualSpeakerStruct(speaker, speakerStored))
  {
    Serial.println(F("DEBUG: Writing speaker to EEPROM"));
    EEPROM.put(SPEAKER_EEPROM_ADDR, speaker);
    return 0;
  }
  else
  {
    Serial.println(F("DEBUG: Speaker is identical, not persisting!"));
    return 1;
  }
}

bool isEqualSpeakerStruct(struct Speaker current, struct Speaker stored)
{
  return ( current.name           == stored.name &&
           current.title          == stored.title &&
           current.company        == stored.company &&
           current.twitterHandle  == stored.twitterHandle &&
           current.blogUrl        == stored.blogUrl &&
           current.youtubeChannel == stored.youtubeChannel
         );
}

Talks::Talk *retrieveTalks()
{
  Talks::Talk talks[MAX_TALKS];
  return talks;
}

int updateTalks(Talks::Talk talks[])
{
  return 0;
}
