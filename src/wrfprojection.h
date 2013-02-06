#ifndef MDS_WRFPROJECTION
#define MDS_WRFPROJECTION

#include <string>

#define WRF_EARTH_RADIUS 6370000

class WrfProjection {
  
  typedef std::string ProjString;
  
  enum Type {
    LAMBERT_CONFORMAL = 1,
    POLAR_STEREOGRAPHIC = 2,
    MERCATOR = 3,
    ROTATED_LATLON = 6
  };
  
public:
protected:
private:
  ProjString projString_;
};

#endif