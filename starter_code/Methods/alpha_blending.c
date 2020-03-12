//Anire Egbe & Wilson
//aegbe2
//alpha_blending.c function

void alpha_blending(Image *Image1, Image *Image2, float alpha){
  // check to make sure inputs are valid
  if( Image1 == NULL || Image2 == NULL || ratio == NULL){
    printf("Incorrect number of arguments\n");
    return 5;
  }
  //check if alpha is in range
  float a = 0; //creates a float value = 0.0
  float b = 1; //creates a float value = 1.0
  if(alpha <= a || alpha >= b){
    printf("Ratio value is out of range\n");
    return 6;
  }
  // Changing Image 1 by alpha
  numpix1 = Image1->rows * Image1->cols; //number of pixels in Image 1
  //create a loop to change each R,G,B value in each pixel
  for(int i = 0; i < numpix1; i++){
    *(Image1.data + i).r = *(Image1.data + i).r * alpha;
    *(Image1.data + i).g = *(Image1.data + i).g * alpha;
    *(Image1.data + i).b = *(Image1.data + i).b * alpha;
  }
  // Changing Image 2 by 1 - alpha
  numpix2 = Image2->rows * Image2->cols; //number of pixels in Image 1
  //create a loop to change each R,G,B value in each pixel
  float alpha1 = 1 - alpha;
  for(int j = 0; i < numpix2; i++){
    *(Image2.data + j).r = *(Image2.data + j).r * alpha1;
    *(Image2.data + j).g = *(Image2.data + j).g * alpha1;
    *(Image2.data + j).b = *(Image2.data + j).b * alpha1;
  }
  //create output Image

  Image *output = (Image*) malloc(sizeof(Image));
  //adds all the Image2 data to Image1
  if(Image1.rows >= Image2.rows){
    for(int k = 0; k < Image2.rows){
      *(Image1.data + k).r = *(Image1.data + k).r + *(Image2.data + k).r;
      //make sure max values for R is 255
      if( *(Image1.data + k).r > 255){
	*(Image1.data + k).r = 255;
      }
      *(Image1.data + k).g = *(Image1.data + k).g + *(Image2.data + k).g;
      //make sure max value for G is 255
      if( *(Image1.data + k).g > 255){
        *(Image1.data + k).g = 255;
      }
      *(Image1.data + k).b = *(Image1.data + k).b + *(Image2.data + k).b;
      //make sue max value for B is 255
      if( *(Image1.data + k).b > 255){
        *(Image1.data + k).b = 255;
      }
    } 
    else {
      for(int l = 0; l < Image1.rows){
        *(Image2.data + l).r = *(Image2.data + l).r + *(Image1.data + l).r;
        //make sue max value for R is 255
        if( *(Image2.data + l).r > 255){
          *(Image2.data + l).r = 255;
        }
        *(Image2.data + l).g = *(Image2.data + l).g + *(Image1.data + l).g;
        //make sue max value for G  is 255
        if( *(Image2.data + l).g > 255){
          *(Image2.data + l).g = 255;
        }
        *(Image2.data + l).b = *(Image2.data + l).b + *(Image1.data + l).b;
        //make sue max value for B is 255
        if( *(Image2.data + k).b > 255){
        *(Image2.data + k).b = 255;
        }
      }
    }//ends else statment
  }//ends if statement
   

