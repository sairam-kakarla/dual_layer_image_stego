#include "PGM.h"
#include <string.h>
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
            if (get_lsb(((int)(image[i] / 2)) + image[i]) == get_bit(secret[i], 2))
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
            if (get_lsb(((int)((image[i] - 1) / 2)) + image[i]) == get_bit(secret[i], 2))
            {
                q1[i] = p1[i] - 1;
            }
            else
            {
                q1[i] = p1[i];
            }
        }
    }
}
void generate_intermediate_two(int *secret, int height, int width, int *p1, int *q1, int *p1_l2, int *p2_l2, int *q1_l2, int *q2_l2)
{
    if (!q1_l2 | !q2_l2 | !p1_l2 | !p2_l2)
    {
        printf("ERROR: Memory Allocation for intermediate layer failed\n");
        exit(1);
    }
    for (int i = 0; i < height * width; i++)
    {
        //Generating p1' and p2'
        if (get_lsb(p1[i]) == get_bit(secret[i], 3))
        {
            p1_l2[i] = p1[i];
            if (get_lsb(p1[i] / 2 + q1[i]) == get_bit(secret[i], 4))
            {
                p2_l2[i] = q1[i];
            }
            else
            {
                p2_l2[i] = q1[i] + 1;
            }
        }
        else
        {
            p1_l2[i] = p1[i] + 1;
            if (get_lsb((p1[i] - 1) / 2 + q1[i]) == get_bit(secret[i], 4))
            {
                p2_l2[i] = q1[i] - 1;
            }
            else
            {
                p2_l2[i] = q1[i];
            }
        }
        // Generating q1' and q2'
        if (get_lsb(p1[i]) == get_bit(secret[i], 5))
        {
            q1_l2[i] = p1[i];
            if (get_lsb(p1[i] / 2 + q1[i]) == get_bit(secret[i], 6))
            {
                q2_l2[i] = q1[i];
            }
            else
            {
                q2_l2[i] = q1[i] + 1;
            }
        }
        else
        {
            q1_l2[i] = p1[i] + 1;
            if (get_lsb((p1[i] - 1) / 2 + q1[i]) == get_bit(secret[i], 6))
            {
                q2_l2[i] = q1[i] - 1;
            }
            else
            {
                q2_l2[i] = q1[i];
            }
        }
    }
}

void generate_second_layer_pair1(int height, int width, int *p1, int *p1_l2, int *q1_l2, int *p1_star, int *q1_star)
{
    if (!p1_star | !q1_star)
    {
        printf("ERROR: Memory Allocation for Final State Failed\n");
        exit(1);
    }
    for (int i = 0; i < height * width; i++)
    {
        if ((2 * p1[i] + 2) == p1_l2[i] + q1_l2[i])
        {
            p1_star[i] = p1_l2[i] - 2;
            q1_star[i] = q1_l2[i];
        }
        else
        {
            p1_star[i] = p1_l2[i];
            q1_star[i] = q1_l2[i];
        }
    }
}

void generate_second_layer_pair2(int height, int width, int *q1, int *p2_l2, int *q2_l2, int *p2_star, int *q2_star)
{
    if (!p2_star | !q2_star)
    {
        printf("ERROR: Memory Allocation for Final State Failed\n");
        exit(1);
    }
    for (int i = 0; i < height * width; i++)
    {
        if ((2 * q1[i]) > (p2_l2[i] + q2_l2[i]) && p2_l2[i] >= q2_l2[i])
        {
            q2_star[i] = q2_l2[i] + 2;
            p2_star[i] = p2_l2[i] + 2;
        }
        else if ((2 * q1[i] + 2) == p2_l2[i] + q2_l2[i])
        {
            p2_star[i] = p2_l2[i] - 2;
            q2_star[i] = q2_l2[i];
        }
        else
        {
            p2_star[i] = p2_l2[i];
            q2_star[i] = q2_l2[i];
        }
    }
}
void encode(int *image, char *image_name, int *secret, int height, int width)
{
    int *p1, *q1;
    p1 = allocate_space(height, width);
    q1 = allocate_space(height, width);
    // Layer One Generation.
    generate_layer_one(image, secret, height, width, p1, q1);
    printf("\nGeneration of layer one sucessfull\n");
    int *p1_l2, *p2_l2, *q1_l2, *q2_l2;
    p1_l2 = allocate_space(height, width);
    q1_l2 = allocate_space(height, width);
    p2_l2 = allocate_space(height, width);
    q2_l2 = allocate_space(height, width);
    // Intermediate pixel generation
    generate_intermediate_two(secret, height, width, p1, q1, p1_l2, p2_l2, q1_l2, q2_l2);
    printf("\nGeneration of intermediate pixels sucessfull\n");
    int *p1_star, *p2_star, *q1_star, *q2_star;
    // Layer two generation.
    // First pair(p1*,p2*);
    p1_star = allocate_space(height, width);
    p2_star = allocate_space(height, width);
    q1_star = allocate_space(height, width);
    q2_star = allocate_space(height, width);
    generate_second_layer_pair1(height, width, p1, p1_l2, q1_l2, p1_star, q1_star);
    generate_second_layer_pair2(height, width, q1, p2_l2, q2_l2, p2_star, q2_star);
    printf("\nGeneration of layer two sucessfull\n");
    // File creation.
    char pStarOne[200] = "P1*_";
    char pStarTwo[200] = "P2*_";
    char qStarOne[200] = "Q1*_";
    char qStarTwo[200] = "Q2*_";
    write_to_pgm(p1_star, strcat(pStarOne, image_name), height, width);
    write_to_pgm(q1_star, strcat(qStarOne, image_name), height, width);
    write_to_pgm(p2_star, strcat(pStarTwo, image_name), height, width);
    write_to_pgm(q2_star, strcat(qStarTwo, image_name), height, width);
    printf("\nInformation encoding succesfull\n");
    // Clean memory allocated to pixels.
    free(p1);
    free(q1);
    free(p1_l2);
    free(p2_l2);
    free(q1_l2);
    free(q2_l2);
    free(p1_star);
    free(p2_star);
    free(q1_star);
    free(q2_star);
}