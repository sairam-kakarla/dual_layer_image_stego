#include "PGM.h"

int main()
{
    char *fname = "baboon.ascii.pgm";
    char *tname = "test.pgm";
    int height, width, *image;
    image = read_from_pgm(fname, &height, &width);
    write_to_pgm(image, tname, height, width);
    return 0;
}