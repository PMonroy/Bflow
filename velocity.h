#include "date.h"
#include "coordinates.h"

extern double *mu;
extern double *phi;
extern double ****dpt;
extern vector ****vroms;



int init_velocity(unsigned long np, sph_coord *pt);
void reset_velocity(unsigned long np);

