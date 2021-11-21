#include "PGM.h"
int main()
{
    char *fname = "columns.ascii.pgm";
    int height, width, *image;
    image = read_from_pgm(fname, &height, &width);
    float startT, endT;
    int *sd = generate_random_secret(height * width);
    int bench_mark_Thread[11] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    float bench_markTime[11];
    for (int i = 0; i < 11; i++)
    {
        omp_set_num_threads(bench_mark_Thread[i]);
        printf("%d\n", omp_get_num_threads());
        startT = omp_get_wtime();
        decode(height, width, "P1*_columns.ascii.pgm", "P2*_columns.ascii.pgm", "Q1*_columns.ascii.pgm", "Q2*_columns.ascii.pgm");
        endT = omp_get_wtime();
        bench_markTime[i] = endT - startT;
    }
    for (int i = 0; i < 11; i++)
        printf("Number of Thread:[%d]       Execution Time:[%.4f]\n", bench_mark_Thread[i], bench_markTime[i] * 1000);

    free(image);
    free(sd);
    return 0;
}