#include "PGM.h"
int *allocate_space(int height, int width)
{
    /*
    Function to allocate space for the image in memory.
    Params: height [int - height of images]
            width [int - height of images],
    Return Value: pointer the alllocated block of memory*/
    int *temp;
    temp = (int *)malloc(height * width * sizeof(int));
    return temp;
}
int *read_from_pgm(char *file_name, int *height, int *width)
{
    /*
    Function to read the grayscale values from a pgm file and store in a continous memory.
    Updates the height,width;
    Params: filename [char pointer - to file name]
            hight [int pointer - to image height]
            width [int pointer - to image width]
    Return Value: pointer the memory block containing the grayscale values*/
    FILE *pgmimage;
    pgmimage = fopen(file_name, "r");
    if (!pgmimage)
    {
        printf("ERROR: Unable to read file %s\n", file_name);
        exit(1);
    }
    char metadata_buffer[100];
    printf("----------------------------------------------\n");
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
    fclose(pgmimage);
    return image_array;
}
