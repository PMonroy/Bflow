#include <stdio.h>
#include <stdlib.h>

#include "memalloc.h"

double* mkdarray1D(unsigned long nt)
/* Function: mkdarray1D
 * --------------------
 * 
 * Allocates a double array with range [0,1,...,(nt-1)].
 * 
 * nt = number of elements
 *
 * returns: return the pointer to the array allocation 
 *          returns NULL on error (if it is out of memory)
 */
{
  double *array;
  
  array =(double *)malloc(nt*sizeof(double));
  if(array == NULL)
    {
      printf("out of memory\n");
      return NULL;
    }
  return array;
}

double** mkdarray2D(unsigned long nt, unsigned long nx)
/* Function: mkdarray2D
 * --------------------
 * 
 * Allocates a double array with range [0,1,...,(nt-1)][0,1,...,(nx-1)].
 * 
 * nt = number of elements
 * nx = number of elements 
 *
 * returns: return the pointer to the array allocation 
 *          returns NULL on error (if it is out of memory)
 */
{
  double **array;
  unsigned long t;

  array =(double **)malloc(nt*sizeof(double *));
  if(array == NULL)
    {
      printf("out of memory\n");
      return NULL;
    }
  for(t = 0; t < nt; t++)
    {
      array[t] = (double *)malloc(nx*sizeof(double));
      if(array[t] == NULL)
	{
	  printf("out of memory\n");
	  return NULL;
	}
    }
  return array;
}

double*** mkdarray3D(unsigned long nt, unsigned long nx, unsigned long ny)
/* Function: mkdarray3D
 * --------------------
 * 
 * Allocates a double array with range [0,1,...,(nt-1)][0,1,...,(nx-1)][0,1,...,(ny-1)].
 * 
 * nt = number of elements
 * nx = number of elements  
 * ny = number of elements 
 *
 * returns: return the pointer to the array allocation 
 *          returns NULL on error (if it is out of memory)
 */
{
  double ***array;
  unsigned long t,i;

  array =(double ***)malloc(nt*sizeof(double **));
  if(array == NULL)
    {
      printf("out of memory\n");
      return NULL;
    }
  for(t = 0; t < nt; t++)
    {
      array[t] = (double **)malloc(nx*sizeof(double*));
      if(array[t] == NULL)
	{
	  printf("out of memory\n");
	  return NULL;
	}
      for(i = 0; i < nx; i++)
	{
	  array[t][i] = (double *)malloc(ny*sizeof(double));
	  if(array[t][i] == NULL)
	    {
	      printf("out of memory\n");
	      return NULL;
	    }
	}
    }
  return array;
}

double**** mkdarray4D(unsigned long nt, unsigned long nx, unsigned long ny, unsigned long nz)
/* Function: mkdarray4D
 * --------------------
 * 
 * Allocates a double array with range [0,1,...,(nt-1)][0,1,...,(nx-1)][0,1,...,(ny-1)][0,1,...,(nz-1)].
 * 
 * nt = number of elements
 * nx = number of elements  
 * ny = number of elements 
 * nz = number of elements 
 *
 * returns: return the pointer to the array allocation 
 *          returns NULL on error (if it is out of memory)
 */
{
  double ****array;
  unsigned long t,i,j;

  array =(double ****)malloc(nt * sizeof(double ***));
  if(array == NULL)
    {
      printf("out of memory\n");
      return NULL;
    }
  for(t = 0; t < nt; t++)
    {
      array[t] = (double ***)malloc(nx * sizeof(double **));
      if(array[t] == NULL)
	{
	  printf("out of memory\n");
	  return NULL;
	}
      for(i = 0; i < nx; i++)
	{
	  array[t][i] = (double **)malloc(ny * sizeof(double *));
	  if(array[t][i] == NULL)
	    {
	      printf("out of memory\n");
	      return NULL;
	    }
	  for(j=0; j<ny; j++)
	    {
	      array[t][i][j] = (double *)malloc(nz * sizeof(double ));
	      if(array[t][i][j] == NULL)
		{
		  printf("out of memory\n");
		  return NULL;
		}
	    }
	}
    }
  return array;
}

void freedarray1D(double* array)
/* Function: freedarray1D
 * -----------------------
 * 
 * Frees a array allocated with mkdarray1D.
 * 
 */
{
  free(array);
}

void freedarray2D(double** array, unsigned long nt)
/* Function: freedarray2D
 * -----------------------
 * 
 * Frees a array allocated with mkdarray2D.
 * 
 */
{
  unsigned long t;

  for (t = 0; t < nt; ++t) 
    free(array[t]);

  free(array);
}

