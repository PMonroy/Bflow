#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <netcdf.h>

#include "velocity.h"
#include "memalloc.h"

//Extern variables
extern date dstart;   // nº 0, 1, 2 
extern int period;    // nº 3
extern char *pathroms;  // nº 4
extern int ximax;     // nº 5
extern int etamax;    // nº 6
extern int smax;      // nº 7

double *mu;
double *phi;
double ****dpt;
vector ****vroms;

void print_error(int ncf)
{
  printf("Error in ncdump: %s\n", nc_strerror(ncf));
}

int ncdump(void )
{
  char ncfile[255];        // Name of the nc file 
  int ncID;                      // netCDF ID for the file
  int lonID;                // netCDF ID for the variables
  int latID;
  int depthID;
  int uID;
  int vID;
  int wID;

  int xiumax = ximax-1;
  int etavmax = etamax-1;

  static size_t start2D[2];
  static size_t count2DLON[2];
  static size_t count2DLAT[2];
  static ptrdiff_t stride2D[2];

  static size_t start4D[4];
  static size_t count4D[4];
  static size_t countu4D[4];
  static size_t countv4D[4];
  static ptrdiff_t stride4D[4];

  int count, sum_count;
  int ncflag; //Error handling.

  int s, xi, eta; //Loop index
  int t, tstart, tend;
  date tdate;

  double *lon;
  double *lat;
  double *depth;
  double *u;
  double *v;
  double *w;
  
  size_t nrho, nu, nv;

  int sml, ml, smlu, mlu, smvl, mvl;

  /* Initialize size_t variables:*/

   start2D[0] = 0;  
   start2D[1] = 0; 

   count2DLON[0] = 1;
   count2DLON[1] = ximax;

   count2DLAT[0] = etamax;
   count2DLAT[1] = 1;

   stride2D[0] = 1;
   stride2D[1] = 1;    

   start4D[0] = 0;
   start4D[1] = 0;
   start4D[2] = 0;
   start4D[3] = 0;

   count4D[0] = 0;
   count4D[1] = smax;
   count4D[2] = etamax;
   count4D[3] = ximax;

   countu4D[0] = 0;
   countu4D[1] = smax;
   countu4D[2] = etamax;
   countu4D[3] = xiumax;

   countv4D[0] = 0;
   countv4D[1] = smax;
   countv4D[2] = etavmax;
   countv4D[3] =  ximax;

   stride4D[0] = 1;
   stride4D[1] = 1;
   stride4D[2] = 1;
   stride4D[3] = 1;

  /* Open the file. NC_NOWRITE tells netCDF we want read-only access
   * to the file.*/
  sprintf(ncfile,"%sextract_roms_avg_Y%dM%d.nc.1", pathroms, dstart.year, dstart.month);  
  if((ncflag = nc_open(ncfile, NC_NOWRITE, &ncID)))
    {
      print_error(ncflag);
      return 1;
    }
  /* Get the varid of the data variable, based on its name. */
  if((ncflag = nc_inq_varid(ncID, "lon_rho", &lonID)))
    {
      print_error(ncflag);   
      return 1;
    }
  if((ncflag = nc_inq_varid(ncID, "lat_rho", &latID)))
    {
      print_error(ncflag);   
      return 1;
    }
      
  /* Read the data */
  if((lon = mkdarray1D(ximax)) == NULL)
      return 1;

  if((lat = mkdarray1D(etamax)) == NULL)
      return 1;

  if((ncflag = nc_get_vars_double(ncID, lonID, start2D, count2DLON, stride2D, lon)))
    {
      print_error(ncflag);   
      return 1;
    }
  if((ncflag = nc_get_vars_double(ncID, latID, start2D, count2DLAT, stride2D, lat)))
    {
      print_error(ncflag);
      return 1;
    }

  /* Close the file, freeing all resources. */
  if((ncflag = nc_close(ncID)))
    {
      print_error(ncflag);
      return 1;
    }  

  /* Transformation from lon[] lat[] to phi[] mu[]*/
 
  if((phi = mkdarray1D(ximax)) == NULL)
      return 1;

  if((mu = mkdarray1D(etamax)) == NULL)
      return 1;

  for(xi=0; xi<ximax; xi++)
    {
      phi[xi]=RADS(lon[xi]);
    }
  for(eta = 0; eta < etamax; eta++)
    {
      mu[eta] = MU(RADS(lat[eta]));
    }

  freedarray1D(lon);
  freedarray1D(lat);

  /* POINTS VARIBLES */
  
  nrho = period*smax*etamax*ximax;
  nu = period*smax*etamax*xiumax;
  nv = period*smax*etavmax*ximax;
    
  if((depth = mkdarray1D(nrho)) == NULL)
    return 1;
  if((w = mkdarray1D(nrho)) == NULL)
    return 1;
  if((v = mkdarray1D(nv)) == NULL)
    return 1;
  if((u = mkdarray1D(nu)) == NULL)
    return 1;
  
  sml = smax*etamax*ximax;
  ml = etamax*ximax;

 
  smlu = smax*etamax*xiumax;
  mlu = etamax*xiumax;

  smvl = smax*etavmax*ximax;
  mvl = etavmax*ximax;
 
  tstart = DATE_TO_TIME(dstart);
  tend = tstart + period;
  t = tstart;
  sum_count = 0;
  while(t < tend)
    {
      TIME_TO_DATE(tdate,t);
      
      if(tdate.day == 0)
	count = 30;
      else
	count = 30-tdate.day;

      if((t + count) > tend)
	count = tend- t;
      
      count4D[0] = countu4D[0] = countv4D[0] = (size_t) count;
      start4D[0] = (size_t) tdate.day;
        
      /* Open the file. NC_NOWRITE tells netCDF we want read-only access
       * to the file.
       */
      sprintf(ncfile,"%sextract_roms_avg_Y%dM%d.nc.1", pathroms, tdate.year, tdate.month);       
      if ((ncflag = nc_open(ncfile, NC_NOWRITE, &ncID)))
	{
	  print_error(ncflag);
	  return 1;
	}  
	/* The netCDF ID for the data variable*/
      if ((ncflag = nc_inq_varid(ncID, "depth", &depthID)))
	{
	  print_error(ncflag);
	  return 1;
	}  
      if ((ncflag = nc_inq_varid(ncID, "u", &uID)))
	{
	  print_error(ncflag);
	  return 1;
	}

      if ((ncflag = nc_inq_varid(ncID, "v", &vID)))
	{
	  print_error(ncflag);
	  return 1;
	}  
      if ((ncflag = nc_inq_varid(ncID, "w", &wID)))
	{
	  print_error(ncflag);
	  return 1;
	}  

      /* Read the variables */
      if ((ncflag = nc_get_vars_double(ncID, depthID, start4D, count4D, stride4D, depth+sum_count*sml)))
	{
	  print_error(ncflag);
	  return 1;
	}  
      if ((ncflag = nc_get_vars_double(ncID, uID, start4D, countu4D, stride4D, u+sum_count*smlu)))
	{
	  print_error(ncflag);
	  return 1;
	}  
      if ((ncflag = nc_get_vars_double(ncID, vID, start4D, countv4D, stride4D, v+sum_count*smvl)))
	{
	  print_error(ncflag);
	  return 1;
	}  
      if ((ncflag = nc_get_vars_double(ncID, wID, start4D, count4D, stride4D, w+sum_count*sml)))
	{
	  print_error(ncflag);
	  return 1;
	}  

      /* Close the file, freeing all resources. */ 
      if ((ncflag = nc_close(ncID)))
	{
	  print_error(ncflag);
	  return 1;
	}  
    
      t += count;
      sum_count += count;
    }


  /* Transformation variables */

  dpt = mkdarray4D(period, ximax, etamax, smax);
  vroms = mkvarray4D(period, ximax, etamax, smax);
  for(t = 0; t < period; t++)
    {
      for(xi = 0; xi < ximax; xi++)
	{
	  for(eta = 0; eta < etamax; eta++)
	    {
	      for(s = 0; s < smax; s++)
		{
		  dpt[t][xi][eta][s] = *(depth + t*sml+s*ml+ eta*ximax+ xi);
		  vroms[t][xi][eta][s].w= *(w + t*sml+s*ml+ eta*ximax+ xi);
		  vroms[t][xi][eta][s].u= (*(u + t*smlu+s*mlu+ eta*xiumax+ xi-(xi==(ximax-1)))+*(u + t*smlu+s*mlu+ eta*xiumax + xi-(xi!=0)))/2.0;
		  vroms[t][xi][eta][s].v= (*(v + t*smvl+s*mvl+ (eta-(eta==(etamax-1)))*ximax+ xi)+*(v + t*smvl+s*mvl+ (eta-(eta!=0))*ximax + xi))/2.0;
		}
	    }
	}
    }

  freedarray1D(depth);
  freedarray1D(u);
  freedarray1D(v);
  freedarray1D(w);
  return 0;
}

void resetgrid(void )
{  
  freedarray1D(mu);
  freedarray1D(phi);
  freedarray4D(dpt,period, ximax, etamax);
  freevarray4D(vroms,period, ximax, etamax);
}
