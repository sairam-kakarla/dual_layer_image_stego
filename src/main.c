#include "PGM.h"

void create
int main()
{
    char *fname = "baboon.ascii.pgm";
    int height, width, *image;
    image = read_from_pgm(fname, &height, &width);
    // if (image)
    // {
    //     char *test_fname = "test.pgm";
    //     write_to_pgm(image, "test_fname", height, width);
    // }
    return 0;
}