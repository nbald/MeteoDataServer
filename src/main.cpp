#include <iostream>
#include <unistd.h>

#include <netcdf.h>

#include "config.h"
#include "uri.h"

int main (void) {
    
  

  //std::cout << "dd : " << config.getString("ddd") << std::endl;
  
  try
  {
    
    Config config ("../conf/mds-config.json");
    std::cout << "dataDirectory : " << config.getString("dataDirectory")
              << '\n';
    
    std::cout << "nThreads : " << config.getInt("nThreads") << '\n';
    
    
    Uri uri;
    uri.parse("/test/?truc=machin&bidule=chouette");
    
    std::cout << "truc : " << uri.getVar("truc") << '\n';
    std::cout << "bidule : " << uri.getVar("bidule") << '\n';
    
    
  } 
  catch (std::string const &e)
  {
    std::cerr << e << '\n';
  }
  
  
  /*
  int status = NC_NOERR;
  int ncid;
  */
   /* 
   * NC_SHARE : from doc : Since the buffering scheme is optimized for
   * sequential access, programs that do not access data sequentially may see
   * some performance improvement by setting the NC_SHARE flag.
   * 
   * NC_DISKLESS : for allowing NC_MMAP. Side effect : any changes performed to
   * the files won't be saved on exit. Not an issue for us.
   * 
   * NC_MMAP : for mapping the file to virtual memory, and let the linux kernel
   * do the RAM cache management for us. See `man mmap`
   */
  /*status = nc_open("/home/nicolas/MeteoDataServer/data/2012-12-16_00/rasp/0.nc", NC_SHARE|NC_DISKLESS|NC_MMAP, &ncid);

  if (status != NC_NOERR) {
    std::cerr << "erreur nc open" << std::endl;
  }
  
  std::cout << "cool" << std::endl;
  */
  //sleep(100000);
  
  
  
  return 0;
}
