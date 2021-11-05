#include "PGM.h"
/*Refer Research paper:[https://sci-hub.ee/10.1007/s11220-019-0262-y]
  for formulation of layers.*/
void generate_layer_one(int *image, int *secret, int height, int width, int *p1, int *q1)
{
    if (!(p1) | !(q1))
    {
        printf("ERROR: Memory Allocation for first layer failed\n.");
        exit(1);
    }
    for (int i = 0; i < height * width; i++)
    {
        // Generation of p1 in layer 1.
        if (get_lsb(image[i]) == get_bit(secret[i], 1))
        {
            p1[i] = image[i];
            // Generation of q1 in layer 1.
            if (get_lsb((image[i] / 2) + image[i]) == get_bit(secret[i], 2))
            {
                q1[i] = p1[i];
            }
            else
            {
                q1[i] = p1[i] + 1;
            }
        }
        else
        {
            p1[i] = image[i] + 1;
            if (get_lsb(((image[i] - 1) / 2) + image[i]) == get_bit(secret[i], 2))
            {
                q1[i] = p1[i] - 1;
            }
            else
            {
                q1[i] = p1[i];
            }
        }
    }
    printf("Layer 1 Generation Successfull\n");
}
