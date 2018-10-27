#include "header.h"

double timer() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

void freeArray(array *A) {
    free(A->ptr);
    free(A);
}

int main(int argc, char *argv[]) {
    double T;
    if (argc < 5) {
        fprintf(stderr, "usage: ./exec a b N T\n");
        exit(EXIT_FAILURE);
    } else if (atoi(argv[4]) < 1) {
        fprintf(stderr, "error: T < 1\n");
        exit(EXIT_FAILURE);
    } else {
        T = atoi(argv[4]);
    }

    double a = atof(argv[1]);
    double b = atof(argv[2]);
    double N = atof(argv[3]);

    array *zeros;

    double wall_time = timer();
    zeros = find_all_zeros_NR(j1, a, b, N, T); // find zeros of bessel function j1
    wall_time = timer() - wall_time;

    printf("Newton-bisection ");
    printf("found %d zeros in %1.6lf s\n", zeros->size, wall_time);

    char correct = 1;
    for (int i = 0; i < zeros->size; i++) {
        if (fabs(j1(zeros->ptr[i])) > 1e-6) {
            correct = 0;
            break;
        }
    }

    if (correct) {
        printf("all zeros, z0, pased the test |fun(z0)| < 1e-6\n");
    } else {
        printf("atleast one zero, z0, failed the test |fun(z0)| < 1e-6\n");
    }

    freeArray(zeros);

    wall_time = timer();
    zeros = find_all_zeros_bisection(j1, a, b, N, T); // find zeros of bessel function j1
    wall_time = timer() - wall_time;

    printf("\nBisection ");
    printf("found %d zeros in %1.6lf s\n", zeros->size, wall_time);

    correct = 1;
    for (int i = 0; i < zeros->size; i++) {
        if (fabs(j1(zeros->ptr[i])) > 1e-6) {
            correct = 0;
            break;
        }
    }

    if (correct) {
        printf("all zeros, z0, passed the test |fun(z0)| < 1e-6\n");
    } else {
        printf("atleast one zero, z0, failed the test |fun(z0)| < 1e-6\n");
    }

    freeArray(zeros);
    return 0;
}
