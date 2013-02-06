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
    std::cout << "dataDirectory : " << config.getString("dataDirectory") << std::endl;
    std::cout << "nThreads : " << config.getInt("nThreads") << std::endl;
    
    
    Uri uri;
    uri.parse("/test/?truc=machin&bidule=chouette");
    
    std::cout << "truc : " << uri.getVar("truc") << std::endl;
    std::cout << "bidule : " << uri.getVar("bidule") << std::endl;
    
    
  } 
  catch (std::string const &e)
  {
    std::cerr << e << std::endl;
  }
  
  
  
  int status = NC_NOERR;
  int ncid;
  
   /* 
   * NC_SHARE : from doc : Since the buffering scheme is optimized for sequential access,
   * programs that do not access data sequentially may see some performance
   * improvement by setting the NC_SHARE flag.
   * 
   * NC_DISKLESS : for allowing NC_MMAP. Side effect : any changes performed to the files
   * won't be saved on exit. Not an issue for us. 
   * 
   * NC_MMAP : for mapping the file to virtual memory, and let the linux kernel
   * do the RAM cache management for us. See `man mmap`
   */
   status = nc_open("/home/nicolas/MeteoDataServer/data/france/2013-01-22_18/wrfout/geo_em.d03.nc", NC_SHARE|NC_DISKLESS|NC_MMAP, &ncid);
  //status = nc_open("/home/nicolas/MeteoDataServer/data/france/2013-01-22_18/wrfout/wrfout.nc", NC_SHARE|NC_DISKLESS|NC_MMAP, &ncid);

  if (status != NC_NOERR) {
    std::cerr << "erreur nc open" << std::endl;
  }
  
  std::cout << "nc open" << std::endl;
  
  sleep(60);
  
  status = nc_close(ncid);

  if (status != NC_NOERR) {
    std::cerr << "erreur nc open" << std::endl;
  }
  
  std::cout << "nc closed" << std::endl;
  
  sleep(100);
  
  return 0;
}