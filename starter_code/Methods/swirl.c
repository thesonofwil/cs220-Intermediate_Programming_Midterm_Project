
#include <stdlib.h>
#include <stdio.h>
#include "ppm_io.h"
#include <math.h>
#include "ppm_io.c"

//swirl alpha value uses double, not float
//swirl changes location of some or all of the pixels in the image
//swirl creates a whirpool effect by performing a non-linear deformation on the image.
//two inputs should be provided by the user, a center and a distortion scale
//a higher scale value results in a lesser amount of swirl effect

void swirl (Image * img) {
  //having trouble wich pixels to pick, how do i convey this through code
  int xCenter;
  int yCenter;

}

//int x is the arbitrary x coordinate of a pixel
//int y is the arbirary y coordinate of a pixel
double calc_alpha (int center_x, int center_y, int scale, int x, int y) {

  double alpha = sqrt(pow(x - center_x, 2) + (pow(y - center_y, 2)))/ scale;
  return alpha;

}	



int main (void) {
	
  printf("If got here, swirl compiling successfully\n");	
   return 0;
}

//note that output pixels corresponding to out-of-bound pixels should just be rendered as black //

