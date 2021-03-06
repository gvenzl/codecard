/*
 * File: cli.h
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

#ifndef CLI_H
#define CLI_H

#include <Arduino.h>

class CLI
{
  private:
    enum class SpeakerInput
    {
      READ,
      NAME,
      TITLE,
      COMPANY,
      TWITTER,
      BLOG,
      YOUTUBE
    };

    SpeakerInput speakerInput = SpeakerInput::READ;

    enum class TalkInput
    {
      READ,
      TITLE,
      TITLELINE2,
      TITLELINE3,
      TIME,
      LOCATION
    };

    TalkInput talkInput = TalkInput::READ;
    
    void validateInput(String input);
    void addTalk(String input);
    void deleteTalk(String input);
    void storeSpeaker(String input);

  public:
    void read();
    void printHelp();
};

#endif
