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
#include "config.h"



Config::Config (const FileName &fileName) : fileName_ (fileName)
{
  reload();
}



void Config::reload()
{
  std::ifstream fileStream (fileName_.c_str());
  
  if ( ! reader_.parse( fileStream, object_ ) )
  {
      throw FileException (reader_.getFormattedErrorMessages());
  }
}



std::string Config::getString(const KeyName &keyName)
{
  if (object_.isMember(keyName))
  {
    if (!object_[keyName].isString()) {
      std::stringstream errorMsg;
      errorMsg << keyName << " parameter is not a string";
      throw BadTypeException(errorMsg.str());
    }
    return object_[keyName].asString();
  }
  else
  {
    std::stringstream errorMsg;
    errorMsg << keyName << " not found";
    throw KeyNotFoundException(errorMsg.str());
  }
}



int Config::getInt(const KeyName &keyName)
{
  if (object_.isMember(keyName))
  {
    if (!object_[keyName].isNumeric())
    {
      std::stringstream errorMsg;
      errorMsg << keyName << " parameter is not a number";
      throw BadTypeException(errorMsg.str());
    }
    return object_[keyName].asInt();
  }
  else
  {
    std::stringstream errorMsg;
    errorMsg << keyName << " not found";
    throw KeyNotFoundException(errorMsg.str());
  }
}
