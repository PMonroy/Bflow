CC=gcc
CFLAGS=-O2 -Wall -mcmodel=medium
LIBS = -lm -L/usr/local/netcdf/lib -lnetcdf
RM=rm -rf
OUT=test.out
PARAMS=parameters.in

all: build

build: pttraj.o memalloc.o velocity.o parameters.o $(PARAMS)
	$(CC) $(CFLAGS) -o $(OUT) pttraj.o memalloc.o velocity.o parameters.o $(LIBS)
	$(RM) *.o

debug: CFLAGS+=-DDEBUG_ON
debug: build

pttraj.o: pttraj.c velocity.h 
	$(CC) $(CFLAGS) -c pttraj.c

velocity.o: velocity.c  velocity.h date.h coordinates.h memalloc.h 
	$(CC) $(CFLAGS) -c velocity.c

parameters.o: parameters.c parameters.h date.h
	$(CC) $(CFLAGS) -c parameters.c

memalloc.o: memalloc.c memalloc.h
	$(CC) $(CFLAGS) -c memalloc.c

$(PARAMS): template_parameters.in
	touch $(PARAMS)
	cat template_parameters.in > $(PARAMS)
clean:
	$(RM) *.o $(OUT)
