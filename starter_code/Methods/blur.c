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

// Creates a copy of the image with 0's past edges
// Pass in original image and sigma 
Image *pad_copy(Image *img, double sigma) {
  int dim = dimensions(sigma);
  Image *paddedCopy = (Image *)malloc(sizeof(Image));
  int rows = img->rows + (dim - 1); // extra rows before first row and after last row
  int cols = img->cols + (dim - 1); // extra cols before first col and after last col
  paddedCopy->rows = rows;
  paddedCopy->cols = cols;
  paddedCopy->data = (Pixel *)calloc(rows * cols, sizeof(Pixel)); // Initialize everything to 0
  //paddedCopy->data = (Pixel *)malloc(rows * cols * sizeof(Pixel));

  // Set everything to 0
  //for (int i = 0; i < rows * cols; i++) {
  //  paddedCopy->data[i].r = 0;
  //  paddedCopy->data[i].g = 0;
  //  paddedCopy->data[i].b = 0;
  //}
  
  // Copy image within border of zeros
  int index = 0;
  for (int i = dim/2; i < img->rows + dim/2; i++) {
    for (int j = dim/2; j < img->cols + dim/2; j++) {
      paddedCopy->data[i * cols + j] = img->data[index];
      //printf("%d ", i * cols + j);
      index++;
    }
  }
  
  return paddedCopy;
}

// Return the Gaussian filter matrix in 1D format
double *create_filter(double sigma) {
  double dx, dy; // The displacements from the center
  int dim = dimensions(sigma); // dimensions of square filter matrix
  
  // Bounds of matrix
  int lowerBound = -1 * (dim/2);
  int upperBound = -1 * lowerBound;
  
  // Create square filter matrix
  double *filter = (double *)malloc(sq(dim) * sizeof(double));

  // Generate values for filter matrix
  // dx and dy are the coordinates of an entry in the matrix
  // Note indexing starts at 0 in C
  int index = 0;
  for (int r = lowerBound; r <= upperBound; r++) {
    dy = r;
    for (int c = lowerBound; c <= upperBound; c++) {
      dx = c;
      filter[index] = gauss_distribute(sigma, dx, dy);
      index++;
    }
  }
  return filter;
}

// Return the current row in the array given an index
int get_current_row(int i, int cols) {
  return i / cols;
}

// Return the current column in the array given an index
int get_current_column(int i, int cols) {
  return i % cols;
}

// Given the 2D index of a pixel from an image, return the corresponding index when
// the image is made into a padded copy.
// Pass in total number of columns in padded copy and the current index in the non-padded image
int get_padded_index(double sigma, int colsInOriginal, int originalIndex) {
  int dim = dimensions(sigma); // Dimensions of filter
  int paddedCols = colsInOriginal + dim - 1;
  int r = get_current_row(originalIndex, colsInOriginal);
  int c = get_current_column(originalIndex, colsInOriginal);
  int paddedIndex = (dim/2) * paddedCols + (r * paddedCols) + (dim/2) + c;
  
  return paddedIndex;
}

// Returns a matrix of data of centered at a target pixel
// Pass in image and target pixel
// get_pixels(&img[i][j], sigma)
Image *get_pixels(Image *img, Image *paddedCopy, double sigma, int index) {
  int dim = dimensions(sigma); // Same dimensions as filter
  Image *pixels = (Image *)malloc(sizeof(Image));
  pixels->rows = dim;
  pixels->cols = dim;
  pixels->data = (Pixel *)malloc(pixels->rows * pixels->cols * sizeof(Pixel));

  // Define the indices of the pixels to be copied from the padded copy
  int center = get_padded_index(sigma, img->cols, index); // Target pixel is at the center
  int start = center - (2 * paddedCopy->cols) - dim / 2; // Beginning padded index
  int end = center + (2 * paddedCopy->cols) + dim / 2; // Ending padded index

  // Copy over pixel data from padded copy, centering the target and obtaining neighbors
  int i = 0;
  int count = 0; // Keep track of when index goes past filter
  for (int paddedIndex = start; paddedIndex <= end; paddedIndex++) {
    if (count == dim) {
      count = 0; // reset count
      paddedIndex += paddedCopy->cols - dim;
    }
    pixels->data[i] = paddedCopy->data[paddedIndex];
    i++;
    count++;
  }
  
  return pixels;
}

