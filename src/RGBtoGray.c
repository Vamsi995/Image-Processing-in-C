#include<stdio.h>


IMAGE* createImage(int height, int width, int maxColor){
	IMAGE *image = (IMAGE *)malloc(sizeof(IMAGE));
    image->height = height;
    image->width = width;
    image->maxColor = maxColor; 
    image->image = (PIXEL **)malloc(height * sizeof(PIXEL));
    int i; 
    for(i=0; i<width; i = i+1){
    	image->image[i] = (PIXEL *)malloc(width * sizeof(PIXEL));
    }
    return image;
}


IMAGE* RGBtoGray(IMAGE* image){
	int i;
	int j;
	int h = image.height;
	int w = image.width;
	IMAGE * temp = createImage(h,w,image.maxColor);
	IMAGE * oneByThree = createImage(w,w,image.maxColor);

	for(i=0; i< h ; i=i+1){
		for(j=0; j < w; j=j+1){
			temp[i][j]->red=image->image[i][j].red + image->image[i][j].green + image->image[i][j].blue; 
		}
	}
	
	for(i=0 ; i<w ; i = i+1){
		for(j=0; j<w ; j = j+1){
			if(i == j){
				oneByThree[i][j].red = 1/3;
			}
			else{
				oneByThree[i][j].red = 0;
			}
		}
	}
	IMAGE* GrayScaled = matrixmul(temp, oneByThree); //expecting this function to already exist

	return GrayScaled;
}