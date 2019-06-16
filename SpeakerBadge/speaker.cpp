/*
 * File: speaker.cpp
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

#include "speaker.h"

Speaker::Speaker()
{
  this->name = "Gerald Venzl";
  this->title = "Master Product Manager";
  this->company = "Oracle Corporation";

  this->twitterHandle = "@GeraldVenzl";
  this->blogUrl = "geraldonit.com";
  this->youtubeChannel = "OracleDevs";
}

Speaker::Speaker(String name, String title, String company)
{
  this->name = name;
  this->title = title;
  this->company = company;
}

Speaker::Speaker(String name, String title, String company, String twitterHandle, String blogUrl, String youtubeChannel)
{
  this->name = name;
  this->title = title;
  this->company = company;
  this->twitterHandle = twitterHandle;
  this->blogUrl = blogUrl;
  this->youtubeChannel = youtubeChannel;
}

void Speaker::setName(String name)
{
  this->name = name;
}

void Speaker::setTitle(String title)
{
  this->title = title;
}

void Speaker::setCompany(String company)
{
  this->company = company;
}

void Speaker::setTwitterHandle(String twitterHandle)
{
  this->twitterHandle = twitterHandle;
}

void Speaker::setBlogUrl(String blogUrl)
{
  this->blogUrl = blogUrl;
}

void Speaker::setYoutubeChannel(String youtubeChannel)
{
  this->youtubeChannel = youtubeChannel;
}

String Speaker::getName()
{
  return this->name;
}

String Speaker::getTitle()
{
  return this->title;
}

String Speaker::getCompany()
{
  return this->company;
}

String Speaker::getTwitterHandle()
{
  return this->twitterHandle;
}

String Speaker::getBlogUrl()
{
  return this->blogUrl;
}

String Speaker::getYoutubeChannel()
{
  return this->youtubeChannel;
}
