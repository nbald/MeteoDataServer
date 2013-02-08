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
    std::cout << "dataDirectory : " << config.getString("dataDirectory") << std::endl;
    std::cout << "nThreads : " << config.getInt("nThreads") << std::endl;
    
    
    Uri uri;
    uri.parse("/test/?truc=machin&bidule=chouette");
    
    std::cout << "truc : " << uri.getVar("truc") << std::endl;
    std::cout << "bidule : " << uri.getVar("bidule") << std::endl;
    
    DataFile dataFile ("/home/nicolas/MeteoDataServer/data/france/2013-01-22_18/wrfout/wrfout.nc");
    
    WrfGrid::Parameters parameters;
    parameters = dataFile.getGridParameters();
    
    std::cout << "dx : " << parameters.dX << std::endl;
    std::cout << "centLat : " << parameters.cenLat << std::endl;
    
  } 
  catch (std::string const &e)
  {
    std::cerr << e << std::endl;
  }
  
  
  
  return 0;
}