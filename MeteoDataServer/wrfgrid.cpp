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
#include "wrfgrid.h"

namespace MeteoDataServer {


  WrfGrid::WrfGrid()
  {
    projection_.initialised = false;
  }




  WrfGrid::~WrfGrid()
  {
    if (projection_.initialised) {
      pj_free(projection_.proj);
    }
  }




  void WrfGrid::initGrid(Parameters const &parameters)
  {
    // create proj4 string 
    projection_.string = makeProjString_(parameters);
    
    // create proj4 projection object
    projection_.proj = pj_init_plus(projection_.string.c_str());
    projection_.initialised = true; // needed for pj_free in ~WrfGrid()
    
  }





  WrfGrid::ProjString WrfGrid::makeProjString_(Parameters const &parameters)
  {
    
    /*
    * ABOUT WRF projection : 
    * 
    * http://www.mmm.ucar.edu/wrf/WG2/wrfbrowser/html_code/share/module_llxy.F.html
    * http://www.mmm.ucar.edu/wrf/src/read_wrf_nc.f
    * 
    * http://mailman.ucar.edu/pipermail/ncl-talk/attachments/20091015/d00d5a47/attachment-0001.obj
    * ftp://ftp.heanet.ie/mirrors/sourceforge/s/sp/spallocator/raster/computeGridGOES_ori.cpp
    * https://collab.firelab.org/software/projects/windninja/repository/entry/branches/stability/src/ninja/wrfSurfInitialization.cpp
    * https://svn.met.no/viewvc/fimex/trunk/src/coordSys/WRFCoordSysBuilder.cc?diff_format=l&view=markup&sortby=date
    * 
    */
    
    std::stringstream projStream;
    
    switch (parameters.mapProj) {
      
      case PROJ_LAMBERT_CONFORMAL: // TODO: needs testing
	projStream << "+proj=lcc"
		  << " +lon_0=" << parameters.standLon
		  << " +lat_0=" << parameters.moadCenLat
		  << " +lat_1=" << parameters.trueLat1
		  << " +lat_2=" << parameters.trueLat2;
	break;
	
      case PROJ_POLAR_STEREOGRAPHIC: 
	throw ProjException("polar stereo proj not implemented");
	break;
	
      case PROJ_MERCATOR: // TODO: needs testing
	projStream << "+proj=merc"
		  << " +lon_0=" << parameters.standLon
		  << " +lat_0=" << parameters.moadCenLat;
	break;
	
      case PROJ_ROTATED_LATLON:
	throw ProjException("latlon proj not implemented");
	break;
	
      default:
	throw ProjException("unknown projection");
	
    }
    
    projStream << " +R=" << WRF_EARTH_RADIUS << " +no_defs";
    
    return projStream.str();
  }







  WrfGrid::GridCoordinates WrfGrid::wgsToGridCoordinates(WgsCoordinates const &wgsCoordinates)
  {
    return wgsToGridCoordinates(wgsCoordinates.lat, wgsCoordinates.lon);
  }

  WrfGrid::GridCoordinates WrfGrid::wgsToGridCoordinates(Latitude const &lat, Longitude const &lon)
  {
    
  }

}  /* End of namespace MeteoDataServer. */