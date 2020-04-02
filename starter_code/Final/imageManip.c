// Wilson Tjoeng, Anire Egbe, Marcelo Morales
// wtjoeng1, aegbe2, lmoral10

// Program that calls on image manipulation method as specified in project.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageManip.h"
#include "change_exposure.h"
#include "alpha_blending.h"
#include "zoom_in.h"
#include "zoom_out.h"
#include "pointilism.h"
#include "swirl.h"
#include "blur.h"


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
    exit(6);
  }

  return parameter;
}

// Call image manipulation methods
void call_method(char *method, int argc, char *argv[], Image *img, FILE *output) {
  // Change Exposure - void
  if (strcmp(method, "exposure") == 0) {
    check_argc(argc, 5);
    float ev = convert_parameter(argv[4]);
    change_exposure(img, ev);
    write_ppm(output, img);
  }  

  // Alpha-blend
  else if (strcmp(method, "blend") == 0) {
  check_argc(argc,6);
  float alpha = convert_parameter(argv[5]);
  FILE *secondInput = fopen(argv[4], "rb");
  if (!secondInput) {
    fprintf(stderr, "Error: second input file could not be opened. \n");
    exit(2);
  }
  Image *img2 = read_ppm(secondInput);
  Image *result = alpha_blending(img, img2, alpha);
  write_ppm(output,result);
  fclose(secondInput);
  free(result->data);
  free(result);
  free(img2->data);
  free(img2);
  }

  // Zoom in - returns an image
  else if (strcmp(method, "zoom_in") == 0) {
   check_argc(argc, 4);
   Image *result = zoom_in(img);
   write_ppm(output, result);
   free(result->data);
   free(result);
  }

  // Zoom out - returns an image
  else if (strcmp(method, "zoom_out") == 0) {
   check_argc(argc, 4);
   Image *result = zoom_out(img);
   write_ppm(output, result);
   free(result->data);
   free(result);
  }

  // Pointilism
  //pointilism is void 
  else if (strcmp(method, "pointilism") == 0) {
    check_argc(argc, 4);
    pointilism(img);
    write_ppm(output, img);
  }

  // Swirl
  else if (strcmp(method, "swirl") == 0) {
    check_argc(argc, 7);
    int scale = (int)convert_parameter(argv[6]);
    int center_x = (int)convert_parameter(argv[4]);  //truncating float to int
    int center_y = (int)convert_parameter(argv[5]);  //truncating float to int

    //center_x and center_y cannot be ouside of image, center x and center y cannot be negative but can be zero
    if (center_x >  img->rows || center_y > img->cols) {
      fprintf(stderr, "Error: center of image has to be inside the image \n");
      exit(6);
    }
    if ( center_x < 0 || center_y < 0 ) {
      fprintf(stderr, "Error: x coordinate or the y coordinate of the center of swirl cannot be negative \n");
      exit(6);
    }

    //distortion scale should be a positive integer
    if ((int)scale <= 0) { 
      fprintf(stderr, "Error: distortion strenght cannot be negative  \n");
      exit(6);
    }

    swirl(img, center_x, center_y, scale);
    write_ppm(output, img);
  
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

  // Operation not found
  else {
    fprintf(stderr, "Error: operation name was invalid. \n");
    exit(4);
  }
}
