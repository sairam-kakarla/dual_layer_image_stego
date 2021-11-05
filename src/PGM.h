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
void generate_intermediate_two(int *secret, int height, int width, int *p1, int *q1, int *p1_l2, int *p2_l2, int *q1_l2, int *q2_l2);
void generate_second_layer_pair1(int height, int width, int *p1, int *p1_l2, int *q1_l2, int *p1_star, int *q1_star);
void generate_second_layer_pair2(int height, int width, int *q1, int *p2_l2, int *q2_l2, int *p2_star, int *q2_star);