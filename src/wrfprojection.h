#ifndef MDS_WRFPROJECTION
#define MDS_WRFPROJECTION

#include <string>

#define WRF_EARTH_RADIUS 6370000

class WrfProjection {
  
  typedef std::string ProjectionString;
  
  enum WrfProjectionType {
    WRF_LAMBERT_CONFORMAL = 1,
    WRF_POLAR_STEREOGRAPHIC = 2,
    WRF_MERCATOR = 3,
    WRF_ROTATED_LATLON = 6
  };
  
public:
protected:
private:
  ProjectionString projectionString_;
};

#endif