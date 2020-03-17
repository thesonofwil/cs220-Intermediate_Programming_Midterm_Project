#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Return a copy of the parameter squared
double sq(double x) {
  return x * x;
}

double gauss_distribute(double sigma, int dx, int dy) {
  const double pi = 3.14159265;
  return (1.0 / (2.0 * pi * sq(sigma))) * exp(-(sq(dx) + sq(dy)) / (2 * sq(sigma)));
}
 
// Return the Gaussian filter matrix
double **create_filter(double sigma) {
  double dx, dy;
  int dim; // dimensions of square filter matrix
  
  // Matrix dimensions must be at least 10 * sigma and odd
  if (fmod(10 * sigma, 2) == 0) {
    dim = 10 * sigma + 1; // even - add an extra dimension
  } else {
    dim = 10 * sigma; // odd - keep as is
    if (dim < 10 * sigma) { // account for more than one decimal places
      dim += 2;
    }
  }
  
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
