#ifndef IMAGEMANIP_H
#define IMAGEMANIP_H

#include "ppm_io.h"

void check_argc(int argc, int req);

float convert_parameter(char *arg);

void call_method(char *method, int argc, char *argv[], Image *img, FILE *output);

#endif
