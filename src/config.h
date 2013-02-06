#ifndef MDS_CONFIG
#define MDS_CONFIG

#include <string>
#include <fstream>
#include <sstream>

#include <jsoncpp/json/json.h>

class Config
{

  typedef std::string ConfigFileName;
  typedef Json::Value ConfigObject;
  typedef std::string ConfigKeyName;
  
  typedef std::string ConfigFileException;
  typedef std::string ConfigKeyNotFoundException;
  typedef std::string ConfigBadTypeException;

public:
  Config(const ConfigFileName &);
  std::string getString(const ConfigKeyName &);
  int getInt(const ConfigKeyName &);
  void reload();

protected:

private:
  ConfigObject configObject_;
  ConfigFileName configFileName_;
  Json::Reader reader_;
};

#endif