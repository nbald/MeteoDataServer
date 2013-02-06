#include "uri.h"

Uri::Uri()
{

}

void Uri::parse(UriString uriString)
{
    size_t i, n;
    std::vector<std::string> args;

    // cleanup
    urlDecode(uriString);

    // find the beginning of ?arg=
    size_t pos = uriString.find_first_of("?&");

    if (pos == std::string::npos || pos+1 >= uriString.size() ) {
        throw UriEmptyException ("Uri is empty");
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
    n = args.size();
    for (i=0; i<n; i++)
    {
        std::vector<std::string> tmp;
        split(tmp, args[i], '=');
        if (tmp.size() == 2)
        {
            vars_.insert(std::pair<std::string,std::string>(tmp[0],tmp[1]));
        } else if (tmp.size() == 1)
        {
            vars_.insert(std::pair<std::string,std::string>(tmp[0],""));
        }
    }

    uriString_ = uriString;

}

bool Uri::isVar(UriKey uriKey) {
    return (vars_.count(uriKey) != 0);
}

Uri::UriValue Uri::getVar(UriKey uriKey)
{
    if ( isVar(uriKey) )
    {
        return vars_[uriKey];
    } else {
        std::stringstream errorMsg;
	errorMsg << uriKey << " parameter is missing";
	throw UriKeyNotFoundException (errorMsg.str());
    }
}

// from http://stackoverflow.com/questions/154536/encode-decode-urls-in-c
void Uri::urlDecode(std::string& SRC)
{
    std::string ret;
    char ch;
    unsigned i, ii;
    for (i=0; i<SRC.length(); i++)
    {
        if (unsigned(SRC[i])==37)
        {
            sscanf(SRC.substr(i+1,2).c_str(), "%x", &ii);
            ch=static_cast<char>(ii);
            ret+=ch;
            i=i+2;
        } else
        {
            ret+=SRC[i];
        }
    }
    SRC=ret;
}

std::string Uri::getUriString()
{
    return uriString_;
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
