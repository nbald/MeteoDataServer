#include "config.h"

Config::Config(const ConfigFileName &configFileName)
{
  
  configFileName_ = configFileName;
  reload();
  
}

void Config::reload()
{
  
  std::ifstream configFileStream (configFileName_.c_str());
  
  bool parsingSuccessful = reader_.parse( configFileStream, configObject_ );
  if ( !parsingSuccessful )
  {
      throw ConfigFileException (reader_.getFormattedErrorMessages());
  }
  
}

std::string Config::getString(const ConfigKeyName &configKeyName)
{
  if (configObject_.isMember(configKeyName))
  {
    if (!configObject_[configKeyName].isString()) {
      std::stringstream errorMsg;
      errorMsg << configKeyName << " parameter is not a string";
      throw ConfigBadTypeException(errorMsg.str());
    }
    return configObject_[configKeyName].asString();
  }
  else
  {
    std::stringstream errorMsg;
    errorMsg << configKeyName << " not found";
    throw ConfigKeyNotFoundException(errorMsg.str());
  }
}


int Config::getInt(const ConfigKeyName &configKeyName)
{
  if (configObject_.isMember(configKeyName))
  {
    if (!configObject_[configKeyName].isNumeric()) {
      std::stringstream errorMsg;
      errorMsg << configKeyName << " parameter is not a number";
      throw ConfigBadTypeException(errorMsg.str());
    }
    return configObject_[configKeyName].asInt();
  }
  else
  {
    std::stringstream errorMsg;
    errorMsg << configKeyName << " not found";
    throw ConfigKeyNotFoundException(errorMsg.str());
  }
}