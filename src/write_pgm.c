#include "PGM.h"
void write_to_pgm(int *image, char *image_name, int height, int width)
{
    FILE *pgmimg;
    pgmimg = fopen(image_name, "wb");
    if (!pgmimg)
    {
        printf("ERROR: Unable to create file %s\n", image_name);
        return;
    }
    printf("-------------------******---------------------");
    // Writing Magic Number P2 to represent PGM Images.
    printf("File Creating Initalized\n");
    printf("File Format [P2]\n");
    fprintf(pgmimg, "P2\n");
    // Writing width and height of images.
    printf("Image Height[%d]\nImage Width[%d]\n",height,width);
    fprintf(pgmimg, "%d %d\n",height,width);
    // Writing the maximum gray value
    printf("Maximum Gray Value [255]\n");
    fprintf(pgmimg, "255\n");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int temp = *((image + i * width) + j);
            fprintf(pgmimg, "%d ", temp);
        }
    }
    fclose(pgmimg);
}
