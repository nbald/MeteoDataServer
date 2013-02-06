#ifndef MDS_CONFIG
#define MDS_CONFIG

#include <string>
#include <fstream>
#include <sstream>

#include <jsoncpp/json/json.h>

class Config
{

  typedef std::string FileName;
  typedef Json::Value Object;
  typedef std::string KeyName;
  
  typedef std::string FileException;
  typedef std::string KeyNotFoundException;
  typedef std::string BadTypeException;

public:
  Config(const FileName &);
  std::string getString(const KeyName &);
  int getInt(const KeyName &);
  void reload();

protected:

private:
  Object object_;
  FileName fileName_;
  Json::Reader reader_;
};

#endif
