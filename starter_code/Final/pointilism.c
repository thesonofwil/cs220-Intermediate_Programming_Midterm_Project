//Marcelo Morales
//lmoral10


#include <stdio.h>
#include <stdlib.h>
#include "ppm_io.h"
#include <math.h>
#include "pointilism.h"

void pointilism(Image *img) {

  int area = img->rows * img->cols;
  int numPixels = area * 0.03; // does this need to be random?
  //have to fix seed?

  //printf("%d %d circle", img->rows, img->cols);
  //printf("check\n");
  for (int i = 0; i <= numPixels; i++) {
    int x_center = rand() % img -> cols; //x coord center of circle
    int y_center = rand() % img -> rows; //y coord center of circle
    int radius = rand() % 5 + 1;

    //loop limit problems?


  for (int y_coord = y_center - radius; y_coord <= y_center + radius; ++y_coord) {

      for (int x_coord = x_center - radius; x_coord <= x_center + radius; ++x_coord) {
          
      
          if ( (y_coord >= 0 && y_coord < img-> rows) && (x_coord >= 0 && x_coord < img->cols) ) {
        
            if  ( pow(x_center - x_coord, 2) + pow(y_center - y_coord, 2) <= pow(radius, 2) ) {

          //printf("%d %d check\n ", x_coord, y_coord);
          //printf("%d %d check2\n", img->cols, img->rows);

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


/*
    for (int y_coord = y_center - radius; y_coord <= y_center + radius; ++y_coord) { 
      for (int x_coord = x_center - radius; x_coord <= x_center + radius; ++x_coord) {
        if ( (y_coord >= 0 && y_coord <= img-> cols) && (x_coord >= 0 && x_coord <= img->rows) ) {
           // printf("%d %d\n", x_coord, y_coord);
          if  ( pow(x_center - x_coord, 2) + pow(y_center - y_coord, 2) <= pow(radius, 2) ) { 
            //color in with center, has to satisfy equation of a circle
          img->data[x_coord * img->cols + y_coord].r = img->data[x_center * img->cols + y_center].r;
          img->data[x_coord * img->cols + y_coord].g = img->data[x_center * img->cols + y_center].g;
          img->data[x_coord * img->cols + y_coord].b = img->data[x_center * img->cols + y_center].b;
          } 
          //color in pixel in the pixel with chosen center
        }
      continue;
      }
    
  
      }  
    }

    //return img;
  }
*/



