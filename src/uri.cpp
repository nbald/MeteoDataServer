#include "uri.h"

void Uri::parse(UriString uriString)
{
    std::vector<std::string> args;

    // cleanup
    urlDecode(uriString);

    // find the beginning of ?arg=
    size_t pos = uriString.find_first_of("?&");

    if (pos == std::string::npos || pos+1 >= uriString.size() ) {
        throw EmptyException ("Uri is empty");
    }

    // we don't want to catch the '?'
    pos++;

    // handle ?&arg= case
    if (uriString.at(pos) == '&') pos++;

    // keep only the interesting part
    uriString = uriString.substr(pos, std::string::npos);

    // cut queries
    split(args, uriString, '&');

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

    uriString_ = uriString;

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
        std::stringstream errorMsg;
	errorMsg << key << " parameter is missing";
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
