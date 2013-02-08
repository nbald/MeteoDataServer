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


#include <MeteoDataServer/wrfgrid.h>


namespace MeteoDataServer {
  

  void WrfGrid::setParameters(const WrfGrid::Parameters& parameters)
  {
    parameters_ = parameters;
  }

  WrfGrid::ProjString WrfGrid::getProjString ()
  {
    std::stringstream projStream;

    switch (parameters_.mapProj) {

      case PROJ_LAMBERT_CONFORMAL:
        projStream << "+proj=lcc"
                   << " +lon_0=" << parameters_.standLon
                   << " +lat_0=" << parameters_.moadCenLat
                   << " +lat_1=" << parameters_.trueLat1
                   << " +lat_2=" << parameters_.trueLat2;
        break;

      case PROJ_POLAR_STEREOGRAPHIC:
        /* TODO proj4 << "+proj=stere";
        {
      double lon0 = (mifi_isnan(standardLon)) ? centralLon : standardLon;
      double lat0 = (mifi_isnan(centralLat)) ? lat2 : centralLat;
      double k = (1+fabs(sin(DEG_TO_RAD*lat1)))/2.;
      proj4 << " +lon_0="<<lon0<<" +lat_0="<<lat0<<" +k="<<k;
        }*/
        throw "polar proj not implemented";
        break;

      case PROJ_MERCATOR:
        projStream << "+proj=merc"
                   << " +lon_0=" << parameters_.standLon
                   << " +lat_0=" << parameters_.moadCenLat;
        break;

      case PROJ_ROTATED_LATLON:
        throw "latlon proj not implemented";
        break;

      default:
        throw "unknown projection";

    }

    projStream << " +R=" << WRF_EARTH_RADIUS << " +no_defs";

    return projStream.str();
  }

  /*
   * http://www.mmm.ucar.edu/wrf/WG2/wrfbrowser/html_code/share/module_llxy.F.html
   * http://www.mmm.ucar.edu/wrf/src/read_wrf_nc.f
   * 
   * http://mailman.ucar.edu/pipermail/ncl-talk/attachments/20091015/d00d5a47/attachment-0001.obj
   * ftp://ftp.heanet.ie/mirrors/sourceforge/s/sp/spallocator/raster/computeGridGOES_ori.cpp
   * https://collab.firelab.org/software/projects/windninja/repository/entry/branches/stability/src/ninja/wrfSurfInitialization.cpp
   * https://svn.met.no/viewvc/fimex/trunk/src/coordSys/WRFCoordSysBuilder.cc?diff_format=l&view=markup&sortby=date
   * 
      proj = wrfFile@MAP_PROJ

      if (proj .eq. 1) then  ; Lambert Conformal
          lon0 = " +lon_0=" + wrfFile@STAND_LON
          lat1 = " +lat_1=" + wrfFile@TRUELAT1
          lat2 = " +lat_2=" + wrfFile@TRUELAT2
          projStr = " +proj=lcc +ellps=sphere" + lon0 + lat1 + lat2
          return projStr
      end if

      if (proj .eq. 3) then  ; Mercator
          latTs = " +lat_ts=" + wrfFile@TRUELAT1
          lon0 = " +lon_0=" + wrfFile@STAND_LON
          projStr = " +proj=merc +ellps=sphere" + lon0 + latTs
          return projStr
      end if

      if (proj .eq. 2) then ; Polar Stereographic
         if (wrfFile@MOAD_CEN_LAT .lt. 0) then
            northSouth = " +lat_0=-90"
         else
            northSouth = " +lat_0=90"
         end if
         stdLon = " +lon_0=" + wrfFile@STAND_LON
         trueLat = " +lat_ts=" + wrfFile@TRUELAT1
         projStr = " +proj=stere +ellps=sphere" + stdLon + northSouth + trueLat
         return projStr
      end if

      if (proj .eq. 6) then  ; rotated Cassini
         ;: as of 4/29/2009, WRF files are not yet wired with these attributes.
         ;;poleLat = " +o_lat_p=" + wrfFile@POLE_LAT
         ;;poleLon = " +o_lon_p=" + wrfFile@POLE_LON

         ; Hardcode values for testing...
         poleLat = " +o_lat_p=50"
         poleLon = " +o_lon_p=180"
         lon0 = " +lon_0=" + wrfFile@STAND_LON
         projStr = " +proj=ob_tran +ellps=sphere +o_proj=cass " +  poleLon + poleLat + lon0
         return projStr
      end if
  */

}  /* End of namespace MeteoDataServer. */
