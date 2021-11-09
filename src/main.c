#include "PGM.h"

int main()
{
    char *fname = "columns.ascii.pgm";
    int height, width, *image;
    image = read_from_pgm(fname, &height, &width);
    int *sd = generate_random_secret(height * width);
    encode(image, fname, sd, height, width);
    free(image);
    free(sd);
    return 0;
}