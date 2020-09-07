
typedef struct rgb
{

    float red;
    float green;
    float blue;

} PIXEL;

typedef struct matrix
{
    int height;
    int width;
    int maxColor;
    PIXEL **data;

} IMAGE;

typedef IMAGE **MATRIX;

