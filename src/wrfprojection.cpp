/*
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