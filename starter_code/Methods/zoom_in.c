#include <stdio.h>
#include <stdlib.h>
#include "ppm_io.c"
#include "ppm_io.h"

// Copy over a row of data from an image (with a fake 2D array) to an output
void copyRow(Image *input, Image *output, int currInputRow, int currInputCol, int inputCols, int currOutputRow, int currOutputCol, int outputCols) {
  int inputIndex = currInputRow * inputCols + currInputCol;
  int outputIndex = currOutputRow * outputCols + currOutputCol;
  output->data[outputIndex] = input->data[inputIndex];
  output->data[outputIndex + 1] = input->data[inputIndex];
}

// 2X zoom i.e twice as many rows and columns
// one pixel from original is cpied into a 2 x 2 square output
Image * zoom_in(Image *img) {
  Image *output = (Image *)malloc(sizeof(Image));
  int cols = img->cols * 2;
  int rows = img->rows * 2;
  output->cols = cols;
  output->rows = rows;
  output->data = (Pixel *)malloc(rows * cols * sizeof(Pixel));
  
  int currOutputRow = 0;
  int currOutputCol = 0;
  for (int currImgRow = 0; currImgRow < img->rows; currImgRow++) {

    // Copy over top half of square
    for (int currImgCol = 0; currImgCol < img->cols; currImgCol++) {
      copyRow(img, output, currImgRow, currImgCol, img->cols, currOutputRow, currOutputCol, cols);
      currOutputCol += 2;
    }
    
    // Copy over bottom half of square
    currOutputCol = 0; // reset column index
    currOutputRow++;
    for (int currImgCol = 0; currImgCol < img->cols; currImgCol++) { 
      copyRow(img, output, currImgRow, currImgCol, img->cols, currOutputRow, currOutputCol, cols);
      currOutputCol += 2;
    }

    currOutputCol = 0; // reset column index
    currOutputRow++; // go to next output row which will be unique
    // Copy over the next input row
  }
 
  return output;
}

int main() {
  FILE *input = fopen("building.ppm", "rb");
  Image *img = read_ppm(input);

  FILE *output = fopen("building_zoomed_in.ppm", "wb");
  Image *img_output = zoom_in(img);
  write_ppm(output, img_output);

  fclose(input);
  fclose(output);
  free(img->data);
  free(img);
  free(img_output->data);
  free(img_output);
  return 0;
}
