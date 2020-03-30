//Marcelo Morales
//lmoral10

#ifndef SWIRL_H
#define SWIRL_H

#include "ppm_io.h"

double calc_alpha (int center_x, int center_y, int scale, int x, int y);
int conversion_for_x_pixel (int x_coord_pixel, int y_coord_pixel, int center_x, int center_y, double alpha);
int conversion_for_y_pixel (int x_coord_pixel, int y_coord_pixel, int center_x, int center_y, double alpha);
Image * swirl (Image * img_input, int center_x, int center_y, int scale);


#endif
