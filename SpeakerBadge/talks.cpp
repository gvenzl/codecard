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

#include "talks.h"

#include <Arduino.h>

Talks::Talks()
{
  Talk talk = { .title="Cloud-Native", .titleLine2="Data Management", .titleLine3="", .time = "Tuesday 17 Sept - 11:30", .location ="Moscone South - Room 301" };
  addTalk(talk);

  talk = { .title="Code One", .titleLine2="Keynote", .titleLine3="", .time="Tuesday 17 Sept - 14:30", .location="Moscone North - Hall F" };
  addTalk(talk);

  talk = { .title="Code One", .titleLine2="Community Keynote:", .titleLine3="Game On!", .time="Wed 18 Sept - 09:00", .location="Moscone North - Hall F" };
  addTalk(talk);
}

bool Talks::hasFreeTalkSlot()
{
  return talkCount < MAX_TALKS;
}

bool Talks::addTalk(Talk talk)
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
  Serial.println("DEBUG: title -> " + talk.title);
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
    talks[i] = { };
  }
  this->talkCount=0;
  this->nextTalkIdx=0;
  return true;
}

bool Talks::deleteTalk(int index)
{
  //TODO: If in the middle, move talks forward in index
  // Delete sencond talk, make talk 3 --> 2, 4 --> 3, etc.
  talks[index] = { };
  return true;
}
