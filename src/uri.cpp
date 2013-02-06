#include "uri.h"

void Uri::parse(String string)
{
    std::vector<std::string> args;

    // cleanup
    urlDecode(string);

    // find the beginning of ?arg=
    size_t pos = string.find_first_of("?&");

    if (pos == std::string::npos || pos+1 >= string.size() ) {
        throw EmptyException ("Uri is empty");
    }

    // we don't want to catch the '?'
    pos++;

    // handle ?&arg= case
    if (string.at(pos) == '&') pos++;

    // keep only the interesting part
    string = string.substr(pos, std::string::npos);

    // cut queries

    split(args, string, '&');

    // to lower
    /*transform(string.begin(), string.end(), string.begin(), ::tolower);*/

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
            vars_.insert(std::make_pair (tmp[0],""));
        }
    }

    string_ = string;
}


bool Uri::isVar(Key uriKey) {
    return (vars_.count(uriKey) != 0);
}

Uri::Value Uri::getVar(Key uriKey)
{
    if ( isVar(uriKey) )
    {
        return vars_[uriKey];
    } else {
        std::stringstream errorMsg;
	errorMsg << uriKey << " parameter is missing";
	throw KeyNotFoundException (errorMsg.str());
    }
}

// from http://stackoverflow.com/questions/154536/encode-decode-urls-in-c
void Uri::urlDecode(std::string& SRC)
{
    std::string ret;
    for (size_t i=0; i<SRC.length(); ++i)
    {
        if (unsigned(SRC[i])==37)
        {
            unsigned ii;
            sscanf(SRC.substr(i+1,2).c_str(), "%x", &ii);
            char ch=static_cast<char>(ii);
            ret+=ch;
            i=i+2;
        } else
        {
            ret+=SRC[i];
        }
    }
    SRC=ret;
}

void Uri::split(std::vector<std::string>& splitStr, std::string str, char delimiter)
{
    std::stringstream ss(str);
    std::string item;
    while (getline(ss, item, delimiter))
    {
        splitStr.push_back(item);
    }
}
