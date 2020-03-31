//Marcelo Morales
//lmoral10

#include <stdlib.h>
#include <stdio.h>
#include "ppm_io.h"
#include <math.h>
#include "swirl.h"


double calc_alpha (int center_x, int center_y, int scale, int x, int y) {
  double alpha = sqrt(pow(x - center_x, 2) + (pow(y - center_y, 2)))/ scale;
  return alpha;
}	

int conversion_for_x_pixel (int x_coord_pixel, int y_coord_pixel, int center_x, int center_y, double alpha) {
  
  return ((x_coord_pixel - center_x) * cos(alpha) - ((y_coord_pixel - center_y) * sin(alpha)) + center_x);
}

int conversion_for_y_pixel (int x_coord_pixel, int y_coord_pixel, int center_x, int center_y, double alpha) {
  return ( ((x_coord_pixel - center_x) * sin(alpha)) + ((y_coord_pixel - center_y) * cos(alpha)) + center_y);
}

Image * swirl (Image * img_input, int center_x, int center_y, int scale) {
  
  //new image has same size and pixels as old image
  Image *img_output = (Image *)malloc(sizeof(Image));
  int cols = img_input -> cols;
  int rows = img_input -> rows;
  img_output -> cols = cols;
  img_output -> rows = rows;
  img_output -> data = (Pixel *) malloc (rows * cols * sizeof(Pixel));


  //initialize output image to all zeros for black image
  //make image data all 0
  for (int r = 0; r < img_output -> rows; ++r) {
    for (int c  = 0; c < img_output -> cols; ++c) {
      img_output->data[(r * img_output ->cols) + c].r = 0;
      img_output->data[(r * img_output ->cols) + c].g = 0;
      img_output->data[(r * img_output ->cols) + c].b = 0;

    }
  }
  /*
  for (int i = 0; i <= img_output->rows * img_output-> cols; i++) {
    img_output->data[i].r = 0;
    img_output->data[i].g = 0;
    img_output->data[i].b = 0;
  }
  */

  int x_coord_pixel = 0;
  int y_coord_pixel = 0;

  //not all pixels are going to be swirled
  for ( x_coord_pixel = 0; x_coord_pixel < img_output -> rows; ++x_coord_pixel) {
    for ( y_coord_pixel = 0; y_coord_pixel < img_output -> cols; ++y_coord_pixel) {

      double alpha = calc_alpha (center_x, center_y, scale, x_coord_pixel, y_coord_pixel);
      int new_x_coord = conversion_for_x_pixel (x_coord_pixel, y_coord_pixel, center_x, center_y, alpha);
      int new_y_coord = conversion_for_y_pixel (x_coord_pixel, y_coord_pixel, center_x, center_y, alpha);

      //swap?
      if (new_x_coord >= 0 && new_y_coord >= 0 && new_x_coord < img_output->cols && new_y_coord < img_output -> rows) {

        img_output -> data[y_coord_pixel * img_output->cols + x_coord_pixel].r = img_input -> data [new_y_coord * img_input->cols + new_x_coord].r;
        img_output -> data[y_coord_pixel * img_output->cols + x_coord_pixel].g = img_input -> data [new_y_coord * img_input->cols + new_x_coord].g;
        img_output -> data[y_coord_pixel * img_output->cols + x_coord_pixel].b = img_input -> data [new_y_coord * img_input->cols + new_x_coord].b;


      //change location of pixel
      //swap old pixel with new pixel, change location of pixel 
      //1d array, row, col
      }
    }
  }
  
  return img_output;
}


