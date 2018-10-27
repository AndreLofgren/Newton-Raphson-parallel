#include "header.h"

/** Numerically calculates the derivative of the function
    pointed to by fun_ptr using central difference. **/
double derive(double (*fun_ptr)(double), double x) {
    const double dx = 1e-6;
    return 1.0/(2.0*dx) * ((*fun_ptr)(x+dx) - (*fun_ptr)(x-dx));
}

/** Finds all zeros in the interval [a, b]. This procedure
    divides the interval [a, b] into N smaller sub intervals and
    then uses Newton-bisection on each of the sub intervalls. **/
array *find_all_zeros_NR(double (*fun_ptr)(double), double a, double b, int N, int T) {
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
        zeros->ptr[i] = find_zero_NR(fun_ptr, xl, xu);
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

/** Finds a zero, using Newton-bisection, in the interval [a, b] of the function
    pointed to by fun_ptr. If no zero is found, the function returns -1.0. **/
double find_zero_NR(double (*fun_ptr)(double), double a, double b) {
    const int max_iter = 50; // maxium number of iterations
    const double tol = 1e-8; // tolerance
    int i = 0; // iteration counter
    double c = a + (b-a)*0.5; // mid-point
    double x_new = c; // x_k+1
    double x_old; // x_k

    /* perform Newton-bisection while |x_k+1 - x_k| > tol, or
       while |b-a| < tol, or the maximum number of iterations
       has not been reached */
    do {
        x_old = x_new;
        x_new = x_old - (*fun_ptr)(x_old)/derive(fun_ptr, x_old);
        if (x_new < a || x_new >= b) { // check if outside the interval
            if ((*fun_ptr)(a) * (*fun_ptr)(c) > 0) { // check sign
                a = c;
            } else {
                b = c;
            }
            c = a + (b-a)*0.5;
            x_old = c;
            x_new = x_old - (*fun_ptr)(x_old)/derive(fun_ptr, x_old);
        }
        i++;
    } while (b-a > tol && fabs(x_new - x_old) > tol && i < max_iter);

    if (fabs(x_new - x_old) <= tol && (x_new >= a && x_new < b)) {
        if (x_new == -1.0) { // add small perturbation if x_new == -1.0
            x_new += 1e-12;
        }
        return x_new;
    } else if (b-a <= tol && (*fun_ptr)(a) * (*fun_ptr)(b) < 0) {
        if (x_new == -1.0) { // add small perturbation if c == -1.0
            c += 1e-12;
        }
        return c;
    } else {
        return -1.0;
    }
}