void freedarray3D(double*** array, unsigned long nt, unsigned long nx)
/* Function: freedarray3D
 * -----------------------
 * 
 * Frees a array allocated with mkdarray3D.
 * 
 */
{
  unsigned long t,i;

  for (t = 0; t < nt; ++t) 
    {
      for(i=0; i<nx; i++)
	{
	  free(array[t][i]);
	}
      free(array[t]);
    }
    free(array);
}
void freedarray4D(double**** array, unsigned long nt, unsigned long nx, unsigned long ny)
/* Function: freedarray4D
 * -----------------------
 * 
 * Frees a array allocated with mkdarray4D.
 * 
 */
{
  unsigned long t,i,j;

  for (t = 0; t < nt; ++t) 
    {
      for(i=0; i<nx; i++)
	{
	  for(j=0; j<ny; j++)
	    free(array[t][i][j]);
	  free(array[t][i]);
	}
      free(array[t]);
    }
  free(array);
}

int* mkiarray1D(unsigned long nt)
/* Function: mkiarray1D
 * --------------------
 * 
 * Allocates a int array with range [0,1,...,(nt-1)].
 * 
 * nt = number of elements
 *
 * returns: return the pointer to the array allocation 
 *          returns NULL on error (if it is out of memory)
 */
{
  int *array;
  
  array =(int *)malloc(nt*sizeof(int));
  if(array == NULL)
    {
      printf("out of memory\n");
      return NULL;
    }
  return array;
}

int** mkiarray2D(unsigned long nt, unsigned long nx)
/* Function: mkiarray2D
 * --------------------
 * 
 * Allocates a int array with range [0,1,...,(nt-1)][0,1,...,(nx-1)].
 * 
 * nt = number of elements
 * nx = number of elements 
 *
 * returns: return the pointer to the array allocation 
 *          returns NULL on error (if it is out of memory)
 */
{
  int **array;
  unsigned long t;

  array =(int **)malloc(nt*sizeof(int *));
  if(array == NULL)
    {
      printf("out of memory\n");
      return NULL;
    }
  for(t = 0; t < nt; t++)
    {
      array[t] = (int *)malloc(nx*sizeof(int));
      if(array[t] == NULL)
	{
	  printf("out of memory\n");
	  return NULL;
	}
    }
  return array;
}

int*** mkiarray3D(unsigned long nt, unsigned long nx, unsigned long ny)
/* Function: mkiarray3D
 * --------------------
 * 
 * Allocates a int array with range [0,1,...,(nt-1)][0,1,...,(nx-1)][0,1,...,(ny-1)].
 * 
 * nt = number of elements
 * nx = number of elements  
 * ny = number of elements 
 *
 * returns: return the pointer to the array allocation 
 *          returns NULL on error (if it is out of memory)
 */
{
  int ***array;
  unsigned long t,i;

  array =(int ***)malloc(nt*sizeof(int **));
  if(array == NULL)
    {
      printf("out of memory\n");
      return NULL;
    }
  for(t = 0; t < nt; t++)
    {
      array[t] = (int **)malloc(nx*sizeof(int*));
      if(array[t] == NULL)
	{
	  printf("out of memory\n");
	  return NULL;
	}
      for(i = 0; i < nx; i++)
	{
	  array[t][i] = (int *)malloc(ny*sizeof(int));
	  if(array[t][i] == NULL)
	    {
	      printf("out of memory\n");
	      return NULL;
	    }
	}
    }
  return array;
}

int**** mkiarray4D(unsigned long nt, unsigned long nx, unsigned long ny, unsigned long nz)
/* Function: mkiarray4D
 * --------------------
 * 
 * Allocates a int array with range [0,1,...,(nt-1)][0,1,...,(nx-1)][0,1,...,(ny-1)][0,1,...,(nz-1)].
 * 
 * nt = number of elements
 * nx = number of elements  
 * ny = number of elements 
 * nz = number of elements 
 *
 * returns: return the pointer to the array allocation 
 *          returns NULL on error (if it is out of memory)
 */
{
  int ****array;
  unsigned long t,i,j;

  array =(int ****)malloc(nt * sizeof(int ***));
  if(array == NULL)
    {
      printf("out of memory\n");
      return NULL;
    }
  for(t = 0; t < nt; t++)
    {
      array[t] = (int ***)malloc(nx * sizeof(int **));
      if(array[t] == NULL)
	{
	  printf("out of memory\n");
	  return NULL;
	}
      for(i = 0; i < nx; i++)
	{
	  array[t][i] = (int **)malloc(ny * sizeof(int *));
	  if(array[t][i] == NULL)
	    {
	      printf("out of memory\n");
	      return NULL;
	    }
	  for(j=0; j<ny; j++)
	    {
	      array[t][i][j] = (int *)malloc(nz * sizeof(int ));
	      if(array[t][i][j] == NULL)
		{
		  printf("out of memory\n");
		  return NULL;
		}
	    }
	}
    }
  return array;
}

