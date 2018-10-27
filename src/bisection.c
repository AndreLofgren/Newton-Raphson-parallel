#include "header.h"

/** Finds a zero, using bisection, in the interval [a, b] of the function
    pointed to by fun_ptr. If no zero is found, the function returns -1.0. **/
double find_zero_bisection(double (*fun_ptr)(double), double a, double b) {
    const int max_iter = 100; // maximum number of iterations
    const double tol = 1e-8; // tolerance
    int i = 0; double c;

    /* perform bisection while the interval length is
       longer than the tolerance, or the maximum number
       of iterations has not been reached. */
    do {
        c = a + (b-a)*0.5; // mid-point
        if ((*fun_ptr)(a) * (*fun_ptr)(c) > 0) { // check sign
            a = c;
        } else {
            b = c;
        }
        i++;
    } while (b-a > tol && i < max_iter);

    /* if sgn(f(a)) == sgn(f(b)), no zero was found */
    if ((*fun_ptr)(a) * (*fun_ptr)(b) > 0) {
        return -1.0;
    }

    return c;
}

/** Finds all zeros in the interval [a, b]. This procedure
    divides the interval [a, b] into N smaller interval and
    then uses bisection on each of the subintervals. **/
array *find_all_zeros_bisection(double (*fun_ptr)(double), double a, double b, int N, int T) {
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
        zeros->ptr[i] = find_zero_bisection(fun_ptr, xl, xu);
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
