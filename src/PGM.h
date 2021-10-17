#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void write_to_pgm(int *image, char *image_name, int height, int width);
int *allocate_space(int height, int width);
int *read_from_pgm(char *file_name, int *height, int *width);