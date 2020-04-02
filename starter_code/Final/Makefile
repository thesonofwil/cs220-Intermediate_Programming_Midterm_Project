CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -g 
LDLIBS=-lm

# Create the project executable
project: project.o ppm_io.o imageManip.o change_exposure.o zoom_in.o blur.o pointilism.o  swirl.o zoom_out.o alpha_blending.o
	$(CC) -o project project.o ppm_io.o imageManip.o change_exposure.o zoom_in.o blur.o pointilism.o swirl.o zoom_out.o alpha_blending.o $(LDLIBS)

project.o: project.c
	$(CC) $(CFLAGS) -c project.c

ppm_io.o: ppm_io.c ppm_io.h
	$(CC) $(CFLAGS) -c ppm_io.c

imageManip.o: imageManip.c imageManip.h
	$(CC) $(CFLAGS) -c imageManip.c

# Compile methods into their respective object files
change_exposure.o: change_exposure.c change_exposure.h
	$(CC) $(CFLAGS) -c change_exposure.c $(LDLIBS)

alpha_blending.o: alpha_blending.c alpha_blending.h
	$(CC) $(CFLAGS) -c alpha_blending.c

zoom_in.o: zoom_in.c zoom_in.h
	$(CC) $(CFLAGS) -c zoom_in.c

blur.o: blur.c blur.h
	$(CC) $(CFLAGS) -c blur.c $(LDLIBS)

zoom_out.o: zoom_out.c zoom_out.h
	$(CC) $(CFLAGS) -c zoom_out.c

pointilism.o: pointilism.c pointilism.h
	$(CC) $(CFLAGS) -c pointilism.c $(LDLIBS)

swirl.o: swirl.c swirl.h
	$(CC) $(CFLAGS) -c swirl.c $(LDLIBS)

clean:
	rm -f *.o project
