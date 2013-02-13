#!/bin/bash

PACKAGES="libproj-dev libfcgi-dev libjsoncpp-dev libdap-dev git"

STARTDIR=$(pwd)

echo "==== installing packages ===="

sudo apt-get install build-essential $PACKAGES


echo "==== installing netcdf-mmap-reader ===="

rm -rf netcdf-mmap-reader >& /dev/null
git clone https://github.com/OpenMeteoData/netcdf-mmap-reader.git

cd netcdf-mmap-reader/src
( \
  make libncmmap.so && sudo make install\
  && cd ../../ && rm -rf netcdf-mmap-reader \
  && echo "====== SUCCESS netcdf-mmap-reader INSTALL====="\
  ) || echo "==== FAILED netcdf-mmap-reader INSTALL ===="

cd ${STARTDIR}
  
echo "===== THE END ====="
