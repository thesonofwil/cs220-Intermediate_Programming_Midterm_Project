#ifndef ZOOM_OUT_H
#define ZOOM_OUT_H

#include "ppm_io.h"

int get_index(int currentRow, int currentCol, int totalCols);

Image * zoom_out(Image *img);

#endif
