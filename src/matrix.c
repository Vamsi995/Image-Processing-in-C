#include "matrix.h"
#include <stdio.h>

int flatten(MATRIX P, MATRIX A)
{



    unsigned short r;
    int m = P->maxColor;

    printf("%d",P->width);
    printf("%d",P->height);

    for (int i = 0; i < 540; i++)
    {

        for (int j = 0; j < 720; j++)
        {


            r = A->image[i][j].red + A->image[i][j].green + A->image[i][j].blue; 
            
            r = (r>m)?m:r;
            //  r = 1;
            // printf("%hu %hu %hu\n",P->image[i][j].red, P->image[i][j].green, P->image[i][j].blue);
            P->image[i][j].red = r;
            P->image[i][j].green = r;
            P->image[i][j].blue = r;
        }
    }

    // P->image[0][0].red = 1;
    // P->image[0][0].green = 1;
    // P->image[0][0].blue = 1;

    return 0;



}



int matrixmul(MATRIX P, MATRIX A, MATRIX B)
{
     if(A->height != B->height || A->width != B->width)
    {
        return 1;
    }


    P->height = A->height;
    P->width = A->width;
    P->maxColor = A->maxColor;

    unsigned short r,g,b;
    int m = A->maxColor;

    for (int i = 0; i < A->height; i++)
    {

        for (int j = 0; j < A->width; j++)
        {


               r = A->image[i][j].red * B->image[i][j].red; 
             g = A->image[i][j].green * B->image[i][j].green;
            b = A->image[i][j].blue * B->image[i][j].blue;

                r = (r>m)?m:r;
                g = (g>m)?m:g;
                b = (b>m)?m:b;


            P->image[i][j].red = r;
            P->image[i][j].green = g;
            P->image[i][j].blue = b;
        }
    }

    return 0;

}



int sub(MATRIX P, MATRIX A, MATRIX B)
{
     if(A->height != B->height || A->width != B->width)
    {
        return 1;
    }


    P->height = A->height;
    P->width = A->width;
    P->maxColor = A->maxColor;

    unsigned short r,g,b;
    int m = A->maxColor;

    for (int i = 0; i < A->height; i++)
    {

        for (int j = 0; j < A->width; j++)
        {


               r = A->image[i][j].red - B->image[i][j].red; 
             g = A->image[i][j].green - B->image[i][j].green;
            b = A->image[i][j].blue - B->image[i][j].blue;

                r = (r>m)?m:r;
                g = (g>m)?m:g;
                b = (b>m)?m:b;


            P->image[i][j].red = r;
            P->image[i][j].green = g;
            P->image[i][j].blue = b;
        }
    }

    return 0;

}



