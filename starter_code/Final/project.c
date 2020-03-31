// Wilson Tjoeng
// wtjoeng1

// Program to call functions on an image. Return 0 if no errors.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm_io.c"
#include "ppm_io.h"
#include "change_exposure.h"
#include "zoom_in.h"
#include "blur.h"
#include "pointilism.h"
#include "swirl.h"
//#include "swirl.c"

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
  if (strlen(check) > 0) { // i.e. argument contains non-numeric symbols, argument is a string
    fprintf(stderr, "Error: specified argument must be a number. \n");
    exit(5);
  }

  return parameter;
}


int main(int argc, char *argv[]) {
  //printf("hello\n");
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
    fprintf(stderr, "Error: No operation name was specified. \n");
    exit(4);
  }
  method = argv[3];
  
  // Call Methods
  // Change Exposure - void
  if (strcmp(method, "exposure") == 0) {
    check_argc(argc, 5);
    float ev = convert_parameter(argv[4]);
    change_exposure(img, ev);
    write_ppm(output, img);
  }  

  // Alpha-blend
  //  else if (strcmp(method, "a-blend") == 0 || strcmp(method, "blend") == 0) {
  // }

  // Zoom in - returns an image
  else if (strcmp(method, "zoom_in") == 0) {
   check_argc(argc, 4);
   Image *result = zoom_in(img);
   write_ppm(output, result);
   printf("CHECK \n \n");
   fprintf(stdout, "check\n");
   free(result->data);
   free(result);
  }

  // Zoom out
  //else if (strcmp(method, "zoom_out") == 0) {
  //}

  // Pointilism
  //pointilism is void 
  else if (strcmp(method, "pointilism") == 0) {
    check_argc(argc, 4);
    pointilism(img);
    write_ppm(output, img);
    fprintf(stdout, "check\n");

  }

  // Swirl
  else if (strcmp(method, "swirl") == 0) {
    check_argc(argc, 7);
    double scale = convert_parameter(argv[6]);
    int center_x = (int)convert_parameter(argv[4]);  //truncating float to int
    int center_y = (int)convert_parameter(argv[5]);  //truncating float to int

    //center_x and center_y cannot be ouside of image
    if (center_x >  img->rows || center_y > img->cols ) {
      fprintf(stderr, "Error: Center of image has to be inside the image \n");
      exit(6);
    }

    //distortion scale should be a positive integer
    if ((int)scale <= 0) { 
      fprintf(stderr, "Error: Center of image has to be inside the image \n");
      exit(6);
    }

    
    Image *result = swirl(img, center_x, center_y, scale);
    write_ppm(output, result);
    fprintf(stdout, "check\n");
    free(result->data);
    free(result);

  }

  // Blur
  else if (strcmp(method, "blur") == 0) {
    check_argc(argc, 5);
    float sigma = convert_parameter(argv[4]);
    Image *result = blur(img, sigma); 
    write_ppm(output, result);
    free(result->data);
    free(result);
  }

  else {
    printf("BAD\n");
    fprintf(stderr, "Error: operation name was invalid. hello \n");
    //exit(4);
  }

  fclose(input);
  fclose(output);

  free(img->data);
  free(img);
    
  return 0; // No errors
}
