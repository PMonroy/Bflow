#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include "velocity.h"
#include "parameters.h"
#include "coordinates.h"

extern char *iptfile;

void print_usage(char *me) 
{
  printf("\n Usage: \n\t %s -i file \n", me);
  printf(" in the file there must be this parameters:\n");
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
  int np = 0;
  char line[1024];

  geo_coord *geo_pt;
  sph_coord *sph_pt;
  int q;
  
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
  if(readinparameters(input))
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

  printf("number of points %d\n",np);
  
  geo_pt=(geo_coord *) malloc(np*sizeof(geo_coord));
  if(geo_pt == NULL)
    return 1;

  sph_pt=(sph_coord *) malloc(np*sizeof(sph_coord));
  if(sph_pt == NULL)
    return 1;

  /* Read the initial positions */
  rewind(ipt);
  for(q=0; q<np; q++)
    {
      if(fscanf(ipt,"%lf %lf %lf", &(geo_pt[q].lon), &(geo_pt[q].lat), &(geo_pt[q].dpt))==EOF)
	{
	  printf("incorrect number of lines in the file %s\n", iptfile);
	  return 1;
	}
      GEO_TO_SPH_COORD(sph_pt[q],geo_pt[q]);
    }
  fclose(ipt);

  //Ïnitialize velocity module
  if(ncdump())
    return 1;


  //Reset velocity module
  resetgrid();
  return 1;
}
