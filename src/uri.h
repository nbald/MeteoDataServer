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
 *  
*/
#ifndef MDS_URI_H
#define MDS_URI_H

#include <vector>
#include <string>
#include <cstdio>
#include <map>

class Uri
{
  
  typedef std::string QueryString;
  typedef std::string Value;
  typedef std::string Key;
  
  typedef std::string EmptyException;
  typedef std::string KeyNotFoundException;
  
public:
    void parse(Uri::QueryString string);
    void urlDecode(Uri::QueryString& queryString);
    void split(std::vector< std::string >& splitStr, const std::string& str, char delimiter);
    Value getVar(Key);
    bool isVar(Key);
protected:
private:
    QueryString uriString_;
    std::map<Key,Value> vars_;
};

#endif
