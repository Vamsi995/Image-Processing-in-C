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
    
    int red;
    int green;
    int blue;

} PIXEL;



typedef struct matrix
{

    PIXEL **image;

} MATRIX;




int main(int argc, char *argv[])
{

    // PPMHEADER *space = (PPMHEADER *)malloc(sizeof(PPMHEADER));

    char space[100];

    char *filename = argv[1];

    FILE *file = fopen(filename, "rb");

    // for(int i=0;i<14;i++){

    int i = 0;

    char *fileFormat = fgets(space, 3, file);

    if (strcmp(fileFormat, "P6") == 0)
    {

        // while (fgets(space, 100, file))
        // {

        //     if (i == 1)
        //     {
        //         break;
        //     }

        //     printf("%s", space);
        //     i++;
        // }

        // printf("%s", space);
        printf("Yes");
    }

    else
    {
        printf("Error: Not a ppm format file");
    }
}
