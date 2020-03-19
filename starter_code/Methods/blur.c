#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ppm_io.c"
#include "ppm_io.h"

// Return a copy of the parameter squared
double sq(double x) {
  return x * x;
}

double gauss_distribute(double sigma, int dx, int dy) {
  const double pi = 3.14159265;
  return (1.0 / (2.0 * pi * sq(sigma))) * exp(-(sq(dx) + sq(dy)) / (2 * sq(sigma)));
}

// Returns a copy of an image with the data stored as a 2D array
Image * copy_to_2D(Image *img) {
  int rows = img->rows;
  int cols = img->cols;
  int size = sizeof(img->data)/sizeof(int);
  Image copy = (Image *)malloc(sizeof(Image));
  copy->data[rows][cols]; // Dimensions are already known
  
  copy->rows = rows;
  copy->cols = cols;

  int index = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols && index < size; j++) {
      copy->data[i][j] = img->data[index++];
    }
  }
  return copy;
}

// Creates a copy of the image with 0's at edge cases
// Pass in copy of image with 2D array
Image * pad_copy(Image *imgCopy, int dimensions) {
  Image paddedCopy = (Image *)malloc(sizeof(Image));
  int rows = imgCopy->rows + (dimensions - 1);
  int cols = imgCopy->cols + (dimensions - 1);
  paddedCopy->rows = rows;
  paddedCopy->cols = cols;
  paddedCopy->data = (Pixel *)calloc(rows * cols, sizeof(Pixel)); // Initialize everythign to 0

  // Convert to 2D copy
  Image *padded2DCopy = copy_to_2D(paddedCopy);
  
  int beginningRow = rows - (dimensions - 1) - img->rows; // start of image
  int beginningCol = cols - (dimensions - 1) - img->cols;
  int endRow = rows - (dimensions - 1); // end of image
  int endCol = cols - (dimensions - 1);

  // Iterate over original image and copy over to padded copy
  int r = 0;
  for (int i = beginningRow; i <= endRow; i++) {
    int c = 0;
    for (int j = begginingCol; j <= endCol; j++) { 
      padded2DCopy[i][j] = imgCopy[r][c];
      c++;
    }
    r++;
  }

  free(paddedCopy->data);
  free(paddedCopy);
  return padded2DCopy;
}

// Return the dimensions of the Gaussian filter (square matrix)
int dimensions(double sigma) {
  int dim;
  
  // Matrix dimensions must be at least 10 * sigma and odd
  if (fmod(10 * sigma, 2) == 0) {
    dim = 10 * sigma + 1; // even - add an extra dimension
  } else {
    dim = 10 * sigma; // odd - keep as is
    if (dim < 10 * sigma) { // account for more than one decimal places
      dim += 2;
    }
  }
  return dim;
}

// Return the Gaussian filter matrix
double **create_filter(double sigma) {
  double dx, dy;
  int dim = dimensions(sigma); // dimensions of square filter matrix
  
  // Bounds of matrix
  int lowerBound = -1 * (dim/2);
  int upperBound = -1 * lowerBound;
  
  // Create square filter matrix
  double **filter = (double **)malloc(dim * sizeof(double *));
  for (int i = 0; i < dim; i++) {
    filter[i] = (double *)malloc(dim * sizeof(double));
  }

  // Generate values for filter matrix
  // dx and dy are the coordinates of an entry in the matrix
  // Note indexing starts at 0 in C
  for (int r = lowerBound; r <= upperBound; r++) {
    dy = r;
    for (int c = lowerBound; c <= upperBound; c++) {
      dx = c;
      filter[r + upperBound][c + upperBound] = gauss_distribute(sigma, dx, dy);
    }
  }
  return filter;
}

// Returns a matrix of data of centered at a target pixel
// Pass in original image
// get_pixels(&img[i][j], sigma)
int **get_pixels(Image *img, int row, int col, double sigma) {
  Image *copy = copy_to_2D(img);
  int dimensions = dimensions(sigma);
  //int index = currentRow * totalCols + currentCol; // index for a fake 2D array

  // Pad the image
  Image *paddedCopy = pad_copy(copy);
  
  int **pixels = (int **)malloc(dimensions * sizeof(int *)); // 2D matrix to hold pixel values
  for (int i = 0; i < dim; i++) {
    pixels[i] = (int *)malloc(dimensions * sizeof(int));
  }

  // Get the pixel values. Beyond edges the values are zeros.
  for (int r = row - dimensions/2; r <= row + dimensions/2; r++) {
    for (int c = col - dimensions/2; c <= dimensions + dimensions/2; c++) {
      pixels[r][c] = paddedCopy->data[r][c];
    }
  }

  free(paddedCopy->data);
  free(paddedCopy);
  free(copy);
  
  return pixels;
}

// Multiply pixel and its surroundings with the filter
// To call: convolve(&img[i][j], &filter[i][j]);
void convolve(Image *img, double filterValue) {
  img->data.r * filterValue;
  img->data.g * filterValue;
  img->data.b * filterValue;
}

void convolve_all(Image *img, double **filter) {
 
}

int main(void) {
  double **matrix = create_filter(0.5);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      printf("%f ", matrix[i][j]);
    }
    printf("\n");
  }
  free(matrix);
}
