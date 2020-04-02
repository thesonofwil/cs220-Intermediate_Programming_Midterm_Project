//Wilson Tjoeng, Anire Egbe
//wtjoeng1, aegbe2
//alpha_blending.c function

#include <stdio.h>
#include <stdlib.h>
#include "alpha_blending.h"

Image *alpha_blending(Image *img1, Image *img2, float alpha){
  // Check alpha is in range
  if (alpha < 0 || alpha > 1) {
    fprintf(stderr, "Error: alpha must be between 0 and 1.");
    exit(6);
  }

  Image *output = (Image *)malloc(sizeof(Image));
  int cols, rows;
  // Get dimensions of output
  if (img1->cols > img2->cols) {
    cols = img1->cols;
  } else {
    cols = img2->cols;
  }

  if (img1->rows > img2->rows) {
    rows = img1->rows;
  } else {
    rows = img2->rows;
  }

  output->rows = rows;
  output->cols = cols;
  output->data = (Pixel *)malloc(rows * cols * sizeof(Pixel));

  int areaImg1 = img1->rows * img1->cols;
  int areaImg2 = img2->rows * img2->cols;

  int count1 = 0; // track index for img1
  int count2 = 0; // track index for img2

  for (int i = 0; i < rows * cols; i++) {

     int input1R = img1->data[count1].r;
     int input1G = img1->data[count1].g;
     int input1B = img1->data[count1].b;
     int input2R = img2->data[count2].r;
     int input2G = img2->data[count2].g;
     int input2B = img2->data[count2].b;
    
    if (count1 >= areaImg1) { // all of img 1 copied over already
      input1R = 1;
      input1G = 1;
      input1B = 1;
    }

    if (count2 >= areaImg2) { // all of img2 copied over already
      input2R = 1;
      input2G = 1;
      input2B = 1;
    }
    
    output->data[i].r = alpha * input1R + (1 - alpha) * input2R;
    output->data[i].g = alpha * input1G + (1 - alpha) * input2G;
    output->data[i].b = alpha * input1B + (1 - alpha) * input2B;

    // Stop incrementing once all of image is inputted
    if (count1 < areaImg1) { 
      count1++;
    }
    if (count2 < areaImg2) {
      count2++;
    }
  }
  return output;
}
