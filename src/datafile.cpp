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
#include "datafile.h"



DataFile::DataFile(const FileName &fileName)
{
  
  #ifdef DEBUG
    std::cout << "open NetCDF file : " << fileName << std::endl;
  #endif
  
  int sucessfullOpen = nc_open(fileName.c_str(), NC_SHARE|NC_DISKLESS|NC_MMAP, &handle_);
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
  
  if (sucessfullOpen != NC_NOERR)
  {
    throw FileException ("can't open " + fileName);
  }

  #ifdef DEBUG
    std::cout << "handle : #" << handle_ << std::endl;
  #endif
  
}



DataFile::~DataFile()
{
  
  #ifdef DEBUG
    std::cout << "close NetCDF file #" << handle_ << std::endl;
  #endif
  
  int successfulClose = nc_close(handle_);
  
  if (successfulClose != NC_NOERR)
  {
    throw FileException ("error closing NetCDF file");
  }
  
}