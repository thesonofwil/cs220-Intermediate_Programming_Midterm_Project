#include <stdlib.h>
#include <stdio.h>
#include "ppm_io.c"
#include "ppm_io.h"

int main(void) {
  FILE *inputT = fopen("trees.ppm", "rb");
  printf("Trees: ");
  Image *trees = read_ppm(inputT);
  printf("\n");
  
  FILE *inputB = fopen("building.ppm", "rb");
  printf("Building: ");
  Image * building = read_ppm(inputB);
  printf("\n");
  
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
