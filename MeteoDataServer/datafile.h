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

#ifndef METEO_DATA_SERVER__DATAFILE__H
#define METEO_DATA_SERVER__DATAFILE__H

#include <string>
#include <vector>
#include <map>

#ifdef DEBUG
#include <iostream>
#endif

#include <NcMmap.h>

#include <MeteoDataServer/wrfgrid.h>

namespace MeteoDataServer {


  class DataFile
  {

    typedef int Handle;
    typedef std::string FileName;
    typedef std::string Time;
    typedef std::vector<Time> TimesList;

    typedef std::string NetCdfException;

  public:
    DataFile(const FileName &);
    ~DataFile();
    WrfGrid::Parameters getGridParameters();
  protected:
  private:
    NcMmap nc_;


  };  /* End of class DataFile. */


}  /* End of namespace MeteoDataServer. */


#endif  /* Undefined METEO_DATA_SERVER__DATAFILE__H. */
