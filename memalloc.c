#include <stdio.h>
#include <stdlib.h>

#include "memalloc.h"

double* mkdarray1D(size_t nt)
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

double** mkdarray2D(size_t nt, size_t nx)
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
  size_t t;

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

double*** mkdarray3D(size_t nt, size_t nx, size_t ny)
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
  size_t t,i;

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

double**** mkdarray4D(size_t nt, size_t nx, size_t ny, size_t nz)
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
  size_t t,i,j;

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

void freedarray2D(double** array, size_t nt)
/* Function: freedarray2D
 * -----------------------
 * 
 * Frees a array allocated with mkdarray2D.
 * 
 */
{
  size_t t;

  for (t = 0; t < nt; ++t) 
    free(array[t]);

  free(array);
}

void freedarray3D(double*** array, size_t nt, size_t nx)
/* Function: freedarray3D
 * -----------------------
 * 
 * Frees a array allocated with mkdarray3D.
 * 
 */
{
  size_t t,i;

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
void freedarray4D(double**** array, size_t nt, size_t nx, size_t ny)
/* Function: freedarray4D
 * -----------------------
 * 
 * Frees a array allocated with mkdarray4D.
 * 
 */
{
  size_t t,i,j;

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

int* mkiarray1D(size_t nt)
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

int** mkiarray2D(size_t nt, size_t nx)
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
  size_t t;

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

int*** mkiarray3D(size_t nt, size_t nx, size_t ny)
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
  size_t t,i;

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

int**** mkiarray4D(size_t nt, size_t nx, size_t ny, size_t nz)
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
  size_t t,i,j;

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

void freeiarray2D(int** array, size_t nt)
/* Function: freeiarray2D
 * -----------------------
 * 
 * Frees a array allocated with mkiarray2D.
 * 
 */
{
  size_t t;

  for (t = 0; t < nt; ++t) 
    free(array[t]);

  free(array);
}

void freeiarray3D(int*** array, size_t nt, size_t nx)
/* Function: freeiarray3D
 * -----------------------
 * 
 * Frees a array allocated with mkiarray3D.
 * 
 */
{
  size_t t,i;

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
void freeiarray4D(int**** array, size_t nt, size_t nx, size_t ny)
/* Function: freeiarray4D
 * -----------------------
 * 
 * Frees a array allocated with mkiarray4D.
 * 
 */
{
  size_t t,i,j;

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

size_t* mkstarray1D(size_t nt)
/* Function: mkstarray1D
 * --------------------
 * 
 * Allocates a size_t array with range [0,1,...,(nt-1)].
 * 
 * nt = number of elements
 *
 * returns: return the posize_ter to the array allocation 
 *          returns NULL on error (if it is out of memory)
 */
{
  size_t *array;
  
  array =(size_t *)malloc(nt*sizeof(size_t));
  if(array == NULL)
    {
      printf("out of memory\n");
      return NULL;
    }
  return array;
}

size_t** mkstarray2D(size_t nt, size_t nx)
/* Function: mkstarray2D
 * --------------------
 * 
 * Allocates a size_t array with range [0,1,...,(nt-1)][0,1,...,(nx-1)].
 * 
 * nt = number of elements
 * nx = number of elements 
 *
 * returns: return the posize_ter to the array allocation 
 *          returns NULL on error (if it is out of memory)
 */
{
  size_t **array;
  size_t t;

  array =(size_t **)malloc(nt*sizeof(size_t *));
  if(array == NULL)
    {
      printf("out of memory\n");
      return NULL;
    }
  for(t = 0; t < nt; t++)
    {
      array[t] = (size_t *)malloc(nx*sizeof(size_t));
      if(array[t] == NULL)
	{
	  printf("out of memory\n");
	  return NULL;
	}
    }
  return array;
}

size_t*** mkstarray3D(size_t nt, size_t nx, size_t ny)
/* Function: mkstarray3D
 * --------------------
 * 
 * Allocates a size_t array with range [0,1,...,(nt-1)][0,1,...,(nx-1)][0,1,...,(ny-1)].
 * 
 * nt = number of elements
 * nx = number of elements  
 * ny = number of elements 
 *
 * returns: return the posize_ter to the array allocation 
 *          returns NULL on error (if it is out of memory)
 */
{
  size_t ***array;
  size_t t,i;

  array =(size_t ***)malloc(nt*sizeof(size_t **));
  if(array == NULL)
    {
      printf("out of memory\n");
      return NULL;
    }
  for(t = 0; t < nt; t++)
    {
      array[t] = (size_t **)malloc(nx*sizeof(size_t*));
      if(array[t] == NULL)
	{
	  printf("out of memory\n");
	  return NULL;
	}
      for(i = 0; i < nx; i++)
	{
	  array[t][i] = (size_t *)malloc(ny*sizeof(size_t));
	  if(array[t][i] == NULL)
	    {
	      printf("out of memory\n");
	      return NULL;
	    }
	}
    }
  return array;
}

size_t**** mkstarray4D(size_t nt, size_t nx, size_t ny, size_t nz)
/* Function: mkstarray4D
 * --------------------
 * 
 * Allocates a size_t array with range [0,1,...,(nt-1)][0,1,...,(nx-1)][0,1,...,(ny-1)][0,1,...,(nz-1)].
 * 
 * nt = number of elements
 * nx = number of elements  
 * ny = number of elements 
 * nz = number of elements 
 *
 * returns: return the posize_ter to the array allocation 
 *          returns NULL on error (if it is out of memory)
 */
{
  size_t ****array;
  size_t t,i,j;

  array =(size_t ****)malloc(nt * sizeof(size_t ***));
  if(array == NULL)
    {
      printf("out of memory\n");
      return NULL;
    }
  for(t = 0; t < nt; t++)
    {
      array[t] = (size_t ***)malloc(nx * sizeof(size_t **));
      if(array[t] == NULL)
	{
	  printf("out of memory\n");
	  return NULL;
	}
      for(i = 0; i < nx; i++)
	{
	  array[t][i] = (size_t **)malloc(ny * sizeof(size_t *));
	  if(array[t][i] == NULL)
	    {
	      printf("out of memory\n");
	      return NULL;
	    }
	  for(j=0; j<ny; j++)
	    {
	      array[t][i][j] = (size_t *)malloc(nz * sizeof(size_t ));
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

void freestarray1D(size_t* array)
/* Function: freestarray1D
 * -----------------------
 * 
 * Frees a array allocated with mkstarray1D.
 * 
 */
{
  free(array);
}

void freestarray2D(size_t** array, size_t nt)
/* Function: freestarray2D
 * -----------------------
 * 
 * Frees a array allocated with mkstarray2D.
 * 
 */
{
  size_t t;

  for (t = 0; t < nt; ++t) 
    free(array[t]);

  free(array);
}

void freestarray3D(size_t*** array, size_t nt, size_t nx)
/* Function: freestarray3D
 * -----------------------
 * 
 * Frees a array allocated with mkstarray3D.
 * 
 */
{
  size_t t,i;

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
void freesize_t_array4D(size_t**** array, size_t nt, size_t nx, size_t ny)
/* Function: freestarray4D
 * -----------------------
 * 
 * Frees a array allocated with mkstarray4D.
 * 
 */
{
  size_t t,i,j;

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

vector* mkvarray1D(size_t nt)
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

vector** mkvarray2D(size_t nt, size_t nx)
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
  size_t t;

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

vector*** mkvarray3D(size_t nt, size_t nx, size_t ny)
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
  size_t t,i;

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

vector**** mkvarray4D(size_t nt, size_t nx, size_t ny, size_t nz)
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
  size_t t,i,j;

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

void freevarray2D(vector** array, size_t nt)
/* Function: freevarray2D
 * -----------------------
 * 
 * Frees a array allocated with mkvarray2D.
 * 
 */
{
  size_t t;

  for (t = 0; t < nt; ++t) 
    free(array[t]);

  free(array);
}

void freevarray3D(vector*** array, size_t nt, size_t nx)
/* Function: freevarray3D
 * -----------------------
 * 
 * Frees a array allocated with mkvarray3D.
 * 
 */
{
  size_t t,i;

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
void freevarray4D(vector**** array, size_t nt, size_t nx, size_t ny)
/* Function: freevarray4D
 * -----------------------
 * 
 * Frees a array allocated with mkvarray4D.
 * 
 */
{
  size_t t,i,j;

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
