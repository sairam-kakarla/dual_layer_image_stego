#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void write_to_pgm(int *image, char *image_name, int height, int width);
int *allocate_space(int height, int width);
int *read_from_pgm(char *file_name, int *height, int *width);
int get_bit(int number, int index);
int get_lsb(int number);
int *generate_random_secret(int length);
void generate_layer_one(int *image, int *secret, int height, int width, int *p1_pointer, int *q1_pointer);