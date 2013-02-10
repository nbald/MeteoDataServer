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
#include <MeteoDataServer/wrfgrid.h>

namespace MeteoDataServer {


  WrfGrid::WrfGrid()
  {
    grid_.proj = NULL;
    
    // intitialize lat/lon projection.
    // TODO: would be better if only one for the whole server.
    latlonProj_ = pj_init_plus("+proj=latlong +datum=WGS84 +ellps=WGS84");
    if (latlonProj_ == NULL)
    {
      throw ProjException ("failed projection initialization: " + grid_.projString);
    }
  }




  WrfGrid::~WrfGrid()
  {
    if (grid_.proj != NULL) {
      pj_free(grid_.proj);
    }
    if (latlonProj_ != NULL) {
      pj_free(latlonProj_);
    }
  }




  void WrfGrid::initGrid(Parameters const &parameters)
  {
    // create proj4 string 
    grid_.projString = makeProjString_(parameters);
    
    // create proj4 projection object
    grid_.proj = pj_init_plus(grid_.projString.c_str());
    if (grid_.proj == NULL)
    {
      throw ProjException ("failed projection initialization: " + grid_.projString);
    }
    
    // compute grid position
    ProjPoint centerMeters = latLonToProjXY_(parameters.cenLat, parameters.cenLon);
    grid_.dX = parameters.dX;
    grid_.dY = parameters.dX;
    grid_.nSouthNorth = parameters.nSouthNorth;
    grid_.nWestEast = parameters.nWestEast;
    grid_.x0 = centerMeters.x - ((grid_.nWestEast/2.)-1) * grid_.dX;
    grid_.y0 = centerMeters.y - ((grid_.nSouthNorth/2.)-1) * grid_.dY;
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
      
      case PROJ_LAMBERT_CONFORMAL: // tested, seems to be working
	projStream << "+proj=lcc"
		  << " +lon_0=" << parameters.standLon
		  << " +lat_0=" << parameters.moadCenLat
		  << " +lat_1=" << parameters.trueLat1
		  << " +lat_2=" << parameters.trueLat2;
	break;
	
      case PROJ_POLAR_STEREOGRAPHIC: 
	throw ProjException("polar stereo proj not implemented");
	break;
	
      case PROJ_MERCATOR: // tested, seems to be working
	projStream << "+proj=merc"
        << " +lon_0=" << parameters.standLon
	<< " +lat_ts=" << parameters.trueLat1;	
	break;
	
      case PROJ_ROTATED_LATLON:
	throw ProjException("latlon proj not implemented");
	break;
	
      case PROJ_NMM_ARAKAWA_E:
	throw ProjException("NMM arakawa proj not implemented");
	break;
	
      default:
	throw ProjException("unknown projection");
	
    }
    
    // WRF earth is a sphere with 6370km radius
    projStream << " +a=6370000. +b=6370000. +no_defs";
    
    return projStream.str();
  }



  
  WrfGrid::ProjPoint WrfGrid::latLonToProjXY_(Latitude const &lat, Longitude const &lon)
  {
    ProjPoint proj;
    proj.x = lon * DEG_TO_RAD;
    proj.y = lat * DEG_TO_RAD;
    int status = pj_transform(latlonProj_, grid_.proj, 1, 1, &proj.x, &proj.y, NULL);
    if (status != 0)
    {
      throw ProjException ("transform failed");
    }
    return proj;
  }


  WrfGrid::GridPoint WrfGrid::latLonToGridXY(LatLon const &latLon)
  {
    return latLonToGridXY(latLon.lat, latLon.lon);
  }
  
  WrfGrid::GridPoint WrfGrid::latLonToGridXY(Latitude const &lat, Longitude const &lon)
  {
    ProjPoint place = latLonToProjXY_(lat, lon);
    
    Meters x = (place.x - grid_.x0); // add 0.5 for rounding
    Meters y = (place.y - grid_.y0);
    
    GridPoint gridPoint;
    gridPoint.x = static_cast<int>(x / grid_.dX + 0.5);
    gridPoint.y = static_cast<int>(y / grid_.dY + 0.5);
    
    if (gridPoint.x < 0) {
      gridPoint.x=0;
    } else if (gridPoint.x >= grid_.nWestEast) {
      gridPoint.x=grid_.nWestEast;
    } 
    
    if (gridPoint.y < 0) {
      gridPoint.y=0;
    } else if (gridPoint.y >= grid_.nSouthNorth) {
      gridPoint.y=grid_.nSouthNorth;
    }
    
    gridPoint.xError = x-gridPoint.x*grid_.dX; 
    gridPoint.yError = y-gridPoint.y*grid_.dY;
    
    if (fabs(gridPoint.xError) > grid_.dX) 
    {
      std::ostringstream errorStream;
      errorStream << "longitude you asked is too far from nearest grid point ("
		  << gridPoint.xError/1000 << " km)";
      throw ProjException (errorStream.str());
    }
    
    if (fabs(gridPoint.yError) > grid_.dY) 
    {
      std::ostringstream errorStream;
      errorStream << "latitude you asked is too far from nearest grid point ("
		  << gridPoint.yError/1000 << " km)";
      throw ProjException (errorStream.str());
    }
    
    return gridPoint;
  }
  
  
  
  #ifdef DEBUG
    void WrfGrid::showXYLatLon(GridX gridX, GridY gridY)
    {
      ProjPoint proj;
      proj.x = grid_.x0 + gridX*grid_.dX;
      proj.y = grid_.y0 + gridY*grid_.dY;
      int status = pj_transform(grid_.proj, latlonProj_, 1, 1, &proj.x, &proj.y, NULL);
      if (status != 0)
      {
	throw ProjException ("transform failed");
      }
      
      proj.x *= 57.2957795;
      proj.y *= 57.2957795;
      
      std::cout << "lat: " << proj.x << std::endl;
      std::cout << "lon: " << proj.y << std::endl;
      
    }
  #endif
  

}  /* End of namespace MeteoDataServer. */