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


#ifndef METEO_DATA_SERVER__DATASET__H
#define METEO_DATA_SERVER__DATASET__H

#include <MeteoDataServer/datafile.h>
#include <MeteoDataServer/wrfgrid.h>


namespace MeteoDataServer {


  class Dataset {

  
  public:
  
  protected:
  private:
    WrfGrid wrfgrid_;

  };


}  /* End of namespace MeteoDataServer. */

  
#endif  /* Undefined METEO_DATA_SERVER__DATASET__H. */
