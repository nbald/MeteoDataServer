/*
 * Copyright (c) 2013 the OpenMeteoData project
 * All rights reserved.
 *
 * Authors: Nicolas BALDECK <nicolas.baldeck@openmeteodata.org>
 *          Dale MELLOR <dale@rdmp.org>
 * 
 * This file is a part of MeteoDataServer
 * 
 * MeteoDataServer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MeteoDataServer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



#include <MeteoDataServer/config.h>


namespace MeteoDataServer {



  void Config::reload ()
  {
    std::ifstream fileStream (fileName_.c_str());

    if (! reader_.parse (fileStream, object_))
      throw FileException (reader_.getFormattedErrorMessages ());
  }



  std::string Config::getString (KeyName const &keyName)
  {
    if (! object_.isMember (keyName))
      throw KeyNotFoundException (keyName + " not found");

    if (! object_[keyName].isString ())
      throw BadTypeException (keyName + " parameter is not a string");

    return object_[keyName].asString ();
  }



  int Config::getInt (KeyName const &keyName)
  {
    if (! object_.isMember (keyName))
      throw KeyNotFoundException (keyName + " not found");

    if (! object_[keyName].isNumeric ())
      throw BadTypeException (keyName + " parameter is not a number");

    return object_[keyName].asInt ();
  }


}  /* End of namespace MeteoDataServer. */
