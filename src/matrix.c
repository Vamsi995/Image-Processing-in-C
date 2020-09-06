#include "matrix.h"
#include <stdio.h>


int flatten(MATRIX p)
{

    IMAGE *P = *(p);

    printf("%p\n",P);

    unsigned short r;
    int m = P->maxColor;

    // printf("%d\n",P->height);

    for (int i = 0; i < P->height; i++)
    {

        for (int j = 0; j < P->width; j++)
        {


            r = P->data[i][j].red + P->data[i][j].green + P->data[i][j].blue; 
            
            r = (r>m)?m:r;

            P->data[i][j].red = r/3;
            P->data[i][j].green = r/3;
            P->data[i][j].blue = r/3;
        }
    }


    return 0;



}



int matrixmul(MATRIX p, MATRIX x, MATRIX y)
{

    IMAGE *P = *(p);
    IMAGE *A = *(x);
    IMAGE *B = *(y);

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


               r = A->data[i][j].red * B->data[i][j].red; 
             g = A->data[i][j].green * B->data[i][j].green;
            b = A->data[i][j].blue * B->data[i][j].blue;

                r = (r>m)?m:r;
                g = (g>m)?m:g;
                b = (b>m)?m:b;


            P->data[i][j].red = r;
            P->data[i][j].green = g;
            P->data[i][j].blue = b;
        }
    }

    return 0;

}



int sub(MATRIX p, MATRIX x, MATRIX y)
{


    IMAGE *P = *(p);
    IMAGE *A = *(x);
    IMAGE *B = *(y);




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


               r = A->data[i][j].red - B->data[i][j].red; 
             g = A->data[i][j].green - B->data[i][j].green;
            b = A->data[i][j].blue - B->data[i][j].blue;

                r = (r>m)?m:r;
                g = (g>m)?m:g;
                b = (b>m)?m:b;


            P->data[i][j].red = r;
            P->data[i][j].green = g;
            P->data[i][j].blue = b;
        }
    }

    return 0;

}



int matrixMul(MATRIX p, MATRIX x, MATRIX y) {

    IMAGE *P = *(p);
    IMAGE *A = *(x);
    IMAGE *B = *(y);


    // if(A->height != B->height || A->width != B->width)
    // {
    //     return 1;
    // }


    P->height = A->height;
    P->width = B->width;
    P->maxColor = B->maxColor;

    printf("%d %d - %d %d\n",A->height,A->width, B->height,B->width);


    for (int i = 0; i < A->height; ++i) {
      for (int j = 0; j < B->width; ++j) {
         for (int k = 0; k < A->width; ++k) {
            P->data[i][j].red += A->data[i][k].red * B->data[k][j].red;
            P->data[i][j].green += A->data[i][k].green * B->data[k][j].green;
            P->data[i][j].blue += A->data[i][k].blue * B->data[k][j].blue;
         }
      }
   }


    return 0;

}

