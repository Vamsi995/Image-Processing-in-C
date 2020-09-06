#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct header
{

    char formatType[2];
    int rows;
    int columns;
    int maxColorValue;

} PPMHEADER;

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
    PIXEL **image;

} IMAGE;

typedef IMAGE *MATRIX;


int sub(MATRIX P, MATRIX A, MATRIX B);
int dotproduct(MATRIX P, MATRIX A, MATRIX B);
int addition(MATRIX P, MATRIX A, MATRIX B);




void write(int width, int height, MATRIX image)
{
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
                fprintf(fp, "%hu %hu %hu ", image->image[v][h].red, image->image[v][h].green, image->image[v][h].blue);
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

            if (maxColor == 0)
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
    image->image = (PIXEL **)malloc(height * sizeof(PIXEL));

    unsigned short red;
    unsigned short green;
    unsigned short blue;

    for (int i = 0; i < height; i++)
    {
        image->image[i] = (PIXEL *)malloc(width * sizeof(PIXEL));
        for (int j = 0; j < width; j++) // Important bug fix here!
        {
            fscanf(file, "%hu %hu %hu", &red, &green, &blue);
            image->image[i][j].red = red;
            image->image[i][j].green = green;
            image->image[i][j].blue = blue;
        }
    }

    fclose(file);
    
    IMAGE * grayed = RGBtoGray(image);
    IMAGE * mirrored = mirror(grayed);

    write(width,height,mirrored);
    

}



int dotproduct(MATRIX P, MATRIX A, MATRIX B)
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




