#include "PGM.h"
int *allocate_space(int height, int width)
{
    int *temp;
    temp = (int *)malloc(height * width * sizeof(int));
    return temp;
}
int *read_from_pgm(char *file_name, int *height, int *width)
{
    FILE *pgmimage;
    pgmimage = fopen(file_name, "r");
    if (!pgmimage)
    {
        printf("ERROR: Unable to read file %s\n", file_name);
        exit(1);
    }
    char *metadata_buffer;
    printf("Reading PGM File.\n");
    fscanf(pgmimage, "%s", metadata_buffer);
    if (strcmp(metadata_buffer, "P2") == 0)
    {
        printf("File Format [%s]\n", metadata_buffer);
    }
    else
    {
        printf("Error: Expected Portable Graymap ASCII[P2] file");
        exit(1);
    }
    fscanf(pgmimage, "%d %d", height, width);
    printf("Image Height:[%d]\n", *height);
    printf("Image Width:[%d]\n", *width);
    int h, w;
    h = *height;
    w = *width;
    int *image_array = allocate_space(h, w);
    if (!image_array)
    {
        printf("Insufficient Memory\n");
        exit(1);
    }
    int max_grey_value;
    fscanf(pgmimage, "%d", &max_grey_value);
    printf("Maximum Grey Value:[%d]\n", max_grey_value);
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int temp;
            fscanf(pgmimage, "%d", &temp);
            image_array[i * w + j] = temp;
        }
    }
    printf("\n");
    fclose(pgmimage);
    return image_array;
}
// int main()
// {
//     char *file_name = "baboon.ascii.pgm";
//     int height, width;
//     int *image_array;
//     image_array = NULL;
//     image_array = read_from_pgm(file_name, &height, &width);
//     if (!image_array)
//     {
//         printf("Image read unsuccessfully\n");
//     }
//     print(image_array);
//     printf("\n");
//     return 0;
// }