/*
 * File: Talks.h
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

#ifndef TALKS_H
#define TALKS_H

#include <Arduino.h>
#include "config.h"

class Talks
{
  public:
  
    class Talk
    {
      protected:
        String title;
        String titleLine2;
        String titleLine3;
        String time;
        String location;

      public:
        void setTitle(String title);
        void setTitleLine2(String titleLine2);
        void setTitleLine3(String titleLine3);
        void setTime(String time);
        void setLocation(String location);
        
        String getTitle();
        String getTitleLine2();
        String getTitleLine3();
        String getTime();
        String getLocation();
    };

    Talks();
    bool hasFreeTalkSlot();
    bool addTalk(Talk &talk);
    Talk getNextTalk();
    int getTalkCount();
    int getNextTalkIndex();
    bool deleteAllTalks();
    bool deleteTalk(int index);
    
  protected:

    Talk talks[MAX_TALKS];
    int talkCount = 0;
    int nextTalkIdx = 0;
};

#endif