void freeiarray1D(int* array)
/* Function: freeiarray1D
 * -----------------------
 * 
 * Frees a array allocated with mkiarray1D.
 * 
 */
{
  free(array);
}

void freeiarray2D(int** array, unsigned long nt)
/* Function: freeiarray2D
 * -----------------------
 * 
 * Frees a array allocated with mkiarray2D.
 * 
 */
{
  unsigned long t;

  for (t = 0; t < nt; ++t) 
    free(array[t]);

  free(array);
}

void freeiarray3D(int*** array, unsigned long nt, unsigned long nx)
/* Function: freeiarray3D
 * -----------------------
 * 
 * Frees a array allocated with mkiarray3D.
 * 
 */
{
  unsigned long t,i;

  for (t = 0; t < nt; ++t) 
    {
      for(i=0; i<nx; i++)
	{
	  free(array[t][i]);
	}
      free(array[t]);
    }
    free(array);
}
void freeiarray4D(int**** array, unsigned long nt, unsigned long nx, unsigned long ny)
/* Function: freeiarray4D
 * -----------------------
 * 
 * Frees a array allocated with mkiarray4D.
 * 
 */
{
  unsigned long t,i,j;

  for (t = 0; t < nt; ++t) 
    {
      for(i=0; i<nx; i++)
	{
	  for(j=0; j<ny; j++)
	    free(array[t][i][j]);
	  free(array[t][i]);
	}
      free(array[t]);
    }
    free(array);
}

unsigned long* mkularray1D(unsigned long nt)
/* Function: mkstarray1D
 * --------------------
 * 
 * Allocates a unsigned long array with range [0,1,...,(nt-1)].
 * 
 * nt = number of elements
 *
 * returns: return the pounsigned longer to the array allocation 
 *          returns NULL on error (if it is out of memory)
 */
{
  unsigned long *array;
  
  array =(unsigned long *)malloc(nt*sizeof(unsigned long));
  if(array == NULL)
    {
      printf("out of memory\n");
      return NULL;
    }
  return array;
}

unsigned long** mkularray2D(unsigned long nt, unsigned long nx)
/* Function: mkstarray2D
 * --------------------
 * 
 * Allocates a unsigned long array with range [0,1,...,(nt-1)][0,1,...,(nx-1)].
 * 
 * nt = number of elements
 * nx = number of elements 
 *
 * returns: return the pounsigned longer to the array allocation 
 *          returns NULL on error (if it is out of memory)
 */
{
  unsigned long **array;
  unsigned long t;

  array =(unsigned long **)malloc(nt*sizeof(unsigned long *));
  if(array == NULL)
    {
      printf("out of memory\n");
      return NULL;
    }
  for(t = 0; t < nt; t++)
    {
      array[t] = (unsigned long *)malloc(nx*sizeof(unsigned long));
      if(array[t] == NULL)
	{
	  printf("out of memory\n");
	  return NULL;
	}
    }
  return array;
}

unsigned long*** mkularray3D(unsigned long nt, unsigned long nx, unsigned long ny)
/* Function: mkstarray3D
 * --------------------
 * 
 * Allocates a unsigned long array with range [0,1,...,(nt-1)][0,1,...,(nx-1)][0,1,...,(ny-1)].
 * 
 * nt = number of elements
 * nx = number of elements  
 * ny = number of elements 
 *
 * returns: return the pounsigned longer to the array allocation 
 *          returns NULL on error (if it is out of memory)
 */
{
  unsigned long ***array;
  unsigned long t,i;

  array =(unsigned long ***)malloc(nt*sizeof(unsigned long **));
  if(array == NULL)
    {
      printf("out of memory\n");
      return NULL;
    }
  for(t = 0; t < nt; t++)
    {
      array[t] = (unsigned long **)malloc(nx*sizeof(unsigned long*));
      if(array[t] == NULL)
	{
	  printf("out of memory\n");
	  return NULL;
	}
      for(i = 0; i < nx; i++)
	{
	  array[t][i] = (unsigned long *)malloc(ny*sizeof(unsigned long));
	  if(array[t][i] == NULL)
	    {
	      printf("out of memory\n");
	      return NULL;
	    }
	}
    }
  return array;
}

