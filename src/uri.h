#ifndef MDS_URI_H
#define MDS_URI_H

#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <map>

class Uri
{
  
  typedef std::string UriString;
  typedef std::string UriValue;
  typedef std::string UriKey;
  
  typedef std::string UriEmptyException;
  typedef std::string UriKeyNotFoundException;
  
public:
    Uri();
    void parse(UriString);
    UriString getUriString();
    void urlDecode(std::string&);
    void split(std::vector<std::string>&, std::string, char);
    UriValue getVar(UriKey);
    bool isVar(UriKey);
protected:
private:
    UriString uriString_;
    std::map<UriKey,UriValue> vars_;
};

#endif
