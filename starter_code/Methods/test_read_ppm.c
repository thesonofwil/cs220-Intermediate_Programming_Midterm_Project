#include <stdlib.h>
#include <stdio.h>
#include "ppm_io.c"
#include "ppm_io.h"

int main(void) {
  FILE *inputT = fopen("trees.ppm", "rb");
  Image *trees = read_ppm(inputT);
   
  FILE *inputB = fopen("building.ppm", "rb");
  Image * building = read_ppm(inputB);
    
  FILE *outputT = fopen("trees_test.ppm", "wb");
  write_ppm(outputT, trees);
  FILE *outputB = fopen("building_test.ppm", "wb");
  write_ppm(outputB, building);

  free(trees->data);
  free(trees);
  free(building->data);
  free(building);

  fclose(inputT);
  fclose(outputT);
  fclose(inputB);
  fclose(outputB);

  return 0;
}