/*
 * File: cli.cpp
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

#include "cli.h"

#include <Arduino.h>

#include "speaker.h"
#include "talks.h"

extern Speaker speaker;
extern Talks talks;
extern int btnAState;

Talks::Talk talk;

void CLI::read()
{
  if (Serial.available() > 0) {
    String input = Serial.readString();
    input.trim();
    Serial.println("Received: " + input);
    validateInput(input);
  }
}

void CLI::validateInput(String input)
{
  if      (input == "help")    { printHelp(); }
  else if (speakerInput != SpeakerInput::READ || input == "speaker") { storeSpeaker(input);  }
  else if (talkInput != TalkInput::READ || input == "talkadd") { addTalk(input); }
  else if (input == "talkdel") { deleteTalk(input); }
  else
  {
    Serial.println("'" + input + "' is not a valid command.");
    printHelp();
  }
}

void CLI::printHelp()
{
  Serial.println(F("Commands:"));
  Serial.println(F("  help       Shows this help"));
  Serial.println(F("  speaker    Adds a new speakers"));
  Serial.println(F("  talkadd    Adds a new talk to the card"));
  Serial.println(F("  talkdel    Deletes one or all talks"));
  Serial.println();
}

void CLI::addTalk(String input)
{
  switch(talkInput)
  {
    case TalkInput::READ:
    {
      // If all talks are used up, cancel
      if (!talks.hasFreeTalkSlot())
      {
        Serial.println(F("You cannot add any more talks. Please delete one/all and retry."));
        talkInput = TalkInput::READ;
        break;
      }
      
      talk = Talks::Talk();
      Serial.println(F("Please enter the title of your talk:"));
      talkInput = TalkInput::TITLE;
      break;
    }
    case TalkInput::TITLE:
    {
      talk.setTitle(input);
      Serial.println(F("Please add the second line, if any:"));
      talkInput = TalkInput::TITLELINE2;
      break;
    }
    case TalkInput::TITLELINE2:
    {
      talk.setTitleLine2(input);
      Serial.println(F("Please add the third line, if any:"));
      talkInput = TalkInput::TITLELINE3;
      break;
    }
    case TalkInput::TITLELINE3:
    {
      talk.setTitleLine3(input);
      Serial.println(F("Please add the date/time of your talk:"));
      talkInput = TalkInput::TIME;
      break;
    }
    case TalkInput::TIME:
    {
      talk.setTime(input);
      Serial.println(F("Please add the location of your talk:"));
      talkInput = TalkInput::LOCATION;
      break;
    }
    case TalkInput::LOCATION:
    {
      talk.setLocation(input);
      talks.addTalk(talk);
      Serial.println(F("Talk details saved"));
      
      // Reset button A state and talks index to sync
      btnAState = talks.getNextTalkIndex();
      
      talkInput = TalkInput::READ;
      break;
    }
    default:
    {
      speakerInput = SpeakerInput::READ;
      break;
    }
  }
}

void CLI::deleteTalk(String input)
{
  Serial.println(F("Deleting all talks"));
  talks.deleteAllTalks();
  
  btnAState = talks.getTalkCount();
}

void CLI::storeSpeaker(String input)
{
  switch(speakerInput)
  {
    case SpeakerInput::READ:
    { 
      Serial.println(F("Please enter your name:"));
      speakerInput = SpeakerInput::NAME;
      break;
    }
    case SpeakerInput::NAME:
    {
      speaker.setName(input);
      Serial.println(F("Please enter your title:"));
      speakerInput = SpeakerInput::TITLE;
      break;
    }
    case SpeakerInput::TITLE:
    {
      speaker.setTitle(input);
      Serial.println(F("Please enter your company:"));
      speakerInput = SpeakerInput::COMPANY;
      break;
    }
    case SpeakerInput::COMPANY:
    {
      speaker.setCompany(input);
      Serial.println(F("Please enter your Twitter handle:"));
      speakerInput = SpeakerInput::TWITTER;
      break;
    }
    case SpeakerInput::TWITTER:
    {
      speaker.setTwitterHandle(input);
      Serial.println(F("Please enter your Blog URL:"));
      speakerInput = SpeakerInput::BLOG;
      break;
    }
    case SpeakerInput::BLOG:
    {
      speaker.setBlogUrl(input);
      Serial.println(F("Please enter your YouTube channel:"));
      speakerInput = SpeakerInput::YOUTUBE;
      break;
    }
    case SpeakerInput::YOUTUBE:
    {
      speaker.setYoutubeChannel(input);
      // Store speaker object
      Serial.println(F("Speaker details saved."));
      speakerInput = SpeakerInput::READ;
      break;
    }
    default:
    {
      speakerInput = SpeakerInput::READ;
      break;
    }
  }
}
