//Wilson Tjoeng, Anire Egbe
//wtjoeng1, aegbe2

#include <stdio.h>
#include <stdlib.h>
#include "zoom_out.h"


// 0.5X zoom i.e half as many rows and columns
// one pixel from original is copied into a 2 x 2 square output

// Return the current index in the fake 2D array
int get_index(int currentRow, int currentCol, int totalCols) {
  return currentRow * totalCols + currentCol;
}

Image * zoom_out(Image *img) {
  Image *output = (Image *)malloc(sizeof(Image));
  int cols = img->cols / 2;
  int rows = img->rows / 2;
  output->cols = cols;
  output->rows = rows;
  output->data = (Pixel *)malloc(rows * cols * sizeof(Pixel));

  // Initialize indices for 2 x 2 square 
  int imgRowTop = 0;
  int imgRowBot = 1;
  
  for (int r = 0; r < rows; r++) {
    int imgColLeft = 0;
    int imgColRight = 1;

    for (int c = 0; c < cols; c++) { 
      int index = get_index(r, c, cols); // current index of output

      
      int topLeft = get_index(imgRowTop, imgColLeft, img->cols);
      int topRight = get_index(imgRowTop, imgColRight, img->cols);
      int botLeft = get_index(imgRowBot, imgColLeft, img->cols);
      int botRight = get_index(imgRowBot, imgColRight, img->cols);

      int averageR = (img->data[topLeft].r + img->data[topRight].r + img->data[botLeft].r + img->data[botRight].r)/4;
      int averageG = (img->data[topLeft].g + img->data[topRight].g + img->data[botLeft].g + img->data[botRight].g)/4;
      int averageB = (img->data[topLeft].b + img->data[topRight].b + img->data[botLeft].b + img->data[botRight].b)/4;

      output->data[index].r = averageR;
      output->data[index].g = averageG;
      output->data[index].b = averageB;

      // Move to next columns
      imgColLeft += 2;
      imgColRight += 2;
    }
    imgRowTop += 2;
    imgRowBot += 2;

    // Column indices will reset after this
  }
  
  return output;
}
