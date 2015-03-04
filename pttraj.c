#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include "velocity.h"
#include "parameters.h"

extern date dstart;   // nº 0, 1, 2 
extern int period;    // nº 3
extern char *pathroms;  // nº 4
extern int ximax;     // nº 5
extern int etamax;    // nº 6
extern int smax;      // nº 7

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

  if(ncdump())
    return 1;

  resetgrid();
  return 1;
}
