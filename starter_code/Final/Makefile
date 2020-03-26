CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -g
LDLIBS=-lm

# Create the project executable
# Add methods here
project: project.o change_exposure.o
	$(CC) $(LDLIBS) -o project project.o change_exposure.o

#demo: demo_ppm.o ppm_io.o
#	$(CC) demo_ppm.o ppm_io.o -o demo

#demo_ppm.o: demo_ppm.c ppm_io.h
#	$(CC) $(CFLAGS) -c demo_ppm.c

ppm_io.o: ppm_io.c ppm_io.h
	$(CC) $(CFLAGS) -c ppm_io.c

# Compile change_exposure.c into an object file
change_exposure.o: change_exposure.c change_exposure.h
	$(CC) $(CFLAGS) $(LDLIBS) -c change_exposure.c 

clean:
	rm -f *.o project
