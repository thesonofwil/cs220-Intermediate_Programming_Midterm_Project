CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -g 
LDLIBS=-lm

# Create the project executable
# Add methods here
project: project.o change_exposure.o zoom_in.o blur.o pointilism.o  swirl.o zoom_out.o alpha_blending.o
	$(CC) $(LDLIBS) -o project project.o change_exposure.o zoom_in.o blur.o pointilism.o swirl.o zoom_out.o alpha_blending.o

#demo: demo_ppm.o ppm_io.o
#	$(CC) demo_ppm.o ppm_io.o -o demo

#demo_ppm.o: demo_ppm.c ppm_io.h
#	$(CC) $(CFLAGS) -c demo_ppm.c

ppm_io.o: ppm_io.c ppm_io.h
	$(CC) $(CFLAGS) -c ppm_io.c

# Compile methods into their respective object files
change_exposure.o: change_exposure.c change_exposure.h
	$(CC) $(CFLAGS) $(LDLIBS) -c change_exposure.c

alpha_blending.o: alpha_blending.c alpha_blending.h
        $(CC) $(CFLAGS) $(LDLIBS) -c alpha_blending.c

zoom_in.o: zoom_in.c zoom_in.h
	$(CC) $(CFLAGS) -c zoom_in.c

blur.o: blur.c blur.h
	$(CC) $(CFLAGS) $(LDLIBS) -c blur.c

zoom_out.o: zoom_out.c zoom_out.h
        $(CC) $(CFLAGS) $(LDLIBS) -c zoom_out.c

pointilism.o: pointilism.c pointilism.h
	$(CC) $(CFLAGS) $(LDLIBS) -c pointilism.c

swirl.o: swirl.c swirl.h
	$(CC) $(CFLAGS) $(LDLIBS) -c swirl.c 

clean:
	rm -f *.o project
