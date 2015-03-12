#define TRIAL_POINT(rtrial, r, alpha, vec)		  \
  rtrial.phi = r.phi + (alpha) * vec.u;		  \
  rtrial.mu  = r.mu  + (alpha) * vec.v;		  \
  rtrial.dpt = r.dpt + (alpha) * vec.w


int rk4(double t, double deltat, double ws, int q, spherical_pt *ptsphe)
{
  eqspace_pt ptmu, ptmu2, ptmu3, ptmu4;
  vector v1,v2,v3,v4;
  double deltat2,deltat6;
  double tau;
  double lambda;
  double mu;
  double h; // scale factor of equally spaced cordinate system
  
  /* Transformation to equally space cordinates*/
  ptmu.phi = ptsphe->phi;
  ptmu.mu = MU(ptsphe->lambda);
  ptmu.dpt = ptsphe->dpt;

  /* Time increments */
  deltat2 = deltat*0.5;
  deltat6 = deltat/6.0;
  
  /* Calculate V1: */
  if(LinearInterpolation(t, q, ptmu, &v1))
    return 1;
  lambda = ptsphe->lambda;
  h = R_EARTH * cos(lambda);
  v1.u = v1.u / h; // rads velocity
  v1.v = v1.v / h; // rads velocity
  v1.w = v1.w + ws; //adding sinking velocity

  /* Calculate V2: */
  tau = t + deltat2;  
  TRIAL_POINT(ptmu2, ptmu, deltat2, v1);
  if(LinearInterpolation(tau, q, ptmu2, &v2))
    return 1;
  lambda = LAMBDA(ptmu2.mu);
  h = R_EARTH * cos(lambda);
  v2.u = v2.u / h; // rads velocity
  v2.v = v2.v / h; // rads velocity
  v2.w = v2.w + ws;//adding sinking velocity

  /* Calculate V3: */
  TRIAL_POINT(ptmu3, ptmu, deltat2, v2);
  if(LinearInterpolation(tau, q, ptmu3, &v3))
    return 1;
  lambda = LAMBDA(ptmu3.mu);
  h = R_EARTH * cos(lambda);
  v3.u = v3.u / h;
  v3.v = v3.v / h;
  v3.w = v3.w + ws;//adding sinking velocity
  
  /* Calculate V4: */
  tau = t + deltat;
  TRIAL_POINT(ptmu4, ptmu, deltat, v3);
  if(LinearInterpolation(tau, q, ptmu4, &v4))
    return 1;
  lambda = LAMBDA(ptmu4.mu);
  h = R_EARTH * cos(lambda);
  v4.u = v4.u / h;
  v4.v = v4.v / h;
  v4.w = v4.w + ws;

  /* Calculate Final point */
  ptsphe->phi = ptmu.phi + deltat6 * (v1.u + v4.u + 2.0 * (v2.u + v3.u));
  mu = ptmu.mu  + deltat6 * (v1.v + v4.v + 2.0 * (v2.v + v3.v));
  ptsphe->lambda = LAMBDA(mu);
  ptsphe->dpt = ptmu.dpt + deltat6 * (v1.w + v4.w + 2.0 * (v2.w + v3.w));

  return 0;
}
