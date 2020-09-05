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

//mirroring the image in horizontal direction
IMAGE * mirror(IMAGE * image){
	int i;
	int j;
	int h = image.height;
	int w = image.width;
	IMAGE * resut = createImage(h,w,image.maxColor);
	IMAGE * temp = createImage(w,w,image.maxColor);
	for(i=0 ; i<w ; i = i+1){
		for(j=0; j<w ; j = j+1){
			if( (i*w) + (j*h) == w*h ){
				temp.red = 1;
			}
			else{
				temp.red = 0;
			}
		}
	}
	IMAGE* result = matrixmul(image, temp);
	return result;
}