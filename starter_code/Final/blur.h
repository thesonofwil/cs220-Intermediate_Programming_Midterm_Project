// Wilson Tjoeng
// wtjoeng1

#ifndef BLUR_H
#define BLUR_H

#include "ppm_io.h"

double sq(double x);

double gauss_distribute(double sigma, int dx, int dy);

int dimensions(double sigma);

Image *copy_image (Image *img);

Image *pad_copy(Image *img, double sigma);

double *create_filter(double sigma);

int get_current_row(int i, int cols);

int get_current_column(int i, int cols);

int get_padded_index(double sigma, int colsInOriginal, int originalIndex);

Image *get_pixels(Image *img, Image *paddedCopy, double sigma, int index);

void convolve(Image *originalImage, Image *output, Image *paddedCopy, double *filter, double sigma, int targetIndex);

void convolve_all(Image *originalIMage, Image *output, double *filter, double sigma);

Image *blur(Image *img, double sigma);

#endif