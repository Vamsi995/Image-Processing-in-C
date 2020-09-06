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

typedef IMAGE *MATRIX;



int sub(MATRIX P, MATRIX A, MATRIX B);
int matrixmul(MATRIX P, MATRIX A, MATRIX B);
int addition(MATRIX P, MATRIX A, MATRIX B);
int flatten(MATRIX P, MATRIX A);
