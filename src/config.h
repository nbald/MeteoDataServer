/*
 * Copyright (c) 2013 the OpenMeteoData project
 * All rights reserved.
 *
 * Author: Nicolas BALDECK <nicolas.baldeck@openmeteodata.org>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *  
*/
#ifndef MDS_CONFIG
#define MDS_CONFIG

#include <string>
#include <fstream>
#include <sstream>

#include <jsoncpp/json/json.h>

class Config
{

  typedef std::string FileName;
  typedef Json::Value Object;
  typedef std::string KeyName;
  
  typedef std::string FileException;
  typedef std::string KeyNotFoundException;
  typedef std::string BadTypeException;

public:
  Config(const FileName &);
  std::string getString(const KeyName &);
  int getInt(const Config::KeyName& keyName);
  void reload();

protected:

private:
  Object object_;
  FileName fileName_;
  Json::Reader reader_;
};

#endif