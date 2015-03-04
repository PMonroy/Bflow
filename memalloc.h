#ifndef MEMALLOC
#define MEMALLOC

#include "coordinates.h"

/* Functions for allocate a double arrays*/ 
double* mkdarray1D(size_t nt);
double** mkdarray2D(size_t nt, size_t nx);
double*** mkdarray3D(size_t nt, size_t nx, size_t ny);
double**** mkdarray4D(size_t nt, size_t nx, size_t ny, size_t nz);

void freedarray1D(double* array);
void freedarray2D(double** array, size_t nt);
void freedarray3D(double*** array, size_t nt, size_t nx);
void freedarray4D(double**** array, size_t nt, size_t nx, size_t ny);

/* Functions for allocate a int arrays*/ 
int* mkiarray1D(size_t nt);
int** mkiarray2D(size_t nt, size_t nx);
int*** mkiarray3D(size_t nt, size_t nx, size_t ny);
int**** mkiarray4D(size_t nt, size_t nx, size_t ny, size_t nz);

void freeiarray1D(int* array);
void freeiarray2D(int** array, size_t nt);
void freeiarray3D(int*** array, size_t nt, size_t nx);
void freeiarray4D(int**** array, size_t nt, size_t nx, size_t ny);

/* Functions for allocate a size_t arrays*/ 
size_t* mkstarray1D(size_t nt);
size_t** mkstarray2D(size_t nt, size_t nx);
size_t*** mkstarray3D(size_t nt, size_t nx, size_t ny);
size_t**** mkstarray4D(size_t nt, size_t nx, size_t ny, size_t nz);

void freestarray1D(size_t* array);
void freestarray2D(size_t** array, size_t nt);
void freestarray3D(size_t*** array, size_t nt, size_t nx);
void freestarray4D(size_t**** array, size_t nt, size_t nx, size_t ny);

/* Functions for allocate a vector arrays*/ 
vector* mkvarray1D(size_t nt);
vector** mkvarray2D(size_t nt, size_t nx);
vector*** mkvarray3D(size_t nt, size_t nx, size_t ny);
vector**** mkvarray4D(size_t nt, size_t nx, size_t ny, size_t nz);

void freevarray1D(vector* array);
void freevarray2D(vector** array, size_t nt);
void freevarray3D(vector*** array, size_t nt, size_t nx);
void freevarray4D(vector**** array, size_t nt, size_t nx, size_t ny);
#endif
