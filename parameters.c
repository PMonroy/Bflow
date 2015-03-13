#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "date.h"

#define SHORTSTRING 128
#define LONGSTRING 256

typedef struct{
  char *name;
  char *type;
  char *value;
} parameter_st;

/*PARAMETERS */
parameter_st param[]={
  { "year_start", "unsigned long", NULL },
  { "month_start", "unsigned int", NULL },
  { "day_start", "unsigned int", NULL },
  { "period", "unsigned long", NULL },
  { "time_step", "double", NULL },
  { "pathroms", "char", NULL },
  { "iptfile", "char", NULL }
}; 
int np = sizeof(param)/sizeof(parameter_st);

date dstart;  
unsigned long period;   
char *pathroms; 
double tstep;
char *iptfile;



void listofparameters(void )
{
  int i;

  printf(" (Name) (Type)\n");
  for(i=0; i<np; i++)
    printf(" %s : %s\n", param[i].name, param[i].type);
}

int readinparameters(FILE *input)
{
  char line[LONGSTRING]; 
  char name[SHORTSTRING], value[SHORTSTRING];
  int *pflag;
  int i;//loop indices

  if(input == NULL)
    {
      printf("File parameters not found\n");
      return 1;
    }

  //allocate memory for pflag
  pflag = (int*) calloc(np, sizeof(int));
  if(pflag==NULL)
    {
      printf("Out of memory\n");
      return 1;
    }
  
  //read the params
  while (fgets(line, sizeof line, input)) 
    {
      if (*line == '#') continue; /* ignore comment line */
      if (*line == '\n') continue; /* ignore blank line */
      if (sscanf(line, "%s : %s", name, value) != 2) 
	{
	  printf("Parameter %s has no value\n", name);
	  return 1;
	}
      else 
	{
	  for(i=0; i<np ;i++)
	    {
	      if(strcmp(name,param[i].name) == 0)
		{
		  pflag[i]++;
		  if(pflag[i]>1)
		    {
		      printf("Parameter %s repeated\n", name);
		      return 1;
		    }
		  param[i].value = (char*) malloc(sizeof(value));
		  strcpy(param[i].value, value);
		  break;
		}
	    }
	  if(i==np)
	    {
	      printf("Unknown parameter %s\n",name); 
	      return 1;
	    }
	}
    }

  for(i=0; i<np; i++) 
    {
      if(pflag[i]==0)
	{
	  printf("Parameter %s not defined\n", param[i].name);
	  return 1;
	}
      if(strcmp(param[i].name,"year_start")==0)
	dstart.year = atoi(param[i].value); 
      else if(strcmp(param[i].name,"month_start")==0)
	dstart.month = atoi(param[i].value); 
      else if(strcmp(param[i].name,"day_start")==0)
	dstart.day = atoi(param[i].value); 
      else if(strcmp(param[i].name,"period")==0)
	period = atoi(param[i].value); 
      else if(strcmp(param[i].name,"time_step")==0)
	tstep = atof(param[i].value); 
      else if(strcmp(param[i].name,"pathroms")==0)
	pathroms = param[i].value; 
      else if(strcmp(param[i].name,"iptfile")==0)
	iptfile = param[i].value; 
      else 
	{
	      printf("Unknown parameter\n");
	      return 1;	    
	}
    }

  free(pflag);
  pflag = NULL;
  
  return 0;
}
