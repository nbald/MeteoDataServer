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
#include <cmath>

#ifdef DEBUG
#include <iostream>
#endif

#include <proj_api.h>


namespace MeteoDataServer {

  
  
  class WrfGrid {

    public:
      typedef std::string ProjString;
      typedef int PointsCount;
      typedef float MetersFloat;
      typedef double Meters;
      typedef float Latitude;
      typedef float Longitude;
      typedef std::string GridType;
      typedef int GridX;
      typedef int GridY;
      
      typedef std::string ProjException;
      
      enum ProjectionType { // do not change the IDs
	PROJ_LAMBERT_CONFORMAL = 1,
	PROJ_POLAR_STEREOGRAPHIC = 2,
	PROJ_MERCATOR = 3,
	PROJ_ROTATED_LATLON = 6,
	PROJ_NMM_ARAKAWA_E = 203
      };
      
      struct Parameters {
	PointsCount nWestEast;
	PointsCount nSouthNorth;
	PointsCount nBottomTop;
	MetersFloat dX;
	MetersFloat dY;
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
      
      struct Grid {
	ProjString projString;
	Meters x0;
	Meters y0;
	PointsCount nWestEast;
	PointsCount nSouthNorth;
	Meters dX;
	Meters dY;
	projPJ proj;
      };

      struct LatLon {
	Latitude lat;
	Longitude lon;
      };
      
      struct GridPoint {
	GridX x;
	GridY y;
	Meters xError;
	Meters yError;
      };
      
      struct ProjPoint {
	Meters x;
	Meters y;
      };
      
      WrfGrid();
      ~WrfGrid();
      void initGrid(Parameters const &);
      GridPoint latLonToGridXY(LatLon const &);
      GridPoint latLonToGridXY(Latitude const &, Longitude const &);
      #ifdef DEBUG
	void showXYLatLon(GridX gridX, GridY gridY);
      #endif
    protected:
    private:
      ProjString makeProjString_(Parameters const &);
      Grid grid_;
      projPJ latlonProj_;
      ProjPoint latLonToProjXY_(Latitude const &, Longitude const &);
  };  /* End of class WrfGrid. */


}  /* End of namespace MeteoDataServer. */


#endif  /* Undefined METEO_DATA_SERVER__WRF_GRID__H. */