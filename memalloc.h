#ifndef MEMALLOC
#define MEMALLOC

#include "coordinates.h"

/* Functions for allocate a double arrays*/ 
double* mkdarray1D(unsigned long nt);
double** mkdarray2D(unsigned long nt, unsigned long nx);
double*** mkdarray3D(unsigned long nt, unsigned long nx, unsigned long ny);
double**** mkdarray4D(unsigned long nt, unsigned long nx, unsigned long ny, unsigned long nz);

void freedarray1D(double* array);
void freedarray2D(double** array, unsigned long nt);
void freedarray3D(double*** array, unsigned long nt, unsigned long nx);
void freedarray4D(double**** array, unsigned long nt, unsigned long nx, unsigned long ny);

/* Functions for allocate a int arrays*/ 
int* mkiarray1D(unsigned long nt);
int** mkiarray2D(unsigned long nt, unsigned long nx);
int*** mkiarray3D(unsigned long nt, unsigned long nx, unsigned long ny);
int**** mkiarray4D(unsigned long nt, unsigned long nx, unsigned long ny, unsigned long nz);

void freeiarray1D(int* array);
void freeiarray2D(int** array, unsigned long nt);
void freeiarray3D(int*** array, unsigned long nt, unsigned long nx);
void freeiarray4D(int**** array, unsigned long nt, unsigned long nx, unsigned long ny);

/* Functions for allocate a unsigned long arrays*/ 
unsigned long* mkularray1D(unsigned long nt);
unsigned long** mkularray2D(unsigned long nt, unsigned long nx);
unsigned long*** mkularray3D(unsigned long nt, unsigned long nx, unsigned long ny);
unsigned long**** mkularray4D(unsigned long nt, unsigned long nx, unsigned long ny, unsigned long nz);

void freeularray1D(unsigned long* array);
void freeularray2D(unsigned long** array, unsigned long nt);
void freeularray3D(unsigned long*** array, unsigned long nt, unsigned long nx);
void freeularray4D(unsigned long**** array, unsigned long nt, unsigned long nx, unsigned long ny);

/* Functions for allocate a vector arrays*/ 
vector* mkvarray1D(unsigned long nt);
vector** mkvarray2D(unsigned long nt, unsigned long nx);
vector*** mkvarray3D(unsigned long nt, unsigned long nx, unsigned long ny);
vector**** mkvarray4D(unsigned long nt, unsigned long nx, unsigned long ny, unsigned long nz);

void freevarray1D(vector* array);
void freevarray2D(vector** array, unsigned long nt);
void freevarray3D(vector*** array, unsigned long nt, unsigned long nx);
void freevarray4D(vector**** array, unsigned long nt, unsigned long nx, unsigned long ny);
#endif
