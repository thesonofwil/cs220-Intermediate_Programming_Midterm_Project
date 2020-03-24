// Wilson Tjoeng
// wtjoeng1

// Program to call functions on an image. Return 0 if no errors.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm_io.c"
#include "ppm_io.h"

int main(int argc, char *argv[]) {
  FILE *input;
  char *filename;
  char *method;
  double parameter;

  // argv should contain the executable, the filename, the manipulation method, and the parameter value for algorithms that need it
  
  if (argc < 2) { // Executable + file = 2
    fprintf(stderr, "Error: please input a filename to be read. \n");
    exit(1);
  } else {
    filename = argv[1]; // argv[0] = executable, argv[1] = file, argv[2] = method
    method = argv[2];
  }

  // Open file in reading and binary mode
  input = fopen(filename, "rb");
  if (!input) {
    fprintf(stderr, "Error: file could not be opened. \n");
    exit(2);
  }


  if (strcmp(method, "exposure") == 0) {
  }

  else if (strcmp(method, "a-blend") == 0 || strcmp(method, "blend") == 0) {
  }

  else if (strcmp(method, "zoom_in") == 0) {
  }

  else if (strcmp(method, "zoom_out") == 0) {
  }

  else if (strcmp(method, "pointilism") == 0) {
  }

  else if (strcmp(method, "swirl") == 0) {
  }

  else if (strcmp(method, "blur") == 0) {
  }

  else {
    fprintf(stderr, "Error: no operation name was specified, or operation name was invalid. \n");
    exit(4);
  }
  return 0; // no errors
}
