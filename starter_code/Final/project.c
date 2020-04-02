// Wilson Tjoeng
// wtjoeng1

// Driver program to call functions on an image. Return 0 if no errors.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageManip.h"

int main(int argc, char *argv[]) {
  char *inputFile;
  char *outputFile;
  char *method;
    
  // argv should contain the executable, the filename, the desired output file, the manipulation method, and the parameter value for algorithms that need it
  
  if (argc < 3) { // Executable + input file + output file
    fprintf(stderr, "Error: please specify an input and an output file. \n");
    exit(1);
  } else {
    inputFile = argv[1]; // argv[0] = executable, argv[1] = input, argv[2] = output, argv[3] = method
    outputFile = argv[2];
  }

  // Open input and output files in reading and binary mode
  FILE *input = fopen(inputFile, "rb");
  if (!input) {
    fprintf(stderr, "Error: file could not be opened. \n");
    exit(2);
  }
  FILE *output = fopen(outputFile, "wb");
  if (!output) {
    fprintf(stderr, "Error: output file could not be opened for writing, or writing output failed. \n");
    exit(7);
  }

  // Read input as image
  Image *img = read_ppm(input); // Error 3 is in ppm_io.c

  // Check if operation was given
  if (argc == 3) {
    fprintf(stderr, "Error: no operation name was specified. \n");
    exit(4);
  }
  method = argv[3];
  
  // Call Methods
  call_method(method, argc, argv, img, output);

  fclose(input);
  fclose(output);

  free(img->data);
  free(img);
    
  return 0; // No errors
}
