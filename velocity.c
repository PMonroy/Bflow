#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <netcdf.h>

#include "velocity.h"
#include "memalloc.h"
#include "locate.h"

typedef struct ncdim_st{
  char name[NC_MAX_NAME+1];
  size_t length;
} ncdim;

//Macros:
#define INTERPOLATION(xint, x, j, alpha, beta)	\
  xint.u = alpha * x[(j)].u + beta * x[(j)+1].u; \
  xint.v = alpha * x[(j)].v + beta * x[(j)+1].v; \
  xint.w = alpha * x[(j)].w + beta * x[(j)+1].w	

//Parameters: Extern variables
extern date dstart; 
extern unsigned long period;  
extern char *pathroms; 

//Global variables 
double *mu;
double *phi;
double *theta;
double ****dpt;
vector ****vroms;
unsigned long tmax, smax, ximax, xiumax, etamax, etavmax;
unsigned long *xib, *etab, ****sb;

//Prototypes functions
void print_error(int ncf);
int ncdump(void );
int locate_slot(unsigned long time, unsigned long q, sph_coord pt);
int huntbox(unsigned long time, unsigned long q, hom_coord pt);

int init_velocity(unsigned long np, sph_coord *pt)
{
  unsigned long q;

  if(ncdump())
    return 1;

  if((xib = mkularray1D(np)) == NULL)
    return 1;
  if((etab =  mkularray1D(np)) == NULL)
    return 1;
  if((sb = mkularray4D(np,2,2,2)) == NULL)
    return 1;
  
  for(q=0; q<np; q++)
    {
      if(locate_slot(0, q, pt[q]))
	return 1;
    }
  return 0;
}

void reset_velocity(unsigned long np)
{
  
  /* Free grid variables and ROMS velocity*/
  freedarray1D(mu);
  freedarray1D(theta);
  freedarray1D(phi);
  freedarray4D(dpt,period+1, ximax, etamax);
  freevarray4D(vroms,period+1, ximax, etamax);

  /* Free slot indices */
  freeularray1D(xib);
  freeularray1D(etab);
  freeularray4D(sb,np,2,2);
}


void print_error(int ncf)
{
  printf("Error in ncdump: %s\n", nc_strerror(ncf));
}

