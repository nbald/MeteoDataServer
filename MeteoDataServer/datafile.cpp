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
 */


#include <MeteoDataServer/datafile.h>
#include <map>


namespace MeteoDataServer {
  

  DataFile::DataFile (FileName const &fileName)
  {

    #ifdef DEBUG
      std::cout << "open NetCDF file : " << fileName << std::endl;
    #endif

    int status = nc_open(fileName.c_str(),
                         NC_SHARE|NC_DISKLESS|NC_MMAP,
                         &handle_);
   /* 
    * NC_SHARE : from doc : Since the buffering scheme is optimized 
    * for sequential access, programs that do not access data sequentially
    * may see some performance improvement by setting the NC_SHARE flag.
    * 
    * NC_DISKLESS : for allowing NC_MMAP. Side effect : any changes
    * performed to the files won't be saved on exit. Not an issue for us. 
    * 
    * NC_MMAP : for mapping the file to virtual memory, and let the linux
    * kernel do the RAM cache management for us. See `man mmap`.
    * To use this flag, NetCDF must be compiled with ./configure --enable-mmap
    * Ubuntu's libnetcdf doesn't include mmap support.
    */

    if (status != NC_NOERR)
    {
      throw NetCdfException ("error opening " + fileName + ":\n"
                                                        + nc_strerror(status));
    }

    #ifdef DEBUG
      std::cout << "handle : #" << handle_ << std::endl;
    #endif

  }


  WrfGrid::Parameters DataFile::getGridParameters()
  {
    WrfGrid::Parameters parameters;

    std::map<const char *, int*> intParameters;
    intParameters["WEST-EAST_GRID_DIMENSION"] = &parameters.nWestEast;
    intParameters["SOUTH-NORTH_GRID_DIMENSION"] = &parameters.nSouthNorth;
    intParameters["BOTTOM-TOP_GRID_DIMENSION"] = &parameters.nBottomTop;
    intParameters["MAP_PROJ"] = &parameters.mapProj;

    std::map<const char *, int*>::iterator iterInt;
    for (iterInt = intParameters.begin();
         iterInt != intParameters.end();
         ++iterInt)
    {
      int status = nc_get_att_int
                          (handle_, NC_GLOBAL, iterInt->first, iterInt->second);

      if (status != NC_NOERR)
      {
        throw NetCdfException (nc_strerror(status));
        // FIXME throw NetCdfException ("error reading " + iterInt->first + " from #" + handle_ + ":\n" + nc_strerror(status));
      }
    }

    std::map<const char *, float*> floatParameters;
    floatParameters["DX"] = &parameters.dX;
    floatParameters["DY"] = &parameters.dY;
    floatParameters["CEN_LAT"] = &parameters.cenLat;
    floatParameters["CEN_LON"] = &parameters.cenLon;
    floatParameters["TRUELAT1"] = &parameters.trueLat1;
    floatParameters["TRUELAT2"] = &parameters.trueLat2;
    floatParameters["MOAD_CEN_LAT"] = &parameters.moadCenLat;
    floatParameters["STAND_LON"] = &parameters.standLon;
    floatParameters["POLE_LAT"] = &parameters.poleLat;
    floatParameters["POLE_LON"] = &parameters.poleLon;

    std::map<const char *, float*>::iterator iterFloat;
    for (iterFloat = floatParameters.begin();
	 iterFloat != floatParameters.end();
	 ++iterFloat)
    {
      int status = nc_get_att_float
		      (handle_, NC_GLOBAL, iterFloat->first, iterFloat->second);
		      
      if (status != NC_NOERR)
      {
        throw NetCdfException (nc_strerror(status));
        // FIXME throw NetCdfException ("error reading " + iterInt->first + " from #"+ handle_ +":\n" + nc_strerror(status));
      }
    }

    return parameters;
  }


  DataFile::~DataFile()
  {

    #ifdef DEBUG
      std::cout << "close NetCDF file #" << handle_ << std::endl;
    #endif

    int status = nc_close(handle_);

    if (status != NC_NOERR)
    {
      throw NetCdfException (nc_strerror(status));
      // FIXME : throw NetCdfException ("error closing #" + handle_ + ":\n" + nc_strerror(status));
    }

  }


}  /* End of namespace MeteoDataServer. */
