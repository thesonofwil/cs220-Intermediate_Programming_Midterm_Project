//Marcelo Morales
//lmoral10


#include <stdlib.h>
#include <stdio.h>
#include "ppm_io.h"
#include <math.h>
#include "ppm_io.c"

/*
swirl does not change the colors any pixels in the image
only change the location of some or all pixels in the image
swirl is an image warping operation that creates a whirpool effect by performing a non-linear deformation 
on the image
two inputs provided by user
a center and a distortion scale
the center specifies the x and y coordinates of the rotation center and scale
a higher scale value results in a lesser amount of swirl effect


*/

//swirl alpha value uses double, not float
//swirl changes location of some or all of the pixels in the image
//swirl creates a whirpool effect by performing a non-linear deformation on the image.
//two inputs should be provided by the user, a center and a distortion scale
//a higher scale value results in a lesser amount of swirl effect

//output pixels corresponding to out of bounds source pixels should just be rendered as black

//arg[4] for blur function requires an int
//will need to convert the string (which should be a sequence of digit characters) into an integer value

//blur should be a floating point value


  //having trouble wich pixels to pick, how do i convey this through code
  int xCenter;

//distorition swirl is a double
  //swirl alpha values should uses double
//int x is the arbitrary x coordinate of a pixel
//int y is the arbirary y coordinate of a pixel

//swirl strengthshould be positive, if negative, report error based on table (should be 6) and exit

//pixel data should be initizliaed to all zeroes

//will need to create a new image to hold the result, the swirl transformation cannot be done in place


double calc_alpha (int center_x, int center_y, int scale, int x, int y) {

  double alpha = sqrt(pow(x - center_x, 2) + (pow(y - center_y, 2)))/ scale;
  return alpha;

}	



int main (void) {
	
  printf("If got here, swirl compiling successfully\n");	
   return 0;
}

//note that output pixels corresponding to out-of-bound pixels should just be rendered as black //

int n;
if (sscanf(argv[4], "%f", &n) != 1) {
  fprintf(stderr, "Incorrect argument given, requires an int as corresponding argument");
  //return 5
  // argv[4] didn't contain valid representation of integer value, report error
}
Image *blurred_image = blur(original, n);
