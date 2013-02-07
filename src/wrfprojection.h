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
#ifndef MDS_WRFPROJECTION
#define MDS_WRFPROJECTION

#include <string>

#define WRF_EARTH_RADIUS 6370000 // do not change

class WrfProjection {

  typedef std::string String;
  
  enum Type {
    LAMBERT_CONFORMAL = 1,
    POLAR_STEREOGRAPHIC = 2,
    MERCATOR = 3,
    ROTATED_LATLON = 6
  };
  
public:
protected:
private:
  
  String string_;
  
  
};

#endif