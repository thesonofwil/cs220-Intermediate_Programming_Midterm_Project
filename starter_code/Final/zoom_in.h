// Wilson Tjoeng
// wtjoeng1

#ifndef ZOOM_IN_H
#define ZOOM_IN_H

#include "ppm_io.h"

void copyRow(Image *input, Image *output, int currInputRow, int currInputCol, int inputCols, int currOutputRow, int currOutputCol, int outputCols);

Image * zoom_in(Image *img);

#endif
