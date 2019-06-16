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

extern Speaker speaker;

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
  else if ( speakerInput != READ || input == "speaker") { storeSpeaker(input);  }
  else if (input == "sessadd") { addSession(); }
  else if (input == "sessdel") { deleteSession(); }
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
  Serial.println(F("  sessadd    Adds a new session to the card"));
  Serial.println(F("  sessdel    Deletes one or all sessions"));
  Serial.println();
}

void CLI::addSession()
{
  
}

void CLI::deleteSession()
{
  
}

void CLI::storeSpeaker(String input)
{
  switch(speakerInput)
  {
    case READ:
    {
      Serial.println(F("Please enter your name:"));
      speakerInput = NAME;
      break;
    }
    case NAME:
    {
      speaker.setName(input);
      Serial.println(F("Please enter your title:"));
      speakerInput = TITLE;
      break;
    }
    case TITLE:
    {
      speaker.setTitle(input);
      Serial.println(F("Please enter your company:"));
      speakerInput = COMPANY;
      break;
    }
    case COMPANY:
    {
      speaker.setCompany(input);
      Serial.println(F("Please enter your Twitter handle:"));
      speakerInput = TWITTER;
      break;
    }
    case TWITTER:
    {
      speaker.setTwitterHandle(input);
      Serial.println(F("Please enter your Blog URL:"));
      speakerInput = BLOG;
      break;
    }
    case BLOG:
    {
      speaker.setBlogUrl(input);
      Serial.println(F("Please enter your YouTube channel:"));
      speakerInput = YOUTUBE;
      break;
    }
    case YOUTUBE:
    {
      speaker.setYoutubeChannel(input);
      // Store speaker object
      Serial.println(F("Speaker details saved."));
      speakerInput = READ;
      break;
    }
    default:
    {
      speakerInput = READ;
      break;
    }
  }
}
