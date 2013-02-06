#ifndef MDS_DATAFILE
#define MDS_DATAFILE

#include <string>

class DataFile
{

  typedef int NetCdfHandle;
  typedef std::string DataFileName;
  
public:
  DataFile(const DataFileName &);
  ~DataFile();
protected:
private:
  NetCdfHandle netCdfHandle_;
};

#endif