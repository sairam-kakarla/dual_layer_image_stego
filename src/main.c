#include "PGM.h"

int main()
{
    char *fname = "baboon.ascii.pgm";
    int height, width, *image;
    image = read_from_pgm(fname, &height, &width);
    int *p1, *q1;
    printf("s1 ok\n");
    int *sd = generate_random_secret(height * width);
    printf("s2 ok\n");
    p1 = allocate_space(height, width);
    q1 = allocate_space(height, width);
    generate_layer_one(image, sd, height, width, p1, q1);
    printf("s3 ok\n");
    write_to_pgm(p1, "p1_image.pgm", height, width);
    write_to_pgm(q1, "q1_image.pgm", height, width);
    printf("s3 ok\n");
    free(image);
    free(sd);
    free(p1);
    free(q1);
    return 0;
}