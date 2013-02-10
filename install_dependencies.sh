#!/bin/bash

PACKAGES="libproj-dev libfcgi-dev libjsoncpp-dev libdap-dev"
NETCDF_VERSION="4.2.1.1"

STARTDIR=$(pwd)

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

if [ -e $(uname -m | grep 64)] # for 32bit systems only
then 

PATCHTXT=" and patch for 64bit files mmap on 32bit system"

echo "- patch : allow mmap NetCDF-64bits files on 32bits computers"
echo "  !!!! this is dangerous. for testing purposes only !!!!"

# 64bit offset NetCDF allows to store much more data in a single file.
# http://www.unidata.ucar.edu/software/netcdf/docs/netcdf/64_002dbit-Offset-Format.html
# But 32bit computers only have limited virtual memory space. (~3GB)
#
# So the NetCDF library have a check and prevents from mmaping 64bit
# files on 32bit computers.
#
# I disable this check, because we needs NetCDF-64bit files (as output
# by the WRF model) and my dev laptop is only 32bits.
#
# This is a bad and dangerous hack. For testing purposes only.
# I don't know exactly what will happen if we try too mmap a
# very big file. The system might crash.
#
# This will not be a problem later since all the servers will be x86_64.

patch netcdf-${NETCDF_VERSION}/libsrc/mmapio.c <<"EOF"
--- netcdf-4.2.1.1/libsrc/mmapio.c-orig	2013-02-10 07:03:44.480919251 +0100
+++ netcdf-4.2.1.1/libsrc/mmapio.c	2013-02-10 07:02:04.808425003 +0100
@@ -21,9 +21,9 @@
 
 #undef DEBUG
 
-#ifdef DEBUG
+//NICO #ifdef DEBUG
 #include <stdio.h>
-#endif
+//NICO #endif
 
 #include <sys/mman.h>
 
@@ -169,7 +169,10 @@
 
     /* See if ok to use mmap */
     if(sizeof(void*) < 8 && fIsSet(ioflags,NC_64BIT_OFFSET))
-	return NC_DISKLESS; /* cannot support */
+    {
+      fprintf(stderr, "**DANGEROUS HACK** : mmap a 64bit offset file on a 32bit system.\n");
+	//NICO return NC_DISKLESS; /* cannot support */
+    }
     mmapio->mapfd = -1;
 
     if(nciopp) *nciopp = nciop;
EOF

fi # end 32bit test

echo "- compiling NetCDF with mmap suport"
cd netcdf-${NETCDF_VERSION}
( \
  ./configure \
      --enable-mmap \
      --disable-netcdf-4 \
      --disable-dap \
      --disable-examples \
      --prefix=$(pwd)/.. \
      CFLAGS="-O3" \
  && make && make check && make install\
  && cd ../ && rm -rf netcdf-${NETCDF_VERSION} \
  && echo "NetCDF ${NETCDF_VERSION} built with mmap support${PATCHTXT}, on $(date)" > VERSION.txt \
  && echo "====== SUCCESS NETCDF INSTALL====="\
  ) || echo "==== FAILED NECTDF INSTALL ===="

cd ${STARTDIR}
  
echo "===== THE END ====="
