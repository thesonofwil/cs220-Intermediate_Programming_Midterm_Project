//Marcelo Morales
//lmoral10

#include <stdio.h>
#include <stdlib.h>
#include "ppm_io.h"
#include <math.h>
#include "pointilism.h"

void pointilism(Image *img) {

  //getting the whole area of the image
  int area = img->rows * img->cols;
  //only need to select three percent of the pixels of the input image
  int numPixels = area * 0.03; 
  
  for (int i = 0; i < numPixels; i++) {
    //selecting random x coordinate of a center of a cirlce
    int x_center = rand() % img -> cols; 
    //selecting random y coordinate of a center of a cirlce
    int y_center = rand() % img -> rows; 
    //for each randomly selected pixe, will use a random radius between 1 and 5
    int radius = rand() % 5 + 1;

  for (int y_coord = y_center - radius; y_coord <= y_center + radius; ++y_coord) {

      for (int x_coord = x_center - radius; x_coord <= x_center + radius; ++x_coord) {
          if ( (y_coord >= 0 && y_coord < img-> rows) && (x_coord >= 0 && x_coord < img->cols) ) {
            
            //point selected has to be inside or border the circle, satisfy equation
            if  ( pow(x_center - x_coord, 2) + pow(y_center - y_coord, 2) <= pow(radius, 2) ) {
            
            //apply pointilism effect by coloring all the pixels that reside in the circle with the same color as the center
            img->data[y_coord * img->cols + x_coord].r = img->data[y_center * img->cols + x_center].r;
            img->data[y_coord * img->cols + x_coord].g = img->data[y_center * img->cols + x_center].g;
            img->data[y_coord * img->cols + x_coord].b = img->data[y_center * img->cols + x_center].b;

          }
        }
      } 
    }
      continue;
  }

}



