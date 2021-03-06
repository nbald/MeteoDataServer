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

    nc_.openFile(fileName);

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
      NcMmap::Attribute* attribute = nc_.getGlobalAttribute(iterInt->first);
      if (attribute->integerValue.size() < 1)
      {
	throw std::string ("missing attribute");
      }
      *iterInt->second = static_cast<int>(attribute->integerValue[0]);
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
      NcMmap::Attribute* attribute = nc_.getGlobalAttribute(iterFloat->first);
      if (attribute->floatValue.size() < 1)
      {
	throw std::string ("missing attribute");
      }
      *iterFloat->second = static_cast<float>(attribute->floatValue[0]);
    }

    return parameters;
  }


  DataFile::~DataFile()
  {

    #ifdef DEBUG
      std::cout << "close file " << std::endl;
    #endif

  }


}  /* End of namespace MeteoDataServer. */
