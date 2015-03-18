#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "integration.h"

#define TRIAL_POINT(rtrial, r, alpha, vec)	  \
  rtrial.phi = r.phi + (alpha) * vec.u;		  \
  rtrial.mu  = r.mu  + (alpha) * vec.v;		  \
  rtrial.dpt = r.dpt + (alpha) * vec.w

//Parameters: Extern variables
extern double gravity; 
extern double omega; 

int rk4(double t, double tstep, double ws, unsigned long q, sph_coord *ptsphe)
{
  hom_coord ptmu, ptmu2, ptmu3, ptmu4;
  vector v1,v2,v3,v4;
  double tstep2,tstep6;
  double tau;
  double theta;
  double mu;
  double h; // scale factor of equally spaced cordinate system
  
  /* Transformation to equally space cordinates*/
  ptmu.phi = ptsphe->phi;
  ptmu.mu = MU(ptsphe->theta);
  ptmu.dpt = ptsphe->dpt;

  /* Time increments */
  tstep2 = tstep*0.5;
  tstep6 = tstep/6.0;
  
  /* Calculate V1: */
  if(get_velocity(t, q, ptmu, &v1))
    return 1;
  theta = ptsphe->theta;
  h = R_EARTH * cos(theta);
  v1.u = v1.u / h; // rads velocity
  v1.v = v1.v / h; // rads velocity
  v1.w = v1.w + ws; //adding sinking velocity

  /* Calculate V2: */
  tau = t + tstep2;  
  TRIAL_POINT(ptmu2, ptmu, tstep2, v1);
  if(get_velocity(tau, q, ptmu2, &v2))
    return 1;
  theta = THETA(ptmu2.mu);
  h = R_EARTH * cos(theta);
  v2.u = v2.u / h; // rads velocity
  v2.v = v2.v / h; // rads velocity
  v2.w = v2.w + ws;//adding sinking velocity

  /* Calculate V3: */
  TRIAL_POINT(ptmu3, ptmu, tstep2, v2);
  if(get_velocity(tau, q, ptmu3, &v3))
    return 1;
  theta = THETA(ptmu3.mu);
  h = R_EARTH * cos(theta);
  v3.u = v3.u / h;
  v3.v = v3.v / h;
  v3.w = v3.w + ws;//adding sinking velocity
  
  /* Calculate V4: */
  tau = t + tstep;
  TRIAL_POINT(ptmu4, ptmu, tstep, v3);
  if(get_velocity(tau, q, ptmu4, &v4))
    return 1;
  theta = THETA(ptmu4.mu);
  h = R_EARTH * cos(theta);
  v4.u = v4.u / h;
  v4.v = v4.v / h;
  v4.w = v4.w + ws;

  /* Calculate Final point */
  ptsphe->phi = ptmu.phi + tstep6 * (v1.u + v4.u + 2.0 * (v2.u + v3.u));
  mu = ptmu.mu  + tstep6 * (v1.v + v4.v + 2.0 * (v2.v + v3.v));
  ptsphe->theta = THETA(mu);
  ptsphe->dpt = ptmu.dpt + tstep6 * (v1.w + v4.w + 2.0 * (v2.w + v3.w));

  return 0;
}

int inertial_rk4(double t, double tstep, double beta, double taup, unsigned long q, sph_coord *ptsphe)
{
  hom_coord ptmu, ptmu2, ptmu3, ptmu4;
  vector v1,v2,v3,v4;
  vector vomega;
  vector acoriolis;
  double tstep2,tstep6;
  double tau;
  double ftau;
  double theta;
  double mu;
  double h; // scale factor of equally spaced cordinate system

  ftau=taup*(beta-1.0);
  
  /* Transformation to equally space cordinates*/
  ptmu.phi = ptsphe->phi;
  ptmu.mu = MU(ptsphe->theta);
  ptmu.dpt = ptsphe->dpt;

  /* Time increments */
  tstep2 = tstep*0.5;
  tstep6 = tstep/6.0;
  
  /* Calculate V1: */
  if(get_velocity(t, q, ptmu, &v1))
    return 1;

  theta = ptsphe->theta;

  vomega.u = 0.0;
  vomega.v = 2.0*omega*cos(theta);
  vomega.w = 2.0*omega*sin(theta);

  PRODVEC(acoriolis,vomega,v1);

  h = R_EARTH * cos(theta);
  v1.u = (v1.u+ftau*acoriolis.u*SECONDS_DAY)/h; // rads velocity
  v1.v = (v1.v+ftau*acoriolis.v*SECONDS_DAY)/h; // rads velocity
  v1.w = v1.w+ftau*(acoriolis.w+gravity)*SECONDS_DAY;

  /* Calculate V2: */
  tau = t + tstep2;  
  TRIAL_POINT(ptmu2, ptmu, tstep2, v1);
  if(get_velocity(tau, q, ptmu2, &v2))
    return 1;
  theta = THETA(ptmu2.mu);

  vomega.u = 0.0;
  vomega.v = 2.0*omega*cos(theta);
  vomega.w = 2.0*omega*sin(theta);

  PRODVEC(acoriolis,vomega,v2);

  h = R_EARTH * cos(theta);
  v2.u = (v2.u+ftau*acoriolis.u*SECONDS_DAY)/h;
  v2.v = (v2.v+ftau*acoriolis.v*SECONDS_DAY)/h;
  v2.w = v2.w+ftau*(acoriolis.w+gravity)*SECONDS_DAY;

  /* Calculate V3: */
  TRIAL_POINT(ptmu3, ptmu, tstep2, v2);
  if(get_velocity(tau, q, ptmu3, &v3))
    return 1;
  theta = THETA(ptmu3.mu);

  vomega.u = 0.0;
  vomega.v = 2.0*omega*cos(theta);
  vomega.w = 2.0*omega*sin(theta);

  PRODVEC(acoriolis,vomega,v3);

  h = R_EARTH * cos(theta);
  v3.u = (v3.u+ftau*acoriolis.u*SECONDS_DAY)/h;
  v3.v = (v3.v+ftau*acoriolis.v*SECONDS_DAY)/h;
  v3.w = v3.w+ftau*(acoriolis.w+gravity)*SECONDS_DAY;
  
  /* Calculate V4: */
  tau = t + tstep;
  TRIAL_POINT(ptmu4, ptmu, tstep, v3);
  if(get_velocity(tau, q, ptmu4, &v4))
    return 1;
  theta = THETA(ptmu4.mu);

  vomega.u = 0.0;
  vomega.v = 2.0*omega*cos(theta);
  vomega.w = 2.0*omega*sin(theta);

  PRODVEC(acoriolis,vomega,v4);

  h = R_EARTH * cos(theta);
  v4.u = (v4.u+ftau*acoriolis.u*SECONDS_DAY)/h;
  v4.v = (v4.v+ftau*acoriolis.v*SECONDS_DAY)/h;
  v4.w = v4.w+ftau*(acoriolis.w+gravity)*SECONDS_DAY;

  /* Calculate Final point */
  ptsphe->phi = ptmu.phi + tstep6 * (v1.u + v4.u + 2.0 * (v2.u + v3.u));
  mu = ptmu.mu  + tstep6 * (v1.v + v4.v + 2.0 * (v2.v + v3.v));
  ptsphe->theta = THETA(mu);
  ptsphe->dpt = ptmu.dpt + tstep6 * (v1.w + v4.w + 2.0 * (v2.w + v3.w));

  return 0;
}
