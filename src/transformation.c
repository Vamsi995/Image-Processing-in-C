#include "matrix.h"
#include <math.h>
#include <stdlib.h>


MATRIX createImage(int height, int width, int maxColor){
	
    IMAGE *test = (IMAGE *)malloc(sizeof(IMAGE));
    MATRIX q = &test;

    test->height = height;
    test->width = width;
    test->maxColor = maxColor; 
    test->data = (PIXEL **)malloc(height * sizeof(PIXEL *));
    int i; 
    for(i=0; i<width; i = i+1){
    	test->data[i] = (PIXEL *)malloc(width * sizeof(PIXEL));
    }

    return q;
}

MATRIX RGBtoGray(MATRIX Pimage){

    IMAGE *image = *(Pimage);
	int h = image->height;
	int w = image->width;
    int m = image->maxColor;

    unsigned short result;
    int s = flatten(&image);

    MATRIX temp = createImage(h,w,m);
    IMAGE *oneByThree = *(temp);

	for(int i=0 ; i<h ; i = i+1){
		for(int j=0; j<w ; j = j+1){
				oneByThree->data[i][j].red = 2;
				oneByThree->data[i][j].green = 2; 
				oneByThree->data[i][j].blue = 2;
                // printf("%hu",oneByThree->data[i][j].red);
		}
	}
    
	int success = matrixmul(&image, &image, &oneByThree); //expecting this function to already exist

    free(oneByThree);

    if(success == 0)
    {
	    return Pimage;
    }

}

MATRIX mirror(MATRIX Pimage){

    IMAGE *image = *(Pimage);
	int h = image->height;
	int w = image->width;
    int m = image->maxColor;

    int k = h;

    // MATRIX q1 = createImage(h,w,m);
    // IMAGE *tempo = *(q1);


    MATRIX q = createImage(h,h,m);
    IMAGE *temp = *(q);

	for(int i=0 ; i<h ; i = i+1){
		for(int j=0; j<h ; j = j+1){
		
        	if(i + j == h-1){  
				temp->data[i][j].red = 1;
				temp->data[i][j].green = 1;
				temp->data[i][j].blue = 1;
			}
			else{
				temp->data[i][j].red = 0;
				temp->data[i][j].green = 0;
				temp->data[i][j].blue = 0;
			
			}
		}
	}


	int success = matrixMul(&image, &temp, &image); //expecting this function to already exist

    if(success == 0)
    {
	    return Pimage;
    }
}

MATRIX edgeDetection(MATRIX Pimage) {

    IMAGE *image = *(Pimage);
	int h = image->height;
	int w = image->width;
    int m = image->maxColor;
     
     int Gx[3][3] = {
        
        {-1,0,1},
        {-2,0,2},
        {-1,0,1}
    };
    
    int Gy[3][3] = {
        
        {-1,-2,-1},
        {0,0,0},
        {1,2,1}
    };
    
    
    MATRIX q = createImage(h,w,m);
    IMAGE *temp = *(q);
    
    
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            temp->data[i][j].red = image->data[i][j].red;
            temp->data[i][j].green = image->data[i][j].green;
            temp->data[i][j].blue = image->data[i][j].blue;
        }
    }
    
    for(int i=0;i<h;i++){

        for(int j=0;j<w;j++){
            
            int Gch = 1;

            float sum_weightRx = 0;
            float sum_weightGx = 0;
            float sum_weightBx = 0;
            
            float sum_weightRy = 0;
            float sum_weightGy = 0;
            float sum_weightBy = 0;
            
            
            for(int k=-1;k<2;k++){
                
                
                for(int l = -1;l<2;l++){
                    
                    if(i+k < 0){
                        break;
                        
                    }
                    else if(i+k>=h){
                        break;
                    }
                    
                    else{
                        
                        if(j+l < 0){
                            
                            continue;
                        }
                        
                        else if(j+l>=w){
                            continue;
                        }
                        else{
                            
                        
                        sum_weightRx += temp->data[i+k][j+l].red * Gx[Gch+k][Gch+l];
                        sum_weightGx += temp->data[i+k][j+l].green * Gx[Gch+k][Gch+l];
                        sum_weightBx += temp->data[i+k][j+l].blue * Gx[Gch+k][Gch+l];
                        
                        sum_weightRy += temp->data[i+k][j+l].red * Gy[Gch+k][Gch+l];
                        sum_weightGy += temp->data[i+k][j+l].green * Gy[Gch+k][Gch+l];
                        sum_weightBy += temp->data[i+k][j+l].blue * Gy[Gch+k][Gch+l];
                            
                            
                        }
                        
                        
                        
                    }
                    
                }
                
            }
            
                unsigned short r = round(sqrt(pow(sum_weightRx,2) + pow(sum_weightRy,2)));
                unsigned short g = round(sqrt(pow(sum_weightGx,2) + pow(sum_weightGy,2)));
                unsigned short b = round(sqrt(pow(sum_weightBx,2) + pow(sum_weightBy,2)));
                
                r = (r>m)?m:r;
                g = (g>m)?m:g;
                b = (b>m)?m:b;
                  
                image->data[i][j].red = r;
                image->data[i][j].blue = b;
                image->data[i][j].green = g;
            
        }
        
        
    }
    
    return Pimage;

}


