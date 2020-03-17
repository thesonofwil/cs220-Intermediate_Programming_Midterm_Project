#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Return a copy of the parameter squared
double sq(double *x) {
  return x * x;
}

// Return the Gaussian filter matrix
double **gauss_distribute(double sigma, double dx, double dy) {
  double g = (1.0 / (2.0 * PI * sq(sigma))) * exp(-(sq(dx) + sq(dy)) / (2 * sq(sigma)));
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
  
  double **filter = (double **)malloc(
}

int main(void) {
}
