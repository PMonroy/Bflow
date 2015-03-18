CC=gcc
CFLAGS=-O2 -Wall -mcmodel=medium
LIBS = -lm -L/usr/local/netcdf/lib -lnetcdf
RM=rm -rf

PARAMS=parameters.in

all: ptracer itracer clean

ptracer: ptracer.o memalloc.o velocity.o pparameters.o integration.o $(PARAMS) locate.o
	$(CC) $(CFLAGS) -o ptracer ptracer.o memalloc.o velocity.o pparameters.o integration.o locate.o $(LIBS)


itracer: itracer.o memalloc.o velocity.o iparameters.o integration.o $(PARAMS) locate.o
	$(CC) $(CFLAGS) -o itracer itracer.o memalloc.o velocity.o iparameters.o integration.o locate.o $(LIBS)


debug: CFLAGS+=-DDEBUG_ON
debug: build

ptracer.o: ptracer.c integration.h parameters.h coordinates.h
	$(CC) $(CFLAGS) -c ptracer.c

itracer.o: itracer.c integration.h parameters.h coordinates.h
	$(CC) $(CFLAGS) -c itracer.c

velocity.o: velocity.c velocity.h date.h coordinates.h memalloc.h locate.h 
	$(CC) $(CFLAGS) -c velocity.c

locate.o: locate.c locate.h 
	$(CC) $(CFLAGS) -c locate.c

pparameters.o: parameters.c parameters.h date.h
	$(CC) $(CFLAGS) -DPTRACER -c parameters.c -o pparameters.o

iparameters.o: parameters.c parameters.h date.h
	$(CC) $(CFLAGS) -DITRACER -c parameters.c -o iparameters.o

memalloc.o: memalloc.c memalloc.h
	$(CC) $(CFLAGS) -c memalloc.c

integration.o: integration.c integration.h velocity.h
	$(CC) $(CFLAGS) -c integration.c

$(PARAMS): parameters.template
	touch $(PARAMS)
	cat parameters.template > $(PARAMS)
clean:
	$(RM) *.o $(OUT)