unsigned long**** mkularray4D(unsigned long nt, unsigned long nx, unsigned long ny, unsigned long nz)
/* Function: mkstarray4D
 * --------------------
 * 
 * Allocates a unsigned long array with range [0,1,...,(nt-1)][0,1,...,(nx-1)][0,1,...,(ny-1)][0,1,...,(nz-1)].
 * 
 * nt = number of elements
 * nx = number of elements  
 * ny = number of elements 
 * nz = number of elements 
 *
 * returns: return the pounsigned longer to the array allocation 
 *          returns NULL on error (if it is out of memory)
 */
{
  unsigned long ****array;
  unsigned long t,i,j;

  array =(unsigned long ****)malloc(nt * sizeof(unsigned long ***));
  if(array == NULL)
    {
      printf("out of memory\n");
      return NULL;
    }
  for(t = 0; t < nt; t++)
    {
      array[t] = (unsigned long ***)malloc(nx * sizeof(unsigned long **));
      if(array[t] == NULL)
	{
	  printf("out of memory\n");
	  return NULL;
	}
      for(i = 0; i < nx; i++)
	{
	  array[t][i] = (unsigned long **)malloc(ny * sizeof(unsigned long *));
	  if(array[t][i] == NULL)
	    {
	      printf("out of memory\n");
	      return NULL;
	    }
	  for(j=0; j<ny; j++)
	    {
	      array[t][i][j] = (unsigned long *)malloc(nz * sizeof(unsigned long ));
	      if(array[t][i][j] == NULL)
		{
		  printf("out of memory\n");
		  return NULL;
		}
	    }
	}
    }
  return array;
}

void freeularray1D(unsigned long* array)
/* Function: freestarray1D
 * -----------------------
 * 
 * Frees a array allocated with mkstarray1D.
 * 
 */
{
  free(array);
}

void freeularray2D(unsigned long** array, unsigned long nt)
/* Function: freestarray2D
 * -----------------------
 * 
 * Frees a array allocated with mkstarray2D.
 * 
 */
{
  unsigned long t;

  for (t = 0; t < nt; ++t) 
    free(array[t]);

  free(array);
}

void freeularray3D(unsigned long*** array, unsigned long nt, unsigned long nx)
/* Function: freestarray3D
 * -----------------------
 * 
 * Frees a array allocated with mkstarray3D.
 * 
 */
{
  unsigned long t,i;

  for (t = 0; t < nt; ++t) 
    {
      for(i=0; i<nx; i++)
	{
	  free(array[t][i]);
	}
      free(array[t]);
    }
    free(array);
}
void freeularray4D(unsigned long**** array, unsigned long nt, unsigned long nx, unsigned long ny)
/* Function: freestarray4D
 * -----------------------
 * 
 * Frees a array allocated with mkstarray4D.
 * 
 */
{
  unsigned long t,i,j;

  for (t = 0; t < nt; ++t) 
    {
      for(i=0; i<nx; i++)
	{
	  for(j=0; j<ny; j++)
	    free(array[t][i][j]);
	  free(array[t][i]);
	}
      free(array[t]);
    }
    free(array);
}

vector* mkvarray1D(unsigned long nt)
/* Function: mkiarray1D
 * --------------------
 * 
 * Allocates a vector array with range [0,1,...,(nt-1)].
 * 
 * nt = number of elements
 *
 * returns: return the povectorer to the array allocation 
 *          returns NULL on error (if it is out of memory)
 */
{
  vector *array;
  
  array =(vector *)malloc(nt*sizeof(vector));
  if(array == NULL)
    {
      printf("out of memory\n");
      return NULL;
    }
  return array;
}

vector** mkvarray2D(unsigned long nt, unsigned long nx)
/* Function: mkiarray2D
 * --------------------
 * 
 * Allocates a vector array with range [0,1,...,(nt-1)][0,1,...,(nx-1)].
 * 
 * nt = number of elements
 * nx = number of elements 
 *
 * returns: return the povectorer to the array allocation 
 *          returns NULL on error (if it is out of memory)
 */
{
  vector **array;
  unsigned long t;

  array =(vector **)malloc(nt*sizeof(vector *));
  if(array == NULL)
    {
      printf("out of memory\n");
      return NULL;
    }
  for(t = 0; t < nt; t++)
    {
      array[t] = (vector *)malloc(nx*sizeof(vector ));
      if(array[t] == NULL)
	{
	  printf("out of memory\n");
	  return NULL;
	}
    }
  return array;
}

