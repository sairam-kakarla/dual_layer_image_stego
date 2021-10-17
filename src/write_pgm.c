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
    // Writing Magic Number P2 to represent PGM Images.
    fprintf(pgmimg, "P2\n");
    // Writing width and height of images.
    fprintf(pgmimg, "%d %d\n", width, height);
    // Writing the maximum gray value
    fprintf(pgmimg, "255\n");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int temp = *((image + i * width) + j);
            fprintf(pgmimg, "%d ", temp);
        }
        fprintf(pgmimg, "\n");
    }
    fclose(pgmimg);
}

// int main()
// {
//     int image[13][13] = {
//         {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15},
//         {31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31},
//         {47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47},
//         {63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
//         {79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79},
//         {95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95},
//         {111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111},
//         {127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127},
//         {143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143},
//         {159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159},
//         {175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175},
//         {191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191},
//         {207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207}};
//     char *filename = "test.pgm";
//     int height, width;
//     height = 13;
//     width = 13;
//     write_to_pgm((int *)image, "test.pgm", height, width);
//     return 0;
// }