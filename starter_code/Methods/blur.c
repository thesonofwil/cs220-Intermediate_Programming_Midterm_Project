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


// Returns a copy of an image with the data stored as a 2D array
//Image * copy_to_2D(Image *img) {
//  int rows = img->rows;
//  int cols = img->cols;
//  int size = sizeof(img->data)/sizeof(int);
//  Image copy = (Image *)malloc(sizeof(Image));
//  copy->data[rows][cols]; // Dimensions are already known
  
//  copy->rows = rows;
//  copy->cols = cols;

//  int index = 0;
//  for (int i = 0; i < rows; i++) {
//    for (int j = 0; j < cols && index < size; j++) {
//      copy->data[i][j] = img->data[index++];
//    }
//  }
//  return copy;
//}

// Creates a copy of the image with 0's past edges
// Pass in original image and sigma 
Image * pad_copy(Image *img, double sigma) {
  int dim = dimensions(sigma);
  Image *paddedCopy = (Image *)malloc(sizeof(Image));
  int rows = img->rows + (dim - 1); // extra rows before first row and after last row
  int cols = img->cols + (dim - 1); // extra cols before first col and after last col
  paddedCopy->rows = rows;
  paddedCopy->cols = cols;
  paddedCopy->data = (Pixel *)calloc(rows * cols, sizeof(Pixel)); // Initialize everything to 0
  
  // Convert to 2D copy
  //Image *padded2DCopy = copy_to_2D(paddedCopy);
  
  //int beginningRow = rows - (dimensions/2 - 1) - img->rows; // start of image
  //int beginningCol = cols - (dimensions/2 - 1) - img->cols;
  //int endRow = rows - (dimensions/2 - 1); // end of image
  //int endCol = cols - (dimensions/2 - 1);

  //int start = cols * dimensions/2 + dimensions/2 - 1;
  // Iterate over original image and copy over to padded copy
  int index = 0;
  for (int i = dim/2; i < dim + dim/2; i++) {
    for (int j = dim/2; j < dim + dim/2; j++) {
      paddedCopy[i * cols + j] = img[index];
      index++;
    }
  }
  
  //int r = 0;
  // for (int i = beginningRow; i <= endRow; i++) {
  //  int c = 0;
  //  for (int j = beginningCol; j <= endCol; j++) { 
  //    padded2DCopy[i][j] = imgCopy[r][c];
  //    c++;
  //  }
  //  r++;
  //}

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

// Return the current colun in the array given an index
int get_current_column(int i, int cols) {
  return i % cols;
}

// Given the 2D index of a pixel from an image, return the corresponding index when
// the image is made into a padded copy.
// Pass in total number of columns in padded copy and the current index in the non-padded image
int get_padded_index(double sigma, int paddedCols, int originalIndex) {
  int dim = dimensions(sigma); // Dimensions of filter 
  int r = get_current_row(originalIndex, paddedCols);
  int c = get_current_column(originalIndex, paddedCols);
  int paddedIndex = (dim/2) * paddedCols + (r * paddedCols) + (dim/2) + c;
  return paddedIndex;
}

// Returns a matrix of data of centered at a target pixel
// Pass in image and target pixel
// get_pixels(&img[i][j], sigma)
Image *get_pixels(Image *img, double sigma, int index) {
  int dim = dimensions(sigma); // Same dimensions as filter
  Image *pixels = (Image *)malloc(sizeof(Image));
  pixels->rows = dim;
  pixels->cols = dim;
  pixels->data = (Pixel *)malloc(pixels->rows * pixels->cols * sizeof(Pixel));

  Image *paddedCopy = pad_copy(img, sigma);
 
  // Define the indices of the pixels to be copied from the padded copy
  int center = get_padded_index(sigma, pixels->cols, index); // Target pixel is at the center
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

  free(paddedCopy->data);
  free(paddedCopy);
  return pixels;
}

// Multiply pixel values by the filter values and return the new pixel value
// Pass in unmodified original image, a copy of the image to be modified, Gaussian filter, and index of pixel to be changed in image
// To call: convolve(&img[i][j], &filter[i][j]);
void convolve(Image *originalImage, Image *output, double *filter, double sigma, int targetIndex) {
  Image *pixels = get_pixels(originalImage, sigma, targetIndex);
  int dim = dimensions(sigma); // Get dimensions of filter

  // Get index of target pixel
  int paddedIndex = get_padded_index(sigma, originalImage->cols + dim - 1, targetIndex);
  int a = get_current_row(paddedIndex, originalImage->rows + dim/2 - 1);
  int b = get_current_column(targetIndex,originalImage->cols + dim/2 - 1);

  double sumFilter = 0;
  double sumR = 0;
  double sumG = 0;
  double sumB = 0;
 
  int index = 0;

  // Boundaries defined as the starting and ending indices in the padded copy
  for (int i = a - dim/2; i <= a + dim/2; i++) {
    for (int j = b - dim/2; j <= b + dim/2; j++) {
      pixels->data[index].r = pixels->data[index].r * filter[index];
      pixels->data[index].g = pixels->data[index].g * filter[index];
      pixels->data[index].b = pixels->data[index].b * filter[index];
      sumR += pixels->data[index].r;
      sumG += pixels->data[index].g;
      sumB += pixels->data[index].b;
      
      // If within boundaries, add up sum for normalization
      if (!(i < dim/2 || i > dim/2 + originalImage->rows - 1 || j < dim/2 || j > dim/2 + originalImage->cols - 1)) {
        sumFilter += filter[index];
      }
      index++;
    }
  }
  output->data[targetIndex].r = sumR/sumFilter;
  output->data[targetIndex].g = sumG/sumFilter;
  output->data[targetIndex].b = sumB/sumFilter;

  free(pixels->data);
  free(pixels);
}

void convolve_all(Image *originalImage, Image *output, double *filter, double sigma) {
  for (int i = 0; i < originalImage->rows * originalImage->cols; i++) {
    convolve(originalImage, output, filter, sigma, i);
  }
}

void driver(FILE *input, double sigma) {
  Image *copyOfOriginalImg = read_ppm(input);
  Image *imgToBeBlurred = read_ppm(input);
  FILE *output = fopen("building_blur.ppm", "wb");

  double *gaussianFilter = create_filter(sigma);
  convolve_all(copyOfOriginalImg, imgToBeBlurred, gaussianFilter, sigma);
  write_ppm(output, imgToBeBlurred);

  free(copyOfOriginalImg->data);
  free(copyOfOriginalImg);
  free(imgToBeBlurred->data);
  free(imgToBeBlurred);
  fclose(output);
}

int main(void) {
  double sigma = 5;
  
  FILE *input = fopen("building.ppm", "rb");
  driver(input, sigma);
  return 0;
}
