#define PTRACER

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include "parameters.h"
#include "coordinates.h"
#include "integration.h"

extern char *iptfile;
extern double tstep;
extern unsigned long period;
extern double vsink;

void print_usage(char *me) 
{
  printf("\n Usage: \n\t %s -i <file> \n", me);
  printf(" In the <file> there must be these parameters:\n");
  listofparameters();
}

int main(int argc, char * argv[])
{
  char *me;
  int option = 0;
  int iflag=0;
  char *ifilename=NULL; 
  FILE *input;
  
  FILE *ipt;
  unsigned long np = 0;
  char line[1024];

  geo_coord *geo_pt;
  sph_coord *sph_pt;
  unsigned long *outsider;
  unsigned long q;
  
  double t, tmax;

  char nameout[256]; 
  FILE *output;

  // COMMAND LINE PARAMETERS
  me = argv[0];
  if (3 != argc)
    {
      print_usage(me);
      return 1;
    }
  while ((option = getopt(argc, argv,"i:")) != -1) 
    {
      switch (option) 
	{
	case 'i' :
	  iflag++;
	  ifilename = optarg;
	  break;
	default: 
	  print_usage(me); 
	  return 1;
	}
    }
  if (iflag != 1) 
    {
      print_usage(me);
      return 1;
    }

  // READ PARAMETERS FROM A TEXT FILE
  input = fopen(ifilename, "r");
  if(readparams(input))
  {
    print_usage(me);
    return 1;
  }
  fclose(input);

  // READ INITIAL POSITIONS
  if((ipt=fopen(iptfile,"r"))==NULL)
    {
      printf("Error: File %s doesn't exist\n",iptfile);
      return 1;
    }
  while(fgets(line,sizeof(line),ipt) != NULL)
    np++;
  
  geo_pt=(geo_coord *) malloc(np*sizeof(geo_coord));
  if(geo_pt == NULL)
    return 1;

  sph_pt=(sph_coord *) malloc(np*sizeof(sph_coord));
  if(sph_pt == NULL)
    return 1;

  outsider=(unsigned long *)calloc(np, sizeof(unsigned long));
  if(outsider == NULL)
    return 1;

  /* Read the initial positions */
  rewind(ipt);
  for(q=0; q<np; q++)
    {
      if(fscanf(ipt,"%lf %lf %lf", &(geo_pt[q].lon), &(geo_pt[q].lat), &(geo_pt[q].dpt))==EOF)
	{
	  
	  printf("incorrect number of lines %lu in the file %s\n", np, iptfile);
	  return 1;
	}
      GEO_TO_SPH_COORD(sph_pt[q],geo_pt[q]);
    }
  fclose(ipt);

  /* Initialize velocity module */
  printf("Velocity module initialized: ");
  if(init_velocity(np, sph_pt))
    {
      printf("FAIL\n");
      return 1;
    }
  else
    printf("OK\n");

  /* Calculating trajectories */

  output = fopen("ptraj_t0.00.dat","w");
  for(q=0; q<np; q++)
    fprintf(output,"%lf %lf %lf\n", DEGREE(sph_pt[q].phi), DEGREE(sph_pt[q].theta), sph_pt[q].dpt);

  fclose(output);

  tmax = (double) (period-1);
  for(t=0; t<tmax; t=t + tstep)
    {
      sprintf(nameout,"ptraj_t%.2f.dat",t+tstep);
      output = fopen(nameout,"w");
      for(q=0; q<np; q++)
	{
	  if(outsider[q]==0)
	    outsider[q]=rk4(t, tstep, vsink, q, &sph_pt[q]);
	   
	  fprintf(output,"%lf %lf %lf\n", DEGREE(sph_pt[q].phi), DEGREE(sph_pt[q].theta), sph_pt[q].dpt);
	}
      fclose(output);
      }

  /* Reset velocity module */
  reset_velocity(np);

  /* Free position vectors of particles */
  free(geo_pt);
  free(sph_pt);

  free(outsider);
  return 0;
}
