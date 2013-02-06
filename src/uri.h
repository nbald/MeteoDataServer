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
  typedef std::string Value;
  typedef std::string Key;
  
  typedef std::string EmptyException;
  typedef std::string KeyNotFoundException;
  
public:
    void parse(UriString);
    void urlDecode(std::string&);
    void split(std::vector<std::string>&, std::string, char);
    Value getVar(Key);
    bool isVar(Key);
protected:
private:
    UriString uriString_;
    std::map<Key,Value> vars_;
};

#endif
