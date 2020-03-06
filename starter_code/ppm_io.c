// Anire Egbe, Wilson Tjoeng
// , wtjoeng1
// ppm_io.c
// 601.220, Spring 2019
// Starter code for midterm project - feel free to edit/add to this file

#include <assert.h>
#include <stdlib.h>
#include "ppm_io.h"
#include <string.h>


/* Read a PPM-formatted image from a file (assumes fp != NULL).
 * Returns the address of the heap-allocated Image struct it
 * creates and populates with the Image data.
 */
Image * read_ppm(FILE *fp) {

  // PPM format:
  //   Top: tag that marks the file as PPM (should be "P6")
  //   Next: three numbers representing columns, rows, and colors. 
  //   Color = 255, the max value
  //   Comments are marked by '#'
  // check that fp is not NULL
  assert(fp); 

  char type[3];
  //int columns, rows,
  int colorSize;
  
  Image *image = (Image *)malloc(sizeof(Image)); // allocate storage to hold image
  
  // Assuming file is already opened in binary format
  // Check file type is P6
  fscanf(fp, "%2s", type); // read 2 characters into type
  type[2] = '\0';
  if (strcmp(type, "P6") != 0) {
    printf("Invalid file type.\n");
    exit(1);
  }

  // Skip comments if any. Assume there is at most one line of comment.
  if (fgetc(fp) == '#') {
    fscanf(fp, "%*[^\n]\n"); // move pointer to next line
  }

  // Read the next three int values
  fscanf(fp, "%d%d%d\n", &image->cols, &image->rows, &colorSize);
  if (colorSize != 255) { // It must always equal 255
    printf("The value for colors must be 255.\n");
    exit(1);
  }

  image->data = (Pixel *)malloc(image->cols * image->rows * sizeof(Pixel)); // array to hold rgb
  
  // Read rgb values of pixels then store into an array
  fread(image->data, sizeof(Pixel), image->cols * image->rows * 3, fp); 

  fclose(fp);
  // free mallocs in main?
  return image;  //TO DO: replace this stub
  
}


/* Write a PPM-formatted image to a file (assumes fp != NULL),
 * and return the number of pixels successfully written.
 */
int write_ppm(FILE *fp, const Image *im) {

  // check that fp is not NULL
  assert(fp); 

  // write PPM file header, in the following format
  // P6
  // cols rows
  // 255
  fprintf(fp, "P6\n%d %d\n255\n", im->cols, im->rows);

  // now write the pixel array
  int num_pixels_written = fwrite(im->data, sizeof(Pixel), im->cols * im->rows, fp);

  if (num_pixels_written != im->cols * im->rows) {
    fprintf(stderr, "Uh oh. Pixel data failed to write properly!\n");
  }

  return num_pixels_written;
}

int main(int argc, char *argv[]) {
  //checks if the user input a file name
  if(argc == 1) {
    printf("File name was not put in.");
    return 1;
  }
  //makes sure the command line argument is just two
  if(argc != 2){
    printf("File could not be opened\n");
    return 2;
  }

  File *input = fopen(argv[1], "rb");
  Image *a = read_ppm(input);
  File *output = fopen("test.ppm", "wb");
  