// Multiply pixel values by the filter values and return the new pixel value
// Pass in unmodified original image, a copy of the image to be modified, Gaussian filter, and index of pixel to be changed in image
// To call: convolve(&img[i][j], &filter[i][j]);
void convolve(Image *originalImage, Image *output, Image *paddedCopy, double *filter, double sigma, int targetIndex) {
  Image *pixels = get_pixels(originalImage, paddedCopy, sigma, targetIndex);
  int dim = dimensions(sigma); // Get dimensions of filter

  // Get index of target pixel
  int paddedIndex = get_padded_index(sigma, paddedCopy->cols, targetIndex);
  int x = get_current_row(paddedIndex, paddedCopy->cols); // Current row in padded copy
  int y = get_current_column(paddedIndex, paddedCopy->cols); // Current col in padded copy

  //printf("Padded Copy cols: %d \n", paddedCopy->cols);
  //printf("Target Index: %d \n", targetIndex);
  //printf("Padded Index: %d \n", paddedIndex);
  //printf("x: %d \n", x);
  //printf("y: %d \n", y);
  //printf("\n");
  
  double sumFilter = 0;
  double sumR = 0;
  double sumG = 0;
  double sumB = 0;
 
  int index = 0;

  // Boundaries defined as the starting and ending indices in the padded copy
  for (int i = x - dim/2; i <= x + dim/2; i++) {
    for (int j = y - dim/2; j <= y + dim/2; j++) {
      double r = pixels->data[index].r * filter[index];
      double g = pixels->data[index].g * filter[index];
      double b = pixels->data[index].b * filter[index];
      sumR += r;
      sumG += g;
      sumB += b;
      
      // If within boundaries, add up sum for normalization
      if ((i > dim/2 && i < dim/2 + originalImage->rows) || (j > dim/2 && j < dim/2 + originalImage->cols)) {
        sumFilter += filter[index];
      }
      index++;
    }
  }
  
  //printf("sumR: %f \n", sumR);
  //printf("sumG: %f \n", sumG);
  //printf("sumB: %f \n", sumB);
  //printf("sumFilter: %f \n", sumFilter);

  output->data[targetIndex].r = sumR/sumFilter;
  output->data[targetIndex].g = sumG/sumFilter;
  output->data[targetIndex].b = sumB/sumFilter;

  free(pixels->data);
  free(pixels);
}

void convolve_all(Image *originalImage, Image *output, double *filter, double sigma) {
  Image *paddedCopy = pad_copy(originalImage, sigma);
  //FILE *padded_copy = fopen("building_padded.ppm", "wb");
  //write_ppm(padded_copy, paddedCopy);
  //Image *pixels = get_pixels(originalImage, paddedCopy, sigma, 5);
  //FILE *pixelOutput = fopen("pixelsCenteredAt5.ppm", "wb");
  //write_ppm(pixelOutput, pixels);
  //free(pixels->data);
  //free(pixels);
  
  for (int i = 0; i < originalImage->rows * originalImage->cols; i++) {
    //printf("%d ", i);
    //if (i % 10000 == 0) {
    //  printf("%d \n", i);
    convolve(originalImage, output, paddedCopy, filter, sigma, i);
  }

  //fclose(pixelOutput);
  free(paddedCopy->data);
  free(paddedCopy);
}

void driver(FILE *input, double sigma) {
  Image *copyOfOriginalImg = read_ppm(input);
  Image *imgToBeBlurred = read_ppm(input);
  FILE *output = fopen("building_blur.ppm", "wb");
  
  double *gaussianFilter = create_filter(sigma);
  printf("Convolve all now\n");
  convolve_all(copyOfOriginalImg, imgToBeBlurred, gaussianFilter, sigma);
  printf("Done \n");
  write_ppm(output, imgToBeBlurred);

  free(gaussianFilter);
  free(copyOfOriginalImg->data);
  free(copyOfOriginalImg);
  free(imgToBeBlurred->data);
  free(imgToBeBlurred);
  fclose(output);
}

int main(void) {
  double sigma = 0.5;
  assert(sigma > 0);
  
  FILE *input = fopen("building.ppm", "rb");
  
  driver(input, sigma);
  fclose(input);
  return 0;
}
