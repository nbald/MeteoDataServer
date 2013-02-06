#include <iostream>

#include <netcdf.h>


int main (void) {
  
  int status = NC_NOERR;
  int ncid;
  
  status = nc_open("/home/nicolas/MeteoDataServer/data/2012-12-16_00/rasp/0.nc", NC_SHARE|NC_MMAP, &ncid);
  if (status != NC_NOERR) {
    std::cerr << "erreur nc open" << std::endl;
  }
  
  std::cout << "cool" << std::endl;
  
  status = nc_close(ncid);       
  if (status != NC_NOERR) {
    std::cerr << "erreur nc close" << std::endl;
  }
  
  return 0;
}