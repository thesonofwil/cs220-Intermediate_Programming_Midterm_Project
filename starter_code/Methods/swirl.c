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

/*
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
*/



double calc_alpha (int center_x, int center_y, int scale, int x, int y) {
  double alpha = sqrt(pow(x - center_x, 2) + (pow(y - center_y, 2)))/ scale;
  return alpha;
}	

int conversion_for_x_pixel (int x_coord_pixel, int y_coord_pixel, int center_x, int center_y, double alpha) {
  return (x_coord_pixel - center_x) cos(alpha) - (y_coord_pixel - center_y) sin (alpha) + center_x;
}

int conversion_for_y_pixel (int x_coord_pixel, int y_coord_pixel, int center_x, int center_y, double alpha) {
  return (x_coord_pixel - center_x) sin(alpha) + (y_coord_pixel - center_y) cos (alpha) + center_y;
}




Image * swirl (Image * img_input, int center_x, int center_y, int scale) {
  Image *img_output = (Image *)malloc(sizeof(Image));
  int cols = img_input -> cols;
  int rows = img_input -> rows;
  img_output -> cols = cols;
  img_output -> rows = rows;
  img_output -> data = (Pixel *) malloc (rows * cols * sizeof(Pixel));

  //initialize output image to all zeros for black image
  for (int i = 0; i <= img->rows * img-> cols; i++) {
    img->data[i].r = 0;
    img->data[i].g = 0;
    img->data[i].b = 0;
  }

  int x_coord_pixel = 0;
  int y_coord_pixel = 0;

  for (int y_coord_pixel = 0; y_coord_pixel < img_output -> rows; ++y_coord_pixel) {
    for (int x_coord_pixel = 0; x_coord_pixel < img_output -> cols; ++x_coord_pixel) {

      double alpha = calc_alpha (center_x, center_y, scale, x_coord_pixel, y_coord_pixel);
      int new_x_coord = conversion_for_x_pixel (x_coord_pixel, y_coord_pixel, center_x, center_y, alpha);
      int new_y_coord = conversion_for_y_pixel (x_coord_pixel, y_coord_pixel, center_x, center_y, alpha);

      //change location of pixel
      //swap old pixel with new pixel, change location of pixel

      



    }
  }

  





  return output;
}


