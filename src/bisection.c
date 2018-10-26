#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

typedef struct array {
    double *ptr;
    int size;
} array;

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

/** Finds a zero, using bisection, in the interval [a, b] of the function
    pointed to by fun_ptr. If no zero is found, the function returns -1.0. **/
double find_zero(double (*fun_ptr)(double), double a, double b) {
    const int max_iter = 100; // maximum number of iterations
    const double tol = 1e-8; // tolerance
    double b_old = b;

    if (b <= a)  {
        fprintf(stderr, "error: a > b\n");
        return -1.0;
    }

    int i = 0; double c;
    /* perform bisection while the interval length is
       longer than the tolerance, or the maximum number
       of iterations has not been reached. */
    do {
        c = a + (b-a)/2.0; // mid-point
        if ((*fun_ptr)(a) * (*fun_ptr)(c) > 0) { // check sign
            a = c;
        } else {
            b = c;
        }
        i++;
    } while (b-a > tol && i < max_iter);

    /* if the b valuse didn't change, no zero was found. */
    if (b == b_old) {
        return -1.0;
    }

    return c;
}

/** Finds all zeros in the interval [a, b]. This procedure
    divides the interval [a, b] into N smaller interval and
    then uses bisection on each of the sub intervalls. **/
array *find_all_zeros(double (*fun_ptr)(double), double a, double b, int N, int T) {
    array *zeros = malloc(sizeof(array));
    zeros->ptr = malloc(N*sizeof(double));
    zeros->size = 0;
    double dn = (b-a)/((double) N);
    double xl, xu;

    int chunk = ceil(N/(double)T);
#pragma omp parallel for num_threads(T) schedule(static, chunk) private(xl, xu)
    for (int i = 0; i < N; i++) {
        xl = a + dn*i;
        xu = a + dn*(i+1);
        zeros->ptr[i] = find_zero(fun_ptr, xl, xu);
    }

    /* collect the found zeros */
    for (int i = 0; i < N; i++) {
        if (zeros->ptr[i] != -1) {
            zeros->ptr[zeros->size] = zeros->ptr[i];
            zeros->size++;
        }
    }
    zeros->ptr = realloc(zeros->ptr, zeros->size*sizeof(double));
    return zeros;
}

int main(int argc, char *argv[]) {
    double T;
    if (argc < 5) {
        fprintf(stderr, "usage: ./exec a b N T\n");
        exit(EXIT_FAILURE);
    } else if (atoi(argv[4]) < 1) {
        fprintf(stderr, "error: T < 1");
        exit(EXIT_FAILURE);
    } else {
        T = atoi(argv[4]);
    }

    double a = atof(argv[1]);
    double b = atof(argv[2]);
    double N = atof(argv[3]);

    double wall_time = timer();
    array *zeros = find_all_zeros(j1, a, b, N, T);
    wall_time = timer() - wall_time;

    printf("found %d zeros in %1.6lf s\n", zeros->size, wall_time);

    freeArray(zeros);
    return 0;
}
