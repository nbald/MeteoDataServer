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

#include <MeteoDataServer/config.h>
#include <MeteoDataServer/uri.h>
#include <MeteoDataServer/datafile.h>
#include <MeteoDataServer/wrfgrid.h>

int main (void)
{
    
  

  //std::cout << "dd : " << config.getString("ddd") << std::endl;
  
  try
  {
    
    MeteoDataServer::Config config ("../conf/mds-config.json");

    std::cout << "dataDirectory : " << config.getString("dataDirectory")
              << '\n';
    
    std::cout << "nThreads : " << config.getInt("nThreads") << '\n';
    
    
    MeteoDataServer::Uri uri;
    uri.parse("/test/?truc=machin&bidule=chouette");
    
    std::cout << "truc : " << uri.getVar("truc") << '\n';
    std::cout << "bidule : " << uri.getVar("bidule") << '\n';
    
    MeteoDataServer::DataFile dataFile ("/home/nicolas/MeteoDataServer/data/france/2013-01-22_18/wrfout/wrfout.nc");
    //MeteoDataServer::DataFile dataFile ("/home/nicolas/MeteoDataServer/sampledata/wrf grids/lambert.nc");
    
    MeteoDataServer::WrfGrid::Parameters parameters;
    parameters = dataFile.getGridParameters();
    
    std::cout << "dx : " << parameters.dX << std::endl;
    std::cout << "centLat : " << parameters.cenLat << std::endl;
    std::cout << "standLon : " << parameters.standLon << std::endl;
    std::cout << "cenLon : " << parameters.cenLon << std::endl;
    
    MeteoDataServer::WrfGrid wrfGrid;
    
    wrfGrid.initGrid(parameters);

    
    
    MeteoDataServer::WrfGrid::GridPoint gridPoint;
    
    
    double lat;
    double lon;
    
    std::cout << "lat?" << std::endl;
    std::cin >> lat;
    std::cout << "lon?" << std::endl;
    std::cin >> lon;
    gridPoint = wrfGrid.latLonToGridXY(lat, lon);
    std::cout << "X : " << gridPoint.x << std::endl;
    std::cout << "Y : " << gridPoint.y << std::endl;
    std::cout << "errX : " << gridPoint.xError << std::endl;
    std::cout << "errY : " << gridPoint.yError << std::endl;
    
    
    
    /*
    int x;
    int y;
    std::cout << "x?" << std::endl;
    std::cin >> x;
    std::cout << "y?" << std::endl;
    std::cin >> y;
    wrfGrid.showXYLatLon(x, y);
    */
    //std::cout << "proj4 : " << wrfGrid.getProjString() << std::endl;

    
  } 
  catch (std::string const &e)
  {
    std::cerr << e << '\n';
  }
  catch (int const &e)
  {
    std::cerr << e << '\n';
  }
  catch (double &e)
  {
    std::cerr << e << '\n';
  }
  
  
  

  
  return 0;
}
