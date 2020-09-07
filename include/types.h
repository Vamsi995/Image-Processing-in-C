
typedef struct rgb
{

    // unsigned short red;
    // unsigned short green;
    // unsigned short blue;
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

