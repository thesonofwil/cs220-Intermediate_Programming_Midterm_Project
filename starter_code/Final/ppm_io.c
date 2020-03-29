// Anire Egbe, Wilson Tjoeng
// , wtjoeng1

// ppm_io.c
// 601.220, Spring 2019
// Starter code for midterm project - feel free to edit/add to this file

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "ppm_io.h"

/* Read a PPM-formatted image from a file (assumes fp != NULL).
 * Returns the address of the heap-allocated Image struct it
 * creates and populates with the Image data.
 */
Image * read_ppm(FILE *fp) {
  
  // check that fp is not NULL
  assert(fp);
  
  char type[3];
  char isComment;
 
  int colorSize;
  int columns, rows;
  
  Image *image = (Image *)malloc(sizeof(Image)); // allocate storage to hold image
   
  // Assuming file is already opened in binary format
  // Check file type is P6
  fscanf(fp, "%2s \n", type); // read 2 characters into type
  type[2] = '\0';
  if (strcmp(type, "P6") != 0) {
    printf("Error: invalid file type.\n");
    exit(3);
  }
   
  // Skip comments if any. Assume there is at most one line of comment.
  isComment = fgetc(fp);
  if (isComment == '#') {
    fscanf(fp, "%*[^\n]"); // read and discard line
  } else {
    ungetc(isComment, fp); // No comment, undo fgetc
  }
  
  // Read the next three int values
  // Space after %d to account for newline
  fscanf(fp, " %d %d %d ", &columns, &rows, &colorSize);
  
  if (colorSize != 255) { // It must always equal 255
    printf("Error: the value for colors must be 255.\n");
    exit(3);
  }

  image->cols = columns;
  image->rows = rows;
  image->data = (Pixel *)calloc(columns * rows + 1, sizeof(Pixel)); // array to hold rgb
  // +1 fixes valgrind issues somehow(?)
  
  // Read rgb values of pixels then store into an array
  fread(image->data, sizeof(Pixel), image->cols * image->rows, fp);
   
  // free mallocs in project.c
  return image;
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
    exit(7); // Added error condition
  }

  return num_pixels_written;
}
