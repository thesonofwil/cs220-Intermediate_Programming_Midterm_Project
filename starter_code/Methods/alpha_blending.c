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
  numpix1 = Image1->rows * Image1->cols; //number of pixels in Image 1
  //create a loop to change each R,G,B value in each pixel
  float alpha1 = 1 - alpha;
  for(int i = 0; i < numpix1; i++){
    *(Image2.data + i).r = *(Image2.data + i).r * alpha1;
    *(Image2.data + i).g = *(Image2.data + i).g * alpha1;
    *(Image2.data + i).b = *(Image2.data + i).b * alpha1;
  }
