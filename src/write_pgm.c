#include "PGM.h"
void write_to_pgm(int *image, char *image_name, int height, int width)
{
    /*Function to write a memory block containing the grayscale numeric values into a pgm file.
    Params: image [int pointer - to memory block]
            image_name [char pointer - to image name]
            height [int - height of image]
            width [int - width of image]*/
    FILE *pgmimg;
    pgmimg = fopen(image_name, "wb");
    if (!pgmimg)
    {
        printf("ERROR: Unable to create file %s\n", image_name);
        return;
    }
    printf("----------------------------------------------\n");
    // Writing Magic Number P2 to represent PGM Images.
    printf("File Creating Initalized\n");
    printf("File Format [P2]\n");
    fprintf(pgmimg, "P2\n");
    // Writing width and height of images.
    printf("Image Height[%d]\nImage Width[%d]\n", height, width);
    fprintf(pgmimg, "%d %d\n", height, width);
    // Writing the maximum gray value
    printf("Maximum Gray Value [255]\n");
    fprintf(pgmimg, "255\n");
    for (int i = 0; i < height * width; i++)
    {
        int temp = image[i];
        fprintf(pgmimg, "%d ", temp);
    }
    fclose(pgmimg);
}
