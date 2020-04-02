//Anire Egbe & Wilson
//aegbe2
//alpha_blending.c function

#include <stdio.h>
#include <stdlib.h>
#include "alpha_blending.h"

Image *alpha_blending(Image *Image1, Image *Image2, float alpha){
  // check to make sure inputs are valid
  /* if( Image1 == NULL || Image2 == NULL || ratio == NULL){
    printf("Incorrect number of arguments\n");
    return 5;
  }
  //check if alpha is in range
  float a = 0; //creates a float value = 0.0
  float b = 1; //creates a float value = 1.0
  if(alpha <= a || alpha >= b){
    printf("Ratio value is out of range\n");
    return 6;
    }*/
  // Changing Image 1 by alpha
  int numpix1 = Image1->rows * Image1->cols; //number of pixels in Image 1
  //create a loop to change each R,G,B value in each pixel
  for(int i = 0; i < numpix1; i++){
    Image1->data[i].r = Image1->data[i].r * alpha;
    Image1->data[i].g = Image1->data[i].g * alpha;
    Image1->data[i].b = Image1->data[i].b * alpha;
    
    /* *(Image1.data + i).r = *(Image1.data + i).r * alpha;
    *(Image1.data + i).g = *(Image1.data + i).g * alpha;
    *(Image1.data + i).b = *(Image1.data + i).b * alpha;*/
  }
  // Changing Image 2 by 1 - alpha
  int numpix2 = Image2->rows * Image2->cols; //number of pixels in Image 1
  //create a loop to change each R,G,B value in each pixel
  float alpha1 = 1 - alpha;
  for(int j = 0; j < numpix2; j++){
    Image2->data[j].r = Image2->data[j].r * alpha1;
    Image2->data[j].g = Image2->data[j].g * alpha1;
    Image2->data[j].b = Image2->data[j].b * alpha1;

    /* *(Image2.data + j).r = *(Image2.data + j).r * alpha1;
    *(Image2.data + j).g = *(Image2.data + j).g * alpha1;
    *(Image2.data + j).b = *(Image2.data + j).b * alpha1;*/
  }
  //create output Image

  Image *output = (Image*) malloc(sizeof(Image));
  //create new dimensions for output image
  if(Image1->rows >= Image2->rows){
    output->rows = Image1->rows;
  }
  else{
    output->rows = Image2->rows;
  }

  if(Image1->cols >= Image2->cols){
    output->cols = Image1->cols;
  }
  else{
    output->cols = Image2->cols;
  }
  //create new data array based on new dimensions for output image
  output->data = (Pixel *) malloc( output->rows * output->cols * sizeof(Pixel));
  int cols1 = Image1->cols;
  //int rows1 = Image1->rows;
  int cols2 = Image2->cols;
  //int rows2 = Image2->rows;
  int ocols = output->cols;
  //int orows = output->rows;

  //case1
  if( (output->rows == Image1->rows) && (output->cols == Image1->cols)){
    for(int k = 0; k < Image2->rows; k++){
      for(int l = 0; l < Image2->cols; l++){
	//combine R values from image1 & image2 into output image
	output->data[k*cols2+1].r = Image1->data[k*cols2+1].r + Image2->data[k*cols2+1].r;
   
	 //combine g values from image1 & image2 into output image
        output->data[k*cols2+1].g = Image1->data[k*cols2+1].g + Image2->data[k*cols2+1].g;
  
	 //combine b values from image1 & image2 into output image
        output->data[k*cols2+1].b = Image1->data[k*cols2+1].b + Image2->data[k*cols2+1].b;
        //makes sure all b values are max 255


	/**(output.data + (k*(Image2->cols)+l)).r =  *(Image1.data + (k*(Image2->cols)+l)).r +  *(Image2.data + (k*(Image2->cols)+l)).r;
	//Make sure all the R values are good
	if (  *(output.data + (k*(Image2->cols)+l)).r > 255) {
	  *(output.data + (k*(Image2->cols)+l)).r = 255;
	}
	//combine G values from image1 & image2 into output image
        *(output.data + (k*(Image2->cols)+l)).g =  *(Image1.data + (k*(Image2->cols)+l)).g +  *(Image2.data + (k*(Image2->cols)+l)).g;
        //Make sure all the G values are good
        if (  *(output.data + (k*(Image2->cols)+l)).g > 255) {
          *(output.data + (k*(Image2->cols)+l)).g = 255;
        }
	//combine B values from image1 & image2 into output image
        *(output.data + (k*(Image2->cols)+l)).b =  *(Image1.data + (k*(Image2->cols)+l)).b +  *(Image2.data + (k*(Image2->cols)+l)).b;
        //Make sure all the B values are good
        if (  *(output.data + (k*(Image2->cols)+l)).b > 255) {
          *(output.data + (k*(Image2->cols)+l)).b = 255;
	  }*/
      }
      //makes sure all the data in the columns for the overlapping rows are equal to image1
      for(int m = Image2->cols; m < output->cols; m++){
	output->data[k*ocols+m].r = Image1->data[k*ocols+m].r;
	output->data[k*ocols+m].g = Image1->data[k*ocols+m].g;
        output->data[k*ocols+m].b = Image1->data[k*ocols+m].b;

	/**(output.data + (k*(output->cols)+m)).r =  *(Image1.data + (k*(output->cols)+m)).r;
	*(output.data + (k*(output->cols)+m)).g =  *(Image1.data + (k*(output->cols)+m)).g;
	*(output.data + (k*(output->cols)+m)).b =  *(Image1.data + (k*(output->cols)+m)).b;*/
      }
    }
    //making the rest of the output data equal to Image 1 data
    for(int n = Image2->rows; n < output->rows; n++){
      for(int o = Image2->cols; o < output->cols; o++){
	output->data[n*ocols+o].r = Image1->data[n*ocols+o].r;
        output->data[n*ocols+o].g = Image1->data[n*ocols+o].g;
        output->data[n*ocols+o].b = Image1->data[n*ocols+o].b;
	/**(output.data + (n*(output->cols)+o)).r =  *(Image1.data + (n*(output->cols)+o)).r;
        *(output.data + (n*(output->cols)+o)).g =  *(Image1.data + (n*(output->cols)+o)).g;
        *(output.data + (n*(output->cols)+o)).b =  *(Image1.data + (n*(output->cols)+o)).b;*/
      }
    }
  }

 //case2
  if( (output->rows == Image1->rows) && (output->cols == Image2->cols)){
    for(int k = 0; k < Image2->rows; k++){
      for(int l = 0; l < Image1->cols; l++){
	//combine R values from image1 & image2 into output image
        output->data[k*cols1+1].r = Image1->data[k*cols1+1].r + Image2->data[k*cols1+1].r;
         //combine g values from image1 & image2 into output image
        output->data[k*cols1+1].g = Image1->data[k*cols1+1].g + Image2->data[k*cols1+1].g;
         //combine b values from image1 & image2 into output image
        output->data[k*cols1+1].b = Image1->data[k*cols1+1].b + Image2->data[k*cols1+1].b;

        //combine R values from image1 & image2 into output image
	/*  *(output.data + (k*(Image1->cols)+l)).r =  *(Image1.data + (k*(Image1->cols)+l)).r +  *(Image2.data + (k*(Image1->cols)+l)).r;
        //Make sure all the R values are good
        if (  *(output.data + (k*(Image1->cols)+l)).r > 255) {
          *(output.data + (k*(Image1->cols)+l)).r = 255;
        }
        //combine G values from image1 & image2 into output image
        *(output.data + (k*(Image1->cols)+l)).g =  *(Image1.data + (k*(Image1->cols)+l)).g +  *(Image2.data + (k*(Image1->cols)+l)).g;
        //Make sure all the G values are good
        if (  *(output.data + (k*(Image1->cols)+l)).g > 255) {
          *(output.data + (k*(Image1->cols)+l)).g = 255;
        }
        //combine B values from image1 & image2 into output image
        *(output.data + (k*(Image1->cols)+l)).b =  *(Image1.data + (k*(Image1->cols)+l)).b +  *(Image2.data + (k*(Image1->cols)+l)).b;
        //Make sure all the B values are good
        if (  *(output.data + (k*(Image1->cols)+l)).b > 255) {
          *(output.data + (k*(Image1->cols)+l)).b = 255;
	  }*/
      }
       //makes sure all the data in the columns for the overlapping rows are equal to image2
      for(int m = Image1->cols; m < output->cols; m++){
	output->data[k*ocols+m].r = Image2->data[k*ocols+m].r;
        output->data[k*ocols+m].g = Image2->data[k*ocols+m].g;
        output->data[k*ocols+m].b = Image2->data[k*ocols+m].b;

        /**(output.data + (k*(output->cols)+m)).r =  *(Image2.data + (k*(output->cols)+m)).r;
        *(output.data + (k*(output->cols)+m)).g =  *(Image2.data + (k*(output->cols)+m)).g;
        *(output.data + (k*(output->cols)+m)).b =  *(Image2.data + (k*(output->cols)+m)).b;*/
      }
    }

     //making the rest of the rows in output data equal to Image 1 data
    for(int n = Image2->rows; n < output->rows; n++){
      for(int o = 0; o < Image1->cols; o++){
	output->data[n*cols1+o].r = Image1->data[n*cols1+o].r;
        output->data[n*cols1+o].g = Image1->data[n*cols1+o].g;
        output->data[n*cols1+o].b = Image1->data[n*cols1+o].b;

        /**(output.data + (n*(Image1->cols)+o)).r =  *(Image1.data + (n*(Image1->cols)+o)).r;
        *(output.data + (n*(Image1->cols)+o)).g =  *(Image1.data + (n*(Image1->cols)+o)).g;
        *(output.data + (n*(Image1->cols)+o)).b =  *(Image1.data + (n*(Image1->cols)+o)).b;*/
      }
      //makiing the rest of the cols in output data equal to Image 2 data
      for(int p = Image1->cols; p < output->cols; p++){
	output->data[n*ocols+p].r = Image2->data[n*ocols+p].r;
        output->data[n*ocols+p].g = Image2->data[n*ocols+p].g;
        output->data[n*ocols+p].b = Image2->data[n*ocols+p].b;
	
	/* *(output.data + (n*(output->cols)+p)).r =  *(Image2.data + (n*(output->cols)+p)).r;
        *(output.data + (n*(output->cols)+p)).g =  *(Image2.data + (n*(output->cols)+p)).g;
        *(output.data + (n*(output->cols)+p)).b =  *(Image2.data + (n*(output->cols)+p)).b;*/
      }
    }
        
  }

 //case3
  if( (output->rows == Image2->rows) && (output->cols == Image1->cols)){
    for(int k = 0; k < Image1->rows; k++){
      for(int l = 0; l < Image2->cols; l++){
	//combine R values from image1 & image2 into output image
        output->data[k*cols2+1].r = Image1->data[k*cols2+1].r + Image2->data[k*cols2+1].r;
         //combine g values from image1 & image2 into output image
        output->data[k*cols2+1].g = Image1->data[k*cols2+1].g + Image2->data[k*cols2+1].g;
         //combine b values from image1 & image2 into output image
        output->data[k*cols2+1].b = Image1->data[k*cols2+1].b + Image2->data[k*cols2+1].b;

        //combine R values from image1 & image2 into output image
        /**(output.data + (k*(Image2->cols)+l)).r =  *(Image1.data + (k*(Image2->cols)+l)).r +  *(Image2.data + (k*(Image2->cols)+l)).r;
        //Make sure all the R values are good
        if (  *(output.data + (k*(Image2->cols)+l)).r > 255) {
          *(output.data + (k*(Image2->cols)+l)).r = 255;
        }
        //combine G values from image1 & image2 into output image
        *(output.data + (k*(Image2->cols)+l)).g =  *(Image1.data + (k*(Image2->cols)+l)).g +  *(Image2.data + (k*(Image2->cols)+l)).g;
        //Make sure all the G values are good
        if (  *(output.data + (k*(Image2->cols)+l)).g > 255) {
          *(output.data + (k*(Image2->cols)+l)).g = 255;
        }
        //combine B values from image1 & image2 into output image
        *(output.data + (k*(Image2->cols)+l)).b =  *(Image1.data + (k*(Image2->cols)+l)).b +  *(Image2.data + (k*(Image2->cols)+l)).b;
        //Make sure all the B values are good
        if (  *(output.data + (k*(Image2->cols)+l)).b > 255) {
          *(output.data + (k*(Image2->cols)+l)).b = 255;
	  }*/
      }
       //makes sure all the data in the columns for the overlapping rows are equal to image1
      for(int m = Image2->cols; m < output->cols; m++){
	output->data[k*ocols+m].r = Image1->data[k*ocols+m].r;
        output->data[k*ocols+m].g = Image1->data[k*ocols+m].g;
        output->data[k*ocols+m].b = Image1->data[k*ocols+m].b;

        /**(output.data + (k*(output->cols)+m)).r =  *(Image1.data + (k*(output->cols)+m)).r;
        *(output.data + (k*(output->cols)+m)).g =  *(Image1.data + (k*(output->cols)+m)).g;
        *(output.data + (k*(output->cols)+m)).b =  *(Image1.data + (k*(output->cols)+m)).b;*/
      }
    }

     //making the rest of the rows in output data equal to Image 2 data
    for(int n = Image1->rows; n < output->rows; n++){
      for(int o = 0; o < Image2->cols; o++){
	output->data[n*cols2+o].r = Image2->data[n*cols2+o].r;
        output->data[n*cols2+o].g = Image2->data[n*cols2+o].g;
        output->data[n*cols2+o].b = Image2->data[n*cols2+o].b;

        /**(output.data + (n*(Image1->cols)+o)).r =  *(Image2.data + (n*(Image1->cols)+o)).r;
        *(output.data + (n*(Image1->cols)+o)).g =  *(Image2.data + (n*(Image1->cols)+o)).g;
        *(output.data + (n*(Image1->cols)+o)).b =  *(Image2.data + (n*(Image1->cols)+o)).b;*/
      }
      //makiing the rest of the cols in output data equal to Image 1 data
      for(int p = Image2->cols; p < output->cols; p++){
	output->data[n*ocols+p].r = Image1->data[n*ocols+p].r;
        output->data[n*ocols+p].g = Image1->data[n*ocols+p].g;
        output->data[n*ocols+p].b = Image1->data[n*ocols+p].b;

        /**(output.data + (n*(output->cols)+p)).r =  *(Image1.data + (n*(output->cols)+p)).r;
        *(output.data + (n*(output->cols)+p)).g =  *(Image1.data + (n*(output->cols)+p)).g;
        *(output.data + (n*(output->cols)+p)).b =  *(Image1.data + (n*(output->cols)+p)).b;*/
      }
    }

  }

 //case4
  if( (output->rows == Image2->rows) && (output->cols == Image2->cols)){
    for(int k = 0; k < Image1->rows; k++){
      for(int l = 0; l < Image1->cols; l++){
	//combine R values from image1 & image2 into output image
        output->data[k*cols1+1].r = Image1->data[k*cols1+1].r + Image2->data[k*cols1+1].r;
         //combine g values from image1 & image2 into output image
        output->data[k*cols1+1].g = Image1->data[k*cols1+1].g + Image2->data[k*cols1+1].g;
         //combine b values from image1 & image2 into output image
        output->data[k*cols1+1].b = Image1->data[k*cols1+1].b + Image2->data[k*cols1+1].b;
        //makes sure all b values are max 255

        //combine R values from image1 & image2 into output image
	/* *(output.data + (k*(Image1->cols)+l)).r =  *(Image1.data + (k*(Image1->cols)+l)).r +  *(Image2.data + (k*(Image1->cols)+l)).r;
        //Make sure all the R values are good
        if (  *(output.data + (k*(Image1->cols)+l)).r > 255) {
          *(output.data + (k*(Image1->cols)+l)).r = 255;
        }
        //combine G values from image1 & image2 into output image
        *(output.data + (k*(Image1->cols)+l)).g =  *(Image1.data + (k*(Image1->cols)+l)).g +  *(Image2.data + (k*(Image1->cols)+l)).g;
        //Make sure all the G values are good
        if (  *(output.data + (k*(Image1->cols)+l)).g > 255) {
          *(output.data + (k*(Image1->cols)+l)).g = 255;
        }
        //combine B values from image1 & image2 into output image
        *(output.data + (k*(Image1->cols)+l)).b =  *(Image1.data + (k*(Image1->cols)+l)).b +  *(Image2.data + (k*(Image1->cols)+l)).b;
        //Make sure all the B values are good
        if (  *(output.data + (k*(Image1->cols)+l)).b > 255) {
          *(output.data + (k*(Image1->cols)+l)).b = 255;
	  }*/
      }
      //makes sure all the data in the columns for the overlapping rows are equal to image2
      for(int m = Image1->cols; m < output->cols; m++){
	output->data[k*ocols+m].r = Image2->data[k*ocols+m].r;
        output->data[k*ocols+m].g = Image2->data[k*ocols+m].g;
        output->data[k*ocols+m].b = Image2->data[k*ocols+m].b;

	/* *(output.data + (k*(output->cols)+m)).r =  *(Image2.data + (k*(output->cols)+m)).r;
        *(output.data + (k*(output->cols)+m)).g =  *(Image2.data + (k*(output->cols)+m)).g;
        *(output.data + (k*(output->cols)+m)).b =  *(Image2.data + (k*(output->cols)+m)).b;*/
      }
    }
     //making the rest of the output data equal to Image 2 data
    for(int n = Image1->rows; n < output->rows; n++){
      for(int o = Image1->cols; o < output->cols; o++){
	output->data[n*ocols+o].r = Image2->data[n*ocols+o].r;
        output->data[n*ocols+o].g = Image2->data[n*ocols+o].g;
        output->data[n*ocols+o].b = Image2->data[n*ocols+o].b;

	/* *(output.data + (n*(output->cols)+o)).r =  *(Image2.data + (n*(output->cols)+o)).r;
        *(output.data + (n*(output->cols)+o)).g =  *(Image2.data + (n*(output->cols)+o)).g;
        *(output.data + (n*(output->cols)+o)).b =  *(Image2.data + (n*(output->cols)+o)).b;*/
      }
    }
  }
  return output;
}


 
  
   