vector*** mkvarray3D(unsigned long nt, unsigned long nx, unsigned long ny)
/* Function: mkvarray3D
 * --------------------
 * 
 * Allocates a vector array with range [0,1,...,(nt-1)][0,1,...,(nx-1)][0,1,...,(ny-1)].
 * 
 * nt = number of elements
 * nx = number of elements  
 * ny = number of elements 
 *
 * returns: return the povectorer to the array allocation 
 *          returns NULL on error (if it is out of memory)
 */
{
  vector ***array;
  unsigned long t,i;

  array =(vector ***)malloc(nt*sizeof(vector **));
  if(array == NULL)
    {
      printf("out of memory\n");
      return NULL;
    }
  for(t = 0; t < nt; t++)
    {
      array[t] = (vector **)malloc(nx*sizeof(vector*));
      if(array[t] == NULL)
	{
	  printf("out of memory\n");
	  return NULL;
	}
      for(i = 0; i < nx; i++)
	{
	  array[t][i] = (vector *)malloc(ny*sizeof(vector));
	  if(array[t][i] == NULL)
	    {
	      printf("out of memory\n");
	      return NULL;
	    }
	}
    }
  return array;
}

vector**** mkvarray4D(unsigned long nt, unsigned long nx, unsigned long ny, unsigned long nz)
/* Function: mkvarray4D
 * --------------------
 * 
 * Allocates a vector array with range [0,1,...,(nt-1)][0,1,...,(nx-1)][0,1,...,(ny-1)][0,1,...,(nz-1)].
 * 
 * nt = number of elements
 * nx = number of elements  
 * ny = number of elements 
 * nz = number of elements 
 *
 * returns: return the povectorer to the array allocation 
 *          returns NULL on error (if it is out of memory)
 */
{
  vector ****array;
  unsigned long t,i,j;

  array =(vector ****)malloc(nt * sizeof(vector ***));
  if(array == NULL)
    {
      printf("out of memory\n");
      return NULL;
    }
  for(t = 0; t < nt; t++)
    {
      array[t] = (vector ***)malloc(nx * sizeof(vector **));
      if(array[t] == NULL)
	{
	  printf("out of memory\n");
	  return NULL;
	}
      for(i = 0; i < nx; i++)
	{
	  array[t][i] = (vector **)malloc(ny * sizeof(vector *));
	  if(array[t][i] == NULL)
	    {
	      printf("out of memory\n");
	      return NULL;
	    }
	  for(j=0; j<ny; j++)
	    {
	      array[t][i][j] = (vector *)malloc(nz * sizeof(vector ));
	      if(array[t][i][j] == NULL)
		{
		  printf("out of memory\n");
		  return NULL;
		}
	    }
	}
    }
  return array;
}

void freevarray1D(vector* array)
/* Function: freevarray1D
 * -----------------------
 * 
 * Frees a array allocated with mkvarray1D.
 * 
 */
{
  free(array);
}

void freevarray2D(vector** array, unsigned long nt)
/* Function: freevarray2D
 * -----------------------
 * 
 * Frees a array allocated with mkvarray2D.
 * 
 */
{
  unsigned long t;

  for (t = 0; t < nt; ++t) 
    free(array[t]);

  free(array);
}

void freevarray3D(vector*** array, unsigned long nt, unsigned long nx)
/* Function: freevarray3D
 * -----------------------
 * 
 * Frees a array allocated with mkvarray3D.
 * 
 */
{
  unsigned long t,i;

  for (t = 0; t < nt; ++t) 
    {
      for(i=0; i<nx; i++)
	{
	  free(array[t][i]);
	}
      free(array[t]);
    }
    free(array);
}
void freevarray4D(vector**** array, unsigned long nt, unsigned long nx, unsigned long ny)
/* Function: freevarray4D
 * -----------------------
 * 
 * Frees a array allocated with mkvarray4D.
 * 
 */
{
  unsigned long t,i,j;

  for (t = 0; t < nt; ++t) 
    {
      for(i=0; i<nx; i++)
	{
	  for(j=0; j<ny; j++)
	    free(array[t][i][j]);
	  free(array[t][i]);
	}
      free(array[t]);
    }
    free(array);
}
