/*
 * Copyright (c) 2013 the OpenMeteoData project
 * All rights reserved.
 *
 * Author: Nicolas BALDECK <nicolas.baldeck@openmeteodata.org>
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

#ifndef METEO_DATA_SERVER__CONFIG__H
#define METEO_DATA_SERVER__CONFIG__H

#include <string>
#include <fstream>

#include <jsoncpp/json/json.h>


namespace MeteoDataServer {
  

  class Config
  {

    typedef std::string FileName;
    typedef Json::Value Object;
    typedef std::string KeyName;
    
    typedef std::string FileException;
    typedef std::string KeyNotFoundException;
    typedef std::string BadTypeException;

  public:

    Config (const FileName &f) : fileName_ (f) { reload(); }

    std::string getString (const KeyName &);

    int getInt (const KeyName &);

    void reload ();


  protected:

  private:
    Object object_;
    FileName fileName_;
    Json::Reader reader_;

  };  /* End of class Config. */


}  /* End of namespace MeteoDataServer. */

  
#endif  /* Undefined METEO_DATA_SERVER__CONFIG__H. */
