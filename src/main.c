#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "matrix.h"

typedef struct rgb
{

    unsigned short red;
    unsigned short green;
    unsigned short blue;

} PIXEL;

typedef struct matrix
{
    int height;
    int width;
    int maxColor;
    PIXEL **data;

} IMAGE;

typedef IMAGE **MATRIX;



int sub(MATRIX P, MATRIX A, MATRIX B);
int matrixmul(MATRIX P, MATRIX A, MATRIX B);
int addition(MATRIX P, MATRIX A, MATRIX B);
int flatten(MATRIX P);








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
	// // MATRIX temp = createImage(h,w,image->maxColor);
	// MATRIX temp = createImage(h,w,image->maxColor);
    // IMAGE *oneByThree = *(temp);

    unsigned short result;
	// printf("%p\n",image);
    int s = flatten(&image);

    MATRIX temp = createImage(h,w,m);
    IMAGE *oneByThree = *(temp);


	for(int i=0 ; i<h ; i = i+1){
		for(int j=0; j<w ; j = j+1){
			// if(i == j){
				oneByThree->data[i][j].red = 1/3;
				oneByThree->data[i][j].green = 1/3;
				oneByThree->data[i][j].blue = 1/3;
			// }
			// else{
				// oneByThree->data[i][j].red = 0;
				// oneByThree->data[i][j].green = 0;
				// oneByThree->data[i][j].blue = 0;
			// }
		}
	}

	int success = matrixmul(&image, &image, &oneByThree); //expecting this function to already exist

    if(success == 0)
    {
	    return Pimage;
    }

}



void write(int width, int height, MATRIX Pimage)
{

    IMAGE *image = *(Pimage);
    FILE *fp = fopen("level.ppm", "wb");

    int error = 1;
    if (fp != NULL)
    {
        fprintf(fp, "P3\n");
        fprintf(fp, "%d %d\n", width, height);
        fprintf(fp, "%d\n", 255);

        for (int v = 0; v < height; v++)
        {
            for (int h = 0; h < width; h++)
            {
                fprintf(fp, "%hu %hu %hu ", image->data[v][h].red, image->data[v][h].green, image->data[v][h].blue);
            }
            fprintf(fp, "\n");
        }

        if (fwrite("\n", sizeof(char), 1, fp) == 1)
            error = 0;
        fclose(fp);
    }

    return;
}

int main(int argc, char *argv[])
{

    char space[100];

    FILE *file = fopen(argv[1], "r");

    int height;
    int width;
    int maxColor;
    char *fileFormat = NULL;

    if (fgets(space, 4, file) != NULL)
    {
        fileFormat = space;
        fileFormat[strlen(space) - 1] = '\0';
    }

    // Raw Version

    if (strcmp(fileFormat, "P3") == 0)
    {

        int flag = 0;

        while (fgets(space, 100, file) != NULL)
        {
            if (space[0] == '#')
            {
                continue;
            }
            if (flag == 1)
            {
                sscanf(space, "%d", &maxColor);
                break;
            }

            sscanf(space, "%d %d %d", &width, &height, &maxColor);

            if (maxColor == 0 || abs(maxColor) > 63575)
            {
                flag = 1;
                continue;
            }
            else
            {
                break;
            }
        }

        printf("%d %d %d\n", width, height, maxColor);
    }

    else
    {
        printf("Error: Not a ppm format file");
    }

    IMAGE *image = (IMAGE *)malloc(sizeof(IMAGE));

    image->height = height;
    image->width = width;
    image->maxColor = maxColor;
    image->data = (PIXEL **)malloc(height * sizeof(PIXEL *));

    unsigned short red;
    unsigned short green;
    unsigned short blue;

    for (int i = 0; i < height; i++)
    {
        image->data[i] = (PIXEL *)malloc(width * sizeof(PIXEL));
        for (int j = 0; j < width; j++) // Important bug fix here!
        {
            fscanf(file, "%hu %hu %hu", &red, &green, &blue);
            image->data[i][j].red = red;
            image->data[i][j].green = green;
            image->data[i][j].blue = blue;
        }
    }

    fclose(file);

    // printf("%p\n", image);
    // write(width,height,&temp);    
    MATRIX grayed = RGBtoGray(&image);
    // MATRIX mirrored = mirror(grayed);

    // unsigned short result;

    //  for (int i = 0; i < height; i++)
    // {

    //     for (int j = 0; j < width; j++)
    //     {


    //         result = image->data[i][j].red + image->data[i][j].green + image->data[i][j].blue; 
            
    //         image->data[i][j].red = result;
    //         image->data[i][j].green = result;
    //         image->data[i][j].blue = result;
    //     }
    // }

    write(width,height,grayed);


}


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

            P->data[i][j].red = r;
            P->data[i][j].green = r;
            P->data[i][j].blue = r;
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



