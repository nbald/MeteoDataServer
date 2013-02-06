#!/bin/bash

PACKAGES="libproj-dev libfcgi-dev libjsoncpp-dev libdap-dev"
NETCDF_VERSION="4.2.1.1"

echo "==== installing packages ===="

sudo apt-get install build-essential $PACKAGES


echo "==== installing netcdf with mmap support ===="

rm -rf netcdf >& /dev/null
mkdir netcdf
cd netcdf

echo "- downloading NetCDF ${NETCDF_VERSION} from UCAR"
wget http://www.unidata.ucar.edu/downloads/netcdf/ftp/netcdf-${NETCDF_VERSION}.tar.gz

echo "- extracting NetCDF"
tar xvfz netcdf-${NETCDF_VERSION}.tar.gz
rm netcdf-${NETCDF_VERSION}.tar.gz

echo "- compiling NetCDF with mmap suport"
cd netcdf-${NETCDF_VERSION}
( \
  ./configure --enable-mmap --disable-netcdf-4 --disable-dap --disable-examples --prefix=$(pwd)/.. \
  && make && make check && make install \
  && echo "====== SUCCESS NETCDF INSTALL====="\
  ) || echo "==== FAILED NECTDF INSTALL ===="
cd ../
rm -rf netcdf-${NETCDF_VERSION}
echo "NetCDF ${NETCDF_VERSION} built with mmap support, on $(date)" > VERSION.txt
cd ../


echo "===== THE END ====="
