#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "IO.h"



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
                fprintf(fp, "%d %d %d ", (int)round(image->data[v][h].red), (int)round(image->data[v][h].green), (int)round(image->data[v][h].blue));
            }
            fprintf(fp, "\n");
        }

        if (fwrite("\n", sizeof(char), 1, fp) == 1)
            error = 0;
        fclose(fp);
    }

    return;
}


void readHeader(IMAGE *image, FILE *file)
{

     //Memory allocation size
    char space[100]; 

    int height;
    int width;
    int maxColor;
    char one,two;
    char *fileFormat = NULL;

     // Header check to see if its ppm
    if (fgets(space, 4, file) != NULL)
    {
        fileFormat = space;
        fileFormat[strlen(space) - 1] = '\0';
    }

    // Raw Version
    // if ppm  -> then this
    if (strcmp(fileFormat, "P3") == 0)
    {

        int flag = 0;
        
        // Reads the header thorough a while loop to be future ready
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

            sscanf(space, "%d%c%d%c%d", &width, &one, &height, &two, &maxColor);

            if (two == '\n')
            {
                flag = 1;
                continue;
            }
            else
            {
                break;
            }
        }

        // Width of the image X Height of the Image X  Maximum color balance
        // printf("%d %d %d\n", width, height, maxColor);
        image->height = height;
        image->width = width;
        image->maxColor = maxColor;
    }

    else
    {
        printf("Error: Not a ppm format file");
    }


}


void readImage(IMAGE *image, FILE *file)
{

    readHeader(image,file);

    int height = image->height;
    int width = image->width;
    int maxColor = image->maxColor;

    image->data = (PIXEL **)malloc(height * sizeof(PIXEL *));

    float red;
    float green;
    float blue;

    for (int i = 0; i < height; i++)
    {
        image->data[i] = (PIXEL *)malloc(width * sizeof(PIXEL));
        for (int j = 0; j < width; j++) // Important bug fix here!
        {
            fscanf(file, "%f %f %f", &red, &green, &blue);
            image->data[i][j].red = red;
            image->data[i][j].green = green;
            image->data[i][j].blue = blue;
        }
    }


    fclose(file);


}


void print_exit(char *message)
{

    printf("Error: %s\n", message);
    exit(1);

}
