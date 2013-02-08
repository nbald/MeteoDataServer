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


#ifndef METEO_DATA_SERVER__URI__H
#define METEO_DATA_SERVER__URI__H


#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <map>


namespace MeteoDataServer {


  class Uri
  {
    typedef std::string QueryString;
    typedef std::string Value;
    typedef std::string Key;

    typedef std::string EmptyException;
    typedef std::string KeyNotFoundException;

  public:

    QueryString getString () const { return uriString_; }

    void parse (QueryString const &string);

    std::string urlDecode (QueryString const &queryString);

    void split (std::vector<std::string> &splitStr,
                std::string const &str,
                char const &delimiter);

    Value getVar (Key const &) const;

    bool isVar (Key const &key) const { return vars_.count (key); }


  protected:

  private:
    QueryString uriString_;
    std::map<Key,Value> vars_;


  };  /* End of class Uri. */


}  /* End of namespace MeteoDataServer. */


#endif  /* Undefined METEO_DATA_SERVER__URI__H. */
