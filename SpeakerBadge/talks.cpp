/*
 * File: Talks.cpp
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

#include "Talks.h"

#include <Arduino.h>

Talks::Talks()
{
  Talk talk = Talk("Cloud-Native", "Data Management","", "Tuesday 17 Sept - 11:30", "Moscone South - Room 301");
  addTalk(talk);

  talk = Talk("Code One", "Keynote", "", "Tuesday 17 Sept - 14:30", "Moscone North - Hall F");
  addTalk(talk);

  talk = Talk("Code One", "Community Keynote:", "Game On!", "Wed 18 Sept - 09:00", "Moscone North - Hall F");
  addTalk(talk);
}

Talks::Talk::Talk()
{
  
}

Talks::Talk::Talk(String title, String titleLine2, String titleLine3, String time, String location)
{
  this->title = title;
  this->titleLine2 = titleLine2;
  this->titleLine3 = titleLine3;
  this->time= time;
  this->location = location;
}

void Talks::Talk::setTitle(String title)
{
  this->title = title;
}

void Talks::Talk::setTitleLine2(String titleLine2)
{
  this->titleLine2 = titleLine2;
}

void Talks::Talk::setTitleLine3(String titleLine3)
{
  this->titleLine3 = titleLine3;
}

void Talks::Talk::setTime(String time)
{
  this->time = time;
}

void Talks::Talk::setLocation(String location)
{
  this->location = location;
}

String Talks::Talk::getTitle()
{
  return this->title;
}

String Talks::Talk::getTitleLine2()
{
  return this->titleLine2;
}

String Talks::Talk::getTitleLine3()
{
  return this->titleLine3;
}

String Talks::Talk::getTime()
{
  return this->time;
}

String Talks::Talk::getLocation()
{
  return this->location;
}

bool Talks::hasFreeTalkSlot()
{
  return talkCount < MAX_TALKS;
}

bool Talks::addTalk(Talk &talk)
{
  if (this->talkCount == MAX_TALKS)
  {
    // Maximum amount of talks reached
    return false;
  }

  this->talks[this->talkCount] = talk;
  this->talkCount++;
  return true;
}

Talks::Talk Talks::getNextTalk()
{
  // Round robin talks, start again from first talk
  if (this->nextTalkIdx >= this->talkCount)
  {
    this->nextTalkIdx = 0;
  }

  Serial.println("DEBUG: nextTalkIdx -> " + String(this->nextTalkIdx));
  Talk talk = this->talks[nextTalkIdx];
  Serial.println("DEBUG: title -> " + talk.getTitle());
  this->nextTalkIdx++;
    
  return talk;
}

int Talks::getTalkCount()
{
  return this->talkCount;
}

int Talks::getNextTalkIndex()
{
  return this->nextTalkIdx;
}

bool Talks::deleteAllTalks()
{
  for(int i=0; i < this->talkCount; i++)
  {
    talks[i] = Talk();
  }
  this->talkCount=0;
  this->nextTalkIdx=0;
  return true;
}

bool Talks::deleteTalk(int index)
{
  return false;
}
