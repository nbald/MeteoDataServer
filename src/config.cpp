#include "config.h"



Config::Config(const FileName &fileName)
{
  
  fileName_ = fileName;
  reload();
  
}



void Config::reload()
{
  
  std::ifstream fileStream (fileName_.c_str());
  
  bool parsingSuccessful = reader_.parse( fileStream, object_ );
  if ( !parsingSuccessful )
  {
      throw FileException (reader_.getFormattedErrorMessages());
  }
  
}



std::string Config::getString(const KeyName &keyName)
{
  if (object_.isMember(keyName))
  {
    if (!object_[keyName].isString()) {
      std::stringstream errorMsg;
      errorMsg << keyName << " parameter is not a string";
      throw BadTypeException(errorMsg.str());
    }
    return object_[keyName].asString();
  }
  else
  {
    std::stringstream errorMsg;
    errorMsg << keyName << " not found";
    throw KeyNotFoundException(errorMsg.str());
  }
}



int Config::getInt(const KeyName &keyName)
{
  if (object_.isMember(keyName))
  {
    if (!object_[keyName].isNumeric()) {
      std::stringstream errorMsg;
      errorMsg << keyName << " parameter is not a number";
      throw BadTypeException(errorMsg.str());
    }
    return object_[keyName].asInt();
  }
  else
  {
    std::stringstream errorMsg;
    errorMsg << keyName << " not found";
    throw KeyNotFoundException(errorMsg.str());
  }
}