int ncdump(void )
{
  char ncfile[NC_MAX_NAME+128];        // Name of the nc file 
  ncdim *dim;
  int ndim;
  int ncID;                      // netCDF ID for the file
  int lonID;                // netCDF ID for the variables
  int latID;
  int depthID;
  int uID;
  int vID;
  int wID;

  static size_t start2D[2];
  static size_t count2DLON[2];
  static size_t count2DLAT[2];
  static ptrdiff_t stride2D[2];

  static size_t start4D[4];
  static size_t count4D[4];
  static size_t countu4D[4];
  static size_t countv4D[4];
  static ptrdiff_t stride4D[4];

  unsigned long count, sum_count;
  int ncflag; //Error handling.

  int i; 
  unsigned long t, tstart, tend;
  date tdate;

  double *lon;
  double *lat;
  double *depth;
  double *u;
  double *v;
  double *w;

  unsigned long  s, xi, eta; //Loop index  
  unsigned long nrho, nu, nv;
  unsigned long sml, ml, smlu, mlu, smvl, mvl;

  /* Open the nc file at initial date */
  sprintf(ncfile,"%sextract_roms_avg_Y%luM%u.nc.1", pathroms, dstart.year, dstart.month);  
  if((ncflag = nc_open(ncfile, NC_NOWRITE, &ncID)))
    {
      print_error(ncflag);
      return 1;
    }

  /* Read the dimensions*/      
  if((ncflag = nc_inq_ndims(ncID, &ndim)))
    {
      print_error(ncflag);
      return 1;
    }
  dim = (ncdim*) malloc(ndim*sizeof(ncdim));
  for(i=0; i<ndim; i++)
    {
      if((ncflag = nc_inq_dim(ncID, i, dim[i].name, &dim[i].length)))
	{
	  print_error(ncflag);
	  return 1;
	}
    }

  for(i=0; i<ndim; i++)
    {
      if(strcmp(dim[i].name,"xi_rho")==0)
	ximax = dim[i].length;
      else if(strcmp(dim[i].name,"xi_u")==0)
	xiumax = dim[i].length;
      else if(strcmp(dim[i].name,"eta_rho")==0)
	etamax = dim[i].length;
      else if(strcmp(dim[i].name,"eta_v")==0)
	etavmax = dim[i].length;
      else if(strcmp(dim[i].name,"s_rho")==0)
	smax = dim[i].length;
      else if(strcmp(dim[i].name,"time")==0)
	tmax = dim[i].length;
      else
	{
	  printf("Unknown dimension\n");
	  return 1;
	}
    }
  free(dim);

  /* Initialize size_t variables:*/

   start2D[0] = 0;  
   start2D[1] = 0; 

   count2DLON[0] = 1;
   count2DLON[1] = (size_t) ximax;

   count2DLAT[0] = (size_t) etamax;
   count2DLAT[1] = 1;

   stride2D[0] = 1;
   stride2D[1] = 1;    

   start4D[0] = 0;
   start4D[1] = 0;
   start4D[2] = 0;
   start4D[3] = 0;

   count4D[0] = 0;
   count4D[1] = (size_t) smax;
   count4D[2] = (size_t) etamax;
   count4D[3] = (size_t) ximax;

   countu4D[0] = 0;
   countu4D[1] = (size_t) smax;
   countu4D[2] = (size_t) etamax;
   countu4D[3] = (size_t) xiumax;

   countv4D[0] = 0;
   countv4D[1] = (size_t) smax;
   countv4D[2] = (size_t) etavmax;
   countv4D[3] = (size_t) ximax;

   stride4D[0] = 1;
   stride4D[1] = 1;
   stride4D[2] = 1;
   stride4D[3] = 1;

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
  if((theta = mkdarray1D(etamax)) == NULL)
      return 1;

  for(xi=0; xi<ximax; xi++)
    {
      phi[xi]=RADS(lon[xi]);
    }
  for(eta = 0; eta < etamax; eta++)
    {
      theta[eta] = RADS(lat[eta]);
      mu[eta] = MU(theta[eta]);
    }

  freedarray1D(lon);
  freedarray1D(lat);

  /* POINTS VARIBLES */
  
  nrho = (period+1)*smax*etamax*ximax;
  nu = (period+1)*smax*etamax*xiumax;
  nv = (period+1)*smax*etavmax*ximax;
    
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
  tend = tstart + (period + 1);
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
      sprintf(ncfile,"%sextract_roms_avg_Y%luM%u.nc.1", pathroms, tdate.year, tdate.month);       
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

  dpt = mkdarray4D(period+1, ximax, etamax, smax);
  vroms = mkvarray4D(period+1, ximax, etamax, smax);
  for(t = 0; t < period+1; t++)
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
		  SCALAR_OP_VECTOR(vroms[t][xi][eta][s], SECONDS_DAY, *, vroms[t][xi][eta][s]); 
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

int locate_slot(unsigned long time, unsigned long q, sph_coord pt)
{

  double *pphi, *ttheta,*ddpt ;
  unsigned long xib_1offset, etab_1offset, sb_1offset;
  int h,i,j;

  /* Locate xib*/
  pphi = phi - 1;
  locate(pphi, ximax, pt.phi, &xib_1offset);
  if(xib_1offset == 0 || xib_1offset == ximax)
    return 1;
  else
    xib[q] = xib_1offset - 1;

  /* Locate etab*/
  ttheta = theta - 1;
  locate(ttheta, etamax, pt.theta, &etab_1offset);
  if(etab_1offset == 0 || etab_1offset == etamax)
    return 1;
  else
    etab[q] = etab_1offset - 1;

  /* Locate sb */
  for(h = 0; h < 2; h++)
    {
      for(i = 0; i < 2; i++)
	{
	  for(j = 0; j < 2; j++)
	    {
	      ddpt = dpt[time+h][xib[q]+i][etab[q]+j] - 1;
	      locate(ddpt, smax, pt.dpt, &sb_1offset);	     
	      if(sb_1offset == 0 || sb_1offset == smax)
		return 1;
	      else
		sb[q][h][i][j] = sb_1offset - 1;
	    }
	}
    }
 
  return 0;
}

int huntbox(unsigned long time, unsigned long q, hom_coord pt)
{

  double *pphi, *mmu,*ddpt ;
  unsigned long xib_1offset, etab_1offset, sb_1offset;
  int h,i,j;

  /* Locate xib*/
  pphi = phi - 1;
  xib_1offset = xib[q] + 1;
  hunt(pphi, ximax, pt.phi, &xib_1offset);
  if(xib_1offset == 0 || xib_1offset == ximax)
    return 1;
  else
    xib[q] = xib_1offset - 1;

  /* Locate etab*/
  mmu = mu - 1;
  etab_1offset = etab[q] + 1;
  hunt(mmu, etamax, pt.mu, &etab_1offset);
  if(etab_1offset == 0 || etab_1offset == etamax)
    return 1;
  else
    etab[q] = etab_1offset - 1;
  
  /* Locate sb */
  for(h = 0; h < 2; h++)
    {
      for(i = 0; i < 2; i++)
	{
	  for(j = 0; j < 2; j++)
	    {
	      ddpt = dpt[time+h][xib[q]+i][etab[q]+j] - 1;
	      sb_1offset = sb[q][h][i][j] + 1;
	      hunt(ddpt, smax, pt.dpt, &sb_1offset);	     
	      if(sb_1offset == 0 || sb_1offset == smax)
		return 1;
	      else
		  sb[q][h][i][j] = sb_1offset - 1;
	    }
	}
    }
  return 0;
}

int get_velocity(double t, unsigned long q, hom_coord pt, vector *vint)
{
  hom_coord ptb[16];
  vector vb[16];
  unsigned long time;
  unsigned int index, contw;  
  double alpha, beta;
  unsigned long eta, xi, s; 
  unsigned int h,i,j,k;

  /* Calculates the vectors vb[15] and points ptmb[15] */
  time = (unsigned long) t;
  if(huntbox(time, q, pt))
    return 1;
  
  /* Vectors and points with only one int index*/
  index = contw = 0;
  for(h = 0; h < 2; h++)
    {
      for(i=0; i < 2; i++)
	{
	  for(j = 0; j < 2; j++)
	    {
	      for(k = 0; k < 2; k++)
		{
		  xi = xib[q]+i;
		  eta = etab[q]+j;
		  s = sb[q][h][i][j]+k;

		  ptb[index].phi = phi[xi];
		  ptb[index].mu = mu[eta];
		  ptb[index].dpt = dpt[time+h][xi][eta][s];

		  vb[index] = vroms[time+h][xi][eta][s];

		  if(vb[index].w==0)
		    contw++;

		  index++; 
		}
	    }
	}
    }
  if(contw==16)
    return 1;// The particle has reached the coast

  /* Depth Interpolation: */
  for(index=0; index<16; index=index+2)
    {
      alpha = (ptb[index+1].dpt - pt.dpt)/(ptb[index+1].dpt - ptb[index].dpt);
      beta = 1 - alpha;
      INTERPOLATION(vb[index/2], vb, index, alpha, beta);
      ptb[index/2] = ptb[index]; 
    }

  /* Mu Interpolation: */
  alpha = (ptb[1].mu - pt.mu)/(ptb[1].mu - ptb[0].mu);
  beta = 1.0 - alpha;
  for(index = 0; index < 8; index=index+2)
    {
      INTERPOLATION(vb[index/2], vb, index, alpha, beta);
      ptb[index/2] = ptb[index];
    }

  /* Phi Interpolation */
  alpha = (ptb[1].phi - pt.phi)/(ptb[1].phi - ptb[0].phi);
  beta = 1.0 - alpha;
  for(index = 0; index < 4; index=index+2)
    {
      INTERPOLATION(vb[index/2], vb, index, alpha, beta);
      ptb[index/2] = ptb[index];
    }

  /* Time Interpolation: */ 
  alpha = ((double) (time + 1)) - t;  
  beta = 1.0 - alpha; 
  INTERPOLATION(vb[0], vb, 0, alpha, beta);

  /* Interpolated V*/
  *vint = vb[0];

  return 0;
}
