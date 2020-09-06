#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "transformation.h"


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

    //Memory allocation size
    char space[100]; 

    // Reading the picture file as input
    FILE *file = fopen(argv[1], "r");

    int height;
    int width;
    int maxColor;
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

        // Width of the image X Height of the Image X  Maximum color balance
        printf("%d %d %d\n", width, height, maxColor);
    }

    else
    {
        printf("Error: Not a ppm format file");
    }


    // Image allocation
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
    MATRIX grayed = mirror(&image);
    // MATRIX mirrored = mirror(&image);
    // MATRIX edge = mirror(&image);

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
