#include "tracer.h"

#define TRIAL_POINT(rtrial, r, alpha, vec)		  \
  rtrial.phi = r.phi + (alpha) * vec.u;		  \
  rtrial.mu  = r.mu  + (alpha) * vec.v;		  \
  rtrial.dpt = r.dpt + (alpha) * vec.w


int rk4(double t, double tstep, double ws, unsigned long q, spherical_pt *ptsphe)
{
  eqspace_pt ptmu, ptmu2, ptmu3, ptmu4;
  vector v1,v2,v3,v4;
  double tstep2,tstep6;
  double tau;
  double lambda;
  double mu;
  double h; // scale factor of equally spaced cordinate system
  
  /* Transformation to equally space cordinates*/
  ptmu.phi = ptsphe->phi;
  ptmu.mu = MU(ptsphe->lambda);
  ptmu.dpt = ptsphe->dpt;

  /* Time increments */
  tstep2 = tstep*0.5;
  tstep6 = tstep/6.0;
  
  /* Calculate V1: */
  if(get_velocity(t, q, ptmu, &v1))
    return 1;
  lambda = ptsphe->lambda;
  h = R_EARTH * cos(lambda);
  v1.u = v1.u / h; // rads velocity
  v1.v = v1.v / h; // rads velocity
  v1.w = v1.w + ws; //adding sinking velocity

  /* Calculate V2: */
  tau = t + tstep2;  
  TRIAL_POINT(ptmu2, ptmu, tstep2, v1);
  if(get_velocity(tau, q, ptmu2, &v2))
    return 1;
  lambda = LAMBDA(ptmu2.mu);
  h = R_EARTH * cos(lambda);
  v2.u = v2.u / h; // rads velocity
  v2.v = v2.v / h; // rads velocity
  v2.w = v2.w + ws;//adding sinking velocity

  /* Calculate V3: */
  TRIAL_POINT(ptmu3, ptmu, tstep2, v2);
  if(get_velocity(tau, q, ptmu3, &v3))
    return 1;
  lambda = LAMBDA(ptmu3.mu);
  h = R_EARTH * cos(lambda);
  v3.u = v3.u / h;
  v3.v = v3.v / h;
  v3.w = v3.w + ws;//adding sinking velocity
  
  /* Calculate V4: */
  tau = t + tstep;
  TRIAL_POINT(ptmu4, ptmu, tstep, v3);
  if(get_velocity(tau, q, ptmu4, &v4))
    return 1;
  lambda = LAMBDA(ptmu4.mu);
  h = R_EARTH * cos(lambda);
  v4.u = v4.u / h;
  v4.v = v4.v / h;
  v4.w = v4.w + ws;

  /* Calculate Final point */
  ptsphe->phi = ptmu.phi + tstep6 * (v1.u + v4.u + 2.0 * (v2.u + v3.u));
  mu = ptmu.mu  + tstep6 * (v1.v + v4.v + 2.0 * (v2.v + v3.v));
  ptsphe->lambda = LAMBDA(mu);
  ptsphe->dpt = ptmu.dpt + tstep6 * (v1.w + v4.w + 2.0 * (v2.w + v3.w));

  return 0;
}
