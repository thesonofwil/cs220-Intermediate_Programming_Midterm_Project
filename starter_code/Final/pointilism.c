//Marcelo Morales
//lmoral10


#include <stdio.h>
#include <stdlib.h>
#include "ppm_io.c"
#include "ppm_io.h"

void pointilism(Image *img) {
  int area = img->rows * img->cols;
  int targetNumber = area * 0.03; // does this need to be random?

  for (int i = 0; i < targetNumber; i++) {
    int col = rand() % img->cols + 1; // generate a random x coordinate
    int row = rand() % img->rows + 1; // generate a random y coordinate

    int radius = rand() % 5 + 1; // get a random radius [0, 5]

  }
}

/*
apply pointilism-like effect to an input image

randomly select a small set (3%) of the pixels in an input image and apply effect to them
imagine each randomly selected pixel is at the center of a cirlce with a random radius between 1 and 5

now apply pointilism effect - color all the pixels that reside in that circle with the same color 
as the color of the randomly selected pixel which is at the center

gives input image a "painting-like" look by creating a set of small filled circles (dots) across 
image, where each dot is uniformly colored with the color of the randomly selected pixel which is
located at the center of that dot

APPLY EFFECT TO ONLY 3% OF THE TOTAL PIXELS OF THE INPUT IMAGE
FOR EACH RANDOMLY SELECTED PIXEL, USE A RANDOM RADIUS BETWEEN 1 AND 5 WHEN VREATING THE FILLED COLOR DOT

DO NOT MAKE ANY CALLS TO srand()

*/

//pointilism algorithm
//iterate from 0 up to 3% of the total pixel count, and each time, pick a random pixel and radius to 
//apply the circle-painting operation

//do not call srand, use the deault random seed
//determine how many pixels will be transformed
//perform transformations, each transformation consists of
//first, determine a random x coord
//second, determine a random y coord
//third, determine a random radius
//four, render the pixel as a disc of the chosen radius

//Would it be more correct to say all pixels satisfying
//(x-a)^2 + (y-b)^2 <= r^2,
//where (a, b) are the coordinates of the central pixel to be pointilized

//Pointilism needs to be an in-place transformation (on original image)

//for the radius, a random integer inclusive between 1 and 5 (inclusive) should be used
//use original color, one from input file

//int curr_x = rand() % im->cols; 
//int curr_y = rand() % im->rows; 
//int curr_radius = rand() % 5 + 1;



/*
code for generating random points and finding points within the radius is
int pPix = 0.03 * numPixel;
  for(int i=0; i<pPix; i++){
    int centerX = rand() % result -> cols;
    int centerY = rand() % result -> rows;
    int radius = rand() % 5 + 1;
    for(int j = centerY - radius; j <=centerY + radius; j++){
      for(int k = centerX - radius; k<=centerX + radius; k++){
        if(k < 0 || k > result->cols || j < 0 || j > result->rows){
          continue;
        }
	//etc.
     	}
    }


*/





