#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "matrix.h"
#include "transformation.h"
#include "IO.h"


int main(int argc, char *argv[])
{

    // Reading the picture file as input
    FILE *file = fopen(argv[1], "r");

    if(file == NULL)
    {
        print_exit("File not found\n Please keep your input.ppm file in Images/input.ppm");
    }

    // Image allocation
    IMAGE *image = (IMAGE *)malloc(sizeof(IMAGE));
    if(image == NULL)
    {
        print_exit("Unable to allocate space for the image");
    }

    //Reading the image file
    readImage(image,file);

    //Abstracting out height,width,maxcolor of the image
    int height = image->height;
    int width = image->width;
    int maxColor = image->maxColor;

    //Makefile target runs
    if(strcmp(argv[3],"T1") == 0)
    {

        MATRIX grayed = RGBtoGray(&image);
        write(width,height,grayed,argv[2]);
        // free(*(grayed)); 

    }
    else if(strcmp(argv[3],"T2") == 0)
    {

        MATRIX q = createImage(height,width,maxColor);
        IMAGE *temp2 = *(q);

        MATRIX mirrored = mirror(&image,&temp2);
        write(width,height,mirrored,argv[2]);
        // free(temp2);
    //   for (int i = 0; i < height-1; i++){
    //          if(temp2->data[i] != NULL)  
    //             free(temp2->data[i]);  
    // }     


    }
    else if(strcmp(argv[3],"run") == 0 || strcmp(argv[3],"test") == 0)
    {

        MATRIX q1 = createImage(height,width,maxColor);
        IMAGE *temp1 = *(q1);
        
        MATRIX grayed = RGBtoGray(&image);
        MATRIX mirrored = mirror(grayed,&temp1);
        write(width,height,mirrored,argv[2]);
        // free(temp1);


    }
    else
    {
        print_exit("Unrecognized command");
    }

    //  for (int i = 0; i < height-1; i++){
    //          if(image->data[i] != NULL)  
    //             free(image->data[i]);  
    // }     
    // free(image);
 
}
