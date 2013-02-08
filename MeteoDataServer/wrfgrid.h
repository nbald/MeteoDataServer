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
#ifndef METEO_DATA_SERVER__WRF_GRID__H
#define METEO_DATA_SERVER__WRF_GRID__H

#include <string>
#include <sstream>

#include <proj_api.h>


#define WRF_EARTH_RADIUS 6370000 // do not change
#define PROJ_NOT_INITIALIZED 0

namespace MeteoDataServer {

  class WrfGrid {

    public:
      typedef std::string ProjString;
      typedef int PointsCount;
      typedef float Meters;
      typedef float Latitude;
      typedef float Longitude;
      typedef std::string GridType;
      typedef unsigned int GridX;
      typedef unsigned int GridY;
      
      typedef std::string ProjException;
      
      enum ProjectionType { // do not change the IDs
	PROJ_LAMBERT_CONFORMAL = 1,
	PROJ_POLAR_STEREOGRAPHIC = 2,
	PROJ_MERCATOR = 3,
	PROJ_ROTATED_LATLON = 6
      };
      
      struct Parameters {
	PointsCount nWestEast;
	PointsCount nSouthNorth;
	PointsCount nBottomTop;
	Meters dX;
	Meters dY;
	GridType gridType;
	Latitude cenLat;
	Longitude cenLon;
	Latitude trueLat1;
	Latitude trueLat2;
	Latitude moadCenLat;
	Longitude standLon;
	Latitude poleLat;
	Longitude poleLon;
	int mapProj; // can't convert int to enum
      };
      
      struct Projection {
	ProjString string;
	Meters top;
	Meters left;
	projPJ proj;
	bool initialised;
      };

      struct WgsCoordinates {
	Latitude lat;
	Longitude lon;
      };
      
      struct GridCoordinates {
	GridX x;
	GridY y;
      };
      
      WrfGrid();
      ~WrfGrid();
      void initGrid(Parameters const &);
      GridCoordinates wgsToGridCoordinates(WgsCoordinates const &);
      GridCoordinates wgsToGridCoordinates(Latitude const &, Longitude const &);
    protected:
    private:
      ProjString makeProjString_(Parameters const &);
      Projection projection_;
  };  /* End of class WrfGrid. */


}  /* End of namespace MeteoDataServer. */


#endif  /* Undefined METEO_DATA_SERVER__WRF_GRID__H. */