#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

void write_to_pgm(int *image, char *image_name, int height, int width);
int *allocate_space(int height, int width);
int *read_from_pgm(char *file_name, int *height, int *width);

int get_bit(int number, int index);
int get_lsb(int number);
void set_bit(int *number, int index, int bit);

int *generate_random_secret(int length);
void generate_layer_one(int *image, int *secret, int height, int width, int *p1_pointer, int *q1_pointer);
void generate_intermediate_two(int *secret, int height, int width, int *p1, int *q1, int *p1_l2, int *p2_l2, int *q1_l2, int *q2_l2);
void generate_second_layer_pair1(int height, int width, int *p1, int *p1_l2, int *q1_l2, int *p1_star, int *q1_star);
void generate_second_layer_pair2(int height, int width, int *q1, int *p2_l2, int *q2_l2, int *p2_star, int *q2_star);
void encode(int *image, char *image_name, int *secret, int height, int width);

void extract_img(int height, int width, int *p1, int *q1, int *p1_star, int *p2_star, int *q1_star, int *q2_star);
void adjust_l1(int height, int width, int *p1_star, int *p2_star, int *q1_star, int *q2_star);
void extract_secret(int *pixel, int height, int width, int *p1, int *q1, int *p1_star, int *p2_star, int *q1_star, int *q2_star);
void decode(int height, int width, char *p1_star_img, char *p2_star_img, char *q1_star_img, char *q2_star_img);