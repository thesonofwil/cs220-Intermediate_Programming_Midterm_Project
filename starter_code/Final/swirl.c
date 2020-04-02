//Marcelo Morales
//lmoral10

#include <stdlib.h>
#include <stdio.h>
#include "ppm_io.h"
#include <math.h>
#include "swirl.h"


//two inputs provided by user of a center (x, y) and a distortion scale are finction parameters
void swirl (Image *img, int x_center, int y_center, int scale) {
  printf("check first\n");
  //definitng all my variables that will be used

  int x_coord;
  int y_coord;
  int delta_x;
  int delta_y;
  int new_x_coord;
  int new_y_coord;
  
  double alpha;
  double cos_a;
  double sin_a;
  
  int columns_of_image = img->cols;
  int rows_of_image = img -> rows;

 

  //array of pixels that will be modified 
  Pixel *array_of_pixels = malloc(sizeof(Pixel) * rows_of_image * columns_of_image);

  for (int current_row= 0; current_row < rows_of_image; ++current_row) {
    for (int current_column = 0; current_column < columns_of_image; ++current_column) {
      //array of pixels initially has all the same red, green, and blue channels as the image
      array_of_pixels[(current_row * columns_of_image) + current_column].r = img->data[(current_row * columns_of_image) + current_column].r;
      array_of_pixels[(current_row * columns_of_image) + current_column].g = img->data[(current_row * columns_of_image) + current_column].g;
      array_of_pixels[(current_row * columns_of_image) + current_column].b = img->data[(current_row * columns_of_image) + current_column].b;
      
      //setting image with all black pixels, will be modified after
      img->data[(current_row * columns_of_image) + current_column].r = 0;
      img->data[(current_row * columns_of_image) + current_column].g = 0;
      img->data[(current_row * columns_of_image) + current_column].b = 0;

    }
  }

  for (x_coord = 0; x_coord < columns_of_image; ++x_coord) {
    for (y_coord = 0; y_coord < rows_of_image; ++y_coord) {
      //implement swirl effect
      delta_x = x_coord - x_center;
      delta_y = y_coord - y_center;
      alpha = sqrt(delta_x * delta_x + delta_y * delta_y) / (double) scale;
      cos_a = cos(alpha);
      sin_a = sin(alpha);
      
      //new location of x coordinate and y coordinate
      new_x_coord = (int) (delta_x * cos_a - delta_y * sin_a + x_center); 
      new_y_coord = (int) (delta_x * sin_a + delta_y * cos_a + y_center); 

      //check to make sure new location of pixel is in the dimensions of the image
      if (new_x_coord >= 0 && new_y_coord >= 0 && new_x_coord < columns_of_image && new_y_coord < rows_of_image) {
   
	
        //changing location of pixel from old coordinates to new coordinates
        img->data[(y_coord * columns_of_image) + x_coord].r = array_of_pixels[(new_y_coord * columns_of_image) + new_x_coord].r;
        img->data[(y_coord * columns_of_image) + x_coord].g = array_of_pixels[(new_y_coord * columns_of_image) + new_x_coord].g;
        img->data[(y_coord * columns_of_image) + x_coord].b = array_of_pixels[(new_y_coord * columns_of_image) + new_x_coord].b;


      }
    }
  }
  free(array_of_pixels);
}
