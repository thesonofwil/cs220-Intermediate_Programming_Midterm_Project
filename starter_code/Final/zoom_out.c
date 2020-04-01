//Anire Egbe
//aegbe2

#include <stdio.h>
#include <stdlib.h>
#include "zoom_out.h"


// 0.5X zoom i.e half as many rows and columns
// one pixel from original is copied into a 2 x 2 square output
Image * zoom_out(Image *img) {
  Image *output = (Image *)malloc(sizeof(Image));
  int cols = img->cols / 2;
  int rows = img->rows / 2;
  output->cols = cols;
  output->rows = rows;
  output->data = (Pixel *)malloc(rows * cols * sizeof(Pixel));
  
  //creating output image
  for (int oRow = 0; oRow < output->rows; oRow++) {
    for (int oCol = 0; oCol < output->cols; oCol++) {
      //adds all the r values from the four pixels in the original image to the pixel in the output image and takes average
      output->data[oRow*cols+oCol].r = (img->data[oRow*cols+oCol].r + img->data[oRow*cols+oCol+1].r +  img->data[(oRow+1)*cols+oCol].r +
					img->data[(oRow+1)*cols+oCol+1].r) /4;
      //adds all the b values from the four pixels in the original image to the pixel in the output image and takes average

      output->data[oRow*cols+oCol].b = (img->data[oRow*cols+oCol].b + img->data[oRow*cols+oCol+1].b +  img->data[(oRow+1)*cols+oCol].b +
                                        img->data[(oRow+1)*cols+oCol+1].b) /4;
      //adds all the g values from the four pixels in the original image to the pixel in the output image and takes average

      output->data[oRow*cols+oCol].g = (img->data[oRow*cols+oCol].g + img->data[oRow*cols+oCol+1].g +  img->data[(oRow+1)*cols+oCol].g +
                                        img->data[(oRow+1)*cols+oCol+1].g) /4;

      /* *(output->data + (oRow*output->cols + oCol)).r = *(img->data + (oRow*output->cols + oCol)).r + *(img->data + (oRow*output->cols + (oCol+1))).r
	+ *(img->data + ( (oRow+1)*output->cols + (oCol+1))).r +   *(img->data + ( (oRow+1)*output->cols +  oCol)).r;
      //take average of the four r pixels
      *(output->data + (oRow*output->cols + oCol)).r = *(output->data + (oRow*output->cols + oCol)).r /4;
      //adds all the g values from the four pixels in the original image to the pixel in the output image
      *(output->data + (oRow*output->cols + oCol)).g = *(img->data + (oRow*output->cols + oCol)).g + *(img->data + (oRow*output->cols + (oCol+1))).g
        + *(img->data + ( (oRow+1)*output->cols + (oCol+1))).g +   *(img->data + ( (oRow+1)*output->cols +  oCol)).g;
      //take average of the four g pixels
      *(output->data + (oRow*output->cols + oCol)).g = *(output->data + (oRow*output->cols + oCol)).g /4;
      //adds all the b values from the four pixels in the original image to the pixel in the output image
      *(output->data + (oRow*output->cols + oCol)).b = *(img->data + (oRow*output->cols + oCol)).b + *(img->data + (oRow*output->cols + (oCol+1))).b
        + *(img->data + ( (oRow+1)*output->cols + (oCol+1))).b +   *(img->data + ( (oRow+1)*output->cols +  oCol)).b;
      //take average of the four b pixels
      *(output->data + (oRow*output->cols + oCol)).b = *(output->data + (oRow*output->cols + oCol)).b /4;*/
    }
  }

  return output;
}
