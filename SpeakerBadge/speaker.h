/*
 * File: speaker.h
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

#ifndef SPEAKER_H
#define SPEAKER_H

#include <Arduino.h>

class Speaker
{
  private:
    String name;
    String title;
    String company;
    String twitterHandle;
    String blogUrl;
    String youtubeChannel;

  public:
    Speaker();
    Speaker(String name, String title, String company);
    Speaker(String name, String title, String company, String twitterHandle, String blogUrl, String youtubeChannel);
    
    void setName(String name);
    void setTitle(String title);
    void setCompany(String company);
    void setTwitterHandle(String twitterHandle);
    void setBlogUrl(String blogUrl);
    void setYoutubeChannel(String youtubeChannel);

    String getName();
    String getTitle();
    String getCompany();
    String getTwitterHandle();
    String getBlogUrl();
    String getYoutubeChannel();
};

#endif
