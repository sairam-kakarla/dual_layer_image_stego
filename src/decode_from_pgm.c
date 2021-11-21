#include "PGM.h"

void extract_img(int height, int width, int *p1, int *q1, int *p1_star, int *p2_star, int *q1_star, int *q2_star)
{
    // Creating the original image.
    int *original_img = (int *)malloc(height * width * sizeof(int));
    if (!original_img)
    {
        printf("ERROR: Memory Allocation of Image Extraction Failed\n");
        exit(1);
    }
#pragma omp parallel for shared(p1_star, q1_star, p2_star, q2_star, original_img, p1, q1) schedule(static, 4)
    for (int i = 0; i < height * width; i++)
    {
        p1[i] = (p1_star[i] + q1_star[i]) / 2;
        q1[i] = (p2_star[i] + q2_star[i]) / 2;
        original_img[i] = (p1[i] + q1[i]) / 2;
    }
    write_to_pgm(original_img, "original.pgm", height, width);
    free(original_img);
}

void adjust_l1(int height, int width, int *p1_star, int *p2_star, int *q1_star, int *q2_star)
{
#pragma omp parallel for shared(p1_star, q1_star, p2_star, q2_star) schedule(static, 4)
    for (int i = 0; i < height * width; i++)
    {
        if (p1_star[i] + 2 == q1_star[i])
        {
            p1_star[i] += 2;
        }
        if (p2_star[i] + 2 == q2_star[i])
        {
            p2_star[i] += 2;
        }
    }
}

void extract_secret(int *pixel, int height, int width, int *p1, int *q1, int *p1_star, int *p2_star, int *q1_star, int *q2_star)
{
#pragma omp parallel for shared(pixel, p1_star, q1_star, p2_star, q2_star, p1, q1) schedule(static, 4)
    for (int i = 0; i < height * width; i++)
    {
        int b1, b2, b3, b4, b5, b6;
        b1 = get_lsb(p1[i]);
        b2 = get_lsb((p1[i] / 2) + q1[i]);
        b3 = get_lsb(p1_star[i]);
        b4 = get_lsb((p1_star[i] / 2) + p2_star[i]);
        b5 = get_lsb(q1_star[i]);
        b6 = get_lsb((q1_star[i] / 2) + q2_star[i]);
        set_bit(&pixel[i], 1, b1);
        set_bit(&pixel[i], 2, b2);
        set_bit(&pixel[i], 3, b3);
        set_bit(&pixel[i], 4, b4);
        set_bit(&pixel[i], 5, b5);
        set_bit(&pixel[i], 6, b6);
    }
}

void decode(int height, int width, char *p1_star_img, char *p2_star_img, char *q1_star_img, char *q2_star_img)
{
    int *p1_star, *p2_star, *q1_star, *q2_star;
    p1_star = allocate_space(height, width);
    p2_star = allocate_space(height, width);
    q1_star = allocate_space(height, width);
    q2_star = allocate_space(height, width);

    p1_star = read_from_pgm(p1_star_img, &height, &width);
    p2_star = read_from_pgm(p2_star_img, &height, &width);
    q1_star = read_from_pgm(q1_star_img, &height, &width);
    q2_star = read_from_pgm(q2_star_img, &height, &width);

    int *p1, *q1;
    p1 = allocate_space(height, width);
    q1 = allocate_space(height, width);
    extract_img(height, width, p1, q1, p1_star, p2_star, q1_star, q2_star);
    adjust_l1(height, width, p1_star, p2_star, q1_star, q2_star);
    int *image = (int *)calloc(height * width, sizeof(int));
    extract_secret(image, height, width, p1, q1, p1_star, p2_star, q1_star, q2_star);
    FILE *secret = fopen("secretE.txt", "w");
    for (int i = 0; i < height * width; i++)
    {
        fprintf(secret, "%d ", image[i]);
        if (i % 100 == 0)
        {
            fprintf(secret, "\n");
        }
    }
    fclose(secret);
    free(p1);
    free(q1);
    free(p1_star);
    free(p2_star);
    free(q1_star);
    free(q2_star);
    free(image);
}