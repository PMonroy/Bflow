#ifndef COORDENATES
#define COORDENATES

/* Coordenates */
typedef struct geo_coord_st{
  double lon; // Longitude in degrees 
  double lat; // Latitude in degrees
  double dpt; // Depth in meters
} geo_coord, *geo_coord_ptr;  // Geographic Coordinate System
    
typedef struct sph_coord_st{
  double phi;   // Longitude in rads 
  double theta;  // Latitude in rads
  double dpt;  // Depth in meters
} sph_coord;   // Spherical Coordinate System

typedef struct hom_coor_st{
  double phi;  // Longitude in rads 
  double mu; // Scaled Latitude in rads
  double dpt; // Depth in meters
} hom_coord;  // Homegeneous Coordinate System

/* Vector */
typedef struct vector_st{
  double u; // Zonal component (V_phi)
  double v; // Meridional component (V_theta)
  double w; // Vertical component (V_r)
} vector; // Tangent vector in unitary basis (Can be velocity, aceleration... 
          // Always their units will be meters and days) 

/* Constants: */
#define R_EARTH 6371000.0
#define SECONDS_DAY 86400.0
#define PI 3.1415926

/* Transformations: */
#define RADS(degree) (PI/180.0)*(degree)
#define DEGREE(rads) (180.0/PI)*(rads)
#define MU(x)  log(fabs((1.0/cos(x))+tan(x))) // x must be in radians. Result value in radians
#define THETA(x) (PI/2.0) -2.0 * atan(exp(-1.0*(x))) // x must be in radians. Result value in radians
#define GEO_TO_SPH_COORD(y,x)			\
  y.phi = RADS(x.lon);				\
  y.theta = RADS(x.lat);			\
  y.dpt = x.dpt
#define GEO_TO_HOM_COORD(y,x)			\
  y.phi = RADS(x.lon);				\
  y.mu = MU(RADS(x.lat));			\
  y.dpt = x.dpt
#define SPH_TO_GEO_COORD(y,x)			\
  y.lon = DEGREE(x.phi);			\
  y.lat =  DEGREE(x.theta);			\
  y.dpt = x.dpt
#define SPH_TO_HOM_COORD(y,x)			\
  y.phi = x.phi;				\
  y.mu =  MU(x.theta);				\
  y.dpt = x.dpt
#define HOM_TO_SPH_COORD(y,x)			\
  y.phi = x.phi;				\
  y.theta =  THETA(x.mu);			\
  y.dpt = x.dpt
#define HOM_TO_GEO_COORD(y,x)			\
  y.lon = DEGREE(x.phi);			\
  y.lat = DEGREE(THETA(x.mu));			\
  y.dpt = x.dpt


/* Vectorial algebra */

#define VECTOR_OP_VECTOR(z, x, op, y)			\
  z.u=x.u op y.u;					\
  z.v=x.v op y.v;					\
  z.w=x.w op y.w					\

#define SCALAR_OP_VECTOR(y, alpha, op, x)		\
  y.u=alpha op x.u;					\
  y.v=alpha op x.v;					\
  y.w=alpha op x.w

#define NORM(x) sqrt((x.u*x.u)+(x.v*x.v)+(x.w*x.w))

#define PRODVEC(x,y,z)				\
  x.u = y.v*z.w - y.w*z.v;			\
  x.v = y.w*z.u - y.u*z.w;			\
  x.w = y.u*z.v - y.v*z.u

#endif
