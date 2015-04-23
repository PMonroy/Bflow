#include "coordinates.h"
#include "velocity.h"

int rk4(double t, double deltat, double ws, unsigned long q, sph_coord *ptsphe);
int inertial_rk4(double t, double tstep, double ws, unsigned long q, sph_coord *ptsphe);
