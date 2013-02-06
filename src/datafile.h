#ifndef MDS_DATAFILE
#define MDS_DATAFILE

#include <string>

class DataFile
{

  typedef int Handle;
  typedef std::string FileName;
  
public:
  DataFile(const FileName &);
  ~DataFile();
protected:
private:
  Handle handle_;
};

#endif