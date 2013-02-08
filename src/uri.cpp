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
#include "uri.h"


void Uri::parse(QueryString queryString)
{
    std::vector<std::string> args;

    // cleanup
    urlDecode(queryString);

    // find the beginning of ?arg=
    size_t pos = queryString.find_first_of("?&");

    if (pos == std::string::npos || pos+1 >= queryString.size() )
    {
        throw EmptyException ("Uri is empty");
    }

    // we don't want to catch the '?'
    pos++;

    // handle ?&arg= case
    if (queryString.at(pos) == '&') pos++;

    // keep only the interesting part
    queryString = queryString.substr(pos, std::string::npos);

    // cut queries
    split(args, queryString, '&');

    // to lower
    /*transform(uriString.begin(), uriString.end(), uriString.begin(), ::tolower);*/

    // separate variables name and data
    size_t n = args.size();
    for (size_t i=0; i<n; i++)
    {
        std::vector<std::string> tmp;
        split(tmp, args[i], '=');
        if (tmp.size() == 2)
        {
            vars_.insert(std::make_pair(tmp[0],tmp[1]));
        } else if (tmp.size() == 1)
        {
            vars_.insert(std::make_pair(tmp[0],""));
        }
    }

    uriString_ = queryString;

}



bool Uri::isVar(Key key) {
    return (vars_.count(key) != 0);
}




Uri::Value Uri::getVar(Key key)
{
    if ( isVar(key) )
    {
        return vars_[key];
    } else {
	throw KeyNotFoundException (key + " parameter is missing");
    }
}


// from http://stackoverflow.com/questions/154536/encode-decode-urls-in-c
void Uri::urlDecode(QueryString& queryString)
{
    std::string ret;

    for (size_t i=0; i<queryString.length(); ++i)
    {
        if (unsigned(queryString[i])==37)
        {
	    unsigned ii;
            sscanf(queryString.substr(i+1,2).c_str(), "%x", &ii);
            char ch=static_cast<char>(ii);
            ret+=ch;
            i=i+2;
        } else
        {
            ret+=queryString[i];
        }
    }
    queryString=ret;
}



void Uri::split(std::vector<std::string>& splitStr, std::string const &str, char delimiter)
{
    std::stringstream ss(str);
    std::string item;
    while (getline(ss, item, delimiter))
    {
        splitStr.push_back(item);
    }
}
