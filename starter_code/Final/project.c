// Wilson Tjoeng
// wtjoeng1

// Program to call functions on an image. Return 0 if no errors.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm_io.c"
#include "ppm_io.h"
#include "change_exposure.h"

// Check if the number of arguments meet what is required for the manipulation
void check_argc(int argc, int req) {
  if (argc != req) {
    fprintf(stderr, "Error: incorrect number of arguments. \n");
    exit(5);
  }
}

// Check if the given argv is a number and convert it to a float
float convert_parameter(char *arg) {
  char *check;

  float parameter = strtof(arg, &check);
  if (strlen(check) > 0) { // i.e. argument contains non-numeric symbols
    fprintf(stderr, "Error: specified argument must be a number. \n");
    exit(5);
  }

  return parameter;
}


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
    method = argv[3];
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

  Image *img = read_ppm(input);
  //Image *result; // Some manipulations will return void
  
  // Call Methods
  // Change Exposure
  if (strcmp(method, "exposure") == 0) {
    check_argc(argc, 5);
    float ev = convert_parameter(argv[4]);
    change_exposure(img, ev);
    write_ppm(output, img);
  }  

  // Alpha-blend
  //  else if (strcmp(method, "a-blend") == 0 || strcmp(method, "blend") == 0) {
  // }

  // Zoom in
  //else if (strcmp(method, "zoom_in") == 0) {
  //  check_argc(argc, 4);
  //  result = zoom_in(img);
  //  write_ppm(output, result);
  //}

  // Zoom out
  //else if (strcmp(method, "zoom_out") == 0) {
  //}

  // Pointilism
  //else if (strcmp(method, "pointilism") == 0) {
  //}

  // Swirl
  //else if (strcmp(method, "swirl") == 0) {
  //}

  // Blur
  //else if (strcmp(method, "blur") == 0) {
  //  check_argc(argc, 5);
  //  float sigma = convert_parameter(argv[3]);
  //  blur(input, output, sigma); // ppm written in blur.c
  //}

  else {
    fprintf(stderr, "Error: no operation name was specified, or operation name was invalid. \n");
    exit(4);
  }

  fclose(input);
  fclose(output);

  free(img->data);
  free(img);
  //free(result->data);
  //free(result);
  
  return 0; // No errors
}
