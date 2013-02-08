/*
 * Copyright (c) 2013 the OpenMeteoData project
 * All rights reserved.
 *
 * Author: Nicolas BALDECK <nicolas.baldeck@openmeteodata.org>
 * 
 * This file is a part of MeteoDataServer
 * 
 * MeteoDataServer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MeteoDataServer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *  
*/
#include <iostream>
#include <unistd.h>

#include "config.h"
#include "uri.h"
#include "datafile.h"

int main (void)
{
    
  

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
    
    DataFile dataFile ("/home/nicolas/MeteoDataServer/data/france/2013-01-22_18/wrfout/wrfout.nc");
    
    WrfGrid::Parameters parameters;
    parameters = dataFile.getGridParameters();
    
    std::cout << "dx : " << parameters.dX << std::endl;
    std::cout << "centLat : " << parameters.cenLat << std::endl;
    
    WrfGrid wrfGrid;
    wrfGrid.setParameters(parameters);
    std::cout << "proj4 : " << wrfGrid.getProjString() << std::endl;
    
  } 
  catch (std::string const &e)
  {
    std::cerr << e << '\n';
  }
  
  
  
  int status = NC_NOERR;
  int ncid;
  
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
